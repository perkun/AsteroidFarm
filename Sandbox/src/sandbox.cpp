#include <fmt/format.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/pca.hpp>
#include <iostream>

#include "GraphicsEngine.h"
#include "Parsers/JsonLoader.h"
#include "SandboxScene.h"

using namespace Sage;

int main()
{
    constexpr glm::uvec2 windowSize{256};

    GraphicsEngine graphicsEngine({
        .width = windowSize.x,
        .height = windowSize.y,
        .title = "RenderEngine window",
        .fullscreen = false,
        .visible = true
    });

    graphicsEngine.pushScene<SandboxScene>(windowSize);
    graphicsEngine.renderScenes();
    graphicsEngine.updateWindow();
    
    std::vector<float> pixelBuffRed(windowSize.x * windowSize.y);
    std::vector<float> pixelBuffGreen(windowSize.x * windowSize.y);
    std::vector<float> pixelBuffBlue(windowSize.x * windowSize.y);

    glReadPixels(0, 0, windowSize.x, windowSize.y, GL_RED, GL_FLOAT, pixelBuffRed.data());
    glReadPixels(0, 0, windowSize.x, windowSize.y, GL_GREEN, GL_FLOAT, pixelBuffGreen.data());
    glReadPixels(0, 0, windowSize.x, windowSize.y, GL_BLUE, GL_FLOAT, pixelBuffBlue.data());

    SaveToJson(pixelBuffRed, "tests/data/pixelBuffRed_shadow.json");
    SaveToJson(pixelBuffGreen, "tests/data/pixelBuffGreen_shadow.json");
    SaveToJson(pixelBuffBlue, "tests/data/pixelBuffBlue_shadow.json");


    getchar();

    return 0;
}
