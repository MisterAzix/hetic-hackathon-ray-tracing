cmake_minimum_required(VERSION 3.29)
project(hetic_hackathon_ray_tracing)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(hetic_hackathon_ray_tracing
        main.cpp
        src/Color.cpp
        src/Color.h
        src/Vector3.cpp
        src/Vector3.h
)
