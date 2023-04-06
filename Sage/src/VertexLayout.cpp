#include "VertexLayout.h"


namespace Sage {

size_t getVertexTypeSize(VertexType type)
{
    switch (type)
    {
        case VertexType::POSITION:
            return 4 * 3;       // float * 3 for xyz
        case VertexType::TEXTURE_COORDS:
            return 4 * 2;       // float * 2 for uv
        case VertexType::COLOR:
            return 4 * 4;       // float * 4 for rgba
        case VertexType::NONE:
        default:
            return 0;
    }
}

size_t VertexLayoutElement::getSize() {
    return getVertexTypeSize(type);
}


void VertexLayout::calculateStrideAndOffsets()
{
    stride = 0;
    size_t offset = 0;
    for (auto &layoutElement : elements)
    {
        layoutElement.offset = offset;
        auto size = layoutElement.getSize();
        offset += size;
        stride += size;
    }
}


} // namespace Sage
