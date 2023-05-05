#! /bin/bash

make
cd tests

bin/Debug/SageTests/SageTests
bin/Debug/PhotometryTests/PhotometryTests

cd ..
