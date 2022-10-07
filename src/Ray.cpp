#include "Ray.h"

Ray::Ray(int x, int y, int z, double vx, double vy, double vz, int reflectionNr) : x(x), y(y), z(z), vx(vx), vy(vy), vz(vz),
                                                                                   reflectionNr(reflectionNr) {}

Ray::Ray(int x, int y, int z, double vx, double vy, double vz) : x(x), y(y), z(z), vx(vx), vy(vy), vz(vz) {
    this->reflectionNr = 0;
}

double Ray::getVx() const {
    return vx;
}

double Ray::getVy() const {
    return vy;
}

double Ray::getVz() const {
    return vz;
}

double Ray::getX() const {
    return x;
}

double Ray::getY() const {
    return y;
}

double Ray::getZ() const {
    return z;
}
