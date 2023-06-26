#include "LightcurveConfig.h"
#include "AsteroidParams.h"
#include "GlmParser.h"

namespace Sage {

void from_json(const nlohmann::json &j, LightcurveConfig &lc)
{
    lc.numPoints = j.at("numPoints").get<unsigned int>();
    lc.startJd = j.at("startJd").get<JulianDay>();
    lc.targetPosition = j.at("targetPosition").get<glm::vec3>();
    lc.observerPosition = j.at("observerPosition").get<glm::vec3>();
    lc.lightPosition = j.at("lightPosition").get<glm::vec3>();
}

void to_json(nlohmann::json &j, const LightcurveConfig &lc)
{
    // TODO
}

void from_json(const nlohmann::json &j, LightcurveSeriesConfig &lc)
{
    lc.modelPath = j.at("modelPath").get<std::filesystem::path>();
    lc.vertexShaderPath = j.at("vertexShaderPath").get<std::filesystem::path>();
    lc.fragmentShaderPath = j.at("fragmentShaderPath").get<std::filesystem::path>();
    lc.asteroidParams = j.at("asteroidParams").get<AsteroidParams>();
    lc.lightcurves = j.at("lightcurves").get<std::vector<LightcurveConfig>>();

    if (const auto it = j.find("outputPath"); it != j.end())
    {
        lc.outputPath = j.at("outputPath").get<std::filesystem::path>();
    }
}

void to_json(nlohmann::json &j, const LightcurveSeriesConfig &lc)
{
    // TODO
    j = {{"modelPath", lc.modelPath}};
}

}  // namespace Sage
