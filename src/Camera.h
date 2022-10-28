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
    Vec4 upDirection; // Which direction is up? Defines an angle relative to the look direction
    double fov; // calculate the eye point with a fov parameter, the aspect ratio is fixed
    double distanceEyeFromScreen;

public:
    Camera(int virtualScreenWidth, double fov, Vec4 pointsAt, Vec4 virtualScreenDisplacement, Vec4 upVector);
    Ray getRayFromPixel;
};


#endif //RAYTRACER_CAMERA_H
