mkdir build
cd build
cmake ..
cmake --build .
copy .\Debug\float16_test.exe ..\float16_test.exe
cd ..