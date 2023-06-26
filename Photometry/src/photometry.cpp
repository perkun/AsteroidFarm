#include "GraphicsEngine.h"
#include "LightcurveConfig.h"
#include "PhotometryScene.h"

#include "JsonLoader.h"

using namespace Sage;

int main()
{
    constexpr glm::uvec2 windowSize{256};

    GraphicsEngine graphicsEngine({.width = windowSize.x,
                                   .height = windowSize.y,
                                   .title = "RenderEngine window",
                                   .fullscreen = false,
                                   .visible = false});

    auto config = LoadFromJson<LightcurveSeriesConfig>("data/testLcConfig.json");
    auto &scene = graphicsEngine.pushScene<PhotometryScene>(windowSize, config);
    graphicsEngine.renderScenes();
    // graphicsEngine.updateWindow();

    return 0;
}
