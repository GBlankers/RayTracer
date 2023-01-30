#ifndef RAYTRACER_CUBE_H
#define RAYTRACER_CUBE_H

#include "Shape.h"
#include <utility>

/**
 * Implementation of the cube shape
 */
class Cube : public Shape{
public:
    explicit Cube(const Transformation &t, LightComponents lightComponents, Material material);

    Collision checkCollision(Ray r) override;

    bool checkHit(Ray r, double &t, bool &inside, double &t2) override;
    bool checkHit(Ray r, double &t) override;

    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;

    /**
     * Check if the ray r at a time t is inside the unit cube
     * @param r the ray
     * @param t the time point
     * @return if the ray is at that time inside the unit cube
     */
    static bool checkInCube(Ray r, double t);

    /**
     * Return the 2 smallest objects of the list by reference
     * @param tList the list to find the 2 smallest objects in
     * @param t1 the smallest object
     * @param t2 the one-to-smallest object
     */
    static void give2Smallest(std::vector<double> tList, double &t1, double &t2);

    void getColor(Vec4 hitPoint, double &r, double &g, double &b) override;

    SingleColor* getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) override;

    bool isPointInside(Vec4 hitPoint) const override;
};


#endif //RAYTRACER_CUBE_H
