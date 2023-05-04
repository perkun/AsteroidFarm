#include "AsteroidParams.h"

namespace Sage {
using namespace nlohmann;

// TODO check for value validity

void from_json(const json &j, AsteroidParams &p)
{
    p.eclipticLongitude = j.at("eclipticLongitude").get<Angle<Units::Degree>>();
    p.eclipticLatitude = j.at("eclipticLatitude").get<Angle<Units::Degree>>();
    p.period = j.at("period").get<JulianDay<Units::Hour>>();
    p.epoch = j.at("epoch").get<JulianDay<Units::Day>>();
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