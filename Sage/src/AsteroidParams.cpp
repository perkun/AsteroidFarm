#include "AsteroidParams.h"

namespace Sage {
using namespace nlohmann;

void from_json(const json &j, AsteroidParams &p)
{
    p.eclipticLongitude = j.at("eclipticLongitude").get<float>();
    p.eclipticLatitude = j.at("eclipticLatitude").get<float>();
    p.period = j.at("period").get<double>();
    p.epoch = j.at("epoch").get<double>();
    p.rotPhaseForEpoch = j.at("rotPhaseForEpoch").get<float>();
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