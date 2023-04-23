#include "GraphicsEngine.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

namespace Sage {

GraphicsEngine::GraphicsEngine()
    : _window({.width = 600, .height = 600, .title = "SageRendering", .fullscreen = false, .visible = true})
{
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (status == 0)
    {
        std::cerr << "Glad failed to initialize " << status << std::endl;
        exit(1);
    }
}

}  // namespace Sage