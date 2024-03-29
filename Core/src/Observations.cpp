#include "Observations.h"
#include "Image.h"

#include <fstream>
#include <fmt/format.h>

using namespace nlohmann;

namespace AsteroidFarm {

std::vector<float> RadarImage::ConstructDelayDoppler(std::vector<float> &radialVelBuffer,
                                                     std::vector<float> &surfaceScatteringBuffer,
                                                     std::vector<float> &depthBuffer,
                                                     int delayDopplerWidth,
                                                     int delayDopplerHeight)
{
    auto maxRadialVel = *std::max_element(radialVelBuffer.begin(), radialVelBuffer.end());
    auto minRadialVel = *std::min_element(radialVelBuffer.begin(), radialVelBuffer.end());

    auto maxDepth = *std::max_element(depthBuffer.begin(), depthBuffer.end());

    // TODO while calculating min/max of buffers, take the background into account, e.g.:
    // * special value for each/one buffer
    // * compare values between buffers
    // * ...
    auto minDepth{maxDepth};
    for (auto depthPixel : depthBuffer)
    {
        if (depthPixel < minDepth && depthPixel != 0.)
        {
            minDepth = depthPixel;
        }
    }

    std::vector<float> delayDopplerImage(delayDopplerWidth * delayDopplerHeight, 0.0);

    for (int i = 0; i < radialVelBuffer.size(); i++)
    {
        if (depthBuffer[i] == 0.)  // background
        {
            continue;
        }

        int vr = floor(delayDopplerWidth * (radialVelBuffer[i] - minRadialVel) /
                       (maxRadialVel - minRadialVel));
        int d = floor(delayDopplerHeight * (depthBuffer[i] - minDepth) / (maxDepth - minDepth));

        if (d < 0 || d >= delayDopplerHeight || vr < 0 || vr >= delayDopplerWidth)
        {
            continue;
        }

        delayDopplerImage[d * delayDopplerWidth + vr] += surfaceScatteringBuffer[i];
    }

    // TODO normalization of values is not that trivial. It has to relate to physics of radar.
    // auto maxVal = *std::max_element(delayDopplerImage.begin(), delayDopplerImage.end());
    // std::for_each(delayDopplerImage.begin(),
    //               delayDopplerImage.end(),
    //               [&maxVal](float &pixel) { pixel /= maxVal; });

    return delayDopplerImage;
}

void RadarImage::exportDelayDoppler(std::filesystem::path filePath, int imageWidth, int imageHeight)
{
    auto delayDoppler = ConstructDelayDoppler(
        radialVelocityBuffer, surfaceScatteringBuffer, depthBuffer, imageWidth, imageHeight);

    Image::SavePng(filePath, imageWidth, imageHeight, delayDoppler, true);
}

void from_json(const json &j, ObsPoint &p)
{
    p.julianDay = j.at("julianDay").get<JulianDay>();
    p.magnitude = j.at("magnitude").get<Magnitude>();
    p.rotPhase = j.at("rotPhase").get<Angle<Units::Radian>>();
    p.step = j.at("step").get<unsigned int>();
    p.observerPosition = j.at("observerPosition").get<glm::vec3>();
    p.targetPosition = j.at("targetPosition").get<glm::vec3>();
}

void from_json(const json &j, LightcurveStorage &obs)
{
    obs.sceneConfig = j.at("scene").get<SceneConfig>();
    obs.asteroidParams = j.at("asteroidParams").get<AsteroidParams>();
    obs.lightcurves = j.at("lightcurves").get<std::vector<Lightcurve>>();
}

void to_json(json &j, const ObsPoint &p)
{
    j = {{"julianDay", p.julianDay},
         {"magnitude", p.magnitude},
         {"rotPhase", p.rotPhase},
         {"step", p.step},
         {"observerPosition", p.observerPosition},
         {"targetPosition", p.targetPosition}};
}

void to_json(json &j, const LightcurveStorage &obs)
{
    j = {{"scene", obs.sceneConfig},
         {"asteroidParams", obs.asteroidParams},
         {"lightcurves", obs.lightcurves}};
}

void to_json(nlohmann::json &j, const RadarStorage &rs)
{
    j = {{"sceneConfig", rs.sceneConfig}, {"asteroidParams", rs.asteroidParams}};
}

void from_json(const nlohmann::json &j, RadarStorage &rs) {}

void from_json(const nlohmann::json &j, RadarImage &r) {}

void to_json(nlohmann::json &j, const RadarImage &r)
{
    j = {{"radialVelocityBuffer", r.radialVelocityBuffer},
         {"surfaceScatteringBuffer", r.surfaceScatteringBuffer},
         {"depthBuffer", r.depthBuffer}};
}

void RadarImage::SaveToBinary(const std::vector<RadarImage> &images, std::filesystem::path filePath)
{
    if (images.empty())
    {
        return;
    }

    auto file = std::ofstream(filePath, std::ofstream::binary);

    size_t numImages = images.size();
    file.write(reinterpret_cast<char *>(&numImages), sizeof(numImages));

    size_t bufferSize = images[0].radialVelocityBuffer.size();
    file.write(reinterpret_cast<char *>(&bufferSize), sizeof(bufferSize));

    for (const auto &image : images)
    {
        file.write(reinterpret_cast<const char *>(&image.radialVelocityBuffer[0]),
                   image.radialVelocityBuffer.size() * sizeof(float));
        file.write(reinterpret_cast<const char *>(&image.surfaceScatteringBuffer[0]),
                   image.surfaceScatteringBuffer.size() * sizeof(float));
        file.write(reinterpret_cast<const char *>(&image.depthBuffer[0]),
                   image.depthBuffer.size() * sizeof(float));
    }
}
std::vector<RadarImage> RadarImage::LoadFromBinary(std::filesystem::path filePath)
{
    auto file = std::ifstream(filePath, std::ifstream::binary);
    if (not file.is_open())
    {
        fmt::print("Could not open file {}.\n", filePath.string());
        return {};
    }

    size_t numImages{0};
    file.read(reinterpret_cast<char *>(&numImages), sizeof(numImages));

    size_t bufferSize{0};
    file.read(reinterpret_cast<char *>(&bufferSize), sizeof(bufferSize));

    std::vector<RadarImage> images;
    for (auto i = 0; i < numImages; i++)
    {
        auto &image = images.emplace_back();
        image.radialVelocityBuffer.resize(bufferSize);
        image.surfaceScatteringBuffer.resize(bufferSize);
        image.depthBuffer.resize(bufferSize);

        file.read(reinterpret_cast<char *>(&image.radialVelocityBuffer[0]),
                  image.radialVelocityBuffer.size() * sizeof(float));
        file.read(reinterpret_cast<char *>(&image.surfaceScatteringBuffer[0]),
                  image.surfaceScatteringBuffer.size() * sizeof(float));
        file.read(reinterpret_cast<char *>(&image.depthBuffer[0]),
                  image.depthBuffer.size() * sizeof(float));
    }
    return images;
}
}  // namespace AsteroidFarm
