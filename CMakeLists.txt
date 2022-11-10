cmake_minimum_required(VERSION 3.23)
project(RayTracer)
set(CMAKE_CXX_STANDARD 17)

set(OpenGLLinkers -lglut -lGLU -lGL)

add_library(srcFiles src/Ray.cpp src/Ray.h src/Objects/Shape.cpp src/Objects/Shape.h src/Collision.cpp src/Collision.h src/Transformation.cpp
        src/Transformation.h src/Math/Vec4.cpp src/Math/Vec4.h src/Math/Matrix4.cpp src/Objects/Plane.h src/Objects/Plane.cpp
        src/Math/Matrix4.h src/Objects/Cube.cpp src/Objects/Cube.h src/Objects/Sphere.h src/Objects/Sphere.cpp src/Objects/Cone.h src/Objects/Cone.cpp
        src/Objects/LightSource.cpp src/Objects/LightSource.h src/Scene.cpp src/Scene.h src/Camera.cpp src/Camera.h src/settings.h src/Math/Utils.cpp src/Math/Utils.h)
set_target_properties(srcFiles PROPERTIES LINKER_LANGUAGE CXX)

add_executable(RayTracer main.cpp)
target_link_libraries(RayTracer srcFiles ${OpenGLLinkers})

add_executable(Test test.cpp)
target_link_libraries(Test srcFiles ${OpenGLLinkers})