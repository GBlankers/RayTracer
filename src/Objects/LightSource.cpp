#include "LightSource.h"

LightSource::LightSource(const Vec4 &position, const Vec4 &pointsAt, double intensity) : position(position),
                                                                                                intensity(intensity){
    this->direction = pointsAt-position;
    this->color = Vec4(1, 0, 1, 0);
}

LightSource LightSource::transform(Matrix4 trans) {
    this->inversePos = trans * this->getPosition();
    return {this->inversePos, trans * this->getDirection(), this->intensity};
}

double LightSource::calculateDiffuse(Vec4 normal, Vec4 hitPoint) {
    Vec4 normalizedDirection = Vec4::normalize(this->inversePos-hitPoint);
    double angle = acos(Vec4::dot(normal, normalizedDirection));
    if(angle > M_PI_2){
        return 0.0;
    } else {
        return 1-(angle/M_PI_2);
    }
}

double LightSource::calculateSpecular(Vec4 viewDirection, Vec4 hitPoint) {
    Vec4 normalizedDirection = Vec4::normalize(this->inversePos-hitPoint);

    return 0;
}

const Vec4 &LightSource::getPosition() const {
    return position;
}

const Vec4 &LightSource::getDirection() const {
    return direction;
}

const Vec4 &LightSource::getInversePos() const {
    return inversePos;
}

const Vec4 &LightSource::getColor() const {
    return color;
}

double LightSource::getIntensity() const {
    return intensity;
}
