#include "Mesh.h"

#include <iostream>
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
    EXPECT_EQ(mesh.indices[0], 1);
    EXPECT_EQ(mesh.indices[1], 2);
    EXPECT_EQ(mesh.indices[2], 3);

    // 123st face
    EXPECT_EQ(mesh.indices[122 * 3 + 0], 65);
    EXPECT_EQ(mesh.indices[122 * 3 + 1], 62);
    EXPECT_EQ(mesh.indices[122 * 3 + 2], 89);

    // 1234st face
    EXPECT_EQ(mesh.indices[1233 * 3 + 0], 701);
    EXPECT_EQ(mesh.indices[1233 * 3 + 1], 700);
    EXPECT_EQ(mesh.indices[1233 * 3 + 2], 702);
}

int main(int argc, char *argv[])
{
//     double ro, scale, sigma;
//     int com_choice, pa_choice;
//     long int seed;
//
//     ro = 1.0;
//     scale = 1.0;
//     sigma = 0.03;
//     com_choice = 1;
//     pa_choice = 1;
//     seed = 0;

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
