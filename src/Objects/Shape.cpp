#include "Shape.h"

/**
 * abstract shape class used to contain the general functions
 * @param t transformation to place the shape in the world space
 * @param R red color component, needs to be 0<=R<=1.0
 * @param G green color component, needs to be 0<=G<=1.0
 * @param B blue color component, needs to be 0<=B<=1.0
 */
Shape::Shape(Transformation t, LightComponents lightComponents, Material material, const std::string &normalMapPath)
    : t(t), lightComponents(std::move(lightComponents)), material(std::move(material)){
    assert(this->lightComponents.color.getX()>=0 && this->lightComponents.color.getX()<=1.0);
    assert(this->lightComponents.color.getY()>=0 && this->lightComponents.color.getY()<=1.0);
    assert(this->lightComponents.color.getZ()>=0 && this->lightComponents.color.getZ()<=1.0);

    if(!normalMapPath.empty()){
        unsigned error = lodepng::decode(normalMap, normalMapWidth, normalMapHeight, normalMapPath, LCT_RGB);
        if(error) {
            printf("error %u: %s\nNo normal map will be used", error, lodepng_error_text(error));
        }
    }

}

Shape::Shape(Transformation t, const std::string &path, LightComponents lightComponents, Material material, const std::string &normalMapPath)
        : t(t), lightComponents(std::move(lightComponents)), material(std::move(material)){
    assert(this->lightComponents.color.getX()>=0 && this->lightComponents.color.getX()<=1.0);
    assert(this->lightComponents.color.getY()>=0 && this->lightComponents.color.getY()<=1.0);
    assert(this->lightComponents.color.getZ()>=0 && this->lightComponents.color.getZ()<=1.0);

    this->lightComponents.color={0, 0, 0, 0};

    unsigned error = lodepng::decode(image, width, height, path, LCT_RGB);
    if(error) {
        printf("error %u: %s\nDefault color will be used", error, lodepng_error_text(error));
    }

    if(!normalMapPath.empty()){
        unsigned error2 = lodepng::decode(normalMap, normalMapWidth, normalMapHeight, normalMapPath, LCT_RGB);
        if(error2) {
            printf("error %u: %s\nNo normal map will be used", error2, lodepng_error_text(error));
        }
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

// With both the normal and hitPoint in local coordinates
Vec4 Shape::manipulateNormal(Vec4 normal, Vec4 hitPoint) {
    double dx, dy, dz;
    Vec4 hitWorld = t.getForward()*hitPoint;
    // Default random noise using hashes and the roughness param
    // dividing the hash by the max value gives a return between 0 and 2 -> -1 -> between -1 and 1;
    // divide by x to give a smaller range and make the displacement of the vector smaller
    dx = (((double)doubleHash(hitWorld.getX()+hitWorld.getY()+hitWorld.getZ())/((double)std::numeric_limits<size_t>::max()/2.0))-1)/5;
    dy = (((double)doubleHash(hitWorld.getX()-hitWorld.getY()+hitWorld.getZ())/((double)std::numeric_limits<size_t>::max()/2.0))-1)/5;
    dz = (((double)doubleHash(hitWorld.getX()+hitWorld.getZ()-hitWorld.getX())/((double)std::numeric_limits<size_t>::max()/2.0))-1)/5;

    Vec4 displacement = {dx, dy, dz, 0};
    return normal + displacement*material.roughness;
}
