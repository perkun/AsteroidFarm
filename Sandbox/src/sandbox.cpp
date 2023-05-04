//#include <fmt/format.h>
//
//#include <chrono>
//#include <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/pca.hpp>
//#include <iostream>
//#include <iomanip>
//
#include "GraphicsEngine.h"
#include "LightcurveConfig.h"
#include "SandboxScene.h"

#include "JsonLoader.h"
#include "AsteroidParams.h"
#include "Time.h"

using namespace Sage;

int main()
{
    constexpr glm::uvec2 windowSize{256};

    GraphicsEngine graphicsEngine({
        .width = windowSize.x,
        .height = windowSize.y,
        .title = "RenderEngine window",
        .fullscreen = false,
        .visible = false
    });

    auto config = LoadFromJson<LightcurveConfig>("data/testLcConfig.json");
    auto &scene = graphicsEngine.pushScene<SandboxScene>(windowSize, config);
    graphicsEngine.renderScenes();
    // graphicsEngine.updateWindow();

    SaveToJson(scene.syntheticObs, "data/testLc.json");


    return 0;
}
