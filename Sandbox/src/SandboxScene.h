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

        myCamera = std::make_shared<OrthograficCamera>(4., 1., 0.1, 10.);
        myCamera->position = glm::vec3{2., 0., 0.};
        myCamera->updateTarget(t.position);

        myLight = std::make_shared<OrthograficCamera>(3., 1., 0.1, 10.);
        myLight->position = glm::vec3{0.};
        myLight->updateTarget(t.position);

        _renderer.bgColor = glm::vec4(0.2, 1., 0.3, 1.0);
        // _renderer.bgColor = glm::vec4{0.,0.,0.,1.};
    }

    void render() override
    {
        // _renderer.framebuffer = &_framebuffer;

        // shadowmap
        _renderer.framebuffer = &_lightFramebuffer;
        camera = myLight;
        light.reset();
        draw();

        // from camera
        _lightFramebuffer.bind_depth_texture(shadowDepthTextureSlot);
        // _renderer.framebuffer = &_framebuffer;
        _renderer.framebuffer = std::nullopt;

        // TODO automate this!
        _renderer.setViewport(0, 0, 600, 600);

        camera = myCamera;
        light = myLight;
        draw();
    }

private:
    Framebuffer _framebuffer;
    Framebuffer _lightFramebuffer;

    std::shared_ptr<Camera> myCamera;
    std::shared_ptr<Camera> myLight;

};

}  // namespace Sage