#include "Scene.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Framebuffer.h"

// TODO namespace for tests?

namespace Sage::Test {

class RenderingTestScene : public Scene
{
public:
    RenderingTestScene(Renderer &renderer, glm::uvec2 framebufferSize)
        : Scene(renderer),
          _framebuffer(
              {.width = framebufferSize.x,
               .height = framebufferSize.y,
               .samples = 1,
               .attachments = {FramebufferTextureFormat::RGBA32F, FramebufferTextureFormat::DEPTH32FSTENCIL8}}),
          _camera(4., 1., 0.1, 10.)
    {
        auto mesh = Mesh::loadFromObj("data/model_shifted.obj");
        mesh.rotateToPrincipalAxes();

        auto shader = std::make_shared<Shader>("data/basic.vs", "data/basic.fs");

        auto asteroid = createEntity();
        asteroid.addComponent<VaoComponent>(mesh);
        auto &t = asteroid.addComponent<TransformComponent>();
        auto &m = asteroid.addComponent<MaterialComponent>(shader);
        t.position = glm::vec3{0., 5., 0.};

        _camera.position = glm::vec3{1., 2., 3.};
        _camera.updateTarget(t.position);

        _renderer.bgColor = glm::vec4(0.2, 1., 0.3, 1.0);
    }

    void render() override
    {
        _renderer.setFramebuffer(&_framebuffer);
        _camera.update();
        _renderer.beginScene(_camera);
        drawEntities();
        _renderer.endScene();
    }

private:
    Framebuffer _framebuffer;
    OrthographicCamera _camera;
};

}  // namespace Sage::Test
