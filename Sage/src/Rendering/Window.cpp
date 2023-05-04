#include "Window.h"
#include <GLFW/glfw3.h>

namespace Sage {

Window::Window(WindowConfig config) : _config(config)
{
    if (! glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(0);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);

    // create window
    glfwWindowHint(GLFW_VISIBLE, _config.visible ? GLFW_TRUE : GLFW_FALSE);

    _winptr = glfwCreateWindow(_config.width,
                               _config.height,
                               _config.title.c_str(),
                               _config.fullscreen ? glfwGetPrimaryMonitor() : NULL,
                               NULL);

    glfwMakeContextCurrent(_winptr);

    // user pointer
    glfwSetWindowUserPointer(_winptr, this);
}

Window::~Window()
{
    destroy();
    glfwTerminate();
}

void Window::close()
{
    glfwSetWindowShouldClose(_winptr, GLFW_TRUE);
}

void Window::destroy()
{
    glfwDestroyWindow(_winptr);
}

void Window::update()
{
    glfwSwapBuffers(_winptr);
}
}  // namespace Sage