#ifndef RAYTRACER_OBJECTPROPERTIES_H
#define RAYTRACER_OBJECTPROPERTIES_H

#include "../Math/Vec4.h"
#include "../Colors/Color.h"
#include "../Normal/normalManipulator.h"
#include "../Normal/normalRoughness.h"

/**
 * Container for all the properties related to light, this includes: the color, ambient, diffuse and specular components.
 * A reset method is also implemented.
 */
struct LightComponents{
    std::string name;
    Color* color;
    double ambient = 0;
    double diffuse = 0;
    double specular = 0;
    double specularExponent = 0;
    void reset(){
        name = "";
        color = {};
        ambient = 0;
        diffuse = 0;
        specular = 0;
        specularExponent = 0;
    }
};

/**
 * A container for all properties related to the material, this includes: a normal manipulator, reflectivity, roughness,
 * transparency and refractive index.
 * A reset method is also implemented as well as a manipulateNormal function to make function calls in objects cleaner.
 */
struct Material{
    std::string name;
    normalManipulator* manipulator;
    double reflectivity = 0;
    double roughness = 0;
    double transparency = 0;
    double refractiveIndex = 1;
    void reset(){
        name = "";
        reflectivity = 0;
        roughness = 0;
        transparency = 0;
        refractiveIndex = 1;
    }
    Vec4 manipulateNormal(Vec4 normal, double u, double v, Vec4 worldHit) const{
        return manipulator->manipulateNormal(normal, this->roughness, u, v, worldHit);
    }
};

#endif //RAYTRACER_OBJECTPROPERTIES_H
