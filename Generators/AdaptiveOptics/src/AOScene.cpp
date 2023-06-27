#include "AOScene.h"

namespace Sage {

AOScene::AOScene(Renderer &renderer, glm::uvec2 framebufferSize, const AOSeriesConfig &config)
    : PhotometryScene(renderer, framebufferSize, config)
{}

void AOScene::render()
{
    _renderer.bgColor = glm::vec4(1., 0., 0., 1.0);
    auto asteroidParams = _config.asteroidParams;

    for (const auto &aoImageConfig : _config.aoImages)
    {
        _framebuffer.resize(aoImageConfig.resolution, aoImageConfig.resolution);

        const auto fbWidth = _framebuffer.specification.width;
        const auto fbHeight = _framebuffer.specification.height;
        std::vector<float> pixelBuffRed(fbWidth * fbHeight);
        std::vector<float> pixelBuffGreen(fbWidth * fbHeight);
        std::vector<float> pixelBuffBlue(fbWidth * fbHeight);

        asteroidParams.setRotPhase(aoImageConfig.jd);

        auto &t = asteroid.getComponent<TransformComponent>();
        auto &vao = asteroid.getComponent<VaoComponent>().vao;
        t.position = aoImageConfig.targetPosition;

        // TODO move this to PhotometryScene
        double distanceObserverToTarget =
            glm::length(aoImageConfig.targetPosition - aoImageConfig.observerPosition);
        double distanceLightToTarget =
            glm::length(aoImageConfig.targetPosition - aoImageConfig.lightPosition);

        _camera = OrthographicCamera(_modelRadius * 2,
                                     1.0,
                                     distanceObserverToTarget - _modelRadius,
                                     distanceObserverToTarget + _modelRadius);
        _camera.position = aoImageConfig.observerPosition;
        _camera.updateTarget(t.position);

        _light = OrthographicCamera(_modelRadius * 2.,
                                    1.0,
                                    distanceLightToTarget - _modelRadius,
                                    distanceLightToTarget + _modelRadius);
        _light.position = aoImageConfig.lightPosition;
        _light.updateTarget(t.position);
        //// TODO ^^^

        t.rotation = asteroidParams.computeXyzRotation();

        renderSceneWithShadows();

        glReadPixels(0, 0, fbWidth, fbHeight, GL_RED, GL_FLOAT, pixelBuffRed.data());
        glReadPixels(0, 0, fbWidth, fbHeight, GL_GREEN, GL_FLOAT, pixelBuffGreen.data());
        glReadPixels(0, 0, fbWidth, fbHeight, GL_BLUE, GL_FLOAT, pixelBuffBlue.data());
    }
}

}  // namespace Sage
