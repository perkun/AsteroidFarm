#include <iostream>

#include "Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fmt/format.h>


using namespace Sage;

int main()
{
    auto mesh = LoadObj("data/model_shifted.obj");
    fmt::print("Voulume: {}\n", mesh.computeVolume());

    return 0;
}
