#include "VertexLayout.h"

#include "glad/glad.h"

namespace Sage {

VertexLayoutElement::VertexLayoutElement(VertexElementType type)
    : type(type), size(getSize(type)), nativeSize(getNativeSize(type)), glType(getGlType(type))
{}

// NOTE this is for traversing arrays, i.e. size=3 means going array.begin() + 3
size_t VertexLayoutElement::getSize(VertexElementType type) const
{
    switch (type)
    {
    case VertexElementType::POSITION:
        return 3;
    case VertexElementType::NORMAL:
        return 3;
    case VertexElementType::TEXTURE:
        return 2;
    case VertexElementType::COLOR:
        return 4;
    case VertexElementType::NONE:
    default:
        return 0;
    }
}

int VertexLayoutElement::getGlType(VertexElementType type) const 
{
    switch (type)
    {
    case VertexElementType::POSITION:
    case VertexElementType::NORMAL:
    case VertexElementType::COLOR:
    case VertexElementType::TEXTURE:
        return GL_FLOAT;
    case VertexElementType::NONE:
    default:
        return GL_NONE;
    }
}

// NOTE this is like getVertexElementSize, but includes type size (needed for OpenGL)
size_t VertexLayoutElement::getNativeSize(VertexElementType type) const
{
    switch (type)
    {
    case VertexElementType::POSITION:
        return 4 * 3;  // float * 3 for xyz
    case VertexElementType::TEXTURE:
        return 4 * 2;  // float * 2 for uv
    case VertexElementType::COLOR:
        return 4 * 4;  // float * 4 for rgba
    case VertexElementType::NONE:
    default:
        return 0;
    }
}

// TODO implement sth similar for native size
void VertexLayout::calculateStrideAndOffsets()
{
    stride = 0;
    size_t offset = 0;
    for (auto &layoutElement : _elements)
    {
        layoutElement.offset = offset;
        auto size = layoutElement.size;
        offset += size;
        stride += size;
    }
}

}  // namespace Sage