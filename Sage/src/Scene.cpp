#include "Scene.h"
#include "Camera.h"
#include "Entity.h"
#include "Components.h"
#include "Renderer.h"

namespace Sage {

Entity Scene::createEntity()
{
    return {_registry.create(), &_registry};
}

void Scene::drawEntities()
{
    auto view = _registry.view<TransformComponent, MaterialComponent, VaoComponent>();
    for (auto e : view)
    {
        Entity entity(e, &_registry);
        draw(entity);
    }
}

void Scene::draw(Entity entity)
{
    auto &transform = entity.getComponent<TransformComponent>();
    auto &material = entity.getComponent<MaterialComponent>();
    auto &vao = entity.getComponent<VaoComponent>();

    material.cacheUniformValue("u_model_matrix", transform.getTransformMatrix());
    _renderer.submit(*vao.vao.get(), material);
}

}  // namespace Sage