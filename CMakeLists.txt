cmake_minimum_required(VERSION 3.15)	    
								        
project(float16_test
        VERSION 1.0
        DESCRIPTION "float16 library test"
        LANGUAGES C CXX)		

set(SOURCE_MAIN float16/main.cpp)	

set(SOURCE_FLOAT16_LIB float16/float16.c float16/float16.h)	 

add_executable(float16_test ${SOURCE_MAIN} ${SOURCE_FLOAT16_LIB})	  