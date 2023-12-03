#!usr/bin/env bash

cd ./build
cmake ..
make | cmake --build .
cp ./Debug/float16_test ../float16_test
cd ..