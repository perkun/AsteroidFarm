#include "ObservationsParser.h"

namespace Sage {

void from_json(const json& j, ObsPoint& p)
{
    p.julianDay = j.at("julianDay").get<double>();
    p.magnitude = j.at("magnitude").get<double>();
    p.observerPosition = j.at("observerPosition").get<glm::vec3>();
    p.targetPosition = j.at("targetPosition").get<glm::vec3>();
}

void from_json(const json& j, LightcurveStorage& obs)
{
    obs.targetName = j.at("targetName").get<std::string>();
    obs.lightcurves = j.at("lightcurves").get<std::vector<Lightcurve>>();
}

} // namespace Sage