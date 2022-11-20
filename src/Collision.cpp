#include "Collision.h"

Collision::Collision(Vec4 collisionPoint, double t, Vec4 color, Vec4 normal, bool inside, double reflectivity, double transparency,
                     double refractiveIndex): collisionPoint(collisionPoint), t(t), color(color), normal(normal), inside(inside),
                     reflectivity(reflectivity), transparency(transparency), refractiveIndex(refractiveIndex) {}

double Collision::getT() const {
    return t;
}

const Vec4 &Collision::getCollisionPoint() const {
    return collisionPoint;
}

const Vec4 &Collision::getColor() const {
    return color;
}

const Vec4 &Collision::getNormal() const {
    return normal;
}

double Collision::getReflectivity() const {
    return reflectivity;
}

double Collision::getTransparency() const {
    return transparency;
}

double Collision::getRefractiveIndex() const {
    return refractiveIndex;
}

/**
 * Check if the collision happened inside an object. This check is necessary for refractions where this depends on which
 * way the ray is going
 * @return if the collision is inside an object
 */
bool Collision::isInside() const {
    return inside;
}

void Collision::setReflectivity(double reflectivity) {
    Collision::reflectivity = reflectivity;
}

