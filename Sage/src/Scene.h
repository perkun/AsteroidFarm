#pragma once

#include <entt/entt.hpp>
#include "Entity.h"

namespace Sage {

class Scene
{
public:
    Scene();
    ~Scene();

    Entity createEntity();
    void draw();
private:
	entt::registry _registry;

};

}  // namespace Sage