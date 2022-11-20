#ifndef RAYTRACER_CONE_H
#define RAYTRACER_CONE_H

#include "Shape.h"

class Cone : public Shape{
public:
    explicit Cone(const Transformation &t, Vec4 color, double ambient, double diffuse, double specular,
                  double specularComponent, double reflectivity, double roughness, double transparency, double refractiveIndex);

    Collision checkCollision(Ray r) override;

    bool checkHit(Ray r, double &t, bool &inside) override;
    bool checkHit(Ray r, double &t) override;
    bool checkHit(Ray r) override;

    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;
};


#endif //RAYTRACER_CONE_H
