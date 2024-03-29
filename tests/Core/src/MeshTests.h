#include "Mesh.h"
#include "VertexLayout.h"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <fmt/format.h>

namespace AsteroidFarm::Test {

TEST(Mesh, LoadObjFile)
{
    auto mesh = Mesh::loadFromObj("data/model_shifted.obj");

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

    // clang-format off
    mesh.vertices = {
        1101, 1102, 1103,   1201, 1202,    1301, 1302, 1303, 1304,
        2101, 2102, 2103,   2201, 2202,    2301, 2302, 2303, 2304,
        3101, 3102, 3103,   3201, 3202,    3301, 3302, 3303, 3304,
        4101, 4102, 4103,   4201, 4202,    4301, 4302, 4303, 4304,
        5101, 5102, 5103,   5201, 5202,    5301, 5302, 5303, 5304,
        6101, 6102, 6103,   6201, 6202,    6301, 6302, 6303, 6304,
        7101, 7102, 7103,   7201, 7202,    7301, 7302, 7303, 7304,
    };
    // clang-format on

    mesh.indices = {0, 1, 2, 2, 3, 4, 4, 5, 6};

    mesh.layout = VertexLayout(
        VertexElementType::POSITION, VertexElementType::TEXTURE, VertexElementType::COLOR);

    mesh.applyToVertexElements(VertexElementType::TEXTURE,
                               [](std::span<float> &textureCoords)
                               {
                                   textureCoords[0] += 10;
                                   textureCoords[1] += 10;
                               });

    // clang-format off
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
    // clang-format on

    // going through every 2nd vertex, i.e.: idx = 1, 3, 5
    // and changing 6th element - 1st element of color
    mesh.applyToFaces([](auto &vertices) { vertices[1][5] += 10; });

    // clang-format off
    expectedVertices = {
        1101, 1102, 1103,   1211, 1212,    1301, 1302, 1303, 1304,
        2101, 2102, 2103,   2211, 2212,    2311, 2302, 2303, 2304,
        3101, 3102, 3103,   3211, 3212,    3301, 3302, 3303, 3304,
        4101, 4102, 4103,   4211, 4212,    4311, 4302, 4303, 4304,
        5101, 5102, 5103,   5211, 5212,    5301, 5302, 5303, 5304,
        6101, 6102, 6103,   6211, 6212,    6311, 6302, 6303, 6304,
        7101, 7102, 7103,   7211, 7212,    7301, 7302, 7303, 7304,
    };
    // clang-format on

    EXPECT_EQ(expectedVertices, mesh.vertices);

    mesh.applyToFacesElements(VertexElementType::COLOR,
                              [](auto &colors)
                              {
                                  for (auto &color : colors)
                                  {
                                      for (int i = 0; i < 4; i++)
                                      {
                                          color[i] += 10;
                                      }
                                  }
                              });

    // clang-format off
    expectedVertices = {
        1101, 1102, 1103,   1211, 1212,    1311, 1312, 1313, 1314,
        2101, 2102, 2103,   2211, 2212,    2321, 2312, 2313, 2314,
        3101, 3102, 3103,   3211, 3212,    3321, 3322, 3323, 3324,
        4101, 4102, 4103,   4211, 4212,    4321, 4312, 4313, 4314,
        5101, 5102, 5103,   5211, 5212,    5321, 5322, 5323, 5324,
        6101, 6102, 6103,   6211, 6212,    6321, 6312, 6313, 6314,
        7101, 7102, 7103,   7211, 7212,    7311, 7312, 7313, 7314,
    };
    // clang-format off

    EXPECT_EQ(expectedVertices, mesh.vertices);
}

TEST(Mesh, Volume)
{
    auto mesh = Mesh::loadFromObj("data/model_shifted.obj");
    EXPECT_FLOAT_EQ(1.410554138012394, mesh.getVolume());
}

TEST(Mesh, CenterOfMass)
{
    auto mesh = Mesh::loadFromObj("data/model_shifted.obj");
    auto centerOfMass = mesh.getCenterOfMass();

    EXPECT_FLOAT_EQ(0.23722456, centerOfMass.x);
    EXPECT_FLOAT_EQ(-0.19607261, centerOfMass.y);
    EXPECT_FLOAT_EQ(0.14658417, centerOfMass.z);
}

TEST(Mesh, TranslateToCenterOfMass)
{
    auto mesh = Mesh::loadFromObj("data/model_shifted.obj");
    mesh.translateToCenterOfMass();
    auto centerOfMass = mesh.getCenterOfMass();

    constexpr float precision = 1e-6;

    EXPECT_LT(centerOfMass.x, precision);
    EXPECT_LT(centerOfMass.y, precision);
    EXPECT_LT(centerOfMass.z, precision);
}

TEST(Mesh, InertiaTensor)
{
    auto mesh = Mesh::loadFromObj("data/model_shifted.obj");
    mesh.translateToCenterOfMass();

    auto inertia = mesh.getInertia();

    EXPECT_FLOAT_EQ(0.31154084, inertia[0][0]);
    EXPECT_FLOAT_EQ(-0.05167585, inertia[0][1]);
    EXPECT_FLOAT_EQ(-0.06256327, inertia[0][2]);

    EXPECT_FLOAT_EQ(.3325195, inertia[1][1]);
    EXPECT_FLOAT_EQ(-0.035295036, inertia[1][2]);

    EXPECT_FLOAT_EQ(0.34198096, inertia[2][2]);
}


TEST(Mesh, PrincipalAxes)
{
    constexpr float precision = 1e-6;

    auto mesh = Mesh::loadFromObj("data/model_shifted.obj");
    mesh.rotateToPrincipalAxes();

    auto vertex = mesh.getVertexElement(VertexElementType::POSITION, 0);
    EXPECT_LT(abs(-0.126412 - vertex[0]), precision);
    EXPECT_LT(abs(0.0472851 - vertex[1]), precision);
    EXPECT_LT(abs(0.542489 - vertex[2]), precision);

    vertex = mesh.getVertexElement(VertexElementType::POSITION, 1000);
    EXPECT_LT(abs(-0.524463 - vertex[0]), precision);
    EXPECT_LT(abs(-0.425167 - vertex[1]), precision);
    EXPECT_LT(abs(0.0424607 - vertex[2]), precision);

    vertex = mesh.getVertexElement(VertexElementType::POSITION, 11933);
    EXPECT_LT(abs(0.701174 - vertex[0]), precision);
    EXPECT_LT(abs(-0.499872 - vertex[1]), precision);
    EXPECT_LT(abs(0.150963 - vertex[2]), precision);

}

TEST(Mesh, Normals)
{
    constexpr float precision = 1e-6;

    auto mesh = Mesh::loadFromObj("data/model_shifted.obj");
    // NOTE it calculates normals too
    mesh.rotateToPrincipalAxes();

    auto vertex = mesh.getVertexElement(VertexElementType::NORMAL, 0);
    EXPECT_LT(abs(0.498685 - vertex[0]), precision);
    EXPECT_LT(abs(-0.257999 - vertex[1]), precision);
    EXPECT_LT(abs(0.827496 - vertex[2]), precision);

    vertex = mesh.getVertexElement(VertexElementType::NORMAL, 1000);
    EXPECT_LT(abs(-0.267745 - vertex[0]), precision);
    EXPECT_LT(abs(-0.950802 - vertex[1]), precision);
    EXPECT_LT(abs(0.155844 - vertex[2]), precision);

    vertex = mesh.getVertexElement(VertexElementType::NORMAL, 11933);
    EXPECT_LT(abs(0.628625 - vertex[0]), precision);
    EXPECT_LT(abs(-0.777697 - vertex[1]), precision);
    EXPECT_LT(abs(0.00419329 - vertex[2]), precision);

}

} // namespace AsteroidFarm::Test
