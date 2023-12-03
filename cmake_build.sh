#!usr/bin/env bash

cd ./build
cmake ..
make | cmake --build .
cd ..