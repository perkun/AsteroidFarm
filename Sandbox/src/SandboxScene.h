#include <memory>
#include <numeric>
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
    SandboxScene(Renderer &renderer, glm::uvec2 framebufferSize)
        : Scene(renderer),
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
        auto mesh = Mesh::loadFromObj("data/model_shifted.obj");
        mesh.rotateToPrincipalAxes();

        auto shader = std::make_shared<Shader>("data/shadow.vs", "data/shadow.fs");

        asteroid = createEntity();
        asteroid.addComponent<VaoComponent>(mesh);
        auto &t = asteroid.addComponent<TransformComponent>();
        auto &m = asteroid.addComponent<MaterialComponent>(shader);
        t.position = glm::vec3{0., 4., 0.};

        _camera.position = glm::vec3{2., 0., 0.};
        _camera.updateTarget(t.position);

        _light.position = glm::vec3{0.};
        _light.updateTarget(t.position);

        _renderer.bgColor = glm::vec4(1., 0., 0., 1.0);
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

        const auto fbWidth = _framebuffer.specification.width;
        const auto fbHeight = _framebuffer.specification.height;
        std::vector<float> pixelBuffRed(fbWidth * fbHeight);

        for (int i = 0; i < numPoints; i++)
        {
            auto &t = asteroid.getComponent<TransformComponent>();
            auto phase = (i * 360. / numPoints) / 180.0 * M_PI;
            t.rotation.z = phase;
            renderSceneWithShadows();

            glReadPixels(0, 0, fbWidth, fbHeight, GL_RED, GL_FLOAT, pixelBuffRed.data());
            auto mag = -2.5 * log10(std::accumulate(pixelBuffRed.begin(), pixelBuffRed.end(), 0.));
            fmt::print("{} {}\n", phase, mag);
        }
    }

private:
    Framebuffer _framebuffer;
    Framebuffer _lightFramebuffer;

    OrthographicCamera _camera;
    OrthographicCamera _light;

    Entity asteroid;
};

}  // namespace Sage