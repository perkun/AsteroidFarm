#pragma once

#include <nlohmann/json.hpp>
#include <glm/vec3.hpp>

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

    static void to_json(json& j, const glm::vec3& vec)
    {
        j = json::array({vec.x, vec.y, vec.z});
    }
};
}  // namespace nlohmann
