#include "Scene.h"
#include "Entity.h"
#include "Components.h"

namespace Sage {

Scene::Scene() {}

Entity Scene::createEntity()
{
    return {_registry.create(), &_registry};
}

void Scene::draw()
{
    auto view = _registry.view<TransformComponent>();
    for (auto e: view)
    {
        Entity entity(e, &_registry);
        draw(entity);
    }

}

void Scene::draw(Entity entity) {
}

}  // namespace Sage