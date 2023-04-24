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

private:
    Window _window;
    Renderer _renderer;
    Scene _scene;


};
}  // namespace Sage