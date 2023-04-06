#include <iostream>

#include "Mesh.h"

int main()
{
    std::cout << "Hello Sage!\n";

    Sage::Mesh mesh;

    mesh.indices.reserve(100);

    return 0;
}
