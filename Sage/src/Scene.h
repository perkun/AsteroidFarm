#pragma once

#include <entt/entt.hpp>
#include "Entity.h"
#include "Renderer.h"

namespace Sage {

class Renderer;

class Scene
{
public:
    Scene(Renderer &renderer);

    Entity createEntity();
    void draw();

    Camera *camera;

private:
    entt::registry _registry;
    void draw(Entity entity);

    Renderer &_renderer;
};

}  // namespace Sage