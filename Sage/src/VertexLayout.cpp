#include "VertexLayout.h"


namespace Sage {

// NOTE this is for traversing arrays, i.e. size=3 means going array.begin() + 3
size_t VertexLayoutElement::getSize() const {
    switch (type)
    {
        case VertexElementType::POSITION:
            return getVertexElementSize<VertexElementType::POSITION>();
        case VertexElementType::NORMAL:
            return getVertexElementSize<VertexElementType::NORMAL>();
        case VertexElementType::TEXTURE:
            return getVertexElementSize<VertexElementType::TEXTURE>();
        case VertexElementType::COLOR:
            return getVertexElementSize<VertexElementType::COLOR>();
        case VertexElementType::NONE:
        default:
            return getVertexElementSize<VertexElementType::NONE>();

    }
}

// NOTE this is like getVertexElementSize, but includes type size (needed for OpenGL)
//size_t VertexLayoutElement::getNativeSize() const {
//    switch (type)
//    {
//        case VertexElementType::POSITION:
//            return 4 * 3;       // float * 3 for xyz
//        case VertexElementType::TEXTURE:
//            return 4 * 2;       // float * 2 for uv
//        case VertexElementType::COLOR:
//            return 4 * 4;       // float * 4 for rgba
//        case VertexElementType::NONE:
//        default:
//            return 0;
//    }
//}

// TODO implement sth similar for native size
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
