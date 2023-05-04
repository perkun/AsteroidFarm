#include "LightcurveConfig.h"
#include "AsteroidParams.h"

namespace Sage {

void from_json(const nlohmann::json &j, LightcurveConfig &lc)
{
    lc.modelPath = j.at("modelPath").get<std::filesystem::path>();
    lc.vertexShaderPath = j.at("vertexShaderPath").get<std::filesystem::path>();
    lc.fragmentShaderPath = j.at("fragmentShaderPath").get<std::filesystem::path>();
    lc.targetName = j.at("targetName").get<std::string>();
    lc.asteroidParams = j.at("asteroidParams").get<AsteroidParams>();
}

void to_json(nlohmann::json &j, const LightcurveConfig &lc)
{
    j = {{"modelPath", lc.modelPath}};
}

}  // namespace Sage