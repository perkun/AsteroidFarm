//#include <fmt/format.h>
//
//#include <chrono>
//#include <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/pca.hpp>
//#include <iostream>
//#include <iomanip>
//
//#include "GraphicsEngine.h"
//#include "Parsers/JsonLoader.h"
//#include "SandboxScene.h"

// #include "Time.h"
#include "Units.h"

using namespace Sage;

int main()
{
    // constexpr glm::uvec2 windowSize{256};

    // GraphicsEngine graphicsEngine({
    //     .width = windowSize.x,
    //     .height = windowSize.y,
    //     .title = "RenderEngine window",
    //     .fullscreen = false,
    //     .visible = false
    // });

    // graphicsEngine.pushScene<SandboxScene>(windowSize);
    // graphicsEngine.renderScenes();
    // graphicsEngine.updateWindow();

    // std::vector<float> pixelBuffRed(windowSize.x * windowSize.y);
    // std::vector<float> pixelBuffGreen(windowSize.x * windowSize.y);
    // std::vector<float> pixelBuffBlue(windowSize.x * windowSize.y);

    // glReadPixels(0, 0, windowSize.x, windowSize.y, GL_RED, GL_FLOAT, pixelBuffRed.data());
    // glReadPixels(0, 0, windowSize.x, windowSize.y, GL_GREEN, GL_FLOAT, pixelBuffGreen.data());
    // glReadPixels(0, 0, windowSize.x, windowSize.y, GL_BLUE, GL_FLOAT, pixelBuffBlue.data());

    // SaveToJson(pixelBuffRed, "tests/data/pixelBuffRed_shadow.json");
    // SaveToJson(pixelBuffGreen, "tests/data/pixelBuffGreen_shadow.json");
    // SaveToJson(pixelBuffBlue, "tests/data/pixelBuffBlue_shadow.json");


    // getchar();
    // auto sysNow = std::chrono::system_clock::now();
    // auto t = std::chrono::system_clock::to_time_t(sysNow);
    // auto tm = *std::localtime(&t);
    // std::cout << std::put_time(&tm, "%F %T") << std::endl;

    using namespace UnitLiterals;
    Angle a = -120.0_deg;
    Angle b = -3_rad;

    auto c = a + b;


    return 0;
}
