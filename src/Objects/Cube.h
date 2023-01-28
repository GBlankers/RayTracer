#ifndef RAYTRACER_CUBE_H
#define RAYTRACER_CUBE_H

#include "Shape.h"

class Cube : public Shape{
public:
    explicit Cube(const Transformation &t, LightComponents lightComponents, Material material);

    Collision checkCollision(Ray r) override;

    bool checkHit(Ray r, double &t, bool &inside, double &t2) override;
    bool checkHit(Ray r, double &t) override;

    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;

    static bool checkInCube(Ray r, double t);
    static void give2Smallest(std::vector<double> tList, double &t1, double &t2);

    void getColor(Vec4 hitPoint, double &r, double &g, double &b) override;

    SingleColor* getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) override;

    bool isPointInside(Vec4 hitPoint) const override;
};


#endif //RAYTRACER_CUBE_H
