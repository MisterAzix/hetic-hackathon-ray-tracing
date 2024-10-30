cmake_minimum_required(VERSION 3.28)
project(hetic_hackathon_ray_tracing)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(hetic_hackathon_ray_tracing
        main.cpp
        src/lib/lodepng.cpp
        src/lib/lodepng.h
        src/Color.cpp
        src/Color.h
        src/Vector3.cpp
        src/Vector3.h
        src/Image.cpp
        src/Image.h
        src/Scene.cpp
        src/Scene.h
        src/Plane.cpp
        src/Plane.h
        src/Sphere.cpp
        src/Sphere.h
        src/Ray.cpp
        src/Ray.h
        src/Object.h
        src/Square.cpp
        src/Square.h
)
