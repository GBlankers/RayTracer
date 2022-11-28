#include "Shape.h"

#include <utility>

/**
 * abstract shape class used to contain the general functions
 * @param t transformation to place the shape in the world space
 * @param R red color component, needs to be 0<=R<=1.0
 * @param G green color component, needs to be 0<=G<=1.0
 * @param B blue color component, needs to be 0<=B<=1.0
 */
Shape::Shape(Transformation t, LightComponents lightComponents, Material material)
    : t(t), lightComponents(std::move(lightComponents)), material(std::move(material)){

    assert(this->lightComponents.color.getX()>=0 && this->lightComponents.color.getX()<=1.0);
    assert(this->lightComponents.color.getY()>=0 && this->lightComponents.color.getY()<=1.0);
    assert(this->lightComponents.color.getZ()>=0 && this->lightComponents.color.getZ()<=1.0);
}

Shape::Shape(Transformation t, const std::string &path, LightComponents lightComponents, Material material)
        : t(t), lightComponents(std::move(lightComponents)), material(std::move(material)){
    assert(this->lightComponents.color.getX()>=0 && this->lightComponents.color.getX()<=1.0);
    assert(this->lightComponents.color.getY()>=0 && this->lightComponents.color.getY()<=1.0);
    assert(this->lightComponents.color.getZ()>=0 && this->lightComponents.color.getZ()<=1.0);

    this->lightComponents.color={0, 0, 0, 0};

    unsigned error = lodepng::decode(image, width, height, path, LCT_RGB);
    if(error) {
        printf("error %u: %s\nDefault color will be used", error, lodepng_error_text(error));
    }
}

const Transformation &Shape::getTransformation() const {
    return t;
}

void Shape::getColor(Vec4 hitPoint, double &r, double &g, double &b) {
    r = lightComponents.color.getX();
    g = lightComponents.color.getY();
    b = lightComponents.color.getZ();
}
