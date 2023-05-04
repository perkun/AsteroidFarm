#include "Observations.h"

#include <fstream>

using namespace nlohmann;

namespace Sage {

void from_json(const json &j, ObsPoint &p)
{
    p.julianDay = j.at("julianDay").get<JulianDay<Units::Day>>();
    p.magnitude = j.at("magnitude").get<Magnitude>();
    p.rotPhase = j.at("rotPhase").get<Angle<Units::Radian>>();
    p.observerPosition = j.at("observerPosition").get<glm::vec3>();
    p.targetPosition = j.at("targetPosition").get<glm::vec3>();
}

void from_json(const json &j, LightcurveStorage &obs)
{
    obs.targetName = j.at("targetName").get<std::string>();
    obs.lightcurves = j.at("lightcurves").get<std::vector<Lightcurve>>();
}

void to_json(json &j, const ObsPoint &p)
{
    j = {{"julianDay", p.julianDay},
         {"magnitude", p.magnitude},
         {"rotPhase", p.rotPhase},
         {"observerPosition", p.observerPosition},
         {"targetPosition", p.targetPosition}};
}

void to_json(json &j, const LightcurveStorage &obs)
{
    j = {{"targetName", obs.targetName}, {"lightcurves", obs.lightcurves}};
}

}  // namespace Sage