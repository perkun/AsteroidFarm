#include "GraphicsEngine.h"
#include "ObservationsConfig.h"
#include "AOScene.h"

#include "JsonLoader.h"

using namespace Sage;


int main(int argc, char *argv[])
{
    // if (argc < 2)
    // {
    //     fmt::print("Not enought arguments.\nUSAGE:\n\t{} <config.json>\n", argv[0]);
    //     return 0;
    // }

    // std::filesystem::path configFilePath{argv[1]};

    // if (not std::filesystem::exists(configFilePath))
    // {
    //     fmt::print("Config file '{}' doesn't exist.\n", configFilePath.string());
    //     return 0;
    // }
    auto config = LoadFromJson<AOSeriesConfig>("data/testAoConfig.json");

    if (not std::filesystem::exists(config.scene.modelPath))
    {
        fmt::print("modelPath '{}' doesn't exist\n", config.scene.modelPath.string());
        return 0;
    }

    if (not std::filesystem::exists(config.scene.vertexShaderPath))
    {
        fmt::print("vertexShaderPath '{}' doesn't exist\n", config.scene.modelPath.string());
        return 0;
    }

    if (not std::filesystem::exists(config.scene.fragmentShaderPath))
    {
        fmt::print("fragmentShaderPath '{}' doesn't exist\n", config.scene.modelPath.string());
        return 0;
    }

    constexpr glm::uvec2 windowSize{512};

    GraphicsEngine graphicsEngine({.width = windowSize.x,
                                   .height = windowSize.y,
                                   .title = "RenderEngine window",
                                   .fullscreen = false,
                                   .visible = true});

    auto &scene = graphicsEngine.pushScene<AOScene>(windowSize, config);
    graphicsEngine.renderScenes();
    graphicsEngine.updateWindow();
    getchar();

    SaveToJson(config, "data/aoConfigOut.json");

    // if (config.outputPath)
    // {
    //     SaveToJson(scene.syntheticObs, config.outputPath.value());
    // }

    return 0;
}
