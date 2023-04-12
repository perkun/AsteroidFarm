#pragma once

#include "VertexLayout.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <filesystem>
#include <fmt/format.h>
#include <functional>
#include <optional>
#include <ranges>
#include <span>
#include <vector>


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

    float getVolume();
    glm::vec3 getCenterOfMass();

    void translateToCenterOfMass();

    void resetMoments();

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    const int numFaceVertices{3};

    VertexLayout layout;

private:
    float computeTetrahedronVolume(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3);
    float computeVolume();
    glm::vec3 computeCenterOfMass();

    std::optional<double> _volume{std::nullopt};
    std::optional<glm::vec3> _centerOfMass{std::nullopt};
};

glm::vec3 &makeVec3Ref(const std::span<float> &span);
Mesh LoadObj(const std::filesystem::path &filename);

}  // namespace Sage
