#pragma once

#include "VertexLayout.h"

#include <filesystem>
#include <ranges>
#include <vector>
#include <span>
#include <functional>
#include <algorithm>
#include <fmt/format.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Sage {

class Mesh
{
public:
    void applyToVertexElements(VertexElementType type,
                               const std::function<
                                       void(std::span<float>&)
                                   > &func);
    void applyToFaces(const std::function<
                              void(const std::vector<std::span<float>>&)
                          > &func);
    void applyToFacesElements(VertexElementType type,
                              const std::function<
                                      void(const std::vector<std::span<float>>&)
                                  > &func);

    double computeVolume();
    glm::vec3 computeCenterOfMass();

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    const int numFaceVertices{3};

    VertexLayout layout;

private:
    double computeTetrahedronVolume(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3);

};

Mesh LoadObj(const std::filesystem::path &filename);

}  // namespace Sage
