#pragma once

#include "Framebuffer.h"
#include "Renderer.h"
#include "Window.h"
#include "Scene.h"

#include <utility>
#include <optional>

namespace AsteroidFarm {

class GraphicsEngine
{
public:
    GraphicsEngine(const WindowConfig &windowConfig);

    Window &getWindow();

    void renderScenes();

    template <typename SceneType, typename... Args>
    SceneType &pushScene(Args &&...args)
    {
        std::unique_ptr<Scene> &scene = _scenes.emplace_back(
            std::make_unique<SceneType>(_renderer, std::forward<Args>(args)...));
        return *dynamic_cast<SceneType *>(scene.get());
    }

    void updateWindow()
    {
        _window.update();
    }

private:
    Window _window;
    Renderer _renderer;

    std::vector<std::unique_ptr<Scene>> _scenes;
};
}  // namespace AsteroidFarm
