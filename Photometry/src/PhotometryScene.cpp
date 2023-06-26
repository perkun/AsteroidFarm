#include "PhotometryScene.h"

namespace Sage {

PhotometryScene::PhotometryScene(Renderer &renderer,
                                 glm::uvec2 framebufferSize,
                                 const LightcurveSeriesConfig &config)
    : Scene(renderer),
      _config(config),
      _framebuffer({.width = framebufferSize.x,
                    .height = framebufferSize.y,
                    .samples = 1,
                    .attachments = {FramebufferTextureFormat::RGBA32F,
                                    FramebufferTextureFormat::DEPTH32FSTENCIL8}}),
      _lightFramebuffer({.width = 2048,
                         .height = 2048,
                         .samples = 1,
                         .attachments = {FramebufferTextureFormat::RGBA32F,
                                         FramebufferTextureFormat::DEPTH32FSTENCIL8}}),
      _camera(4., 1., 0.1, 10.),
      _light(3., 1., 0.1, 10.)
{
    auto mesh = Mesh::loadFromObj(_config.scene.modelPath);
    mesh.rotateToPrincipalAxes();

    auto shader = std::make_shared<Shader>(_config.scene.vertexShaderPath,
                                           _config.scene.fragmentShaderPath);

    asteroid = createEntity();
    asteroid.addComponent<VaoComponent>(mesh);
    asteroid.addComponent<TransformComponent>();
    auto &m = asteroid.addComponent<MaterialComponent>(shader);

    _renderer.bgColor = glm::vec4(1., 0., 0., 1.0);
}

void PhotometryScene::renderSceneWithShadows()
{
    _camera.update();
    _light.update();

    // shadowmap
    _renderer.setFramebuffer(&_lightFramebuffer);
    _renderer.beginScene(_light);
    drawEntities();
    _renderer.endScene();

    // from camera
    _lightFramebuffer.bindDepthTexture(shadowDepthTextureSlot);
    _renderer.setFramebuffer(&_framebuffer);

    _renderer.beginScene(_camera, _light);
    drawEntities();
    _renderer.endScene();
}

void PhotometryScene::render()
{
    const auto fbWidth = _framebuffer.specification.width;
    const auto fbHeight = _framebuffer.specification.height;
    std::vector<float> pixelBuffRed(fbWidth * fbHeight);

    auto asteroidParams = _config.asteroidParams;

    for (const auto &lightcurveConfig : _config.lightcurves)
    {
        const auto numPoints = lightcurveConfig.numPoints;
        asteroidParams.setRotPhase(lightcurveConfig.startJd);

        Lightcurve lightcurve;
        lightcurve.reserve(numPoints);

        auto phaseIncrement = 2 * Pi / numPoints;
        auto timeIncrement = asteroidParams.period / numPoints;

        auto &t = asteroid.getComponent<TransformComponent>();
        t.position = lightcurveConfig.targetPosition;

        _camera.position = lightcurveConfig.observerPosition;
        _camera.updateTarget(t.position);

        _light.position = lightcurveConfig.lightPosition;
        _light.updateTarget(t.position);

        for (unsigned int i = 0; i < numPoints; i++)
        {
            t.rotation = asteroidParams.computeXyzRotation();

            renderSceneWithShadows();

            glReadPixels(0, 0, fbWidth, fbHeight, GL_RED, GL_FLOAT, pixelBuffRed.data());
            auto mag = Magnitude::cast(
                -2.5 * log10(std::accumulate(pixelBuffRed.begin(), pixelBuffRed.end(), 0.)));
            // fmt::print("{} {}\n", phase.value(), mag.value());

            lightcurve.push_back({.julianDay = lightcurveConfig.startJd + (i * timeIncrement),
                                  .rotPhase = asteroidParams.rotPhase,
                                  .step = i,
                                  .magnitude = mag,
                                  .observerPosition = _camera.position,
                                  .targetPosition = t.position});

            asteroidParams.rotPhase += phaseIncrement;
            asteroidParams.normalizeRotPhase();
        }

        syntheticObs.lightcurves.push_back(lightcurve);
    }
}

}  // namespace Sage
