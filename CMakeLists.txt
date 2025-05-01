cmake_minimum_required(VERSION 3.15)
project(OOCatcher)

set(CMAKE_CXX_STANDARD 20)

add_executable(OOCatcher
        Preliminary/main.cpp
        Preliminary/Point.cpp
        Preliminary/Segment.cpp
        Preliminary/Body.cpp
)
