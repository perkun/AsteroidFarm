#pragma once

#include <entt/entt.hpp>
#include "Entity.h"
#include "Renderer.h"

namespace Sage {

class Renderer;

class Scene
{
public:
    virtual ~Scene() = default;

    Entity createEntity();
    virtual void render() = 0;

    // TODO unique ptr?
    std::shared_ptr<Camera> camera{nullptr};

protected:
    entt::registry _registry;
    void draw();
    void draw(Entity entity);

    Renderer _renderer;
};

}  // namespace Sage