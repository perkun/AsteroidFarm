#include <memory>
#include <numeric>
#include "Units.h"
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Framebuffer.h"
#include "Observations.h"

namespace AsteroidFarm {

template <class Config>
class PhotometryScene : public Scene
{
public:
    PhotometryScene(Renderer &renderer, glm::uvec2 framebufferSize, const Config &config)
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
        _modelRadius = mesh.getRadius();

        auto shader = std::make_shared<Shader>(_config.scene.vertexShaderPath,
                                               _config.scene.fragmentShaderPath);

        _asteroid = createEntity();
        _asteroid.addComponent<VaoComponent>(mesh);
        _asteroid.addComponent<TransformComponent>();
        auto &m = _asteroid.addComponent<MaterialComponent>(shader);

        _renderer.bgColor = glm::vec4(0., 0., 0., 1.0);
    }

    void renderSceneWithShadows();
    void updatePositions(JulianDay jd,
                         AsteroidParams &asteroidParams,
                         const glm::vec3 &targetPos,
                         const glm::vec3 &observerPos,
                         const glm::vec3 &lightPos);

protected:
    const Config &_config;

    Framebuffer _framebuffer;
    Framebuffer _lightFramebuffer;

    OrthographicCamera _camera;
    OrthographicCamera _light;

    Entity _asteroid;

    double _modelRadius;
};

template <class Config>
void PhotometryScene<Config>::renderSceneWithShadows()
{
    _camera.update();
    _light.update();

    // shadowmap
    _renderer.setFramebuffer(&_lightFramebuffer);
    _renderer.beginScene(_light);
    drawEntities();
    _renderer.endScene();

    // from camera
    _lightFramebuffer.bindDepthTexture(_renderer.shadowDepthTextureSlot);
    _renderer.setFramebuffer(&_framebuffer);
    // _renderer.setDefaultFramebuffer();

    _renderer.beginScene(_camera, _light);
    drawEntities();
    _renderer.endScene();
}

template <class Config>
void PhotometryScene<Config>::updatePositions(JulianDay jd,
                                              AsteroidParams &asteroidParams,
                                              const glm::vec3 &targetPos,
                                              const glm::vec3 &observerPos,
                                              const glm::vec3 &lightPos)
{
    // TODO move observer and target to positions multiplied by a factor.
    // Models could have arbitrary size, although if processed by Mesh algorithm they shoud have a
    // radius of 1 unit. The positions are defined in astronomical units, so there will be problems
    // with lighting, shadows etc if positions and relative distances are approaching 1, which they
    // will.

    auto &t = _asteroid.getComponent<TransformComponent>();
    t.position = targetPos;

    double distanceObserverToTarget = glm::length(targetPos - observerPos);
    double distanceLightToTarget = glm::length(targetPos - lightPos);

    _camera = OrthographicCamera(_modelRadius * 2,
                                 1.0,
                                 distanceObserverToTarget - _modelRadius,
                                 distanceObserverToTarget + _modelRadius);
    _camera.position = observerPos;
    _camera.updateTarget(t.position);

    _light = OrthographicCamera(_modelRadius * 2.,
                                1.0,
                                distanceLightToTarget - _modelRadius,
                                distanceLightToTarget + _modelRadius);
    _light.position = lightPos;
    _light.updateTarget(t.position);

    asteroidParams.setRotPhase(jd);
    t.rotation = asteroidParams.computeXyzRotation();
}

}  // namespace AsteroidFarm
