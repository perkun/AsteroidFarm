#pragma once

#include <string>
#include <filesystem>
#include "AsteroidParams.h"

#include <nlohmann/json.hpp>

namespace Sage {

struct LightcurveConfig
{
    std::filesystem::path modelPath;
    std::filesystem::path vertexShaderPath;
    std::filesystem::path fragmentShaderPath;
    std::string targetName;
    AsteroidParams asteroidParams;
};

void from_json(const nlohmann::json &j, LightcurveConfig &lc);
void to_json(nlohmann::json &j, const LightcurveConfig &lc);

}  // namespace Sage