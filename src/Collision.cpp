#include "Collision.h"

Collision::Collision(Vec4 collisionPoint, double t, double r, double g, double b) : collisionPoint(collisionPoint), t(t),
                                                                                    r(r), g(g), b(b) {}

double Collision::getT() const {
    return t;
}

const Vec4 &Collision::getCollisionPoint() const {
    return collisionPoint;
}

double Collision::getR() const {
    return r;
}

double Collision::getG() const {
    return g;
}

double Collision::getB() const {
    return b;
}
