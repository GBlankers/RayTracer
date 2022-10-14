#include "Transformation.h"

const trans &Transformation::getForwardTransformation() const {
    return forwardTransformation;
}

const trans &Transformation::getInverseTransformation() const {
    return inverseTransformation;
}

Transformation::Transformation(trans forwardTransformation) : forwardTransformation(forwardTransformation){
    this->calculateInverseTransformation();
}

void Transformation::calculateInverseTransformation() {
    this->inverseTransformation.translation.setX(-this->forwardTransformation.translation.getX());
    this->inverseTransformation.translation.setY(-this->forwardTransformation.translation.getY());
    this->inverseTransformation.translation.setZ(-this->forwardTransformation.translation.getZ());
    // TODO: Add rotation and scaling
}

Transformation::Transformation() = default;
