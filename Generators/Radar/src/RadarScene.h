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

class RadarScene : public PhotometryScene<RadarSeriesConfig>
{
public:
    RadarScene(Renderer &renderer, glm::uvec2 framebufferSize, const RadarSeriesConfig &config);

    void render() override;

    RadarStorage radarImages;

private:
    void saveImage(int idx, unsigned int width, unsigned int height);
    std::vector<float> constructDelayDoppler(std::vector<float> &radial_vel_buffer,
                                             std::vector<float> &normal_buffer,
                                             std::vector<float> &depth_buffer,
                                             int buffer_width,
                                             int buffer_height);
};

}  // namespace Sage
