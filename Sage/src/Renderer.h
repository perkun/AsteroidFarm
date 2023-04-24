#pragma once

#include <glm/glm.hpp>

namespace Sage {

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
    void submit();

private:
};

}  // namespace Sage