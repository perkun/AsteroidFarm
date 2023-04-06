#pragma once

#include <vector>

namespace Sage {

enum class VertexType
{
    NONE = 0,
    POSITION,
    TEXTURE_COORDS,
    COLOR
};

size_t getVertexTypeSize(VertexType);

struct VertexLayoutElement
{
    VertexType type;
    size_t offset;

    size_t getSize();
};

struct VertexLayout {
    VertexLayout() = default;
    VertexLayout(std::vector<VertexLayoutElement> elements) : elements(elements) {}

    size_t stride;
    std::vector<VertexLayoutElement> elements;

    void calculateStrideAndOffsets();
};

} // namespace Sage
