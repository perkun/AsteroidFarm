#pragma once

#include <glm/vec3.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>


// TODO move this to separate file e.g. TypeParser
// partial specialization (full specialization works too)
namespace nlohmann {
template <>
struct adl_serializer<glm::vec3>
{
    static void from_json(const json& j, glm::vec3& vec)
    {
        vec.x = j.at(0);
        vec.y = j.at(1);
        vec.z = j.at(2);
    }
};
}  // namespace nlohmann


namespace Sage {

struct ObsPoint
{
    double julianDay{0};
    double magnitude{0};
    glm::vec3 observerPosition{0};
    glm::vec3 targetPosition{0};
};

using Lightcurve = std::vector<ObsPoint>;

struct Observations
{
    std::string targetName;
    std::vector<Lightcurve> lightcurves;
};


using namespace nlohmann;
void from_json(const json& j, obspoint& p)
{
    p.julianday = j.at("julianday").get<double>();
    p.magnitude = j.at("magnitude").get<double>();
    p.observerposition = j.at("observerposition").get<glm::vec3>();
    p.targetposition = j.at("targetposition").get<glm::vec3>();
}

}  // namespace Sage