#pragma once

#include "stb_image/stb_image_write.h"

#include <filesystem>
#include <vector>

namespace Sage::Image {

void SavePng(std::filesystem::path filename,
             unsigned int width,
             unsigned int height,
             std::vector<float> &red,
             std::vector<float> &green,
             std::vector<float> &blue,
             std::vector<float> &alpha,
             bool normalize = false);

void SavePng(std::filesystem::path filename,
             unsigned int width,
             unsigned int height,
             std::vector<float> &buff,
             bool normalize = false);

}
