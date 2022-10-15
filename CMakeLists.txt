cmake_minimum_required(VERSION 3.23)
project(RayTracer)
set(CMAKE_CXX_STANDARD 17)

set(OpenGLLinkers -lglut -lGLU -lGL)

add_library(srcFiles src/Ray.cpp src/Ray.h src/Shape.cpp src/Shape.h src/Collision.cpp src/Collision.h src/Transformation.cpp
        src/Transformation.h src/helpers.cpp src/helpers.h src/Math/Vec4.cpp src/Math/Vec4.h src/settings.h src/Math/Matrix4.cpp
        src/Math/Matrix4.h src/Sphere.cpp src/Sphere.h)
set_target_properties(srcFiles PROPERTIES LINKER_LANGUAGE CXX)

add_executable(RayTracer main.cpp)
target_link_libraries(RayTracer srcFiles ${OpenGLLinkers})

add_executable(Test test.cpp)
target_link_libraries(Test srcFiles)