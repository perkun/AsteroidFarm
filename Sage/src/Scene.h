#pragma once

#include <entt/entt.hpp>
#include "Entity.h"

namespace Sage {

class Scene
{
public:
    Scene();

    Entity createEntity();
    void draw();
private:
	entt::registry _registry;
    void draw(Entity entity);

};

}  // namespace Sage