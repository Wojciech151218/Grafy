cmake_minimum_required(VERSION 3.27)
project(untitled16)

set(CMAKE_CXX_STANDARD 17)
include_directories(/home/wojciech/CLionProjects/TimeCounter)
add_executable(untitled16 main.cpp
        EdgeListGraph.cpp
        EdgeListGraph.h
        AdjacencyListGraph.cpp
        AdjacencyListGraph.h
)
target_link_libraries(untitled16 /home/wojciech/CLionProjects/TimeCounter/cmake-build-debug/libTimeCounter.a)

