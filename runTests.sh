#! /bin/bash

make
cd tests

bin/Debug/SageTests/SageTests
bin/Debug/LightcurveTests/LightcurveTests

cd ..
