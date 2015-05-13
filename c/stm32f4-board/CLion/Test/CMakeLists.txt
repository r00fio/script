cmake_minimum_required(VERSION 2.8.4)
project(Test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

set(SOURCE_FILES main.cpp)
add_executable(Test ${SOURCE_FILES})