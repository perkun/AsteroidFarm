#include "Mesh.h"

#include <string>
#include <fmt/format.h>
#include <fstream>
#include "VertexLayout.h"


namespace Sage {

void Mesh::applyToVertexElements(
    VertexElementType type, const std::function<void(std::span<float> &)> &func)
{
    const auto layoutElementIt = layout.getElement(type);
    if (!layoutElementIt)
    {
        // TODO introduce proper logging
        fmt::print("Vertex Layout Element Not found in Mesh");
        return;
    }


    for (int vertexBegin = 0; vertexBegin < vertices.size(); vertexBegin += layout.stride)
    {
        std::span<float> vertexElement{vertices.begin() + vertexBegin + layoutElementIt->offset,
                                       layoutElementIt->size};
        func(vertexElement);
    }

}
void Mesh::applyToFaces(
    const std::function<void(const std::vector<std::span<float>> &)> &func)
{
    for (int faceBegin = 0; faceBegin < indices.size(); faceBegin += numFaceVertices)
    {
        std::vector<std::span<float>> faceVertices;
        faceVertices.reserve(numFaceVertices);

        for (int i = 0; i < numFaceVertices; i++)
        {
            auto &vertexIndex = *(indices.begin() + faceBegin + i);
            faceVertices.emplace_back(vertices.begin() + (vertexIndex * layout.stride), layout.stride);
        }

        func(faceVertices);
    }
}
void Mesh::applyToFacesElements(
    VertexElementType type,
    const std::function<void(const std::vector<std::span<float>> &)> &func)
{
    const auto layoutElement = layout.getElement(type);
    if (!layoutElement)
    {
        // TODO introduce proper logging
        fmt::print("Vertex Layout Element Not found in Mesh");
        return;
    }

    for (int faceBegin = 0; faceBegin < indices.size(); faceBegin += numFaceVertices)
    {
        std::vector<std::span<float>> faceVertices;
        faceVertices.reserve(numFaceVertices);

        for (int i = 0; i < numFaceVertices; i++)
        {
            auto &vertexIndex = *(indices.begin() + faceBegin + i);
            faceVertices.emplace_back(vertices.begin() + (vertexIndex * layout.stride) +
                                          layoutElement->offset,
                                      layoutElement->size);
        }

        func(faceVertices);
    }
}

float Mesh::getVolume()
{
    if (not _volume.has_value())
    {
        _volume = computeVolume();
    }
    return _volume.value();
}

glm::vec3 Mesh::getCenterOfMass()
{
    if (not _centerOfMass.has_value())
    {
        _centerOfMass = computeCenterOfMass();
    }
    return _centerOfMass.value();
}

void Mesh::translateToCenterOfMass()
{
    auto centerOfMass = getCenterOfMass();
    applyToVertexElements(VertexElementType::POSITION, [&centerOfMass](auto &vertex)
    {
        auto &v = makeVec3Ref(vertex);
        v -= centerOfMass;
    });
    resetMoments();
}

// TODO think about when and who should reset those, or event if cashing should
// be done at all (it might introduce bugs...).
void Mesh::resetMoments()
{
    _volume = std::nullopt;
    _centerOfMass = std::nullopt;
}

float Mesh::computeTetrahedronVolume(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3)
{
    return 1./6. * glm::dot( glm::cross(v1, v2), v3);
}

float Mesh::computeVolume()
{
    double volume{0.f};

    applyToFacesElements(VertexElementType::POSITION, [&volume, this](auto &faces)
    {
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

    applyToFacesElements(VertexElementType::POSITION, [&centerOfMass, &volume, this](auto &faces)
    {
        glm::vec3 v1 = glm::make_vec3(faces[0].data());
        glm::vec3 v2 = glm::make_vec3(faces[1].data());
        glm::vec3 v3 = glm::make_vec3(faces[2].data());

        glm::vec3 centroid = (v1 + v2 + v3) / 4.0f;
        float tetrahedronVolume = computeTetrahedronVolume(v1, v2, v3);

        centerOfMass += centroid * tetrahedronVolume;
        volume += tetrahedronVolume;
    });

    return centerOfMass/volume;
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
    if (!objFile.is_open())
    {
        fmt::print("Could not open file.\n");
        return {};
    }

    std::vector<float> positions;
    positions.reserve(50000);
    std::vector<unsigned int> indices;
    indices.reserve(100000);

    std::string line;
    while (std::getline(objFile, line))
    {
        if (line[0] == 'v' && (line[1] == ' ' || line[1] == '\t'))
        {
            float x, y, z;
            sscanf(line.c_str(), "%*s %f %f %f", &x, &y, &z);
            positions.emplace_back(x);
            positions.emplace_back(y);
            positions.emplace_back(z);
        }
        if (line[0] == 'f' && (line[1] == ' ' || line[1] == '\t'))
        {
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
