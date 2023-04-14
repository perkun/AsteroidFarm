#include <fmt/format.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/pca.hpp>
#include <iostream>

#include "Mesh.h"

using namespace Sage;

int main()
{
    auto mesh = LoadObj("data/model_shifted.obj");

//     mesh.translateToCenterOfMass();
//     auto inertia = mesh.getInertia();
//
//     for (int i = 0; i < 3; i++)
//     {
//         for (int j = 0; j < 3; j++)
//         {
//             fmt::print("{}\t", inertia[i][j]);
//         }
//         fmt::print("\n");
//     }

    mesh.rotateToPrincipalAxes();
    SaveObj(mesh, "data/model_pa.obj");

    return 0;
}
