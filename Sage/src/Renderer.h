#pragma once

#include <glm/glm.hpp>
#include "Components.h"
#include "VertexArrayObject.h"

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

    // void beginScene(std::shared_ptr<Camera> camera);
    // void endScene();
    void submit(const VertexArrayObject &vao, MaterialComponent &material);

private:
    // std::shared_ptr<Camera> _camera;
};

}  // namespace Sage