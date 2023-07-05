#pragma once

#include "AsteroidParams.h"
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>

#include <string>
#include <filesystem>
#include <optional>

namespace AsteroidFarm {

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

struct AOConfig
{
    JulianDay jd;
    glm::vec3 observerPosition;
    glm::vec3 targetPosition;
    glm::vec3 lightPosition;
    size_t imageSize;
};


struct AOSeriesConfig
{
    SceneConfig scene;
    AsteroidParams asteroidParams;
    std::vector<AOConfig> aoImages;
    std::filesystem::path outputFolderPath;
    std::string imagePrefix;
};

struct RadarConfig
{
    JulianDay jd;
    glm::vec3 observerPosition;
    glm::vec3 targetPosition;
    std::optional<size_t> imageSize;
};

struct RadarSeriesConfig
{
    SceneConfig scene;
    AsteroidParams asteroidParams;
    std::vector<RadarConfig> radarImages;
    bool exportDelayDoppler;
    std::optional<std::filesystem::path> outputPath;
    std::optional<std::filesystem::path> exportFolderPath;
    std::optional<std::string> imagePrefix;

};

void from_json(const nlohmann::json &j, SceneConfig &lc);
void to_json(nlohmann::json &j, const SceneConfig &lc);

void from_json(const nlohmann::json &j, LightcurveConfig &lc);
void to_json(nlohmann::json &j, const LightcurveConfig &lc);

void from_json(const nlohmann::json &j, LightcurveSeriesConfig &lc);
void to_json(nlohmann::json &j, const LightcurveSeriesConfig &lc);

void from_json(const nlohmann::json &j, AOConfig &ao);
void to_json(nlohmann::json &j, const AOConfig &ao);

void from_json(const nlohmann::json &j, AOSeriesConfig &ao);
void to_json(nlohmann::json &j, const AOSeriesConfig &ao);

void from_json(const nlohmann::json &j, RadarConfig &r);
void to_json(nlohmann::json &j, const RadarConfig &r);

void from_json(const nlohmann::json &j, RadarSeriesConfig &r);
void to_json(nlohmann::json &j, const RadarSeriesConfig &r);


}  // namespace AsteroidFarm
