#include <iostream>

#include "Mesh.h"

#include <fmt/format.h>

using namespace Sage;

int main()
{
    Mesh mesh;

    mesh.vertices = {
        1101, 1102, 1103,   1201, 1202,    1301, 1302, 1303,
        2101, 2102, 2103,   2201, 2202,    2301, 2302, 2303,
        3101, 3102, 3103,   3201, 3202,    3301, 3302, 3303,
    };

    mesh.indices = {
        0,1,2,
        2,1,2,
        2,2,2
    };

    mesh.layout = VertexLayout(VertexElementType::POSITION,
                               VertexElementType::TEXTURE,
                               VertexElementType::NORMAL);

    mesh.iterateVertexElements(VertexElementType::TEXTURE,
        [](auto &textureCoords) {
            for (auto &vn : textureCoords) {
                vn += 10;
            }
        });

    mesh.iterateFaces([](const auto &vertices){
        vertices[2][6] += 20;
    });


    mesh.iterateFacesElements(VertexElementType::NORMAL, [](const auto &elements){
        elements[0][1] += 30;
    });

    return 0;
}
