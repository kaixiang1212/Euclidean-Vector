cmake_minimum_required(VERSION 3.14)
project(ev)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ev
        client.cpp
        client.sampleout
        euclidean_vector.cpp
        euclidean_vector.h
        euclidean_vector_test.cpp cmake-build-debug/test.cpp)
