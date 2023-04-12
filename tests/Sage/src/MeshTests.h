#include "Mesh.h"
#include "VertexLayout.h"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <fmt/format.h>

using namespace Sage;

TEST(Mesh, LoadObjFile)
{
    auto mesh = LoadObj("data/model_shifted.obj");

    EXPECT_EQ(mesh.vertices.size(), 49158);
    EXPECT_EQ(mesh.indices.size(), 98304);

    // 1st vertex
    EXPECT_FLOAT_EQ(mesh.vertices[0], -0.223791);
    EXPECT_FLOAT_EQ(mesh.vertices[1], -0.142740);
    EXPECT_FLOAT_EQ(mesh.vertices[2], 0.458241);

    // 23th vertex
    EXPECT_FLOAT_EQ(mesh.vertices[22 * 3 + 0], -0.243770);
    EXPECT_FLOAT_EQ(mesh.vertices[22 * 3 + 1], -0.229935);
    EXPECT_FLOAT_EQ(mesh.vertices[22 * 3 + 2], 0.464645);

    // 1234th vertex
    EXPECT_FLOAT_EQ(mesh.vertices[1233 * 3 + 0], 0.530792);
    EXPECT_FLOAT_EQ(mesh.vertices[1233 * 3 + 1], -0.594790);
    EXPECT_FLOAT_EQ(mesh.vertices[1233 * 3 + 2], 0.713187);

    // 1st face
    EXPECT_EQ(mesh.indices[0], 0);
    EXPECT_EQ(mesh.indices[1], 1);
    EXPECT_EQ(mesh.indices[2], 2);

    // 123st face
    EXPECT_EQ(mesh.indices[122 * 3 + 0], 64);
    EXPECT_EQ(mesh.indices[122 * 3 + 1], 61);
    EXPECT_EQ(mesh.indices[122 * 3 + 2], 88);

    // 1234st face
    EXPECT_EQ(mesh.indices[1233 * 3 + 0], 700);
    EXPECT_EQ(mesh.indices[1233 * 3 + 1], 699);
    EXPECT_EQ(mesh.indices[1233 * 3 + 2], 701);
}

TEST(Mesh, ApplyToVertices)
{
    Mesh mesh;

    mesh.vertices = {
        1101, 1102, 1103,   1201, 1202,    1301, 1302, 1303, 1304,
        2101, 2102, 2103,   2201, 2202,    2301, 2302, 2303, 2304,
        3101, 3102, 3103,   3201, 3202,    3301, 3302, 3303, 3304,
        4101, 4102, 4103,   4201, 4202,    4301, 4302, 4303, 4304,
        5101, 5102, 5103,   5201, 5202,    5301, 5302, 5303, 5304,
        6101, 6102, 6103,   6201, 6202,    6301, 6302, 6303, 6304,
        7101, 7102, 7103,   7201, 7202,    7301, 7302, 7303, 7304,
    };

    mesh.indices = {
        0,1,2,
        2,3,4,
        4,5,6
    };

    mesh.layout = VertexLayout(VertexElementType::POSITION,
                               VertexElementType::TEXTURE,
                               VertexElementType::COLOR);

    mesh.applyToVertexElements(VertexElementType::TEXTURE,
                               [](auto &textureCoords) {
                                   textureCoords[0] += 10;
                                   textureCoords[1] += 10;
                               });

    std::vector<float> expectedVertices{
        1101, 1102, 1103,   1211, 1212,    1301, 1302, 1303, 1304,
        2101, 2102, 2103,   2211, 2212,    2301, 2302, 2303, 2304,
        3101, 3102, 3103,   3211, 3212,    3301, 3302, 3303, 3304,
        4101, 4102, 4103,   4211, 4212,    4301, 4302, 4303, 4304,
        5101, 5102, 5103,   5211, 5212,    5301, 5302, 5303, 5304,
        6101, 6102, 6103,   6211, 6212,    6301, 6302, 6303, 6304,
        7101, 7102, 7103,   7211, 7212,    7301, 7302, 7303, 7304,
    };
    EXPECT_EQ(expectedVertices, mesh.vertices);


    // going through every 2nd vertex, i.e.: idx = 1, 3, 5
    // and changing 6th element - 1st element of color
    mesh.applyToFaces([](auto &vertices){
        vertices[1][5] += 10;
    });

    expectedVertices = {
        1101, 1102, 1103,   1211, 1212,    1301, 1302, 1303, 1304,
        2101, 2102, 2103,   2211, 2212,    2311, 2302, 2303, 2304,
        3101, 3102, 3103,   3211, 3212,    3301, 3302, 3303, 3304,
        4101, 4102, 4103,   4211, 4212,    4311, 4302, 4303, 4304,
        5101, 5102, 5103,   5211, 5212,    5301, 5302, 5303, 5304,
        6101, 6102, 6103,   6211, 6212,    6311, 6302, 6303, 6304,
        7101, 7102, 7103,   7211, 7212,    7301, 7302, 7303, 7304,
    };

    EXPECT_EQ(expectedVertices, mesh.vertices);

    mesh.applyToFacesElements(VertexElementType::COLOR, [](auto &colors){
        for (auto &color : colors)
        {
            for (int i = 0; i < 4; i++)
            {
                color[i] += 10;
            }
        }
    });

    expectedVertices = {
        1101, 1102, 1103,   1211, 1212,    1311, 1312, 1313, 1314,
        2101, 2102, 2103,   2211, 2212,    2321, 2312, 2313, 2314,
        3101, 3102, 3103,   3211, 3212,    3321, 3322, 3323, 3324,
        4101, 4102, 4103,   4211, 4212,    4321, 4312, 4313, 4314,
        5101, 5102, 5103,   5211, 5212,    5321, 5322, 5323, 5324,
        6101, 6102, 6103,   6211, 6212,    6321, 6312, 6313, 6314,
        7101, 7102, 7103,   7211, 7212,    7311, 7312, 7313, 7314,
    };

    EXPECT_EQ(expectedVertices, mesh.vertices);
}

TEST(Mesh, Volume)
{
    auto mesh = LoadObj("data/model_shifted.obj");
    EXPECT_DOUBLE_EQ(1.410554138012394, mesh.computeVolume());
}

TEST(Mesh, CenterOfMass)
{
    auto mesh = LoadObj("data/model_shifted.obj");
    auto centerOfMass = mesh.computeCenterOfMass();

    EXPECT_FLOAT_EQ(0.23722456, centerOfMass.x);
    EXPECT_FLOAT_EQ(-0.19607261, centerOfMass.y);
    EXPECT_FLOAT_EQ(0.14658417, centerOfMass.z);
}
