#pragma once

#include "Units.h"
#include "JulianDay.h"
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>

namespace Sage {

class AsteroidParams
{
public:
    std::string name;
    Angle<Units::Radian> eclipticLongitude;
    Angle<Units::Radian> eclipticLatitude;
    Duration<Units::Hour> period;
    JulianDay epoch;
    Angle<Units::Radian> rotPhaseForEpoch;
    Angle<Units::Radian> rotPhase;

    glm::vec3 computeXyzRotation();
    void setRotPhase(const JulianDay &jd);
    void normalizeRotPhase();

private:
    Angle<Units::Radian> computeRotPhase(const JulianDay &jd);
};

void from_json(const nlohmann::json &j, AsteroidParams &p);
void to_json(nlohmann::json &j, const AsteroidParams &obs);

}  // namespace Sage
