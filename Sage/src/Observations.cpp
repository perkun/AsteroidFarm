#include "Observations.h"
#include "ObservationsParser.h"
#include <nlohmann/json.hpp>

#include <fstream>

namespace Sage {


LightcurveStorage LightcurveStorage::loadFromJson(const std::filesystem::path &filePath)
{
    // TODO check if file exists, etc
    std::ifstream file(filePath);
    return nlohmann::json::parse(file);
}

} // namespace Sage