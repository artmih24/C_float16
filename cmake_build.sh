#!usr/bin/env bash

mkdir ./build
cd ./build
cmake ..
make | cmake --build .
cp ./bin/float16_test ./float16_test
cd ..