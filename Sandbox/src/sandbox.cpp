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
    auto obs = LightcurveStorage::loadFromJson("data/obs_out.json");    
    // auto obs = LightcurveStorage::loadFromJson("data/obs.json");    
    // LightcurveStorage::saveToJson(obs, "data/obs_out.json");

    return 0;
}
