#include <iostream>

#include "Mesh.h"

#include <fmt/format.h>

using namespace Sage;

int main()
{
    auto mesh = LoadObj("data/model_shifted.obj");

    fmt::print("num vertices: {}, num indices: {}\n", mesh.vertices.size(), mesh.indices.size());
    fmt::print("num points: {}, num triangles: {}\n", mesh.vertices.size()/3, mesh.indices.size()/3);

    return 0;
}
