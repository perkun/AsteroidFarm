#pragma once

#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace Sage {

template <typename T>
T LoadFromJson(const std::filesystem::path &filePath)
{
    // TODO check if file exists, etc
    std::ifstream file(filePath);
    return nlohmann::json::parse(file);

}

template <typename T>
void SaveToJson(const T &data, const std::filesystem::path &filePath)
{
    std::ofstream file(filePath);
    nlohmann::json j = data;
    file << j;
}

} // namespace Sage