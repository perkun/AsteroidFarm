#include "VertexArrayObject.h"

#include "Mesh.h"

namespace Sage {
VertexArrayObject::VertexArrayObject(const Mesh &mesh)
{
    numDrawElements = mesh.indices.size() * 3;

    // create VAO
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    // generate buffers
    glGenBuffers(1, &_vboId);
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(float), &mesh.vertices[0], GL_STATIC_DRAW);

    for (unsigned int locationIndex = 0; const VertexLayoutElement &vle : mesh.layout.getElements())
    {
        glEnableVertexAttribArray(locationIndex);
        glVertexAttribPointer(
            locationIndex, vle.size, vle.glType, GL_FALSE, mesh.layout.stride * sizeof(float), (void *)vle.nativeOffset);
        locationIndex++;
    }

    // indices
    glGenBuffers(1, &_idxsId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idxsId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(1, &_vboId);
    glDeleteBuffers(1, &_idxsId);
}
}  // namespace Sage