#include "GraphicsEngine.h"

#include "Renderer.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

namespace Sage {

GraphicsEngine::GraphicsEngine(const WindowConfig &windowConfig) : _window(windowConfig), _scene(_renderer)
{
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (status == 0)
    {
        std::cerr << "Glad failed to initialize " << status << std::endl;
        exit(1);
    }

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

Scene &GraphicsEngine::getScene()
{
    return _scene;
}

Window &GraphicsEngine::getWindow()
{
    return _window;
}

Renderer &GraphicsEngine::getRenderer()
{
    return _renderer;
}

}  // namespace Sage