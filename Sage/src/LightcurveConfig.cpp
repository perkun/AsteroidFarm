#include "LightcurveConfig.h"
#include "AsteroidParams.h"
#include "GlmParser.h"

namespace Sage {

void from_json(const nlohmann::json &j, LightcurveConfig &lc)
{
    lc.modelPath = j.at("modelPath").get<std::filesystem::path>();
    lc.vertexShaderPath = j.at("vertexShaderPath").get<std::filesystem::path>();
    lc.fragmentShaderPath = j.at("fragmentShaderPath").get<std::filesystem::path>();
    lc.targetName = j.at("targetName").get<std::string>();
    lc.startJd = j.at("startJd").get<JulianDay<Units::Day>>();
    lc.asteroidParams = j.at("asteroidParams").get<AsteroidParams>();
    lc.targetPosition = j.at("targetPosition").get<glm::vec3>();
    lc.observerPosition = j.at("observerPosition").get<glm::vec3>();
    lc.lightPosition = j.at("lightPosition").get<glm::vec3>();

    if (const auto it = j.find("outputPath");
        it != j.end())
    {
        lc.outputPath = j.at("outputPath").get<std::filesystem::path>();
    }

    lc.asteroidParams.setRotPhase(lc.startJd);
}

void to_json(nlohmann::json &j, const LightcurveConfig &lc)
{
    j = {{"modelPath", lc.modelPath}};
}

}  // namespace Sage