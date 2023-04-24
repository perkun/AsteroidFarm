#include <fmt/format.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/pca.hpp>
#include <iostream>

#include "Mesh.h"
#include "Observations.h"
#include "Parsers/JsonLoader.h"
#include "GraphicsEngine.h"
// #include "AsteroidParams.h"

using namespace Sage;

int main()
{
    GraphicsEngine graphicsEngine;    
    auto &scene = graphicsEngine.getScene();

    auto asteroid = scene.createEntity();

    getchar();

    return 0;
}
