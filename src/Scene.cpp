#include "Scene.h"

Scene::Scene() = default;

void Scene::fillScene() {
    Transformation tSphere1;
    tSphere1.addScaling(400, 400, 400);
    tSphere1.addTranslation(2000, -1000, -1000);
    Sphere sphere1(tSphere1, {0, 0, 1, 0});
    objectVector.push_back(std::make_shared<Sphere>(sphere1));

    Transformation tSphere2;
    tSphere2.addScaling(400, 400, 400);
    tSphere2.addTranslation(2000, -500, -500);
    Sphere sphere2(tSphere2, {0, 1, 0, 0});
    objectVector.push_back(std::make_shared<Sphere>(sphere2));

    Transformation tSphere3;
    tSphere3.addScaling(400, 400, 400);
    tSphere3.addTranslation(2000, 0, 0);
    Sphere sphere3(tSphere3, {1, 0, 0, 0});
    objectVector.push_back(std::make_shared<Sphere>(sphere3));

    Transformation tSphere4;
    tSphere4.addScaling(400, 400, 400);
    tSphere4.addTranslation(2000, 500, 500);
    Sphere sphere4(tSphere4, {0, 1, 0, 0});
    objectVector.push_back(std::make_shared<Sphere>(sphere4));

    Transformation tSphere5;
    tSphere5.addScaling(400, 400, 400);
    tSphere5.addTranslation(2000, 1000, 1000);
    Sphere sphere5(tSphere5, {0, 0, 1, 0});
    objectVector.push_back(std::make_shared<Sphere>(sphere5));


    Transformation tCube1;
    tCube1.addScaling(400, 400, 400);
    tCube1.addRotationY(DEG_TO_RADIANS(-30));
    tCube1.addRotationX(DEG_TO_RADIANS(30));
    tCube1.addTranslation(2000, 800, -1200);
    Cube cube1(tCube1, {1, 1, 0, 0});
    objectVector.push_back(std::make_shared<Cube>(cube1));

    Transformation tCube2;
    tCube2.addScaling(400, 400, 400);
    tCube2.addRotationY(DEG_TO_RADIANS(-30));
    tCube2.addRotationX(DEG_TO_RADIANS(30));
    tCube2.addTranslation(2000, -800, 1200);
    Cube cube2(tCube2, {0, 1, 1, 0});
    objectVector.push_back(std::make_shared<Cube>(cube2));

    Transformation tCone1;
    tCone1.addScaling(400, 400, 400);
    tCone1.addRotationZ(DEG_TO_RADIANS(-30));
    tCone1.addRotationX(DEG_TO_RADIANS(30));
    tCone1.addTranslation(2000, -700, -1900);
    Cone cone1(tCone1, {0, 1, 1, 0});
    objectVector.push_back(std::make_shared<Cone>(cone1));


    Transformation tPlane1;
    tPlane1.addTranslation(0, -2000, 0);
    Plane plane1(tPlane1, {0.5, 0.5, 0.5, 0});
    objectVector.push_back(std::make_shared<Plane>(plane1));
}

const std::vector<std::shared_ptr<Shape>> &Scene::getObjectVector() const {
    return objectVector;
}
