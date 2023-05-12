#include <memory>
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Framebuffer.h"

// TODO namespace for tests?

namespace Sage::Test {

class RenderingShadowTestScene : public Scene
{
public:
    RenderingShadowTestScene(Renderer &renderer, glm::uvec2 framebufferSize)
        : Scene(renderer),
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
        auto mesh = Mesh::loadFromObj("data/model_shifted.obj");
        mesh.rotateToPrincipalAxes();

        auto shader = std::make_shared<Shader>("data/shadow.vs", "data/shadow.fs");

        auto asteroid = createEntity();
        asteroid.addComponent<VaoComponent>(mesh);
        auto &t = asteroid.addComponent<TransformComponent>();
        auto &m = asteroid.addComponent<MaterialComponent>(shader);
        t.position = glm::vec3{0., 4., 0.};

        auto asteroid2 = createEntity();
        asteroid2.addComponent<VaoComponent>(mesh);
        auto &t2 = asteroid2.addComponent<TransformComponent>();
        auto &m2 = asteroid2.addComponent<MaterialComponent>(shader);
        t2.position = glm::vec3{0., 7., .5};
        t2.scale = glm::vec3{0.5f};

        _camera.position = glm::vec3{2., 0., 0.};
        _camera.updateTarget(t.position);

        _light.position = glm::vec3{0.};
        _light.updateTarget(t.position);

        _renderer.bgColor = glm::vec4(0.2, 1., 0.3, 1.0);
    }

    void render() override
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

private:
    Framebuffer _framebuffer;
    Framebuffer _lightFramebuffer;

    OrthographicCamera _camera;
    OrthographicCamera _light;
};

}  // namespace Sage::Test
