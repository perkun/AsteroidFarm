#include "AOScene.h"
#include "Image.h"

namespace AsteroidFarm {

AOScene::AOScene(Renderer &renderer, glm::uvec2 framebufferSize, const AOSeriesConfig &config)
    : PhotometryScene(renderer, framebufferSize, config)
{}

void AOScene::render()
{
    auto asteroidParams = _config.asteroidParams;

    int idx = 0;
    for (const auto &aoImageConfig : _config.aoImages)
    {
        _framebuffer.resize(aoImageConfig.resolution, aoImageConfig.resolution);

        updatePositions(aoImageConfig.jd,
                        asteroidParams,
                        aoImageConfig.targetPosition,
                        aoImageConfig.observerPosition,
                        aoImageConfig.lightPosition);

        renderSceneWithShadows();

        saveImage(idx++, _framebuffer.specification.width, _framebuffer.specification.height);
    }
}

void AOScene::saveImage(int idx, unsigned int width, unsigned int height)
{
    std::vector<float> pixelBuffRed(width * height);
    std::vector<float> pixelBuffGreen(width * height);
    std::vector<float> pixelBuffBlue(width * height);
    std::vector<float> pixelBuffAlpha(width * height);
    glReadPixels(0, 0, width, height, GL_RED, GL_FLOAT, pixelBuffRed.data());
    glReadPixels(0, 0, width, height, GL_GREEN, GL_FLOAT, pixelBuffGreen.data());
    glReadPixels(0, 0, width, height, GL_BLUE, GL_FLOAT, pixelBuffBlue.data());
    glReadPixels(0, 0, width, height, GL_ALPHA, GL_FLOAT, pixelBuffAlpha.data());

    auto filename = fmt::format("{}_{}.png", _config.imagePrefix, idx);
    auto filePath = _config.outputFolderPath / filename;
    Image::SavePng(
        filePath, width, height, pixelBuffRed, pixelBuffGreen, pixelBuffBlue, pixelBuffAlpha);
}

}  // namespace AsteroidFarm
