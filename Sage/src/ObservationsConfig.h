#pragma once

#include "AsteroidParams.h"
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>

#include <string>
#include <filesystem>
#include <optional>

namespace Sage {

struct SceneConfig
{
    std::filesystem::path modelPath;
    std::filesystem::path vertexShaderPath;
    std::filesystem::path fragmentShaderPath;
};

struct LightcurveConfig
{
    unsigned int numPoints;
    JulianDay startJd;
    glm::vec3 observerPosition;
    glm::vec3 targetPosition;
    glm::vec3 lightPosition;
};

struct LightcurveSeriesConfig
{
    SceneConfig scene;
    AsteroidParams asteroidParams;
    std::vector<LightcurveConfig> lightcurves;
    std::optional<std::filesystem::path> outputPath;
};

void from_json(const nlohmann::json &j, SceneConfig &lc);
void to_json(nlohmann::json &j, const SceneConfig &lc);

void from_json(const nlohmann::json &j, LightcurveConfig &lc);
void to_json(nlohmann::json &j, const LightcurveConfig &lc);

void from_json(const nlohmann::json &j, LightcurveSeriesConfig &lc);
void to_json(nlohmann::json &j, const LightcurveSeriesConfig &lc);

}  // namespace Sage