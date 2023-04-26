#pragma once

#include <glm/glm.hpp>
#include "Components.h"
#include "VertexArrayObject.h"

namespace Sage {

class Framebuffer;
class Renderer
{
public:
    Renderer();
    ~Renderer();

    void clear();
    void clear(glm::vec4 color);
    void setViewport(int x, int y, int width, int height);
    void bindDefaultFramebuffer();

    void beginScene();
    void endScene();
    void submit(const VertexArrayObject &vao, MaterialComponent &material);
    glm::vec4 bgColor{0.0};

    Framebuffer *framebuffer;

private:
};

}  // namespace Sage