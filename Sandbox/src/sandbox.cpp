#include <iostream>

#include "Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fmt/format.h>


using namespace Sage;

int main()
{
    auto mesh = LoadObj("data/model_shifted.obj");
    mesh.translateToCenterOfMass();
    auto inertia = mesh.getInertia();

    float x = 1.0;
    for (int i = 0; i < 3; i++)
    {
        fmt::print("{} {} {}\n", inertia[i][0]/x, inertia[i][1]/x, inertia[i][2]/x);
    }
    
    x = inertia[2][2];
    fmt::print("Reduction by I_zz = {}\n", x);
    for (int i = 0; i < 3; i++)
    {
        fmt::print("{} {} {}\n", inertia[i][0]/x, inertia[i][1]/x, inertia[i][2]/x);
    }

    return 0;
}
