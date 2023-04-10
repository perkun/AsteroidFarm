//
// Created by perkun on 04.04.23.
//

#include "Mesh.h"

#include <string>
#include <fmt/format.h>
#include <fstream>

namespace Sage {

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
            indices.emplace_back(a);
            indices.emplace_back(b);
            indices.emplace_back(c);
        }
    }
    mesh.vertices = positions;
    mesh.indices = indices;

    // TODO do it while parsing, and recognize other elements
    mesh.layout.pushElement(VertexElementType::POSITION);

    return mesh;
}

void Mesh::iterateVertexElements(
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
void Mesh::iterateFaces(
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
void Mesh::iterateFacesElements(
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
}  // namespace Sage
