#pragma once

#include "Window.h"

namespace Sage {

class GraphicsEngine
{
public:
    GraphicsEngine();
    ~GraphicsEngine() = default;

private:
    Window _window;

};
}  // namespace Sage