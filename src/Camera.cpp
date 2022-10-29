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
Camera::Camera(int virtualScreenWidth, double fov, Vec4 pointsAt, Vec4 virtualScreenDisplacement, double theta, double phi) : displacement(virtualScreenDisplacement){
    this->distanceEyeFromScreen = ((double)virtualScreenWidth/2)/(tan(fov*M_PI/360));
    this->viewDirection = Vec4::normalize(pointsAt-virtualScreenDisplacement);

    // Up direction calculation
    this->upDirection = Vec4(theta, phi);

    // Calculation for the eye direction
    double stepPerT = Vec4::length(this->viewDirection);
    double tForDistance = distanceEyeFromScreen/stepPerT;
    Ray rayDirection(this->displacement, this->viewDirection);
    this->eyePosition = rayDirection.at(-tForDistance);

    // Cross vector calculation
    this->crossDirection = Vec4::cross(this->viewDirection, this->upDirection);
}

Ray Camera::getRayFromPixel(double pixelX, double pixelY) {
    return {this->eyePosition,
            Vec4::normalize((this->displacement+this->crossDirection*pixelX+this->upDirection*pixelY)- this->eyePosition)};
}

Camera::Camera(int virtualScreenWidth, double fov, Vec4 pointsAt, Vec4 virtualScreenDisplacement) : displacement(virtualScreenDisplacement){
    this->distanceEyeFromScreen = ((double)virtualScreenWidth/2)/(tan(fov*M_PI/360));
    this->viewDirection = Vec4::normalize(pointsAt-virtualScreenDisplacement);

    double theta, phi;
    theta = atan(-viewDirection.getY()/viewDirection.getX());
    phi = M_PI_2-atan(-viewDirection.getZ()/viewDirection.getX());
    // Up direction calculation
    this->upDirection = Vec4(theta, phi);

    // Calculation for the eye direction
    double stepPerT = Vec4::length(this->viewDirection);
    double tForDistance = distanceEyeFromScreen/stepPerT;
    Ray rayDirection(this->displacement, this->viewDirection);
    this->eyePosition = rayDirection.at(-tForDistance);

    // Cross vector calculation
    this->crossDirection = Vec4::cross(this->viewDirection, this->upDirection);
}
