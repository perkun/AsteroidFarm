#include "GraphicsEngine.h"
#include "RenderingTestScene.h"
#include "Parsers/JsonLoader.h"

#include <gtest/gtest.h>

using namespace Sage;

TEST(Rendering, RenderAsteroid)
{
    constexpr glm::uvec2 windowSize{256};

    GraphicsEngine graphicsEngine{{.width = windowSize.x,
                                   .height = windowSize.y,
                                   .title = "RenderEngine window",
                                   .fullscreen = false,
                                   .visible = false}};

    auto &scene = graphicsEngine.pushScene<RenderingTestScene>(windowSize);
    graphicsEngine.renderScenes();

    std::vector<float> pixelBuffRed(windowSize.x * windowSize.y);
    std::vector<float> pixelBuffGreen(windowSize.x * windowSize.y);
    std::vector<float> pixelBuffBlue(windowSize.x * windowSize.y);

    glReadPixels(0, 0, windowSize.x, windowSize.y, GL_RED, GL_FLOAT, pixelBuffRed.data());
    glReadPixels(0, 0, windowSize.x, windowSize.y, GL_GREEN, GL_FLOAT, pixelBuffGreen.data());
    glReadPixels(0, 0, windowSize.x, windowSize.y, GL_BLUE, GL_FLOAT, pixelBuffBlue.data());

    auto expectedPixelBuffRed = LoadFromJson<std::vector<float>>("data/pixelBuffRed.json");
    auto expectedPixelBuffGreen = LoadFromJson<std::vector<float>>("data/pixelBuffGreen.json");
    auto expectedPixelBuffBlue = LoadFromJson<std::vector<float>>("data/pixelBuffBlue.json");

    EXPECT_EQ(expectedPixelBuffRed, pixelBuffRed);
    EXPECT_EQ(expectedPixelBuffGreen, pixelBuffGreen);
    EXPECT_EQ(expectedPixelBuffBlue, pixelBuffBlue);
}