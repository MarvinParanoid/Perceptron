cmake_minimum_required(VERSION 3.30)
project(Perceptron)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

file(GLOB SOURCES "src/*.cpp")

link_libraries(sfml-graphics)
add_executable(Perceptron ${SOURCES})
