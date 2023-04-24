#pragma once

#include <glm/glm.hpp>

#include <string>
#include <map>
#include <fmt/printf.h>

namespace Sage {

class Shader
{
public:
    Shader();
    Shader(std::string vertexFilename, std::string fragmentFilename);
    Shader(const Shader &other);
    ~Shader();

    void setUniform3fv(std::string name, glm::vec3 data);
    void setUniform4fv(std::string name, glm::vec4 data);
    void setUniform1f(std::string name, float data);
    void setUniform1i(std::string name, int data);
    void setUniformMat4f(std::string name, glm::mat4 data);

    void bind();
    void unbind();

    void destroy();

    void createShader(const char *vertexShaderSource, const char *fragmentShaderSource);

    void createShader(const char *vertexShaderSource,
                      const char *geometryShaderSource,
                      const char *fragmentShaderSource);

    unsigned int program;

private:
    int getUniformLocation(std::string name);
    unsigned int compileShader(unsigned int type, const char *source);
    std::map<std::string, int> uniformLocationCache;
};

}  // namespace Sage