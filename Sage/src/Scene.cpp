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

void Scene::draw()
{
    _renderer.beginScene();

    auto view = _registry.view<TransformComponent, MaterialComponent, VaoComponent>();
    for (auto e : view)
    {
        Entity entity(e, &_registry);
        draw(entity);
    }

    _renderer.endScene();
}

void Scene::draw(Entity entity)
{
    if (!camera)
    {
        return;
    }

    // NOTE: we do not check for existance of these componenets, we rely on 
    // function calling this one checking for it
    // TODO check for existance?
    auto &transform = entity.getComponent<TransformComponent>();
    auto &material = entity.getComponent<MaterialComponent>();
    auto &vao = entity.getComponent<VaoComponent>();

    camera->update();
    material.cacheUniformValue("u_view_matrix", camera->getView());
    material.cacheUniformValue("u_perspective_matrix", camera->getPerspective());

    if (light)
    {
        light->update();
        material.cacheUniformValue("u_light_position", light->position);
        material.cacheUniformValue("u_light_view_matrix", light->getView());
        material.cacheUniformValue("u_light_perspective_matrix", light->getPerspective());

        // TODO what does this number mean? Texture index?
        material.cacheUniformValue("u_depth_map", shadowDepthTextureSlot);

    }

    material.cacheUniformValue("u_model_matrix", transform.getTransformMatrix());
    _renderer.submit(*vao.vao.get(), material);
}

}  // namespace Sage