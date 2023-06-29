#pragma once

#include <glm/glm.hpp>
#include "Components.h"
#include "VertexArrayObject.h"

#include <optional>

namespace AsteroidFarm {

class Framebuffer;
class Renderer
{
public:
    Renderer(glm::ivec2 defaultFramebufferSize);
    ~Renderer();

    void clear();
    void clear(glm::vec4 color);
    void setViewport(int x, int y, int width, int height);
    void bindDefaultFramebuffer();

    void beginScene(const Camera &camera);
    void beginScene(const Camera &camera, const Camera &light);
    void endScene();
    void submit(const VertexArrayObject &vao, MaterialComponent &material);
    glm::vec4 bgColor{0.0};

    void setFramebuffer(Framebuffer *framebuffer);
    void setDefaultFramebuffer();

    static constexpr int shadowDepthTextureSlot{1};

private:
    struct ScenData
    {
        glm::mat4 view{1};
        glm::mat4 perspective{1};

        std::optional<glm::vec3> lightPosition{std::nullopt};
        std::optional<glm::mat4> lightView{std::nullopt};
        std::optional<glm::mat4> lightPerspecitve{std::nullopt};
    } sceneData;

    // TODO I don't like this pointer...
    std::optional<Framebuffer *> _framebuffer;
    glm::ivec2 _defaultFramebufferSize;
};

}  // namespace AsteroidFarm
