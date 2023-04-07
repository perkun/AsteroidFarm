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
    mesh.layout.elements.push_back({VertexLayoutElement{.type= VertexType::POSITION}});

    // TODO do it after evety push back in VertexLayout?
    mesh.layout.calculateStrideAndOffsets();

    return mesh;
}

}  // namespace Sage
