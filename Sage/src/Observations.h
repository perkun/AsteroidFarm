#pragma once

#include "Parsers/GlmParser.h"

#include <nlohmann/json.hpp>
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

struct LightcurveStorage
{
    std::string targetName;
    std::vector<Lightcurve> lightcurves;
};

void from_json(const nlohmann::json &j, ObsPoint &p);
void from_json(const nlohmann::json &j, LightcurveStorage &obs);

void to_json(nlohmann::json &j, const ObsPoint &p);
void to_json(nlohmann::json &j, const LightcurveStorage &p);

}  // namespace Sage