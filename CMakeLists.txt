cmake_minimum_required(VERSION 3.15)	    
								        
project(float16_test
        VERSION 1.0
        DESCRIPTION "float16 library test"
        LANGUAGES C CXX)	

set(SOURCES_DIR ./float16)

set(SOURCE_MAIN ${SOURCES_DIR}/main.cpp)	

set(SOURCE_FLOAT16_LIB ${SOURCES_DIR}/float16.c ${SOURCES_DIR}/float16.h)	 

add_executable(float16_test ${SOURCE_MAIN} ${SOURCE_FLOAT16_LIB})	  