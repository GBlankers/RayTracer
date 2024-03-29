#include "Collision.h"

Collision::Collision(Ray incoming, double t, Vec4 normal, bool inside, LightComponents lightComponents, Material material, double t2) :
                incoming(incoming), t(t), t2(t2), normal(normal), inside(inside), lightComponents(std::move(lightComponents)),
                material(std::move(material)), hitPoint(incoming.at(t)), color(lightComponents.color->getColor(0, 0, {}, {})) {}


Collision::Collision() = default;

double Collision::getT() const {
    return t;
}

double Collision::getT2() const {
    return t2;
}

const Vec4 &Collision::getCollisionPoint() const {
    return hitPoint;
}

const Vec4 &Collision::getColor() const {
    return color;
}

const Vec4 &Collision::getNormal() const {
    return normal;
}

double Collision::getRefractiveIndex() const {
    return material.refractiveIndex;
}

/**
 * Check if the collision happened inside an object. This check is necessary for refractions where this depends on which
 * way the ray is going
 * @return if the collision is inside an object
 */
bool Collision::isInside() const {
    return inside;
}

const LightComponents &Collision::getLightComponents() const {
    return lightComponents;
}

const Material &Collision::getMaterial() const {
    return material;
}

/**
     * Needed for total internal refraction
     * @param reflectivity
     */
void Collision::setReflectivity(double reflectivity) {
    material.reflectivity = reflectivity;
}

const Ray &Collision::getIncoming() const {
    return incoming;
}

