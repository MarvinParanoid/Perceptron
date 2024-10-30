cmake_minimum_required(VERSION 3.30)
project(Perceptron)

set(CMAKE_CXX_STANDARD 20)

add_executable(Perceptron main.cpp
        Matrix.cpp
        Matrix.h
        DatasetReader.cpp
        DatasetReader.h
        ActivateFunction.cpp
        ActivateFunction.h
        Network.cpp
        Network.h)
