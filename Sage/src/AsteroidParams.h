#pragma once

#include <nlohmann/json.hpp>

namespace Sage {

struct AsteroidParams
{
    float eclipticLongitude;
    float eclipticLatitude;
    double period;
    double epoch;
    float rotPhaseForEpoch;
};

void from_json(const nlohmann::json& j, AsteroidParams& p);
void to_json(nlohmann::json& j, const AsteroidParams& obs);

} // namespace Sage