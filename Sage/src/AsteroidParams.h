#pragma once

namespace Sage {

struct AsteroidParams
{
    float eclipticLongitude;
    float eclipticLatitude;
    double period;
    double epoch;
    float rotPhaseForEpoch;
};

} // namespace Sage