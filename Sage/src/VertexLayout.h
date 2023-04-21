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

struct VertexLayoutElement
{
    VertexLayoutElement() = delete;
    explicit VertexLayoutElement(VertexElementType type);

    const VertexElementType type;
    const size_t size;
    const size_t nativeSize;

    size_t offset{0};

private:
    [[nodiscard]] size_t getSize(VertexElementType type) const;
    [[nodiscard]] size_t getNativeSize(VertexElementType type) const;
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

    const VertexLayoutElement* getElement(VertexElementType type) const
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
