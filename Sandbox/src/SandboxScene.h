#include <memory>
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Framebuffer.h"

// TODO namespace for tests?

namespace Sage {

class SandboxScene : public Scene
{
public:
    SandboxScene(glm::uvec2 framebufferSize)
        : _framebuffer(
              {.width = framebufferSize.x,
               .height = framebufferSize.y,
               .samples = 1,
               .attachments = {FramebufferTextureFormat::RGBA32F, FramebufferTextureFormat::DEPTH32FSTENCIL8}}),
          _lightFramebuffer(
              {.width = 2048,
               .height = 2048,
               .samples = 1,
               .attachments = {FramebufferTextureFormat::RGBA32F, FramebufferTextureFormat::DEPTH32FSTENCIL8}})
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

        camera = std::make_unique<OrthograficCamera>(4., 1., 0.1, 10.);
        camera->position = glm::vec3{2., 0., 0.};
        camera->updateTarget(t.position);

        light = std::make_unique<OrthograficCamera>(3., 1., 0.1, 10.);
        light->position = glm::vec3{0.};
        light->updateTarget(t.position);

        _renderer.bgColor = glm::vec4(0.2, 1., 0.3, 1.0);
    }

    void render() override
    {
        camera->update();
        light->update();
        // _renderer.framebuffer = &_framebuffer;

        // shadowmap
        _renderer.framebuffer = &_lightFramebuffer;
        _renderer.beginScene(camera.get());
        drawEntities();
        _renderer.endScene();

        // from camera
        _lightFramebuffer.bind_depth_texture(shadowDepthTextureSlot);
        // _renderer.framebuffer = &_framebuffer;
        _renderer.framebuffer = std::nullopt;

        // TODO automate this!
        _renderer.setViewport(0, 0, 600, 600);

        _renderer.beginScene(camera.get(), light.get());
        drawEntities();
        _renderer.endScene();
    }

private:
    Framebuffer _framebuffer;
    Framebuffer _lightFramebuffer;

    std::unique_ptr<Camera> camera;
    std::unique_ptr<Camera> light;

};

}  // namespace Sage