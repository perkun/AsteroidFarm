#pragma once

#include <vector>
#include <optional>
#include <algorithm>

namespace AsteroidFarm {

enum class VertexElementType
{
    NONE = 0,
    POSITION,
    NORMAL,
    TEXTURE,
    COLOR
};

struct VertexLayoutElement
{
    VertexLayoutElement() = delete;
    explicit VertexLayoutElement(VertexElementType type);

    const VertexElementType type;
    const size_t size;
    const size_t nativeSize;
    const int glType;

    size_t offset{0};
    size_t nativeOffset{0};

private:
    [[nodiscard]] size_t getSize(VertexElementType type) const;
    [[nodiscard]] size_t getNativeSize(VertexElementType type) const;
    [[nodiscard]] int getGlType(VertexElementType) const;
};

struct VertexLayout
{
    VertexLayout() = default;

    VertexLayout(std::convertible_to<VertexElementType> auto &&...args)
    {
        (_elements.emplace_back(std::forward<VertexElementType>(args)), ...);
        calculateStrideAndOffsets();
    }

    void pushElement(VertexElementType type)
    {
        _elements.emplace_back(type);
        calculateStrideAndOffsets();
    }

    const VertexLayoutElement *getElement(VertexElementType type) const
    {
        auto element = std::find_if(_elements.begin(),
                                    _elements.end(),
                                    [&type](const auto &elem) { return elem.type == type; });
        if (element != _elements.end())
        {
            return &(*element);
        }
        return nullptr;
    }

    size_t stride{0};

    const std::vector<VertexLayoutElement> &getElements() const
    {
        return _elements;
    }

private:
    std::vector<VertexLayoutElement> _elements;
    void calculateStrideAndOffsets();
};

}  // namespace AsteroidFarm
