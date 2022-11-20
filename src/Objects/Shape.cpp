#include "Shape.h"

/**
 * abstract shape class used to contain the general functions
 * @param t transformation to place the shape in the world space
 * @param R red color component, needs to be 0<=R<=1.0
 * @param G green color component, needs to be 0<=G<=1.0
 * @param B blue color component, needs to be 0<=B<=1.0
 */
Shape::Shape(Transformation t, Vec4 color, double ambient, double diffuse, double specular, double specularComponent,
             double reflectivity, double roughness, double transparency, double refractiveIndex)
    : t(t), color(color), ambient(ambient), diffuse(diffuse), specular(specular), specularExponent(specularComponent),
    reflectivity(reflectivity), roughness(roughness), transparency(transparency), refractiveIndex(refractiveIndex){
    assert(this->color.getX()>=0 && this->color.getX()<=1.0);
    assert(this->color.getY()>=0 && this->color.getY()<=1.0);
    assert(this->color.getZ()>=0 && this->color.getZ()<=1.0);
}

const Transformation &Shape::getT() const {
    return t;
}

void Shape::setColor(const Vec4 &colorArg) {
    Shape::color = colorArg;
}

const Vec4 &Shape::getColor() const {
    return color;
}

double Shape::getAmbient() const {
    return ambient;
}

double Shape::getReflectivity() const {
    return reflectivity;
}

Vec4 Shape::calculateDiffuseSpecularColor(double diffuseComponent, double specularComponent, Vec4 lightColor, Collision c) const {
    return lightColor*c.getColor()*this->diffuse*diffuseComponent
            +lightColor*c.getColor()*this->specular*pow(specularComponent, this->specularExponent);
}

double Shape::getRoughness() const {
    return roughness;
}

double Shape::getTransparency() const {
    return transparency;
}

double Shape::getRefractiveIndex() const {
    return refractiveIndex;
}
