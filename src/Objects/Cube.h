#ifndef RAYTRACER_CUBE_H
#define RAYTRACER_CUBE_H

#include "Shape.h"

class Cube : public Shape{
public:
    explicit Cube(const Transformation &t, Vec4 color, double ambient, double diffuse, double specular);

    Collision checkCollision(Ray r) override;

    double shadowDiffuseSpecular(Vec4 hitPoint, std::vector<std::shared_ptr<LightSource>> l,
                                 std::vector<std::shared_ptr<Shape>> worldObjects) override;

    bool checkHit(Ray r, double &t) override;
    bool checkHit(Ray r) override;
    Vec4 calculateNormal(Vec4 hitPoint) override;

    static bool checkInCube(Ray r, double t);
};


#endif //RAYTRACER_CUBE_H
