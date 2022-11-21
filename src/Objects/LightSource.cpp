#include "LightSource.h"

LightSource::LightSource(const Vec4 &position, const Vec4 &pointsAt, Vec4 color, double intensity)
        : position(position), color(color), intensity(intensity){}

double LightSource::calculateDiffuse(Vec4 normal, Vec4 hitPoint) {
    Vec4 normalizedDirection = Vec4::normalize(this->position-hitPoint);
    double angle = acos(Vec4::dot(normal, normalizedDirection));
    if(angle > M_PI_2){
        return 0.0;
    } else {
        return 1-(angle/M_PI_2);
    }
}

double LightSource::calculateSpecular(Vec4 normal, Vec4 viewDirection, Vec4 hitPoint) {
    Vec4 normalizedDirection = Vec4::normalize(this->position-hitPoint);
    Vec4 directionToEye = Vec4::normalize(viewDirection*-1);
    Vec4 halfWayVector = Vec4::normalize(normalizedDirection+directionToEye);

    return Vec4::dot(halfWayVector, normal);
}

const Vec4 &LightSource::getPosition() const {
    return position;
}

const Vec4 &LightSource::getColor() const {
    return color;
}

double LightSource::getIntensity() const {
    return intensity;
}
