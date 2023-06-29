#include "Renderer.h"

#include <glad/glad.h>
#include "Framebuffer.h"

namespace AsteroidFarm {

Renderer::Renderer(glm::ivec2 defaultFramebufferSize)
    : _defaultFramebufferSize(defaultFramebufferSize)
{}

Renderer::~Renderer() {}

void Renderer::clear(glm::vec4 color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    clear();
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setViewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void Renderer::bindDefaultFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, _defaultFramebufferSize.x, _defaultFramebufferSize.y);
}

void Renderer::beginScene(const Camera &camera, const Camera &light)
{
    sceneData.lightPosition = light.position;
    sceneData.lightView = light.getView();
    sceneData.lightPerspecitve = light.getPerspective();

    beginScene(camera);
}

void Renderer::beginScene(const Camera &camera)
{
    sceneData.view = camera.getView();
    sceneData.perspective = camera.getPerspective();

    if (_framebuffer)
    {
        _framebuffer.value()->bind();
    }
    else
    {
        bindDefaultFramebuffer();
    }

    clear(bgColor);
}

void Renderer::endScene()
{
    sceneData = ScenData{};
}

void Renderer::setFramebuffer(Framebuffer *framebuffer)
{
    _framebuffer = framebuffer;
}

void Renderer::setDefaultFramebuffer()
{
    _framebuffer.reset();
}

void Renderer::submit(const VertexArrayObject &vao, MaterialComponent &material)
{
    material.cacheUniformValue("u_view_matrix", sceneData.view);
    material.cacheUniformValue("u_perspective_matrix", sceneData.perspective);
    material.cacheUniformValue("u_depth_map", shadowDepthTextureSlot);

    if (sceneData.lightPosition)
    {
        material.cacheUniformValue("u_light_position", sceneData.lightPosition.value());
    }
    if (sceneData.lightView)
    {
        material.cacheUniformValue("u_light_view_matrix", sceneData.lightView.value());
    }
    if (sceneData.lightPerspecitve)
    {
        material.cacheUniformValue("u_light_perspective_matrix",
                                   sceneData.lightPerspecitve.value());
    }

    material.setUniforms();

    glBindVertexArray(vao.vaoId);
    glDrawElements(vao.drawType, vao.numDrawElements, GL_UNSIGNED_INT, NULL);
}

}  // namespace AsteroidFarm
