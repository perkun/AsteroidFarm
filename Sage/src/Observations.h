#pragma once

#include <glm/vec3.hpp>
#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <filesystem>

namespace Sage {

struct ObsPoint
{
    double julianDay{0};
    double magnitude{0};
    glm::vec3 observerPosition{0};
    glm::vec3 targetPosition{0};
};

using Lightcurve = std::vector<ObsPoint>;

struct LightcurveStorage
{
    static LightcurveStorage loadFromJson(const std::filesystem::path &filePath);
    static void saveToJson(const LightcurveStorage &storage, const std::filesystem::path &filePath);

    std::string targetName;
    std::vector<Lightcurve> lightcurves;
};

}  // namespace Sage