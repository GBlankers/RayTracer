#include "Scene.h"

Scene::Scene() = default;

const std::vector<std::shared_ptr<Shape>> &Scene::getObjectVector() const {
    return objectVector;
}

const std::vector<std::shared_ptr<LightSource>> &Scene::getLightVector() const {
    return lightVector;
}

const Camera &Scene::getCamera() const {
    return camera;
}

void Scene::fillScene() {
//    Transformation tSphere1;
//    tSphere1.addScaling(400, 400, 400);
//    tSphere1.addTranslation(2000, -1200, -1200);
//    Sphere sphere1(tSphere1, {0, 0, 1, 0});
//    objectVector.push_back(std::make_shared<Sphere>(sphere1));

    Transformation tSphere2;
    tSphere2.addScaling(200, 200, 200);
    tSphere2.addTranslation(2000, -300, -300);
    Sphere sphere2(tSphere2, {0, 0, 1, 0}, 0.1, 0.6, 0.1, 40, 0.2);
    objectVector.push_back(std::make_shared<Sphere>(sphere2));

    Transformation tSphere3;
    tSphere3.addScaling(200, 200, 200);
    tSphere3.addTranslation(2000, 0, 0);
    Sphere sphere3(tSphere3, {1, 0, 0, 0}, 0.1, 0.5, 0.3, 20, 0.2);
    objectVector.push_back(std::make_shared<Sphere>(sphere3));

//    Transformation tSphere4;
//    tSphere4.addScaling(200, 200, 200);
//    tSphere4.addTranslation(2000, 300, 300);
//    Sphere sphere4(tSphere4, {0, 1, 0, 0});
//    objectVector.push_back(std::make_shared<Sphere>(sphere4));

//    Transformation tSphere5;
//    tSphere5.addScaling(400, 400, 400);
//    tSphere5.addTranslation(2000, 1200, 1200);
//    Sphere sphere5(tSphere5, {0, 0, 1, 0});
//    objectVector.push_back(std::make_shared<Sphere>(sphere5));


//    Transformation tCube1;
//    tCube1.addScaling(200, 200, 200);
//    tCube1.addRotationY(DEG_TO_RADIANS(-30));
//    tCube1.addRotationX(DEG_TO_RADIANS(30));
//    tCube1.addTranslation(2000, 0, -0);
//    Cube cube1(tCube1, {1, 0, 0, 0}, 0.2, 0.8, 0.1, 50);
//    objectVector.push_back(std::make_shared<Cube>(cube1));
//
//    Transformation tCube2;
//    tCube2.addScaling(200, 200, 200);
//    tCube2.addRotationY(DEG_TO_RADIANS(-30));
//    tCube2.addRotationX(DEG_TO_RADIANS(30));
//    tCube2.addTranslation(2000, -400, 600);
//    Cube cube2(tCube2, {0, 1, 1, 0});
//    objectVector.push_back(std::make_shared<Cube>(cube2));
//
    Transformation tCone1;
    tCone1.addScaling(200, 200, 200);
    tCone1.addRotationZ(DEG_TO_RADIANS(-30));
    tCone1.addRotationX(DEG_TO_RADIANS(120));
    tCone1.addTranslation(2000, 350, -950);
    Cone cone1(tCone1, {0, 0, 1, 0}, 0.3, 0.4, 0.3, 10, 0.2);
    objectVector.push_back(std::make_shared<Cone>(cone1));


//    Transformation tPlane1;
//    tPlane1.addTranslation(0, -800, 0);
//    Plane plane1(tPlane1, {1, 1, 1, 0});
//    plane1.setCheckerBoardPattern(true, 150);
//    objectVector.push_back(std::make_shared<Plane>(plane1));

    // LIGHT
    LightSource light({2000,1000,0,1}, {2000,0,0,0}, {1,1,1,0});
    lightVector.push_back(std::make_shared<LightSource>(light));

    camera = Camera(2 * W, 10, {2000, 0, 0, 1}, {0, 100, 0, 1});
}

void Scene::fillScene2() {
    Transformation tCube1;
    tCube1.addScaling(200, 200, 200);
    tCube1.addRotationY(DEG_TO_RADIANS(-30));
    tCube1.addRotationX(DEG_TO_RADIANS(30));
    tCube1.addTranslation(2000, 200, -100);
    Cube cube1(tCube1, {1, 1, 0, 0}, 0.1, 0.9, 0, 0, 0.2);
    objectVector.push_back(std::make_shared<Cube>(cube1));

    Transformation tSphere2;
    tSphere2.addScaling(200, 200, 200);
    tSphere2.addTranslation(2000, -400, 100);
    Sphere sphere2(tSphere2, {0, 0, 1, 0}, 0.1, 0.9, 0, 0, 0.2);
    objectVector.push_back(std::make_shared<Sphere>(sphere2));

//    Transformation tPlane1;
//    tPlane1.addTranslation(0, -450, 0);
//    Plane plane1(tPlane1, {1, 1, 1, 0}, 0.1, 0.9, 0, 0);
//    //plane1.setCheckerBoardPattern(true);
//    objectVector.push_back(std::make_shared<Plane>(plane1));

    // LIGHT
    LightSource light({2000,2000,0,1}, {0,-2000,0,0}, {1,1,1,0});
    lightVector.push_back(std::make_shared<LightSource>(light));

    LightSource l2({0, 0, 0, 1}, {2000, 0, 0, 0}, {1,1,1,0});
    lightVector.push_back(std::make_shared<LightSource>(l2));

    camera = Camera(2 * W, 10, {2000, 0, 0, 1}, {0, 100, 0, 1});
}

void Scene::fillScene3(){
    Transformation tSphere2;
    tSphere2.addScaling(200, 200, 200);
    tSphere2.addTranslation(5000, -300, -400);
    Sphere sphere2(tSphere2, {0, 0, 1, 0}, 0.1, 0.7, 0.2, 20, 0.1);
    objectVector.push_back(std::make_shared<Sphere>(sphere2));

    Transformation tSphere3;
    tSphere3.addScaling(220, 220, 220);
    tSphere3.addTranslation(5000, 0, 0);
    Sphere sphere3(tSphere3, {1, 0, 0, 0}, 0.1, 0.7, 0.2, 20, 1);
    objectVector.push_back(std::make_shared<Sphere>(sphere3));

    Transformation tSphere4;
    tSphere4.addScaling(200, 200, 200);
    tSphere4.addTranslation(5000, -300, 400);
    Sphere sphere4(tSphere4, {0, 1, 0, 0}, 0.1, 0.7, 0.2, 20, 0.1);
    objectVector.push_back(std::make_shared<Sphere>(sphere4));

    Transformation tPlane1;
    tPlane1.addTranslation(0, -500, 0);
    Plane plane1(tPlane1, {1, 1, 1, 0}, 0, 0.5, 0.2, 20, 0);
    //plane1.setCheckerBoardPattern(true);
    objectVector.push_back(std::make_shared<Plane>(plane1));

    // LIGHT
    LightSource light({3300,1000,0,1}, {5000,0,0,0}, {1,1,1,0});
    lightVector.push_back(std::make_shared<LightSource>(light));

    camera = Camera(2 * W, 10, {2000, 0, 0, 1}, {0, 100, 0, 1});
}

void Scene::fillScene4() {
    Transformation tCube1;
    tCube1.addScaling(150, 150, 150);
    tCube1.addRotationY(DEG_TO_RADIANS(30));
    tCube1.addRotationZ(DEG_TO_RADIANS(30));
    tCube1.addTranslation(2500, 0, 0);
    Cube cube1(tCube1, {0, 0, 1, 0}, 0.05, 0.8, 0, 0, 0.2);
    objectVector.push_back(std::make_shared<Cube>(cube1));

    Transformation tCube2;
    tCube2.addScaling(150, 150, 150);
    tCube2.addRotationZ(DEG_TO_RADIANS(60));
    tCube2.addRotationX(DEG_TO_RADIANS(30));
    tCube2.addTranslation(2500, -250, 475);
    Cube cube2(tCube2, {0, 1, 0, 0}, 0.05, 0.8, 0, 0, 0.2);
    objectVector.push_back(std::make_shared<Cube>(cube2));

    Transformation tCube3;
    tCube3.addScaling(150, 150, 150);
    tCube3.addRotationZ(DEG_TO_RADIANS(-60));
    tCube3.addRotationX(DEG_TO_RADIANS(30));
    tCube3.addTranslation(2500, -250, -475);
    Cube cube3(tCube3, {1, 0, 0, 0}, 0.05, 0.8, 0, 0, 0.2);
    objectVector.push_back(std::make_shared<Cube>(cube3));


    Transformation tPlane1;
    tPlane1.addTranslation(0, -500, 0);
    Plane plane1(tPlane1, {1, 1, 1, 0}, 0.03, 0.6, 0, 0, 0.2);
    plane1.setCheckerBoardPattern(true, 130);
    objectVector.push_back(std::make_shared<Plane>(plane1));

    // LIGHT
    LightSource light({2500,200,2000,1}, {2500,0,0,0}, {1, 1, 1, 0});
    lightVector.push_back(std::make_shared<LightSource>(light));

    camera = Camera(2 * W, 10, {1500, 0, 0, 1}, {0, 100, 0, 1});
}

void Scene::fillScene5(){
    Transformation tSphere;
    tSphere.addScaling(350, 350, 350);
    tSphere.addTranslation(2300, 0, 0);
    Sphere sphere(tSphere, {1, 0, 0, 0}, 0.1, 0.6, 0.3, 10, 0.2);
    objectVector.push_back(std::make_shared<Sphere>(sphere));

    Transformation tPlane1;
    tPlane1.addTranslation(0, -500, 0);
    Plane plane1(tPlane1, {1, 1, 1, 0}, 0, 0.5, 0, 0, 0.2);
    plane1.setCheckerBoardPattern(true, 130);
    objectVector.push_back(std::make_shared<Plane>(plane1));

    // LIGHT
    LightSource light({1500,500,0,1}, {2500,0,0,0}, {1, 1, 1, 0});
    lightVector.push_back(std::make_shared<LightSource>(light));

    camera = Camera(2 * W, 10, {2000, 0, 0, 1}, {0, 0, 0, 1});
}
