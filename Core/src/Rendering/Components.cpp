#include "Components.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

namespace AsteroidFarm {

TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : position(position), rotation(rotation), scale(scale)
{}

glm::mat4 TransformComponent::getTransformMatrix()
{
    return glm::translate(position) * getRotationMatrix() * glm::scale(scale);
}

glm::mat4 TransformComponent::getRotationMatrix()
{
    return glm::toMat4(glm::quat(rotation));
}

VaoComponent::VaoComponent(std::shared_ptr<VertexArrayObject> vao) : vao(vao) {}

VaoComponent::VaoComponent(const Mesh &mesh)
{
    vao = std::make_shared<VertexArrayObject>(mesh);
}

void MaterialComponent::cacheUniformValue(std::string name, glm::vec4 value)
{
    _uniforms.vec4s[name] = value;
}

void MaterialComponent::cacheUniformValue(std::string name, glm::vec3 value)
{
    _uniforms.vec3s[name] = value;
}

void MaterialComponent::cacheUniformValue(std::string name, glm::mat4 value)
{
    _uniforms.mat4s[name] = value;
}

void MaterialComponent::cacheUniformValue(std::string name, int value)
{
    _uniforms.ints[name] = value;
}

void MaterialComponent::cacheUniformValue(std::string name, float value)
{
    _uniforms.floats[name] = value;
}

void MaterialComponent::setUniforms()
{
    _shader->bind();
    for (auto [name, value] : _uniforms.vec4s)
    {
        _shader->setUniform4fv(name, value);
    }
    for (auto [name, value] : _uniforms.vec3s)
    {
        _shader->setUniform3fv(name, value);
    }
    for (auto [name, value] : _uniforms.mat4s)
    {
        _shader->setUniformMat4f(name, value);
    }
    for (auto [name, value] : _uniforms.ints)
    {
        _shader->setUniform1i(name, value);
    }
    for (auto [name, value] : _uniforms.floats)
    {
        _shader->setUniform1f(name, value);
    }
}

}  // namespace AsteroidFarm
