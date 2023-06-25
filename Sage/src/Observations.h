#pragma once

#include "GlmParser.h"
#include "Units.h"
#include "JulianDay.h"

#include <nlohmann/json.hpp>
#include <glm/vec3.hpp>

#include <string>
#include <vector>
#include <filesystem>

namespace Sage {

// TODO grrr...
using namespace UnitLiterals;
struct ObsPoint
{
    JulianDay julianDay{0_jd};
    Angle<Units::Radian> rotPhase{0_rad};
    unsigned int step{0};

    Magnitude magnitude;
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
