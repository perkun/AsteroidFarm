#pragma once
#include <fmt/format.h>

#include <algorithm>
#include <filesystem>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/pca.hpp>
#include <optional>
#include <ranges>
#include <span>
#include <vector>

#include "VertexLayout.h"

namespace Sage {

class Mesh
{
public:
    void applyToVertexElements(
        VertexElementType type,
        const std::function<void(std::span<float> &)> &func);
    void applyToFaces(
        const std::function<void(const std::vector<std::span<float>> &)> &func);
    void applyToFacesElements(
        VertexElementType type,
        const std::function<void(const std::vector<std::span<float>> &)> &func);

    float getVolume();
    glm::vec3 getCenterOfMass();
    glm::mat3 getInertia();

    void translateToCenterOfMass();
    void rotateToPrincipalAxes();


    void resetMoments();

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    const int numFaceVertices{3};

    VertexLayout layout;

private:
    float computeTetrahedronVolume(const glm::vec3 &v1, const glm::vec3 &v2,
                                   const glm::vec3 &v3);
    float computeVolume();
    glm::vec3 computeCenterOfMass();
    glm::mat3 computeInertia();

    void computeNormals();

    struct Moments
    {
        std::optional<double> volume{std::nullopt};
        std::optional<glm::vec3> centerOfMass{std::nullopt};
        std::optional<glm::mat3> inertia{std::nullopt};
    };
    Moments _moments;
};

glm::vec3 &makeVec3Ref(const std::span<float> &span);
Mesh LoadObj(const std::filesystem::path &filename);
void SaveObj(Mesh &mesh, const std::filesystem::path &filename);

}  // namespace Sage
