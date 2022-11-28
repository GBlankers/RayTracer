#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H

#include <cassert>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>

#include "LightSource.h"
#include "objectProperties.h"
#include "../Math/Vec4.h"
#include "../Collision.h"
#include "../Ray.h"
#include "../Transformation.h"
#include "../settings.h"

#include "../../include/code/lodepng.h"

class Shape {
protected:
    Transformation t;
    LightComponents lightComponents;
    Material material;
    std::vector<unsigned char> image;
    unsigned width = 0, height = 0;
public:
    explicit Shape(Transformation t, LightComponents lightComponents, Material material);
    explicit Shape(Transformation t, const std::string &path, LightComponents lightComponents, Material material);

    virtual Collision checkCollision(Ray r) = 0;
    virtual bool checkHit(Ray r, double &t, bool &inside) = 0;
    virtual bool checkHit(Ray r, double &t) = 0;

    virtual Vec4 calculateNormal(Vec4 hitPoint, bool inside) = 0;
    virtual void getColor(Vec4 hitPoint, double &r, double &g, double &b);

    const Transformation &getTransformation() const;
};

#endif //RAYTRACER_SHAPE_H
