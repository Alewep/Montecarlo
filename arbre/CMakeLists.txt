cmake_minimum_required(VERSION 3.5)

project(arbre LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(arbre arbre.cpp main.cpp)
