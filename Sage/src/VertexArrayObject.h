#pragma once

#include "glad/glad.h"

namespace Sage {

class Mesh;

class VertexArrayObject
{
public:
    VertexArrayObject(const Mesh &mesh);
    ~VertexArrayObject();

    int numDrawElements{0};
private:
    const unsigned int _drawType{GL_TRIANGLES};

    GLuint _vaoId;
    GLuint _vboId;
    GLuint _idxsId;
};

}  // namespace Sage