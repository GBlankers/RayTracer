#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <cmath>

#include "Ray.h"
#include "Math/Vec4.h"

class Camera {

// Function to return a ray given a certain pixel on the virtual screen
private:
    Vec4 displacement; // define where the virtual screen is located in space (assume the middle pixel having x=0)
    Vec4 viewDirection; // define the look direction -> 'points at'
    Vec4 crossDirection; // the cross product between the up vector and the view vector
    Vec4 upDirection; // Which direction is up? Defines an angle relative to the look direction
    Vec4 eyePosition; // Where is the eye positioned in front of the screen
    double distanceEyeFromScreen; // how many pixels is the eye from the screen
public:
    Camera(int virtualScreenWidth, double fov, Vec4 pointsAt, Vec4 virtualScreenDisplacement, double theta, double phi);
    Camera(int virtualScreenWidth, double fov, Vec4 pointsAt, Vec4 virtualScreenDisplacement);
    Camera() = default;
    Ray getRayFromPixel(double pixelX, double pixelY);
};


#endif //RAYTRACER_CAMERA_H
