#include "Observations.h"
#include "ObservationsParser.h"

#include <fstream>

namespace Sage {


LightcurveStorage LightcurveStorage::loadFromJson(const std::filesystem::path &filePath)
{
    // TODO check if file exists, etc
    std::ifstream file(filePath);
    return nlohmann::json::parse(file);
}

void LightcurveStorage::saveToJson(const LightcurveStorage &storage, const std::filesystem::path &filePath)
{
    std::ofstream file(filePath);
    nlohmann::json j = storage;
    file << j;
}

} // namespace Sage