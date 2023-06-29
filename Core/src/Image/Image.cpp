#include "Image.h"
#include <algorithm>

namespace AsteroidFarm::Image {

void SavePng(std::filesystem::path filename,
             unsigned int width,
             unsigned int height,
             std::vector<float> &red,
             std::vector<float> &green,
             std::vector<float> &blue,
             std::vector<float> &alpha,
             bool normalize)
{
    float maxValue = 1.0;
    float minValue = 0.0;
    if (normalize)
    {
        auto maxRed = *std::max_element(red.begin(), red.end());
        auto maxGreen = *std::max_element(green.begin(), green.end());
        auto maxBlue = *std::max_element(blue.begin(), blue.end());
        maxValue = std::max(std::max(maxRed, maxGreen), maxBlue);

        auto minRed = *std::min_element(red.begin(), red.end());
        auto minGreen = *std::min_element(green.begin(), green.end());
        auto minBlue = *std::min_element(blue.begin(), blue.end());
        minValue = std::min(std::min(minRed, minGreen), minBlue);
    }

    stbi_flip_vertically_on_write(1);
    int channels = 4;

    unsigned char *png_data = new unsigned char[width * height * channels];

    for (int i = 0; i < width * height; i++)
    {
        png_data[i * channels + 0] =
            (unsigned char)((red[i] - minValue) / (maxValue - minValue) * 255);
        png_data[i * channels + 1] =
            (unsigned char)((green[i] - minValue) / (maxValue - minValue) * 255);
        png_data[i * channels + 2] =
            (unsigned char)((blue[i] - minValue) / (maxValue - minValue) * 255);
        png_data[i * channels + 3] = (unsigned char)(alpha[i] * 255);
    }

    stbi_write_png(filename.string().c_str(), width, height, channels, png_data, width * channels);
    delete[] png_data;
}

void SavePng(std::filesystem::path filename,
             unsigned int width,
             unsigned int height,
             std::vector<float> &buff,
             bool normalize)
{
    float maxValue = 1.0;
    float minValue = 0.0;
    if (normalize)
    {
        maxValue = *std::max_element(buff.begin(), buff.end());
        minValue = *std::min_element(buff.begin(), buff.end());
    }
    stbi_flip_vertically_on_write(1);
    int channels = 1;

    unsigned char *png_data = new unsigned char[width * height * channels];

    for (int i = 0; i < width * height; i++)
    {
        png_data[i * channels + 0] =
            (unsigned char)((buff[i] - minValue) / (maxValue - minValue) * 255);
    }

    stbi_write_png(filename.string().c_str(), width, height, channels, png_data, width * channels);
    delete[] png_data;
}

}  // namespace AsteroidFarm::Image
