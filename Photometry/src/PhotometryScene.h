#include <memory>
#include <numeric>
#include "Units.h"
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Framebuffer.h"
#include "Observations.h"

namespace Sage {

class PhotometryScene : public Scene
{
public:
    PhotometryScene(Renderer &renderer,
                    glm::uvec2 framebufferSize,
                    const LightcurveSeriesConfig &config);

    void renderSceneWithShadows();
    void render() override;

    LightcurveStorage syntheticObs;

private:
    const LightcurveSeriesConfig &_config;

    Framebuffer _framebuffer;
    Framebuffer _lightFramebuffer;

    OrthographicCamera _camera;
    OrthographicCamera _light;

    Entity asteroid;

    double _modelRadius;

};

}  // namespace Sage
