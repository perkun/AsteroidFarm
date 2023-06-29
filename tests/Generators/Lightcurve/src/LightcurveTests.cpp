#include "LightcurveTests.h"

#include <iostream>
#include <gtest/gtest.h>
#include <fmt/format.h>

using namespace AsteroidFarm;

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
