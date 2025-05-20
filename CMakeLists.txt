cmake_minimum_required(VERSION 3.15)
project(OOCatcher)

set(CMAKE_CXX_STANDARD 20)

add_executable(OOCatcher
#        Preliminary/main.cpp
#        Preliminary/Point.cpp
#        Preliminary/Segment.cpp
#        Preliminary/Body.cpp
        Final/Point.cpp
        Final/Segment.cpp
        Final/Body.cpp
)

add_executable(SnowballMode
        Final/snowball_mode.cpp
        Final/Body.cpp
        Final/Segment.cpp
        Final/Point.cpp
)

add_executable(WalkerMode
        Final/walker_mode.cpp
        Final/Body.cpp
        Final/Segment.cpp
        Final/Point.cpp
)