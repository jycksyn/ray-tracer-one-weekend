cmake_minimum_required(VERSION 3.22)
project(ray_tracer_one_weekend)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(src)

add_executable(ray_tracer_one_weekend
        src/ray-tracer.cpp
        src/ray.h
        src/hitable.h
        src/sphere.h
        src/hitablelist.h
        src/camera.h
        src/material.h
        src/lambertian.h
        src/metal.h
        src/textured.h
        src/dielectric.h)
