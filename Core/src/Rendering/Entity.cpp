#include "Entity.h"
// #include "Components.h"

namespace AsteroidFarm {

Entity::~Entity() {}

void Entity::destroy()
{
    if (! *this)
    {
        return;
    }

    _sceneRegistry->destroy(_handle);
}

}  // namespace AsteroidFarm
