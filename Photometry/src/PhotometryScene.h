#include <memory>
#include <numeric>
#include "Angle.h"
#include "Camera.h"
#include "LightcurveConfig.h"
#include "Scene.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Framebuffer.h"

#include "Observations.h"

// TODO namespace for tests?

namespace Sage {

class PhotometryScene : public Scene
{
public:
    PhotometryScene(Renderer &renderer, glm::uvec2 framebufferSize, const LightcurveConfig &config)
        : Scene(renderer),
          _config(config),
          _framebuffer(
              {.width = framebufferSize.x,
               .height = framebufferSize.y,
               .samples = 1,
               .attachments = {FramebufferTextureFormat::RGBA32F, FramebufferTextureFormat::DEPTH32FSTENCIL8}}),
          _lightFramebuffer(
              {.width = 2048,
               .height = 2048,
               .samples = 1,
               .attachments = {FramebufferTextureFormat::RGBA32F, FramebufferTextureFormat::DEPTH32FSTENCIL8}}),
          _camera(4., 1., 0.1, 10.),
          _light(3., 1., 0.1, 10.)
    {
        auto mesh = Mesh::loadFromObj(_config.modelPath);
        mesh.rotateToPrincipalAxes();

        auto shader = std::make_shared<Shader>(_config.vertexShaderPath, _config.fragmentShaderPath);

        asteroid = createEntity();
        asteroid.addComponent<VaoComponent>(mesh);
        auto &t = asteroid.addComponent<TransformComponent>();
        auto &m = asteroid.addComponent<MaterialComponent>(shader);
        t.position = _config.targetPosition;

        _camera.position = _config.observerPosition;
        _camera.updateTarget(t.position);

        _light.position = _config.lightPosition;
        _light.updateTarget(t.position);

        _renderer.bgColor = glm::vec4(1., 0., 0., 1.0);

        syntheticObs.targetName = _config.targetName;
    }

    void renderSceneWithShadows()
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

    void render() override
    {
        constexpr int numPoints = 90;

        auto asteroidParams = _config.asteroidParams;

        // NOTE this should be done while parsing, but to be extra sure...
        asteroidParams.setRotPhase(_config.startJd);

        const auto fbWidth = _framebuffer.specification.width;
        const auto fbHeight = _framebuffer.specification.height;
        std::vector<float> pixelBuffRed(fbWidth * fbHeight);

        Lightcurve lightcurve;
        lightcurve.reserve(numPoints);

        auto phaseIncrement = 2 * Pi / numPoints;
        auto timeIncrement = asteroidParams.period / numPoints;

        for (unsigned int i = 0; i < numPoints; i++)
        {
            auto &t = asteroid.getComponent<TransformComponent>();
            t.rotation = asteroidParams.computeXyzRotation();

            renderSceneWithShadows();

            glReadPixels(0, 0, fbWidth, fbHeight, GL_RED, GL_FLOAT, pixelBuffRed.data());
            auto mag = Magnitude::cast(-2.5 * log10(std::accumulate(pixelBuffRed.begin(), pixelBuffRed.end(), 0.)));
            // fmt::print("{} {}\n", phase.value(), mag.value());

            using namespace UnitLiterals;
            lightcurve.push_back({.julianDay = _config.startJd + (i * timeIncrement),
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

    LightcurveStorage syntheticObs;

private:
    LightcurveConfig _config;

    Framebuffer _framebuffer;
    Framebuffer _lightFramebuffer;

    OrthographicCamera _camera;
    OrthographicCamera _light;

    Entity asteroid;
};

}  // namespace Sage