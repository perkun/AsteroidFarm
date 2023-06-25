// #include <fmt/format.h>
//
// #include <chrono>
// #include <glm/glm.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include <glm/gtx/pca.hpp>
// #include <iostream>
// #include <iomanip>
//
#include "GraphicsEngine.h"
#include "LightcurveConfig.h"
// #include "SandboxScene.h"

#include "JsonLoader.h"
#include "AsteroidParams.h"
#include "Units.h"
#include "JulianDay.h"

using namespace Sage;
using namespace Sage::UnitLiterals;

int main()
{

    Angle<Units::Degree> a = 21.2_deg;
    // Angle<Units::Day> b;
    auto h = 48_h + 30_min;

    // Unit<Dimension::Angle, Units::Day> c;

    JulianDay jd{1234.567};
    JulianDay jd2{1237.567};
    jd = jd + h;
    std::cout << jd.value() << std::endl;
    std::cout << jd2 - jd << std::endl;

    return 0;
}
