#pragma once

#include <entt/entt.hpp>
#include "Entity.h"
#include "Renderer.h"

namespace AsteroidFarm {

class Renderer;

class Scene
{
public:
    Scene(Renderer &renderer) : _renderer(renderer) {}
    virtual ~Scene() = default;

    Entity createEntity();
    virtual void render() = 0;

protected:
    entt::registry _registry;
    void drawEntities();
    void draw(Entity entity);

    Renderer &_renderer;
};

}  // namespace AsteroidFarm
