#pragma once

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
    Scene _scene;


};
}  // namespace Sage