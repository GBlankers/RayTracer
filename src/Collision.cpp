#include "Collision.h"

Collision::Collision(Vec4 collisionPoint, double t, Vec4 color) : collisionPoint(collisionPoint), t(t), color(color) {}

double Collision::getT() const {
    return t;
}

const Vec4 &Collision::getCollisionPoint() const {
    return collisionPoint;
}

double Collision::getR() const {
    return this->color.getX();
}

double Collision::getG() const {
    return this->color.getY();
}

double Collision::getB() const {
    return this->color.getZ();
}
