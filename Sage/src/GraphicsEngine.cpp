#include "GraphicsEngine.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

namespace Sage {

GraphicsEngine::GraphicsEngine(const WindowConfig &windowConfig) : _window(windowConfig)
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

GraphicsEngine::~GraphicsEngine()
{
    for (auto s : _scenes)
    {
        delete s;
    }
}

Window &GraphicsEngine::getWindow()
{
    return _window;
}

void GraphicsEngine::renderScenes()
{
    // TODO think of passing results from one scene to the next.
    for (auto &scene : _scenes)
    {
        scene->render();
    }
}

}  // namespace Sage