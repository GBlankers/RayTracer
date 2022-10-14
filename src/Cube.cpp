#include "Cube.h"

Cube::Cube(const Transformation &t) : Shape(t) {}

Collision Cube::checkCollision(Ray r) {
    return {Vec3(0,0,0),0,0,0,0};
}
