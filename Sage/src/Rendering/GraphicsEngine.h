#pragma once

#include "Framebuffer.h"
#include "Renderer.h"
#include "Window.h"
#include "Scene.h"

#include <utility>
#include <optional>

namespace Sage {

class GraphicsEngine
{
public:
    GraphicsEngine(const WindowConfig &windowConfig);
    ~GraphicsEngine();

    Window &getWindow();

    void renderScenes();
    template <typename T, typename... Args>
    T &pushScene(Args &&...args)
    {
        auto s = new T(_renderer, std::forward<Args>(args)...);
        _scenes.emplace_back(s);
        return *s;
    }

    void updateWindow()
    {
        _window.update();
    }

private:
    Window _window;
    Renderer _renderer;

    std::vector<Scene *> _scenes;
};
}  // namespace Sage