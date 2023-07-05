#include "RadarScene.h"
#include "Image.h"

#include <algorithm>

namespace AsteroidFarm {

RadarScene::RadarScene(Renderer &renderer,
                       glm::uvec2 framebufferSize,
                       const RadarSeriesConfig &config)
    : PhotometryScene(renderer, framebufferSize, config)
{
    storage.asteroidParams = _config.asteroidParams;
    storage.sceneConfig = _config.scene;
}

void RadarScene::render()
{
    auto asteroidParams = _config.asteroidParams;

    for (const auto &radarImageConfig : _config.radarImages)
    {
        updatePositions(radarImageConfig.jd,
                        asteroidParams,
                        radarImageConfig.targetPosition,
                        radarImageConfig.observerPosition,
                        radarImageConfig.observerPosition);

        renderSceneWithShadows();
        storeImage();
    }
}

void RadarScene::storeImage()
{
    const auto width = _framebuffer.specification.width;
    const auto height = _framebuffer.specification.height;

    std::vector<float> radialVelocityBuffer(width * height);
    std::vector<float> surfaceScatteringBuffer(width * height);
    std::vector<float> depthBuffer(width * height);

    glReadPixels(0, 0, width, height, GL_RED, GL_FLOAT, radialVelocityBuffer.data());
    glReadPixels(0, 0, width, height, GL_GREEN, GL_FLOAT, surfaceScatteringBuffer.data());
    glReadPixels(0, 0, width, height, GL_BLUE, GL_FLOAT, depthBuffer.data());

    storage.images.push_back({radialVelocityBuffer, surfaceScatteringBuffer, depthBuffer});
}


}  // namespace AsteroidFarm
