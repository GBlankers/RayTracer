#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H

#include <cassert>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include <utility>

#include "LightSource.h"
#include "objectProperties.h"
#include "../Math/Vec4.h"
#include "../Collision.h"
#include "../Ray.h"
#include "../Transformation.h"
#include "../settings.h"
#include "../Colors/Color.h"
#include "../Colors/SingleColor.h"
#include "../Colors/ImageColor.h"

class Shape {
protected:
    Transformation t;
    LightComponents lightComponents;
    Material material;
public:
    explicit Shape(Transformation t, LightComponents lightComponents, Material material);

    virtual Collision checkCollision(Ray r) = 0;
    virtual bool checkHit(Ray r, double &t, bool &inside, double &t2) = 0;
    virtual bool checkHit(Ray r, double &t) = 0;

    virtual Vec4 calculateNormal(Vec4 hitPoint, bool inside) = 0;
    virtual void getColor(Vec4 hitPoint, double &r, double &g, double &b) = 0;
    virtual SingleColor* getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) = 0;

    const Transformation &getTransformation() const;
    virtual const LightComponents &getLightComponents() const;

    virtual bool isPointInside(Vec4 hitPoint) const = 0;
};

#endif //RAYTRACER_SHAPE_H
