cmake_minimum_required(VERSION 3.0)
project(lab_1 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES main.cpp)

add_executable(lab_1 ${SOURCES})