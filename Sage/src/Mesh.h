#pragma once

#include "VertexLayout.h"

#include <vector>

namespace Sage {


struct Mesh
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

    VertexLayout layout;
};

}  // namespace Sage
