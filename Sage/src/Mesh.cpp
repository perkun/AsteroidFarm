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

    for (int vertexBegin = 0; vertexBegin < vertices.size(); vertexBegin += layout.stride) 
    {
        std::span<float> vertexElement{
            vertices.begin() + vertexBegin + layoutElementIt->offset,
            layoutElementIt->size};
        func(vertexElement);
    }
}

void Mesh::applyToFaces(
    const std::function<void(const std::vector<std::span<float>> &)> &func)
{
    for (int faceBegin = 0; faceBegin < indices.size(); faceBegin += verticesPerFace) {
        std::vector<std::span<float>> faceVertices;
        faceVertices.reserve(verticesPerFace);

        for (int i = 0; i < verticesPerFace; i++) {
            auto &vertexIndex = *(indices.begin() + faceBegin + i);
            faceVertices.emplace_back(getVertex(vertexIndex));
        }

        func(faceVertices);
    }
}

void Mesh::applyToFacesElements(
    VertexElementType type,
    const std::function<void(const std::vector<std::span<float>> &)> &func)
{
    for (int faceBegin = 0; faceBegin < indices.size(); faceBegin += verticesPerFace) 
    {
        std::vector<std::span<float>> faceVertices;
        faceVertices.reserve(verticesPerFace);

        for (int i = 0; i < verticesPerFace; i++) 
        {
            auto &vertexIndex = *(indices.begin() + faceBegin + i);
            faceVertices.emplace_back(getVertexElement(type, vertexIndex));
        }

        func(faceVertices);
    }
}

void Mesh::applyToFacesIndices(std::function<void(const std::span<unsigned int> &)> func)
{
    for (int i = 0; i < indices.size(); i += verticesPerFace)
    {
        func({indices.begin() + i, verticesPerFace});
    }
}

std::span<float> Mesh::getVertex(int index)
{
    if (index >= vertices.size() / layout.stride)
    {
        // TODO introduce proper logging. Throw exeption here
        fmt::print("Index out of bounds");
        return {};
    }

    return {vertices.begin() + (index * layout.stride), layout.stride};
}

std::span<float> Mesh::getVertexElement(VertexElementType type, int index)
{
    const auto layoutElementIt = layout.getElement(type);
    if (!layoutElementIt) {
        // TODO introduce proper logging
        fmt::print("Vertex Layout Element Not found in Mesh");
        return {};
    }

    auto vertex = getVertex(index);
    return {vertex.begin() + layoutElementIt->offset, layoutElementIt->size};
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

void Mesh::rotateToPrincipalAxes()
{
    translateToCenterOfMass();
    auto inertia = getInertia();

    glm::vec3 eigenValues;
    glm::mat3 eigenVectors;

    glm::findEigenvaluesSymReal(inertia, eigenValues, eigenVectors);
    glm::sortEigenvalues(eigenValues, eigenVectors);

    // flip the matrix, because of reverse sorting
    glm::mat3 rotMatrixTmp;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            rotMatrixTmp[i][j] = eigenVectors[2 - i][j];
        }
    }
    // See if the Z axis has not been twisted by more than 90 deg
    // (0,0,1)*Q*(0,0,1)^T must be > 0 (i.e. Q[2][2] > 0 )
    // if not - change the sign of the last row
    if (rotMatrixTmp[2][2] < 0) {
        rotMatrixTmp[2] *= -1.0;
    }
    // Moderate the rotation of X axis to less than 90 deg
    // (1,0,0)*Q*(1,0,0)^T must be > 0
    if (rotMatrixTmp[0][0] < 0) {
        rotMatrixTmp[0] *= -1.0;
    }

    // vcs matrix is O(3) by definition, but we need it to be SO(3).
    // Multiply the second row by (-1) if it is not (adjust Y axis)
    auto dz = glm::determinant(rotMatrixTmp);
    if (dz < 0.0) {
        rotMatrixTmp[1] *= -1.0;
    }

    // row-major to column-major transformation
    glm::mat3 rotMatrix;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            rotMatrix[i][j] = rotMatrixTmp[j][i];
        }
    }

    applyToVertexElements(VertexElementType::POSITION, [&rotMatrix](auto &vertex)
    {
                              auto &v = makeVec3Ref(vertex);
                              v = rotMatrix * v;
    });

    resetMoments();
    computeNormals();
}

// TODO finish this...
// need to add face indices as parameters to lambdas in applyToFaces*
// this could be done in sharder during rendering anyways...
void Mesh::computeNormals()
{
    std::vector<float> newVertices(vertices.size() * 2, 0.0f);
    VertexLayout newLayout{VertexElementType::POSITION, VertexElementType::NORMAL};

    auto positionElementIt = newLayout.getElement(VertexElementType::POSITION);
    auto normalElementIt = newLayout.getElement(VertexElementType::NORMAL);

    applyToFacesIndices([&](auto &faceIndices)
    {
        auto &v1 = makeVec3Ref(getVertexElement(VertexElementType::POSITION, faceIndices[0]));
        auto &v2 = makeVec3Ref(getVertexElement(VertexElementType::POSITION, faceIndices[1]));
        auto &v3 = makeVec3Ref(getVertexElement(VertexElementType::POSITION, faceIndices[2]));

        glm::vec3 v12 = v2 - v1;
        glm::vec3 v13 = v3 - v1;
        glm::vec3 normal = glm::normalize(glm::cross(v12, v13));

        size_t vertexBegin1 = faceIndices[0] * newLayout.stride;
        size_t vertexBegin2 = faceIndices[1] * newLayout.stride;
        size_t vertexBegin3 = faceIndices[2] * newLayout.stride;

        for (int i = 0; i < positionElementIt->size; i++)
        {
            newVertices.at(vertexBegin1 + positionElementIt->offset + i) = v1[i];
            newVertices.at(vertexBegin2 + positionElementIt->offset + i) = v2[i];
            newVertices.at(vertexBegin3 + positionElementIt->offset + i) = v3[i];
        }

        for (int i = 0; i < normalElementIt->size; i++)
        {
            newVertices.at(vertexBegin1 + normalElementIt->offset + i) += normal[i];
            newVertices.at(vertexBegin2 + normalElementIt->offset + i) += normal[i];
            newVertices.at(vertexBegin3 + normalElementIt->offset + i) += normal[i];
        }
    });

    vertices = newVertices;
    layout = std::move(newLayout);

    applyToVertexElements(VertexElementType::NORMAL, [](auto &normal) 
    {
        auto &n = makeVec3Ref(normal);
        n = glm::normalize(n);
    });
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

    applyToFacesElements(VertexElementType::POSITION, [&products,
                                                       this](auto &faces) {
        const auto &v1 = makeVec3Ref(faces[0]);
        const auto &v2 = makeVec3Ref(faces[1]);
        const auto &v3 = makeVec3Ref(faces[2]);

        auto volume = computeTetrahedronVolume(v1, v2, v3);

        for (int k = 0; k < 3; k++) {
            for (int j = k; j < 3; j++) {
                products[k][j] +=
                volume / 20. *
                (2 * v1[k] * v1[j] + 2 * v2[k] * v2[j] + 2 * v3[k] * v3[j] +
                 v1[k] * v2[j] + v1[j] * v2[k] + v1[k] * v3[j] +
                 v1[j] * v3[k] + v2[k] * v3[j] + v2[j] * v3[k]);
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

Mesh Mesh::loadFromObj(const std::filesystem::path &filename)
{
    Mesh mesh;

    // NOTE for now only v and f will be supported

    std::ifstream objFile(filename);
    if (not objFile.is_open()) {
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

void Mesh::saveToObj(Mesh &mesh, const std::filesystem::path &filename)
{
    std::ofstream objFile(filename);
    if (not objFile.is_open()) {
        fmt::print("Could not open file.\n");
        return;
    }

    mesh.applyToVertexElements(VertexElementType::POSITION, [&objFile](const auto &position) 
    {
        objFile << "v " << position[0] << " " << position[1] << " " << position[2] << "\n";
    });

    mesh.applyToVertexElements(VertexElementType::NORMAL, [&objFile](const auto &normal) 
    {
        objFile << "vn " << normal[0] << " " << normal[1] << " " << normal[2] << "\n";
    });

    for (int i = 0; i < mesh.indices.size(); i += mesh.verticesPerFace) {
        objFile << "f";
        for (int j = 0; j < mesh.verticesPerFace; j++) {
            objFile << " " << mesh.indices[i + j] + 1;
        }
        objFile << "\n";
    }
}

}  // namespace Sage
