#include "LightcurveScene.h"

namespace AsteroidFarm {

LightcurveScene::LightcurveScene(Renderer &renderer,
                                 glm::uvec2 framebufferSize,
                                 const LightcurveSeriesConfig &config)
    : PhotometryScene(renderer, framebufferSize, config)
{}

void LightcurveScene::render()
{
    const auto fbWidth = _framebuffer.specification.width;
    const auto fbHeight = _framebuffer.specification.height;
    std::vector<float> pixelBuffRed(fbWidth * fbHeight);

    auto asteroidParams = _config.asteroidParams;

    for (const auto &lightcurveConfig : _config.lightcurves)
    {
        const auto numPoints = lightcurveConfig.numPoints;

        Lightcurve lightcurve;
        lightcurve.reserve(numPoints);

        auto phaseIncrement = 2. * Pi / numPoints;
        auto timeIncrement = asteroidParams.period / numPoints;

        updatePositions(lightcurveConfig.startJd,
                        asteroidParams,
                        lightcurveConfig.targetPosition,
                        lightcurveConfig.observerPosition,
                        lightcurveConfig.lightPosition);

        auto &t = _asteroid.getComponent<TransformComponent>();

        for (unsigned int i = 0; i < numPoints; i++)
        {
            t.rotation = asteroidParams.computeXyzRotation();

            renderSceneWithShadows();

            glReadPixels(0, 0, fbWidth, fbHeight, GL_RED, GL_FLOAT, pixelBuffRed.data());
            auto mag = Magnitude::cast(
                -2.5 * log10(std::accumulate(pixelBuffRed.begin(), pixelBuffRed.end(), 0.)));
            // fmt::print("{} {}\n", asteroidParams.rotPhase.value(), mag.value());

            lightcurve.push_back({.julianDay = lightcurveConfig.startJd + (i * timeIncrement),
                                  .rotPhase = asteroidParams.rotPhase,
                                  .step = i,
                                  .magnitude = mag,
                                  .observerPosition = _camera.position,
                                  .targetPosition = t.position});

            asteroidParams.rotPhase += phaseIncrement;
            asteroidParams.normalizeRotPhase();
        }

        syntheticObs.lightcurves.push_back(lightcurve);
    }
}

}  // namespace AsteroidFarm
