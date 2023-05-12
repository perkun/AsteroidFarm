#include "Shader.h"

#include "glad/glad.h"
#include <fmt/core.h>

namespace Sage {

Shader::Shader(std::string vertexFilename, std::string fragmentFilename)
{
    FILE *f = fopen(vertexFilename.c_str(), "rb");
    if (f == NULL)
    {
        // TODO logging
        fmt::print("Clould not open vertex shader file: {}\n", vertexFilename);
        return;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET); /* same as rewind(f); */

    char *vertexShaderSource = (char *)malloc(fsize + 1);
    fread(vertexShaderSource, 1, fsize, f);
    vertexShaderSource[fsize] = 0;
    fclose(f);

    f = fopen(fragmentFilename.c_str(), "rb");
    if (f == NULL)
    {
        fmt::print("Clould not open fragment shader file: {}\n", fragmentFilename);
        return;
    }

    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    fseek(f, 0, SEEK_SET); /* same as rewind(f); */

    char *fragmentShaderSource = (char *)malloc(fsize + 1);
    fread(fragmentShaderSource, 1, fsize, f);
    fragmentShaderSource[fsize] = 0;
    fclose(f);

    createShader(vertexShaderSource, fragmentShaderSource);

    free(vertexShaderSource);
    free(fragmentShaderSource);
}

Shader::Shader(const Shader &other)
{
    program = other.program;
}

Shader::~Shader()
{
    destroy();
}

void Shader::destroy()
{
    glDeleteProgram(program);
}

void Shader::bind()
{
    glUseProgram(program);
}

void Shader::unbind()
{
    glUseProgram(0);
}

unsigned int Shader::compileShader(unsigned int type, const char *source)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        fmt::print("Failed to compile {} shader",
                   (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
        fmt::print("{}", message);
        glDeleteShader(id);
        return 0;
    }

    return id;
}

void Shader::createShader(const char *vertexShaderSource, const char *fragmentShaderSource)
{
    program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::createShader(const char *vertexShaderSource,
                          const char *geometryShaderSource,
                          const char *fragmentShaderSource)
{
    program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int gs = compileShader(GL_GEOMETRY_SHADER, geometryShaderSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(program, vs);
    glAttachShader(program, gs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(gs);
    glDeleteShader(fs);
}

int Shader::getUniformLocation(std::string name)
{
    if (uniformLocationCache.find(name) != uniformLocationCache.end())
        return uniformLocationCache[name];

    int location;
    location = glGetUniformLocation(program, name.c_str());
    if (location == -1)
    {
        fmt::print("The name {} does not exist in shader", name);
    }

    uniformLocationCache[name] = location;

    return location;
}
void Shader::setUniform3fv(std::string name, glm::vec3 data)
{
    glUniform3fv(getUniformLocation(name), 1, &data[0]);
}

void Shader::setUniform4fv(std::string name, glm::vec4 data)
{
    glUniform4fv(getUniformLocation(name), 1, &data[0]);
}

void Shader::setUniformMat4f(std::string name, glm::mat4 data)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &data[0][0]);
}

void Shader::setUniform1f(std::string name, float data)
{
    glUniform1f(getUniformLocation(name), data);
}

void Shader::setUniform1i(std::string name, int data)
{
    glUniform1i(getUniformLocation(name), data);
}
}  // namespace Sage