#include "Shape.h"

/**
 * abstract shape class used to contain the general functions
 * @param t transformation to place the shape in the world space
 * @param R red color component, needs to be 0<=R<=1.0
 * @param G green color component, needs to be 0<=G<=1.0
 * @param B blue color component, needs to be 0<=B<=1.0
 */
Shape::Shape(Transformation t, LightComponents lightComponents, Material material)
    : t(t), lightComponents(std::move(lightComponents)), material(std::move(material)){}

const Transformation &Shape::getTransformation() const {
    return t;
}
