#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
#include "Camera.h"

/**
 * Constructor for the camera class, with adaptable theta and phi to tilt the virtual screen
 * @param virtualScreenWidth what is the width of the screen, in most coses this is 2*W. Used to calculate the distance
 * to the virtual screen with the fov.
 * @param fov field of view in degrees. Used to calculate the distance to the virtual screen
 * @param pointsAt where are most of the objects located
 * @param virtualScreenDisplacement at what coordinate is the middle pixel of the virtual screen located
 * @param theta angle between the up-vector and the positive y-axis
 * @param phi angle between the up-vector and the positive z-axis
 */
Camera::Camera(double fov, Vec4 pointsAt, Vec4 virtualScreenDisplacement, double theta, double phi) : displacement(virtualScreenDisplacement){
    this->distanceEyeFromScreen = W/(tan(fov*M_PI/360));
    this->viewDirection = Vec4::normalize(pointsAt-virtualScreenDisplacement);

    // Up direction calculation
    this->upDirection = Vec4(theta*M_PI/180, phi*M_PI/180);

    // Calculation for the eye direction
    double stepPerT = Vec4::length(this->viewDirection);
    double tForDistance = distanceEyeFromScreen/stepPerT;
    Ray rayDirection(this->displacement, this->viewDirection);
    this->eyePosition = rayDirection.at(-tForDistance);

    // Cross vector calculation
    this->crossDirection = Vec4::cross(this->viewDirection, this->upDirection);
}

Camera::Camera(double fov, Vec4 pointsAt, Vec4 virtualScreenDisplacement) : displacement(virtualScreenDisplacement){
    this->distanceEyeFromScreen = W/(tan(fov*M_PI/360));
    this->viewDirection = Vec4::normalize(pointsAt-virtualScreenDisplacement);

    // Up direction calculation
    double phi = M_PI_2-atan(-viewDirection.getZ()/viewDirection.getX());
    if(std::isnan(phi)){
        this->upDirection = Vec4(1, 0, 0, 0);
    } else {
        this->upDirection = Vec4(0, phi);
    }

    // Calculation for the eye direction
    double stepPerT = Vec4::length(this->viewDirection);
    double tForDistance = distanceEyeFromScreen/stepPerT;
    Ray rayDirection(this->displacement, this->viewDirection);
    this->eyePosition = rayDirection.at(-tForDistance);

    // Cross vector calculation
    this->crossDirection = Vec4::cross(this->viewDirection, this->upDirection);
}

Ray Camera::getRayFromPixel(double pixelX, double pixelY) {
    return {eyePosition,Vec4::normalize((displacement+crossDirection*pixelX+upDirection*pixelY)-eyePosition)};
}

#pragma clang diagnostic pop