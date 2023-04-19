#pragma once

#include "Observations.h"
#include "GlmParser.h"

#include <nlohmann/json.hpp>

using namespace nlohmann;

namespace Sage {

void from_json(const json& j, ObsPoint& p);
void from_json(const json& j, LightcurveStorage& obs);

void to_json(json &j, const ObsPoint&p);
void to_json(json &j, const LightcurveStorage&p);

} // namespace Sage