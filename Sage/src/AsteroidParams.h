#pragma once

#include "Angle.h"
#include "Time.h"
#include <nlohmann/json.hpp>

namespace Sage {

struct AsteroidParams
{
    Angle<Units::Degree> eclipticLongitude;
    Angle<Units::Degree> eclipticLatitude;
    JulianDay<Units::Hour> period;
    JulianDay<Units::Day> epoch;
    Angle<Units::Degree> rotPhaseForEpoch;
};

void from_json(const nlohmann::json& j, AsteroidParams& p);
void to_json(nlohmann::json& j, const AsteroidParams& obs);

} // namespace Sage