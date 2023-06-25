#pragma once

#include "AsteroidParams.h"
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>

#include <string>
#include <filesystem>
#include <optional>

namespace Sage {

struct LightcurveConfig
{
    std::filesystem::path modelPath;
    std::filesystem::path vertexShaderPath;
    std::filesystem::path fragmentShaderPath;
    std::string targetName;
    unsigned int numPoints;
    JulianDay startJd;
    AsteroidParams asteroidParams;
    glm::vec3 observerPosition;
    glm::vec3 targetPosition;
    glm::vec3 lightPosition;
    std::optional<std::filesystem::path> outputPath;
};

void from_json(const nlohmann::json &j, LightcurveConfig &lc);
void to_json(nlohmann::json &j, const LightcurveConfig &lc);

}  // namespace Sage
