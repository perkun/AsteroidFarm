#include "RadarScene.h"
#include "Image.h"

#include <algorithm>

namespace AsteroidFarm {

RadarScene::RadarScene(Renderer &renderer,
                       glm::uvec2 framebufferSize,
                       const RadarSeriesConfig &config)
    : PhotometryScene(renderer, framebufferSize, config)
{}

void RadarScene::render()
{
    auto asteroidParams = _config.asteroidParams;

    int idx = 0;
    for (const auto &radarImageConfig : _config.radarImages)
    {
        updatePositions(radarImageConfig.jd,
                        asteroidParams,
                        radarImageConfig.targetPosition,
                        radarImageConfig.observerPosition,
                        radarImageConfig.observerPosition);

        renderSceneWithShadows();
        saveImage(idx++, radarImageConfig.imageSize, radarImageConfig.imageSize);
    }
}

void RadarScene::saveImage(int idx, unsigned int imageWidth, unsigned int imageHeight)
{
    std::vector<float> pixelBuffVelocity(_framebuffer.specification.width *
                                         _framebuffer.specification.height);
    std::vector<float> pixelBuffScattering(_framebuffer.specification.width *
                                           _framebuffer.specification.height);
    std::vector<float> pixelBuffDepth(_framebuffer.specification.width *
                                      _framebuffer.specification.height);
    glReadPixels(0,
                 0,
                 _framebuffer.specification.width,
                 _framebuffer.specification.height,
                 GL_RED,
                 GL_FLOAT,
                 pixelBuffVelocity.data());
    glReadPixels(0,
                 0,
                 _framebuffer.specification.width,
                 _framebuffer.specification.height,
                 GL_GREEN,
                 GL_FLOAT,
                 pixelBuffScattering.data());
    glReadPixels(0,
                 0,
                 _framebuffer.specification.width,
                 _framebuffer.specification.height,
                 GL_BLUE,
                 GL_FLOAT,
                 pixelBuffDepth.data());

    auto delayDoppler = constructDelayDoppler(
        pixelBuffVelocity, pixelBuffScattering, pixelBuffDepth, imageWidth, imageHeight);

    auto filename = fmt::format("{}_{}.png", _config.imagePrefix, idx);
    auto filePath = _config.outputFolderPath / filename;
    Image::SavePng(filePath, imageWidth, imageHeight, delayDoppler, true);
}

std::vector<float> RadarScene::constructDelayDoppler(std::vector<float> &radialVelBuffer,
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

}  // namespace AsteroidFarm
