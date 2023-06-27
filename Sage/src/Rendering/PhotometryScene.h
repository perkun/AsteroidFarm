#include <memory>
#include <numeric>
#include "Units.h"
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Framebuffer.h"
#include "Observations.h"

namespace Sage {

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

        asteroid = createEntity();
        asteroid.addComponent<VaoComponent>(mesh);
        asteroid.addComponent<TransformComponent>();
        auto &m = asteroid.addComponent<MaterialComponent>(shader);

        _renderer.bgColor = glm::vec4(0., 0., 0., 1.0);
    }

    void renderSceneWithShadows();

protected:
    const Config &_config;

    Framebuffer _framebuffer;
    Framebuffer _lightFramebuffer;

    OrthographicCamera _camera;
    OrthographicCamera _light;

    Entity asteroid;

    double _modelRadius;
};

template<class Config>
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
    _lightFramebuffer.bindDepthTexture(shadowDepthTextureSlot);
    // _renderer.setFramebuffer(&_framebuffer);
    _renderer.setDefaultFramebuffer();

    _renderer.beginScene(_camera, _light);
    drawEntities();
    _renderer.endScene();
}


}  // namespace Sage
