#pragma once

#include "VertexLayout.h"

#include <vector>
#include <filesystem>

namespace Sage {


struct Mesh
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

    VertexLayout layout;
};

Mesh LoadObj(const std::filesystem::path &filename);

}  // namespace Sage
