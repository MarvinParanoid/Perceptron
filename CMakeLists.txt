cmake_minimum_required(VERSION 3.30)
project(Perceptron)

set(CMAKE_CXX_STANDARD 20)

add_executable(Perceptron main.cpp
        DatasetReader.cpp
        DatasetReader.h)
