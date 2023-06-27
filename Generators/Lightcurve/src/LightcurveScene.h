#include <memory>
#include <numeric>
#include "Units.h"
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Framebuffer.h"
#include "Observations.h"
#include "PhotometryScene.h"

namespace Sage {

class LightcurveScene : public PhotometryScene<LightcurveSeriesConfig>
{
public:
    LightcurveScene(Renderer &renderer,
                    glm::uvec2 framebufferSize,
                    const LightcurveSeriesConfig &config);

    void render() override;

    LightcurveStorage syntheticObs;
};

}  // namespace Sage
