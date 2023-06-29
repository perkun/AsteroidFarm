#! /bin/bash

make
cd tests

bin/Debug/CoreTests/CoreTests
bin/Debug/LightcurveTests/LightcurveTests

cd ..
