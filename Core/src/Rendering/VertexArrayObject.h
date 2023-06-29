#pragma once

#include "glad/glad.h"

namespace AsteroidFarm {

class Mesh;

class VertexArrayObject
{
public:
    VertexArrayObject(const Mesh &mesh);
    ~VertexArrayObject();

    int numDrawElements{0};
    GLuint vaoId;
    const unsigned int drawType{GL_TRIANGLES};

private:
    GLuint _vboId;
    GLuint _idxsId;
};

}  // namespace AsteroidFarm
