#include <fmt/format.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/pca.hpp>
#include <iostream>

#include "Parsers/JsonLoader.h"
#include "Mesh.h"
#include "Observations.h"
// #include "AsteroidParams.h"

using namespace Sage;

int main()
{
    // auto obs = LightcurveStorage::loadFromJson("data/obs_out.json");    
    // auto obs = LightcurveStorage::loadFromJson("data/obs.json");    
    // LightcurveStorage::saveToJson(obs, "data/obs_out.json");

    auto obs = LoadFromJson<LightcurveStorage>("data/obs.json");
    SaveToJson(obs, "data/obs_out.json");

    // auto mesh = Mesh::loadFromObj("data/model_shifted.obj");
    // mesh.rotateToPrincipalAxes();
    // Mesh::saveToObj(mesh, "data/model_normals.obj");




    return 0;
}
