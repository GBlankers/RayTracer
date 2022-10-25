#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include "Objects/Shape.h"
#include "Objects/Sphere.h"
#include "Objects/Cube.h"
#include "Objects/Plane.h"

#include <memory>
#include <vector>


#define DEG_TO_RADIANS(X) (X*M_PI/180)

class Scene {
private:
    std::vector<std::shared_ptr<Shape>> objectVector;

public:
    using array_type = std::vector<std::shared_ptr<Shape>>;
    using iterator = array_type::iterator;
    using const_iterator = array_type::const_iterator;

    explicit Scene();
    int numberOfObjects();

    inline iterator begin() noexcept {return objectVector.begin();}
    inline const_iterator cbegin() const noexcept {return objectVector.cbegin();}
    inline iterator end() noexcept {return objectVector.end();}
    inline const_iterator cend() const noexcept {return objectVector.cend();}

};


#endif //RAYTRACER_SCENE_H
