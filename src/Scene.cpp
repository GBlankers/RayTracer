#include "Scene.h"

Scene::Scene() = default;

void Scene::fillScene2() {
    Transformation tCube1;
    tCube1.addScaling(400, 400, 400);
    tCube1.addRotationY(DEG_TO_RADIANS(-30));
    tCube1.addRotationX(DEG_TO_RADIANS(30));
    tCube1.addTranslation(2000, 200, -100);
    Cube cube1(tCube1, {1, 1, 0, 0});
    objectVector.push_back(std::make_shared<Cube>(cube1));

    Transformation tSphere2;
    tSphere2.addScaling(400, 400, 400);
    tSphere2.addTranslation(2000, -800, 100);
    Sphere sphere2(tSphere2, {0, 0, 1, 0});
    objectVector.push_back(std::make_shared<Sphere>(sphere2));

//    Transformation tPlane1;
//    tPlane1.addTranslation(0, -450, 0);
//    Plane plane1(tPlane1, {1, 1, 1, 0});
//    //plane1.setCheckerBoardPattern(true);
//    objectVector.push_back(std::make_shared<Plane>(plane1));

    // LIGHT
    LightSource light({2000,2000,0,1}, {0,-2000,0,0});
    lightVector.push_back(std::make_shared<LightSource>(light));

    LightSource l2({0, 0, 0, 1}, {2000, 0, 0, 0});
    lightVector.push_back(std::make_shared<LightSource>(l2));
}

void Scene::fillScene() {
//    Transformation tSphere1;
//    tSphere1.addScaling(400, 400, 400);
//    tSphere1.addTranslation(2000, -1200, -1200);
//    Sphere sphere1(tSphere1, {0, 0, 1, 0});
//    objectVector.push_back(std::make_shared<Sphere>(sphere1));

    Transformation tSphere2;
    tSphere2.addScaling(400, 400, 400);
    tSphere2.addTranslation(2500, -600, -600);
    Sphere sphere2(tSphere2, {0, 0, 1, 0});
    objectVector.push_back(std::make_shared<Sphere>(sphere2));

    Transformation tSphere3;
    tSphere3.addScaling(400, 400, 400);
    tSphere3.addTranslation(2500, 0, 0);
    Sphere sphere3(tSphere3, {1, 0, 0, 0});
    objectVector.push_back(std::make_shared<Sphere>(sphere3));

    Transformation tSphere4;
    tSphere4.addScaling(400, 400, 400);
    tSphere4.addTranslation(2500, 600, 600);
    Sphere sphere4(tSphere4, {0, 1, 0, 0});
    objectVector.push_back(std::make_shared<Sphere>(sphere4));

//    Transformation tSphere5;
//    tSphere5.addScaling(400, 400, 400);
//    tSphere5.addTranslation(2000, 1200, 1200);
//    Sphere sphere5(tSphere5, {0, 0, 1, 0});
//    objectVector.push_back(std::make_shared<Sphere>(sphere5));


    Transformation tCube1;
    tCube1.addScaling(400, 400, 400);
    tCube1.addRotationY(DEG_TO_RADIANS(-30));
    tCube1.addRotationX(DEG_TO_RADIANS(30));
    tCube1.addTranslation(2500, 800, -1200);
    Cube cube1(tCube1, {1, 1, 0, 0});
    objectVector.push_back(std::make_shared<Cube>(cube1));

    Transformation tCube2;
    tCube2.addScaling(400, 400, 400);
    tCube2.addRotationY(DEG_TO_RADIANS(-30));
    tCube2.addRotationX(DEG_TO_RADIANS(30));
    tCube2.addTranslation(2500, -800, 1200);
    Cube cube2(tCube2, {0, 1, 1, 0});
    objectVector.push_back(std::make_shared<Cube>(cube2));

    Transformation tCone1;
    tCone1.addScaling(400, 400, 400);
    tCone1.addRotationZ(DEG_TO_RADIANS(-30));
    tCone1.addRotationX(DEG_TO_RADIANS(30));
    tCone1.addTranslation(2500, -700, -1900);
    Cone cone1(tCone1, {0, 0, 1, 0});
    objectVector.push_back(std::make_shared<Cone>(cone1));


    Transformation tPlane1;
    tPlane1.addTranslation(0, -1500, 0);
    Plane plane1(tPlane1, {1, 1, 1, 0});
    //plane1.setCheckerBoardPattern(true);
    objectVector.push_back(std::make_shared<Plane>(plane1));

    // LIGHT
    LightSource light({0,1000,0,1}, {2000,-1000,0,0});
    lightVector.push_back(std::make_shared<LightSource>(light));
}

void Scene::fillScene3(){
    Transformation tSphere2;
    tSphere2.addScaling(400, 400, 400);
    tSphere2.addTranslation(2500, -600, -800);
    Sphere sphere2(tSphere2, {0, 0, 1, 0});
    objectVector.push_back(std::make_shared<Sphere>(sphere2));

    Transformation tSphere3;
    tSphere3.addScaling(400, 400, 400);
    tSphere3.addTranslation(2500, 0, 0);
    Sphere sphere3(tSphere3, {1, 0, 0, 0});
    objectVector.push_back(std::make_shared<Sphere>(sphere3));

    Transformation tSphere4;
    tSphere4.addScaling(400, 400, 400);
    tSphere4.addTranslation(2500, -600, 800);
    Sphere sphere4(tSphere4, {0, 1, 0, 0});
    objectVector.push_back(std::make_shared<Sphere>(sphere4));

    Transformation tPlane1;
    tPlane1.addTranslation(0, -1000, 0);
    Plane plane1(tPlane1, {1, 1, 1, 0});
    //plane1.setCheckerBoardPattern(true);
    objectVector.push_back(std::make_shared<Plane>(plane1));

    // LIGHT
    LightSource light({2500,1000,0,1}, {0,-1000,0,0});
    lightVector.push_back(std::make_shared<LightSource>(light));
}

const std::vector<std::shared_ptr<Shape>> &Scene::getObjectVector() const {
    return objectVector;
}

const std::vector<std::shared_ptr<LightSource>> &Scene::getLightVector() const {
    return lightVector;
}

void Scene::fillScene4() {
    Transformation tCube1;
    tCube1.addScaling(300, 300, 300);
    tCube1.addRotationY(DEG_TO_RADIANS(30));
    tCube1.addRotationZ(DEG_TO_RADIANS(30));
    tCube1.addTranslation(2500, 0, 0);
    Cube cube1(tCube1, {0, 0, 1, 0});
    objectVector.push_back(std::make_shared<Cube>(cube1));

    Transformation tCube2;
    tCube2.addScaling(300, 300, 300);
    tCube2.addRotationZ(DEG_TO_RADIANS(60));
    tCube2.addRotationX(DEG_TO_RADIANS(30));
    tCube2.addTranslation(2500, -500, 950);
    Cube cube2(tCube2, {0, 1, 0, 0});
    objectVector.push_back(std::make_shared<Cube>(cube2));

    Transformation tCube3;
    tCube3.addScaling(300, 300, 300);
    tCube3.addRotationZ(DEG_TO_RADIANS(-60));
    tCube3.addRotationX(DEG_TO_RADIANS(30));
    tCube3.addTranslation(2500, -500, -950);
    Cube cube3(tCube3, {1, 0, 0, 0});
    objectVector.push_back(std::make_shared<Cube>(cube3));


    Transformation tPlane1;
    tPlane1.addTranslation(0, -1000, 0);
    Plane plane1(tPlane1, {1, 1, 1, 0});
    plane1.setCheckerBoardPattern(true, 500);
    objectVector.push_back(std::make_shared<Plane>(plane1));

    // LIGHT
    LightSource light({2500,4000,0,1}, {0,-1000,0,0});
    lightVector.push_back(std::make_shared<LightSource>(light));
}
