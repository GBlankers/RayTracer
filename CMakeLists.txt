cmake_minimum_required(VERSION 3.23)
project(RayTracer)
set(CMAKE_CXX_STANDARD 17)

set(OpenGLLinkers -lglut -lGLU -lGL)

add_library(srcFiles src/Ray.cpp src/Ray.h src/Objects/Shape.cpp src/Objects/Shape.h src/Collision.cpp src/Collision.h src/Transformation.cpp
        src/Transformation.h src/Math/Vec4.cpp src/Math/Vec4.h src/Math/Matrix4.cpp src/Objects/Plane.h src/Objects/Plane.cpp
        src/Math/Matrix4.h src/Objects/Cube.cpp src/Objects/Cube.h src/Objects/Sphere.h src/Objects/Sphere.cpp src/Objects/Cone.h src/Objects/Cone.cpp
        src/Objects/LightSource.cpp src/Objects/LightSource.h src/Scene.cpp src/Scene.h src/Camera.cpp src/Camera.h src/settings.h
        src/Math/Utils.cpp src/Math/Utils.h src/Objects/SkyBox.cpp src/Objects/SkyBox.h include/code/lodepng.h include/code/lodepng.cpp src/Objects/objectProperties.h
        src/Colors/Color.h src/Colors/SingleColor.cpp src/Colors/SingleColor.h src/Colors/ImageColor.cpp src/Colors/ImageColor.h src/Colors/CheckerBoard.cpp src/Colors/CheckerBoard.h)
set_target_properties(srcFiles PROPERTIES LINKER_LANGUAGE CXX)

find_package(RapidJSON)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(RayTracer main.cpp)
target_link_libraries(RayTracer srcFiles ${OpenGLLinkers} Threads::Threads)


add_executable(Test test.cpp)
target_link_libraries(Test srcFiles ${OpenGLLinkers})