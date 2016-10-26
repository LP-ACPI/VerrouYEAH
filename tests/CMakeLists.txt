# cmake_minimum_required(VERSION <specify CMake version here>)
project(Test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcrypto -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Coffre ${SOURCE_FILES})