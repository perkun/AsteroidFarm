#pragma once

#include <filesystem>
#include <ranges>
#include <vector>
#include <span>
#include <functional>
#include <algorithm>
#include <fmt/format.h>

#include "VertexLayout.h"

namespace Sage {

struct Mesh
{
    void iterateVertexElements(VertexElementType type, const std::function<void(std::span<float>&)> &func);
    void iterateFaces(const std::function<void(const std::vector<std::span<float>>&)> &func);
    void iterateFacesElements(VertexElementType type,
                              const std::function<void(const std::vector<std::span<float>>&)> &func);

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    const int numFaceVertices{3};

    VertexLayout layout;
};

Mesh LoadObj(const std::filesystem::path &filename);

}  // namespace Sage
