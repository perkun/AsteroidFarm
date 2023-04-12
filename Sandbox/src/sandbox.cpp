#include <iostream>

#include "Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fmt/format.h>


using namespace Sage;

int main()
{
    std::vector<float> vec{1,2,3,4,5,6,7,8,9};
    std::span<float> s{vec.begin() + 2, 3}; // 3,4,5

    // glm::vec3 *v = (glm::vec3*)(s.data());
    glm::vec3 v = *(reinterpret_cast<glm::vec3*>(s.data()));


    return 0;
}
