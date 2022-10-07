#include "Transformation.h"

const trans &Transformation::getForwardTransformation() const {
    return forwardTransformation;
}

const trans &Transformation::getInverseTransformation() const {
    return inverseTransformation;
}

Transformation::Transformation(trans forwardTransformation) : forwardTransformation(forwardTransformation){ }

void Transformation::calculateInverseTransformation() {
    this->inverseTransformation.translationX = -this->forwardTransformation.translationX;
    this->inverseTransformation.translationY = -this->forwardTransformation.translationY;
    this->inverseTransformation.translationZ = -this->forwardTransformation.translationZ;

}

Transformation::Transformation() = default;
