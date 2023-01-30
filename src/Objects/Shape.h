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

    /**
     * Check if a ray collides with the current object. If there is a collision, a Collision object will be constructed
     * with all the necessary parameters (see the Collision class for more information). If there is no collision, an empty
     * Collision class will be returned
     * @param r the incoming ray which will be used to check the collision
     * @return a collision class, empty or filled depending on the collision
     */
    virtual Collision checkCollision(Ray r) = 0;

    /**
     * The actual implementation of the math used for collision checking with the ray. The time of the hit as well as the
     * time when the ray exits the object and if the ray starts inside will be returned as reference parameters
     * @param r the incoming ray, used to check the collision
     * @param t the time when the hit occurred, will be -1 when there is no hit
     * @param inside boolean, check if the ray starts inside the object (needed for normal calculations)
     * @param t2 the time when the ray exits the object
     * @return boolean if there is a hit or not
     */
    virtual bool checkHit(Ray r, double &t, bool &inside, double &t2) = 0;

    /**
     * Simplified version of the check hit function. This one will be used for lighting calculation, the simplified version
     * only takes the ray, changes the time of the hit and returns a boolean when there is a hit or not.
     * @param r the incoming ray, used to check the collision
     * @param t the time when the hit occurred, will be -1 when there is no hit
     * @return boolean if there is a hit or not
     */
    virtual bool checkHit(Ray r, double &t) = 0;


    /**
     * Calculate the normal at the point where the hit occurred. When the object is inside the direction of the normal
     * needs to be flipped.
     * @param hitPoint the point in world coordinates where the hit happened
     * @param inside boolean, if the normal is pointing inside the object.
     * @return the normal in Vec4 form.
     */
    virtual Vec4 calculateNormal(Vec4 hitPoint, bool inside) = 0;

    /**
     * Get the color of the object at the point where the hit occurred. Use call by reference to return the color values
     * @param hitPoint the point in world coordinates where the hit happened
     * @param r the red value
     * @param g the green value
     * @param b the blue value
     */
    virtual void getColor(Vec4 hitPoint, double &r, double &g, double &b) = 0;

    /**
     * Function used to create more realistic boolean difference shapes. The solid texture of another object will be
     * projected onto this object
     * @param hitPoint the point in world coordinates where the hit happened
     * @param l the light components of the other object.
     * @return a single color of the hit on this object using the light components of the second shape.
     */
    virtual SingleColor* getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) = 0;


    /**
     * Return the transformation of the current shape
     * @return the transformation of the current shape
     */
    const Transformation &getTransformation() const;

    /**
     * get the light components of the current shape
     * @return the light components of the current shape
     */
    virtual const LightComponents &getLightComponents() const;


    /**
     * Given a point, check if this point is on or inside the current shape
     * @param hitPoint the point in world coordinates, which needs to be checked.
     * @return if the point is on or inside the current object
     */
    virtual bool isPointInside(Vec4 hitPoint) const = 0;
};

#endif //RAYTRACER_SHAPE_H
