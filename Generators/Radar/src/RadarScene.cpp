#include "RadarScene.h"
#include "Image.h"

#include <algorithm>

namespace Sage {

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
        _framebuffer.resize(radarImageConfig.resolution, radarImageConfig.resolution);

        updatePositions(radarImageConfig.jd,
                        asteroidParams,
                        radarImageConfig.targetPosition,
                        radarImageConfig.observerPosition,
                        radarImageConfig.observerPosition);

        renderSceneWithShadows();
        saveImage(idx++, _framebuffer.specification.width, _framebuffer.specification.height);
    }
}

void RadarScene::saveImage(int idx, unsigned int width, unsigned int height)
{
    std::vector<float> pixelBuffVelocity(width * height);
    std::vector<float> pixelBuffNormals(width * height);
    std::vector<float> pixelBuffDepth(width * height);
    glReadPixels(0, 0, width, height, GL_RED, GL_FLOAT, pixelBuffVelocity.data());
    glReadPixels(0, 0, width, height, GL_GREEN, GL_FLOAT, pixelBuffNormals.data());
    glReadPixels(0, 0, width, height, GL_BLUE, GL_FLOAT, pixelBuffDepth.data());

    auto delayDoppler = constructDelayDoppler(pixelBuffVelocity, pixelBuffDepth, pixelBuffNormals, width, height);

    auto filename = fmt::format("{}_{}.png", _config.imagePrefix, idx);
    auto filePath = _config.outputFolderPath / filename;
    Image::SavePng(filePath, width, height, delayDoppler);
}

std::vector<float> RadarScene::constructDelayDoppler(std::vector<float> &radial_vel_buffer,
                                       std::vector<float> &depth_buffer,
                                       std::vector<float> &normal_buffer,
                                       int buffer_width,
                                       int buffer_height)
{
    auto max_vr = *std::max_element(radial_vel_buffer.begin(), radial_vel_buffer.end());
    auto min_vr = *std::min_element(radial_vel_buffer.begin(), radial_vel_buffer.end());

    auto max_depth = *std::max_element(depth_buffer.begin(), depth_buffer.end());
    auto min_depth = *std::min_element(depth_buffer.begin(), depth_buffer.end());

    int delay_dopler_width = buffer_width;
    int delay_dopler_height = buffer_height;

    std::vector<float> delay_doppler(delay_dopler_width * delay_dopler_height, 0.0);

    for (int i = 0; i < buffer_width * buffer_height; i++)
    {
        if (depth_buffer[i] == 0.)  // background
        {
            continue;
        }

        int vr = floor(delay_dopler_width * (radial_vel_buffer[i] - min_vr) / (max_vr - min_vr));
        int d =
            floor(delay_dopler_height * (depth_buffer[i] - min_depth) / (max_depth - min_depth));

        // 		if (i == 200*400 + 170)
        // 			TRACE("vr, d: {}, {}", vr, d);

        if (d < 0 || d >= delay_dopler_height)
            continue;
        if (vr < 0 || vr >= delay_dopler_width)
            continue;

        delay_doppler[d * delay_dopler_width + vr] += normal_buffer[i];
    }

    // normalize delay_doppler
    float dd_max = delay_doppler[0];
    for (int i = 0; i < delay_dopler_width * delay_dopler_height; i++)
        if (delay_doppler[i] > dd_max)
            dd_max = delay_doppler[i];
    for (int i = 0; i < delay_dopler_width * delay_dopler_height; i++)
        delay_doppler[i] /= dd_max;

    return delay_doppler;
}

}  // namespace Sage
