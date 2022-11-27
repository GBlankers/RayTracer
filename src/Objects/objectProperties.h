#ifndef RAYTRACER_OBJECTPROPERTIES_H
#define RAYTRACER_OBJECTPROPERTIES_H

#include "../Math/Vec4.h"

struct LightComponents{
    std::string name;
    Vec4 color{};
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

struct Material{
    std::string name;
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
};

#endif //RAYTRACER_OBJECTPROPERTIES_H
