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

class AOScene : public PhotometryScene<AOSeriesConfig>
{
public:
    AOScene(Renderer &renderer,
                    glm::uvec2 framebufferSize,
                    const AOSeriesConfig &config);

    void render() override;

    AOStorage aoImages;

private:
    void saveImage(int idx, unsigned int width, unsigned int height);
};

}  // namespace AsteroidFarm
