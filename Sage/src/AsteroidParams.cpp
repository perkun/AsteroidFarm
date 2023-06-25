#include "AsteroidParams.h"

#include <glm/gtx/quaternion.hpp>
#include "Units.h"
#include "JulianDay.h"

namespace Sage {
using namespace nlohmann;

void AsteroidParams::setRotPhase(const JulianDay &jd)
{
    rotPhase = computeRotPhase(jd);
    normalizeRotPhase();
}

Angle<Units::Radian> AsteroidParams::computeRotPhase(const JulianDay &jd)
{
    auto rotPhase = (jd - epoch) / period * 2 * Pi;
    return rotPhase;
}

void AsteroidParams::normalizeRotPhase()
{
    using namespace UnitLiterals;
    while (rotPhase > 2 * Pi)
    {
        rotPhase -= 2 * Pi;
    }
    while (rotPhase < 0_rad)
    {
        rotPhase += 2 * Pi;
    }
}

glm::vec3 AsteroidParams::computeXyzRotation()
{
    glm::quat ql, qb, qg;
    // rotate gamma about z axis
    qg.w = cos((rotPhaseForEpoch + rotPhase).value() / 2);
    qg.x = 0;
    qg.y = 0;
    qg.z = sin((rotPhaseForEpoch + rotPhase).value() / 2);

    // // rotate beta about y axis
    qb.w = cos((M_PI_2 - eclipticLatitude.value()) / 2);
    qb.x = 0;
    qb.y = sin((M_PI_2 - eclipticLatitude.value()) / 2);
    qb.z = 0;

    // // rotate alpha about z axis
    ql.w = cos(eclipticLongitude.value() / 2);
    ql.x = 0;
    ql.y = 0;
    ql.z = sin(eclipticLongitude.value() / 2);

    return glm::eulerAngles(ql * qb * qg);
}

// TODO check for value validity

void from_json(const json &j, AsteroidParams &p)
{
    p.eclipticLongitude = j.at("eclipticLongitude").get<Angle<Units::Degree>>();
    p.eclipticLatitude = j.at("eclipticLatitude").get<Angle<Units::Degree>>();
    p.period = j.at("period").get<Duration<Units::Hour>>();
    p.epoch = j.at("epoch").get<JulianDay>();
    p.rotPhaseForEpoch = j.at("rotPhaseForEpoch").get<Angle<Units::Degree>>();
}

void to_json(json &j, const AsteroidParams &p)
{
    j = {{"eclipticLongitude", p.eclipticLongitude},
         {"eclipticLatitude", p.eclipticLatitude},
         {"period", p.period},
         {"epoch", p.epoch},
         {"rotPhaseForEpoch", p.rotPhaseForEpoch}};
}

}  // namespace Sage
