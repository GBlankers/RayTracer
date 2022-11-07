#include "Collision.h"

Collision::Collision(Vec4 collisionPoint, double t, Vec4 color) : collisionPoint(collisionPoint), t(t), color(color) {}

double Collision::getT() const {
    return t;
}

const Vec4 &Collision::getCollisionPoint() const {
    return collisionPoint;
}

const Vec4 &Collision::getColor() const {
    return color;
}

