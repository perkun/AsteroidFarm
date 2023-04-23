#include "Scene.h"
#include "Entity.h"

namespace Sage {

Scene::Scene() {}

Entity Scene::createEntity() 
{
    return {_registry.create(), &_registry};
}

void Scene::draw()
{

}

}  // namespace Sage