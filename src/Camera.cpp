#include "Camera.h"

Camera::Camera(int virtualScreenWidth, double fov, Vec4 pointsAt, Vec4 virtualScreenDisplacement, Vec4 upVector) : fov(fov) {
    this->distanceEyeFromScreen = ((double)virtualScreenWidth/2)/(tan(fov*M_PI/360));
    this->viewDirection = virtualScreenDisplacement-pointsAt;
    this->upDirection = upVector;
}
