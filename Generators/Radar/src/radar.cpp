#include "GraphicsEngine.h"
#include "ObservationsConfig.h"
#include "RadarScene.h"

#include "JsonLoader.h"

using namespace AsteroidFarm;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fmt::print("Not enought arguments.\nUSAGE:\n\t{} <config.json>\n", argv[0]);
        return 0;
    }

    std::filesystem::path configFilePath{argv[1]};

    if (not std::filesystem::exists(configFilePath))
    {
        fmt::print("Config file '{}' doesn't exist.\n", configFilePath.string());
        return 0;
    }
    auto config = LoadFromJson<RadarSeriesConfig>(configFilePath);

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
    if (config.exportFolderPath.has_value())
    {
        if (not std::filesystem::exists(config.exportFolderPath.value()))
        {
            fmt::print("outputFolderPath '{}' doesn't exist\n",
                       config.exportFolderPath.value().string());
            return 0;
        }
    }

    constexpr glm::uvec2 windowSize{1024};

    GraphicsEngine graphicsEngine({.width = windowSize.x,
                                   .height = windowSize.y,
                                   .title = "RenderEngine window",
                                   .fullscreen = false,
                                   .visible = false});

    auto &scene = graphicsEngine.pushScene<RadarScene>(windowSize, config);
    graphicsEngine.renderScenes();

    if (config.outputPath.has_value())
    {
        SaveToJson(scene.storage, config.outputPath.value());

        // TODO store data in binary file
        auto binDataPath = config.outputPath.value().replace_extension("bin");
        // ...
    }

    if (config.exportDelayDoppler)
    {
        int idx = 0;
        for (auto &image : scene.storage.images)
        {
            auto filename = fmt::format("{}_{}.png", config.imagePrefix.value(), idx);
            auto filePath = config.exportFolderPath.value() / filename;

            image.exportDelayDoppler(filePath,
                            config.radarImages[idx].imageSize.value(),
                            config.radarImages[idx].imageSize.value());
            idx++;
        }
    }

    return 0;
}
