#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include "Objects/Shape.h"
#include "Objects/Sphere.h"
#include "Objects/Cube.h"
#include "Objects/Plane.h"
#include "Objects/Cone.h"

#include "rapidjson/document.h"

#include <memory>
#include <vector>
#include <fstream>
#include <sstream>


#define DEG_TO_RADIANS(X) (X*M_PI/180)

class Scene {
private:
    std::vector<std::shared_ptr<Shape>> objectVector;
    std::vector<std::shared_ptr<LightSource>> lightVector;

public:
    explicit Scene();
    void fillScene(const std::string& filename);
    void fillScene();
    void fillScene2();
    void fillScene3();
    void fillScene4();

    const std::vector<std::shared_ptr<Shape>> &getObjectVector() const;

    const std::vector<std::shared_ptr<LightSource>> &getLightVector() const;
};


#endif //RAYTRACER_SCENE_H
