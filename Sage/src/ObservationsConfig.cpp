#include "ObservationsConfig.h"
#include "AsteroidParams.h"
#include "GlmParser.h"

namespace Sage {

void from_json(const nlohmann::json &j, SceneConfig &oc)
{
    oc.modelPath = j.at("modelPath").get<std::filesystem::path>();
    oc.vertexShaderPath = j.at("vertexShaderPath").get<std::filesystem::path>();
    oc.fragmentShaderPath = j.at("fragmentShaderPath").get<std::filesystem::path>();
}

void to_json(nlohmann::json &j, const SceneConfig &oc)
{
    j = {{"modelPath", oc.modelPath},
         {"vertexShaderPath", oc.vertexShaderPath},
         {"fragmentShaderPath", oc.fragmentShaderPath}};
}

void from_json(const nlohmann::json &j, LightcurveConfig &lc)
{
    lc.numPoints = j.at("numPoints").get<unsigned int>();
    lc.startJd = j.at("startJd").get<JulianDay>();
    lc.targetPosition = j.at("targetPosition").get<glm::vec3>();
    lc.observerPosition = j.at("observerPosition").get<glm::vec3>();
    lc.lightPosition = j.at("lightPosition").get<glm::vec3>();
}

void to_json(nlohmann::json &j, const LightcurveConfig &lc)
{
    // TODO
}

void from_json(const nlohmann::json &j, LightcurveSeriesConfig &lc)
{
    lc.scene = j.at("scene").get<SceneConfig>();
    lc.asteroidParams = j.at("asteroidParams").get<AsteroidParams>();
    lc.lightcurves = j.at("lightcurves").get<std::vector<LightcurveConfig>>();
    if (j.find("outputPath") != j.end())
    {
        lc.outputPath = j.at("outputPath").get<std::filesystem::path>();
    }
}

void to_json(nlohmann::json &j, const LightcurveSeriesConfig &lc)
{
    // TODO
    j = {{"scene", lc.scene},
         {"asteroidParams", lc.asteroidParams},
         {"lightcurves", lc.lightcurves}};

    if (lc.outputPath)
    {
        j.push_back(nlohmann::json::object_t::value_type("outputPath", lc.outputPath.value()));
    }
}

void from_json(const nlohmann::json &j, AOConfig &ao)
{
    ao.jd = j.at("jd").get<JulianDay>();
    ao.targetPosition = j.at("targetPosition").get<glm::vec3>();
    ao.observerPosition = j.at("observerPosition").get<glm::vec3>();
    ao.lightPosition = j.at("lightPosition").get<glm::vec3>();
    ao.resolution = j.at("resolution").get<size_t>();
}

void to_json(nlohmann::json &j, const AOConfig &ao)
{
    j = {{"jd", ao.jd},
         {"targetPosition", ao.targetPosition},
         {"observerPosition", ao.observerPosition},
         {"lightPosition", ao.lightPosition},
         {"resolution", ao.resolution}};
}

void from_json(const nlohmann::json &j, AOSeriesConfig &ao)
{
    ao.scene = j.at("scene").get<SceneConfig>();
    ao.asteroidParams = j.at("asteroidParams").get<AsteroidParams>();
    ao.aoImages = j.at("aoImages").get<std::vector<AOConfig>>();
    ao.imagePrefix = j.at("imagePrefix").get<std::string>();
}

void to_json(nlohmann::json &j, const AOSeriesConfig &ao)
{
    // TODO
}

}  // namespace Sage
