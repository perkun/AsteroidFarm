#pragma once

#include "Renderer.h"
#include "Window.h"
#include "Scene.h"

namespace Sage {

class GraphicsEngine
{
public:
    GraphicsEngine();
    ~GraphicsEngine() = default;

    Scene& getScene();
    Window _window;

private:
    Renderer _renderer;
    Scene _scene;


};
}  // namespace Sage