#pragma once

#include "Renderer.h"
#include "Window.h"
#include "Scene.h"

namespace Sage {

class GraphicsEngine
{
public:
    GraphicsEngine(const WindowConfig &windowConfig);
    ~GraphicsEngine() = default;

    Scene& getScene();
    Window& getWindow();
    Renderer& getRenderer();

private:
    Window _window;
    Renderer _renderer;
    Scene _scene;


};
}  // namespace Sage