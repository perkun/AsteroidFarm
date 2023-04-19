#pragma once

#include <glm/vec3.hpp>
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

struct LightcurveSeries
{
    std::string targetName;
    std::vector<Lightcurve> lightcurves;
};

LightcurveSeries LoadLightcurveSeries(const std::filesystem::path &filePath);

}  // namespace Sage