cmake_minimum_required(VERSION 3.23)
project(RayTracer)
set(CMAKE_CXX_STANDARD 17)

add_library(srcFiles src/Ray.cpp src/Ray.h src/Shape.cpp src/Shape.h src/Collision.cpp src/Collision.h src/Transformation.cpp src/Transformation.h src/helpers.cpp src/helpers.h src/Sphere.cpp src/Sphere.h src/Cube.cpp src/Cube.h src/Vec3.cpp src/Vec3.h)
set_target_properties(srcFiles PROPERTIES LINKER_LANGUAGE CXX)

add_executable(RayTracer main.cpp)
target_link_libraries(RayTracer srcFiles)