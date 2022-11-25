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
#include "../../include/code/lodepng.h"

class Shape {
protected:
    Transformation t;
    Vec4 color{0, 0, 0, 0};
    double ambient, diffuse, specular, specularExponent, reflectivity, roughness, transparency, refractiveIndex;
    bool useColor = true;
    std::vector<unsigned char> image;
    unsigned width=0, height=0;
public:
    explicit Shape(Transformation t, Vec4 color, double ambient, double diffuse, double specular, double specularComponent,
                   double reflectivity, double roughness, double transparency, double refractiveIndex);
    explicit Shape(Transformation t, const std::string& path, double ambient, double diffuse, double specular, double specularComponent,
                   double reflectivity, double roughness, double transparency, double refractiveIndex);

    virtual Collision checkCollision(Ray r) = 0;
    virtual bool checkHit(Ray r, double &t, bool &inside) = 0;
    virtual bool checkHit(Ray r, double &t) = 0;
    virtual bool checkHit(Ray r) = 0;
    virtual Vec4 calculateNormal(Vec4 hitPoint, bool inside) = 0;
    virtual void getColor(Vec4 hitPoint, double &r, double &g, double &b);

    void setColor(const Vec4 &colorArg);
    double getReflectivity() const;
    double getAmbient() const;
    double getRoughness() const;
    double getTransparency() const;
    double getRefractiveIndex() const;

    Vec4 calculateDiffuseSpecularColor(double diffuseComponent, double specularComponent, Vec4 lightColor, Collision c) const;

    const Transformation &getT() const;
};


#endif //RAYTRACER_SHAPE_H
