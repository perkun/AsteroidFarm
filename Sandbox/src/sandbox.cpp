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

    mesh.rotateToPrincipalAxes();

    SaveObj(mesh, "data/model_pa.obj");

    return 0;
}
