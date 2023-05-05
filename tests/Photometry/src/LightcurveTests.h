#pragma once

#include "GraphicsEngine.h"
#include "LightcurveConfig.h"
#include "Observations.h"
#include "PhotometryScene.h"

#include "JsonLoader.h"

#include <gtest/gtest.h>

namespace Sage::Test {

// TODO move this to apropriate place
// inline std::ostream& operator<<(std::ostream& out, const glm::vec3 &v)
// {
//     return out << v.x << " " << v.y << " " << v.z;
// }


TEST(Photometry, SingleLightcurve)
{
    constexpr glm::uvec2 windowSize{256};

    GraphicsEngine graphicsEngine({.width = windowSize.x,
                                   .height = windowSize.y,
                                   .title = "RenderEngine window",
                                   .fullscreen = false,
                                   .visible = false});

    auto config = LoadFromJson<LightcurveConfig>("data/lightcurveConfig.json");
    auto &scene = graphicsEngine.pushScene<PhotometryScene>(windowSize, config);
    graphicsEngine.renderScenes();
    // graphicsEngine.updateWindow();

    auto expectedLightcurve = LoadFromJson<LightcurveStorage>("data/testLightcurve.json").lightcurves.front();
    auto &synthLightcurve = scene.syntheticObs.lightcurves.front();

    for (int i = 0; i < expectedLightcurve.size(); i++)
    {
        auto &expectedObsPoint = expectedLightcurve[i];
        auto &synthObsPoint = synthLightcurve[i];

        EXPECT_EQ(expectedObsPoint.rotPhase, synthObsPoint.rotPhase);
        EXPECT_EQ(expectedObsPoint.magnitude, synthObsPoint.magnitude);
        EXPECT_EQ(expectedObsPoint.julianDay, synthObsPoint.julianDay);
        EXPECT_EQ(expectedObsPoint.step, synthObsPoint.step);

        for (int i = 0; i < 3; i++)
        {
            EXPECT_EQ(expectedObsPoint.observerPosition[i], synthObsPoint.observerPosition[i]);
            EXPECT_EQ(expectedObsPoint.targetPosition[i], synthObsPoint.targetPosition[i]);
        }

    }
}

}  // namespace Sage::Test