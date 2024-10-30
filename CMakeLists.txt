cmake_minimum_required(VERSION 3.30)
project(Perceptron)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "src/*.cpp")

add_executable(Perceptron ${SOURCES})
