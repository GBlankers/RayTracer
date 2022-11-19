#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H

#include <cassert>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>

#include "../Math/Vec4.h"
#include "../Collision.h"
#include "../Ray.h"
#include "../Transformation.h"
#include "LightSource.h"
#include "../settings.h"

class Shape {
private:
    Transformation t;
    Vec4 color;
    double ambient, diffuse, specular, specularExponent, reflectivity, roughness, transparency;
public:
    explicit Shape(Transformation t, Vec4 color, double ambient, double diffuse, double specular,
                   double specularComponent, double reflectivity, double roughness);

    virtual Collision checkCollision(Ray r) = 0;
    virtual bool checkHit(Ray r, double &t) = 0;
    virtual bool checkHit(Ray r) = 0;
    virtual Vec4 calculateNormal(Vec4 hitPoint) = 0;

    void setColor(const Vec4 &colorArg);
    const Vec4 &getColor() const;
    double getReflectivity() const;
    double getAmbient() const;
    double getRoughness() const;

    Vec4 calculateDiffuseSpecularColor(double diffuseComponent, double specularComponent, Vec4 lightColor, Collision c) const;

    const Transformation &getT() const;
};


#endif //RAYTRACER_SHAPE_H
