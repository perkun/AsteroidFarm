#include <fmt/format.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/pca.hpp>
#include <iostream>

#include "Mesh.h"
#include "Observations.h"

using namespace Sage;

int main()
{
    LightcurveSeries obs = LoadLightcurveSeries("data/obs.json");    


    return 0;
}
