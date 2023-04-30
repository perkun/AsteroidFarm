#include <fmt/format.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/pca.hpp>
#include <iostream>

#include "GraphicsEngine.h"
#include "SandboxScene.h"

using namespace Sage;

int main()
{
    constexpr glm::uvec2 windowSize{600};

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

    getchar();

    return 0;
}
