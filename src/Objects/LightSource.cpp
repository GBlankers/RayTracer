#include "LightSource.h"

LightSource::LightSource(const Vec4 &position, const Vec4 &pointsAt) : position(position) {
    this->direction = pointsAt-position;
}

LightSource LightSource::transform(Matrix4 trans) {
    this->inversePos = trans * this->getPosition();
    return {this->inversePos, trans * this->getDirection()};
}

double LightSource::calculateIntensity(Vec4 normal, Vec4 hitPoint) {
    Vec4 normalizedDirection = this->inversePos-hitPoint;
    normalizedDirection.normalize();
    double angle = acos(Vec4::dot(normal, normalizedDirection));
    if(angle > M_PI_2){
        return 0.0;
    } else {
        return 1-(angle/M_PI_2);
    }
}

const Vec4 &LightSource::getPosition() const {
    return position;
}

const Vec4 &LightSource::getDirection() const {
    return direction;
}
