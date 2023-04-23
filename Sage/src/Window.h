#pragma once

#include <string>

class GLFWwindow;

struct WindowConfig
{
    int width;
    int height;
    std::string title;
    bool fullscreen;
    bool visible;
};

class Window
{
public:
    Window(WindowConfig config);
    ~Window();

private:
    void destroy();
    void close();

    GLFWwindow* _winptr;
    WindowConfig _config;
};