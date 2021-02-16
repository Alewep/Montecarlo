cmake_minimum_required(VERSION 3.0)

project(tree)


find_package(Threads)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)
add_compile_options(-Wall -Wpedantic)


set(SRCS
    arbrebin.cpp
    arbrecontigu.cpp
    narytree.cpp
    )
    
set(HEADERS
    arbrebin.h
    arbrecontigu.h
    narytree.h
    )


add_library(tree ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} )
