cmake_minimum_required(VERSION 3.5)
project(RayTracing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -ansi -pedantic -Wall -O0 -lGL -lGLU -lglut")

set(SOURCE_FILES src/main.cpp src/Ray.h src/Point.h src/Ray.h src/Sphere.h src/Pixel.h src/Vec3.h src/LightSource.h src/Color.h src/Sphere.cpp src/Scene.cpp src/Scene.h src/Shape.h src/Plane.cpp src/Plane.h)

add_executable(RayTracing ${SOURCE_FILES})
