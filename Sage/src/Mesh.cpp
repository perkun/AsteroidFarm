#include "Mesh.h"

#include <fmt/format.h>
#include <math.h>

#include <fstream>
#include <string>

#include "VertexLayout.h"

namespace Sage {

void Mesh::applyToVertexElements(
    VertexElementType type, const std::function<void(std::span<float> &)> &func)
{
    const auto layoutElementIt = layout.getElement(type);
    if (!layoutElementIt) {
        // TODO introduce proper logging
        fmt::print("Vertex Layout Element Not found in Mesh");
        return;
    }

    for (int vertexBegin = 0; vertexBegin < vertices.size();
         vertexBegin += layout.stride) {
        std::span<float> vertexElement{
            vertices.begin() + vertexBegin + layoutElementIt->offset,
            layoutElementIt->size};
        func(vertexElement);
    }
}
void Mesh::applyToFaces(
    const std::function<void(const std::vector<std::span<float>> &)> &func)
{
    for (int faceBegin = 0; faceBegin < indices.size();
         faceBegin += numFaceVertices) {
        std::vector<std::span<float>> faceVertices;
        faceVertices.reserve(numFaceVertices);

        for (int i = 0; i < numFaceVertices; i++) {
            auto &vertexIndex = *(indices.begin() + faceBegin + i);
            faceVertices.emplace_back(
                vertices.begin() + (vertexIndex * layout.stride),
                layout.stride);
        }

        func(faceVertices);
    }
}
void Mesh::applyToFacesElements(
    VertexElementType type,
    const std::function<void(const std::vector<std::span<float>> &)> &func)
{
    const auto layoutElement = layout.getElement(type);
    if (!layoutElement) {
        // TODO introduce proper logging
        fmt::print("Vertex Layout Element Not found in Mesh");
        return;
    }

    for (int faceBegin = 0; faceBegin < indices.size();
         faceBegin += numFaceVertices) {
        std::vector<std::span<float>> faceVertices;
        faceVertices.reserve(numFaceVertices);

        for (int i = 0; i < numFaceVertices; i++) {
            auto &vertexIndex = *(indices.begin() + faceBegin + i);
            faceVertices.emplace_back(vertices.begin() +
                                          (vertexIndex * layout.stride) +
                                          layoutElement->offset,
                                      layoutElement->size);
        }

        func(faceVertices);
    }
}

float Mesh::getVolume()
{
    if (not _moments.volume.has_value()) {
        _moments.volume = computeVolume();
    }
    return _moments.volume.value();
}

glm::vec3 Mesh::getCenterOfMass()
{
    if (not _moments.centerOfMass.has_value()) {
        _moments.centerOfMass = computeCenterOfMass();
    }
    return _moments.centerOfMass.value();
}

glm::mat3 Mesh::getInertia()
{
    if (not _moments.inertia.has_value()) {
        _moments.inertia = computeInertia();
    }
    return _moments.inertia.value();
}

void Mesh::translateToCenterOfMass()
{
    auto centerOfMass = getCenterOfMass();
    applyToVertexElements(VertexElementType::POSITION,
                          [&centerOfMass](auto &vertex) {
                              auto &v = makeVec3Ref(vertex);
                              v -= centerOfMass;
                          });
    resetMoments();
}

// TODO think about when and who should reset those, or event if cashing should
// be done at all (it might introduce bugs...).
void Mesh::resetMoments() { _moments = Moments{}; }

float Mesh::computeTetrahedronVolume(const glm::vec3 &v1, const glm::vec3 &v2,
                                     const glm::vec3 &v3)
{
    return 1. / 6. * glm::dot(glm::cross(v1, v2), v3);
}

float Mesh::computeVolume()
{
    double volume{0.f};

    applyToFacesElements(VertexElementType::POSITION,
                         [&volume, this](auto &faces) {
                             glm::vec3 v1 = glm::make_vec3(faces[0].data());
                             glm::vec3 v2 = glm::make_vec3(faces[1].data());
                             glm::vec3 v3 = glm::make_vec3(faces[2].data());

                             volume += computeTetrahedronVolume(v1, v2, v3);
                         });

    return volume;
}

glm::vec3 Mesh::computeCenterOfMass()
{
    glm::vec3 centerOfMass(0.f);
    float volume{0.f};

    applyToFacesElements(VertexElementType::POSITION, [&centerOfMass, &volume,
                                                       this](auto &faces) {
        glm::vec3 v1 = glm::make_vec3(faces[0].data());
        glm::vec3 v2 = glm::make_vec3(faces[1].data());
        glm::vec3 v3 = glm::make_vec3(faces[2].data());

        glm::vec3 centroid = (v1 + v2 + v3) / 4.0f;
        float tetrahedronVolume = computeTetrahedronVolume(v1, v2, v3);

        centerOfMass += centroid * tetrahedronVolume;
        volume += tetrahedronVolume;
    });

    return centerOfMass / volume;
}

glm::mat3 Mesh::computeInertia()
{
    glm::mat3 products{0};

    applyToFacesElements(VertexElementType::POSITION, [&products, this](auto &faces) 
    {
        const auto &v1 = makeVec3Ref(faces[0]);
        const auto &v2 = makeVec3Ref(faces[1]);
        const auto &v3 = makeVec3Ref(faces[2]);

        auto volume = computeTetrahedronVolume(v1, v2, v3);


        // 00 01 02
        // 10 11 12
        // 20 21 22
        for (int j = 0; j < 3; j++)
        {
            for (int k = j; k < 3; k++)
            {
                products[j][k] += volume/20. * (
                    2*v1[j]*v1[k] + 2*v2[j]*v2[k] + 2*v3[j]*v3[k]
                    + v1[j]*v2[k] + v1[k]*v2[j] 
                    + v1[j]*v3[k] + v1[k]*v3[j]
                    + v2[j]*v3[k] + v2[k]*v3[j]
                );
            }
        }


    });

    glm::mat3 inertia;
    inertia[0][0] = products[1][1] + products[2][2];
    inertia[1][1] = products[0][0] + products[2][2];
    inertia[2][2] = products[0][0] + products[1][1];

    inertia[1][2] = -products[1][2];
    inertia[0][2] = -products[0][2];
    inertia[0][1] = -products[0][1];

    inertia[2][1] = inertia[1][2];
    inertia[2][0] = inertia[0][2];
    inertia[1][0] = inertia[0][1];

    return inertia;
}

glm::vec3 &makeVec3Ref(const std::span<float> &span)
{
    return *(reinterpret_cast<glm::vec3 *>(span.data()));
}

Mesh LoadObj(const std::filesystem::path &filename)
{
    Mesh mesh;

    // for now only v and f will be supported

    std::ifstream objFile(filename);
    if (!objFile.is_open()) {
        fmt::print("Could not open file.\n");
        return {};
    }

    std::vector<float> positions;
    positions.reserve(50000);
    std::vector<unsigned int> indices;
    indices.reserve(100000);

    std::string line;
    while (std::getline(objFile, line)) {
        if (line[0] == 'v' && (line[1] == ' ' || line[1] == '\t')) {
            float x, y, z;
            sscanf(line.c_str(), "%*s %f %f %f", &x, &y, &z);
            positions.emplace_back(x);
            positions.emplace_back(y);
            positions.emplace_back(z);
        }
        if (line[0] == 'f' && (line[1] == ' ' || line[1] == '\t')) {
            int a, b, c;
            sscanf(line.c_str(), "%*s %d %d %d", &a, &b, &c);
            indices.emplace_back(a - 1);
            indices.emplace_back(b - 1);
            indices.emplace_back(c - 1);
        }
    }
    mesh.vertices = positions;
    mesh.indices = indices;

    // TODO do it while parsing, and recognize other elements
    mesh.layout.pushElement(VertexElementType::POSITION);

    return mesh;
}

}  // namespace Sage
