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

namespace AsteroidFarm {

class RadarScene : public PhotometryScene<RadarSeriesConfig>
{
public:
    RadarScene(Renderer &renderer, glm::uvec2 framebufferSize, const RadarSeriesConfig &config);

    void render() override;

    RadarStorage storage;

private:
    void storeImage();
};

}  // namespace AsteroidFarm
