#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <cmath>

#include "Ray.h"
#include "Math/Vec4.h"
#include "settings.h"

/**
 * Camera class to generate the rays going through pixels
 */
class Camera {
private:
    /**
     * define where the virtual screen is located in space (assume the middle pixel having x=0)
     */
    Vec4 displacement;
    /**
     * define the look direction -> 'points at'
     */
    Vec4 viewDirection;
    /**
     * the cross product between the up vector and the view vector
     */
    Vec4 crossDirection;
    /**
     * Which direction is up? Defines an angle relative to the look direction
     */
    Vec4 upDirection;
    /**
     * Where is the eye positioned in front of the screen
     */
    Vec4 eyePosition;
    /**
     * how many pixels is the eye from the screen
     */
    double distanceEyeFromScreen;
public:
    Camera(double fov, Vec4 pointsAt, Vec4 virtualScreenDisplacement, double theta, double phi);
    Camera(double fov, Vec4 pointsAt, Vec4 virtualScreenDisplacement);
    Camera() = default;
    /**
     * Function to return a ray given a certain pixel on the virtual screen
     * @param pixelX the x coordinate
     * @param pixelY the y coordinate
     * @return the ray that goes through the pixel
     */
    Ray getRayFromPixel(double pixelX, double pixelY);
};


#endif //RAYTRACER_CAMERA_H
