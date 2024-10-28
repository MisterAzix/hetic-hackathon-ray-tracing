cmake_minimum_required(VERSION 3.29)
project(hetic_hackathon_ray_tracing)

set(CMAKE_CXX_STANDARD 23)

add_executable(hetic_hackathon_ray_tracing 
    src/main.cpp 
    src/Vector3.cpp 
    src/Ray.cpp 
    src/Sphere.cpp 
    src/Scene.cpp
    
)

include_directories(include)
