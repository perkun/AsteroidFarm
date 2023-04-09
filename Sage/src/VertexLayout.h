#pragma once

#include <vector>
#include <optional>
#include <concepts>

namespace Sage {

enum class VertexElementType
{
    NONE = 0,
    POSITION,
    NORMAL,
    TEXTURE,
    COLOR
};

template<VertexElementType Type>
size_t getVertexElementSize()
{
    if constexpr (Type == VertexElementType::POSITION)
    {
        return 3;
    }
    if constexpr (Type == VertexElementType::NORMAL)
    {
        return 3;
    }
    if constexpr (Type == VertexElementType::TEXTURE)
    {
        return 2;
    }
    if constexpr (Type == VertexElementType::COLOR)
    {
        return 4;
    }
    if constexpr (Type == VertexElementType::NONE)
    {
        return 0;
    }
}

struct VertexLayoutElement
{
    VertexLayoutElement() = default;
    VertexLayoutElement(VertexElementType type) : type(type) {}
    const VertexElementType type;
    size_t offset;

    [[nodiscard]] size_t getSize() const;
//    size_t getNativeSize() const;
};

struct VertexLayout {
    VertexLayout() = default;

    VertexLayout(std::convertible_to<VertexElementType> auto&& ... args)
    {
        (elements.emplace_back(std::forward<VertexElementType>(args)), ...);
        calculateStrideAndOffsets();
    }

    void pushElement(VertexElementType type) {
        elements.emplace_back(type);
        calculateStrideAndOffsets();
    }

    VertexLayoutElement* getElement(VertexElementType type)
    {
        auto element = std::find_if(elements.begin(), elements.end(),
                            [&type](const auto &elem){
                              return elem.type == type;
                            });
        if (element != elements.end())
        {
            return &(*element);
        }
        return nullptr;
    }

    size_t stride{0};
private:
    std::vector<VertexLayoutElement> elements;
    void calculateStrideAndOffsets();
};

} // namespace Sage
