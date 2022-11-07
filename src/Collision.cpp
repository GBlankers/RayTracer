#include "Collision.h"

Collision::Collision(Vec4 collisionPoint, double t, Vec4 color, Vec4 normal)
        : collisionPoint(collisionPoint), t(t), color(color), normal(normal) {}

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

