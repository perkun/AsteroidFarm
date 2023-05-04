#pragma once

#include "VertexArrayObject.h"
#include "Shader.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <memory>

namespace Sage {

class TransformComponent
{
public:
    TransformComponent() = default;
    TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    glm::vec3 position{0.};
    glm::vec3 rotation{0.};
    glm::vec3 scale{1.};

    glm::mat4 getTransformMatrix();

private:
    glm::mat4 getRotationMatrix();
};

struct VaoComponent
{
    VaoComponent(std::shared_ptr<VertexArrayObject> vao);
    VaoComponent(const Mesh &mesh);
    std::shared_ptr<VertexArrayObject> vao;
};

class MaterialComponent
{
public:
    MaterialComponent(std::shared_ptr<Shader> shader) : _shader(shader) {}

    void cacheUniformValue(std::string name, glm::vec4 value);
    void cacheUniformValue(std::string name, glm::vec3 value);
    void cacheUniformValue(std::string name, glm::mat4 value);
    void cacheUniformValue(std::string name, int value);
    void cacheUniformValue(std::string name, float value);
    void setUniforms();

private:
    std::shared_ptr<Shader> _shader;

    struct Uniforms
    {
        std::map<std::string, glm::vec4> vec4s;
        std::map<std::string, glm::mat4> mat4s;
        std::map<std::string, glm::vec3> vec3s;
        std::map<std::string, int> ints;
        std::map<std::string, float> floats;
    };
    Uniforms _uniforms;
};

struct CameraComponent
{
    CameraComponent(std::shared_ptr<Camera> camera) : camera(camera) {}
    std::shared_ptr<Camera> camera;
};

}  // namespace Sage