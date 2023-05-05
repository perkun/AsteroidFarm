#pragma once

#include "Angle.h"
#include "Time.h"
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>

namespace Sage {

class AsteroidParams
{
public:
    Angle<Units::Radian> eclipticLongitude;
    Angle<Units::Radian> eclipticLatitude;
    JulianDay<Units::Hour> period;
    JulianDay<Units::Day> epoch;
    Angle<Units::Radian> rotPhaseForEpoch;
    Angle<Units::Radian> rotPhase;

    glm::vec3 computeXyzRotation();
    void setRotPhase(const JulianDay<Units::Day> &jd);
    void normalizeRotPhase();

private:
    Angle<Units::Radian> computeRotPhase(const JulianDay<Units::Day> &jd);
};

void from_json(const nlohmann::json& j, AsteroidParams& p);
void to_json(nlohmann::json& j, const AsteroidParams& obs);

} // namespace Sage