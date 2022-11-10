#include "Scene.h"

Scene::Scene() = default;

const std::vector<std::shared_ptr<Shape>> &Scene::getObjectVector() const {
    return objectVector;
}

const std::vector<std::shared_ptr<LightSource>> &Scene::getLightVector() const {
    return lightVector;
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
    Sphere sphere2(tSphere2, {0, 0, 1, 0}, 0.1, 0.6, 0.1, 40);
    objectVector.push_back(std::make_shared<Sphere>(sphere2));

    Transformation tSphere3;
    tSphere3.addScaling(200, 200, 200);
    tSphere3.addTranslation(2000, 0, 0);
    Sphere sphere3(tSphere3, {1, 0, 0, 0}, 0.1, 0.5, 0.3, 20);
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
    Cone cone1(tCone1, {0, 0, 1, 0}, 0.3, 0.4, 0.3, 10);
    objectVector.push_back(std::make_shared<Cone>(cone1));


//    Transformation tPlane1;
//    tPlane1.addTranslation(0, -800, 0);
//    Plane plane1(tPlane1, {1, 1, 1, 0});
//    plane1.setCheckerBoardPattern(true, 150);
//    objectVector.push_back(std::make_shared<Plane>(plane1));

    // LIGHT
    LightSource light({2000,1000,0,1}, {2000,0,0,0}, {1,1,1,0});
    lightVector.push_back(std::make_shared<LightSource>(light));
}

void Scene::fillScene2() {
    Transformation tCube1;
    tCube1.addScaling(200, 200, 200);
    tCube1.addRotationY(DEG_TO_RADIANS(-30));
    tCube1.addRotationX(DEG_TO_RADIANS(30));
    tCube1.addTranslation(2000, 200, -100);
    Cube cube1(tCube1, {1, 1, 0, 0}, 0.1, 0.9, 0, 0);
    objectVector.push_back(std::make_shared<Cube>(cube1));

    Transformation tSphere2;
    tSphere2.addScaling(200, 200, 200);
    tSphere2.addTranslation(2000, -400, 100);
    Sphere sphere2(tSphere2, {0, 0, 1, 0}, 0.1, 0.9, 0, 0);
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
}

void Scene::fillScene3(){
    Transformation tSphere2;
    tSphere2.addScaling(200, 200, 200);
    tSphere2.addTranslation(2500, -300, -400);
    Sphere sphere2(tSphere2, {0, 0, 1, 0}, 0.1, 0.7, 0.2, 20);
    objectVector.push_back(std::make_shared<Sphere>(sphere2));

    Transformation tSphere3;
    tSphere3.addScaling(220, 220, 220);
    tSphere3.addTranslation(2300, 0, 0);
    Sphere sphere3(tSphere3, {1, 0, 0, 0}, 0.1, 0.7, 0.2, 20);
    objectVector.push_back(std::make_shared<Sphere>(sphere3));

    Transformation tSphere4;
    tSphere4.addScaling(200, 200, 200);
    tSphere4.addTranslation(2500, -300, 400);
    Sphere sphere4(tSphere4, {0, 1, 0, 0}, 0.1, 0.7, 0.2, 20);
    objectVector.push_back(std::make_shared<Sphere>(sphere4));

    Transformation tPlane1;
    tPlane1.addTranslation(0, -500, 0);
    Plane plane1(tPlane1, {1, 1, 1, 0}, 0, 0.5, 0.2, 20);
    //plane1.setCheckerBoardPattern(true);
    objectVector.push_back(std::make_shared<Plane>(plane1));

    // LIGHT
    LightSource light({1500,1000,0,1}, {2500,0,0,0}, {1,1,1,0});
    lightVector.push_back(std::make_shared<LightSource>(light));
}

void Scene::fillScene4() {
    Transformation tCube1;
    tCube1.addScaling(150, 150, 150);
    tCube1.addRotationY(DEG_TO_RADIANS(30));
    tCube1.addRotationZ(DEG_TO_RADIANS(30));
    tCube1.addTranslation(2500, 0, 0);
    Cube cube1(tCube1, {0, 0, 1, 0}, 0.05, 0.8, 0, 0);
    objectVector.push_back(std::make_shared<Cube>(cube1));

    Transformation tCube2;
    tCube2.addScaling(150, 150, 150);
    tCube2.addRotationZ(DEG_TO_RADIANS(60));
    tCube2.addRotationX(DEG_TO_RADIANS(30));
    tCube2.addTranslation(2500, -250, 475);
    Cube cube2(tCube2, {0, 1, 0, 0}, 0.05, 0.8, 0, 0);
    objectVector.push_back(std::make_shared<Cube>(cube2));

    Transformation tCube3;
    tCube3.addScaling(150, 150, 150);
    tCube3.addRotationZ(DEG_TO_RADIANS(-60));
    tCube3.addRotationX(DEG_TO_RADIANS(30));
    tCube3.addTranslation(2500, -250, -475);
    Cube cube3(tCube3, {1, 0, 0, 0}, 0.05, 0.8, 0, 0);
    objectVector.push_back(std::make_shared<Cube>(cube3));


    Transformation tPlane1;
    tPlane1.addTranslation(0, -500, 0);
    Plane plane1(tPlane1, {1, 1, 1, 0}, 0, 0.8, 0, 0);
    plane1.setCheckerBoardPattern(true, 130);
    objectVector.push_back(std::make_shared<Plane>(plane1));

    // LIGHT
    LightSource light({2500,200,2000,1}, {2500,0,0,0}, {1, 1, 1, 0});
    lightVector.push_back(std::make_shared<LightSource>(light));
}

void Scene::fillScene(const std::string& filename) {
    // Filename is defined in the main, this file is 1 directory deeper
    std::ifstream generalFile("../"+filename);
    // Save and convert the contents of the file to a const c-string
    std::stringstream bufferGeneralFile;
    bufferGeneralFile << generalFile.rdbuf();
    std::string generalString = bufferGeneralFile.str();
    const char* jsonString = generalString.c_str();

    // Convert to rapidJson object
    rapidjson::Document generalDocument;
    generalDocument.Parse(jsonString);
    assert(generalDocument.IsObject());

    // Load the scene json file defined in the general json file
    assert(generalDocument.HasMember("scene"));
    assert(generalDocument["scene"].IsString());
    std::string sceneFileName(generalDocument["scene"].GetString());
    std::ifstream sceneFile("../include/"+sceneFileName);

    // Save and convert the contents of the file to a const c-string
    std::stringstream buffer2;
    buffer2 << sceneFile.rdbuf();
    std::string tempString2 = buffer2.str();
    const char* jsonSceneString = tempString2.c_str();

    // Convert to rapidJSON object
    rapidjson::Document s;
    s.Parse(jsonSceneString);
    assert(s.IsObject());
    assert(s["Scene"].GetBool());

    // Temporary Variables
    rapidjson::Value value, valueArray;

    // Add the objects
    assert(s.HasMember("Objects"));
    Vec4 color{};
    double ambient, diffuse, specular, specularExponent;
    Transformation temp;
    for(auto& v : s["Objects"].GetArray()){
        temp.clear();
        // Check for transformations
        if(v.HasMember("transformations")){
            for(auto& i : v["transformations"].GetArray()){
                if(i.HasMember("scaling")){
                    assert(i["scaling"].IsArray());
                    valueArray = i["scaling"].GetArray();
                    temp.addScaling(valueArray[0].GetDouble(), valueArray[1].GetDouble(), valueArray[2].GetDouble());
                }
                if(i.HasMember("rotation")){
                    assert(i["rotation"].IsArray());
                    for(auto& j : i["rotation"].GetArray()){
                        if(j.HasMember("x")){
                            temp.addRotationX(DEG_TO_RADIANS(j["x"].GetDouble()));
                        } else if(j.HasMember("y")){
                            temp.addRotationY(DEG_TO_RADIANS(j["y"].GetDouble()));
                        } else if(j.HasMember("z")){
                            temp.addRotationZ(DEG_TO_RADIANS(j["z"].GetDouble()));
                        }
                    }
                }
                if(i.HasMember("translation")){
                    assert(i["translation"].IsArray());
                    valueArray = i["translation"].GetArray();
                    temp.addTranslation(valueArray[0].GetDouble(), valueArray[1].GetDouble(), valueArray[2].GetDouble());
                }
            }
        }
        // Check color/material properties
        assert(v.HasMember("color"));
        valueArray = v["color"];
        assert(valueArray.IsArray());
        color = {valueArray[0].GetDouble(), valueArray[1].GetDouble(), valueArray[2].GetDouble(), 0};
        assert(v.HasMember("ambient"));
        ambient = v["ambient"].GetDouble();
        assert(v.HasMember("diffuse"));
        diffuse = v["diffuse"].GetDouble();
        assert(v.HasMember("specular"));
        specular = v["specular"].GetDouble();
        assert(v.HasMember("specularExponent"));
        specularExponent = v["specularExponent"].GetDouble();

        // Check object type
        assert(v.HasMember("type"));
        if(strcmp(v["type"].GetString(), "cube") == 0){
            objectVector.push_back(std::make_shared<Cube>(Cube(temp, color, ambient, diffuse, specular, specularExponent)));
        } else if(strcmp(v["type"].GetString(), "sphere") == 0){
            objectVector.push_back(std::make_shared<Sphere>(Sphere(temp, color, ambient, diffuse, specular, specularExponent)));
        } else if(strcmp(v["type"].GetString(), "plane") == 0){
            Plane tempPlane(temp, color, ambient, diffuse, specular, specularExponent);
            if(v.HasMember("checkerBoard")){
                tempPlane.setCheckerBoardPattern(true, v["checkerBoard"].GetInt());
            }
            objectVector.push_back(std::make_shared<Plane>(tempPlane));
        } else if(strcmp(v["type"].GetString(), "cone") == 0){
            objectVector.push_back(std::make_shared<Cone>(Cone(temp, color, ambient, diffuse, specular, specularExponent)));
        } else {
            perror("Unknown object type in json file");
        }
    }

    // Add the lightSources
    assert(s.HasMember("Light"));
    Vec4 position{}, pointsAt{};
    for(auto& v : s["Light"].GetArray()){
        assert(v.HasMember("position"));
        valueArray = v["position"];
        assert(valueArray.IsArray());
        position = {valueArray[0].GetDouble(), valueArray[1].GetDouble(), valueArray[2].GetDouble(), 1};
        assert(v.HasMember("pointsAt"));
        valueArray = v["pointsAt"];
        assert(valueArray.IsArray());
        pointsAt = {valueArray[0].GetDouble(), valueArray[1].GetDouble(), valueArray[2].GetDouble(), 1};
        assert(v.HasMember("color"));
        valueArray = v["color"];
        assert(valueArray.IsArray());
        color = {valueArray[0].GetDouble(), valueArray[1].GetDouble(), valueArray[2].GetDouble(), 0};

        lightVector.push_back(std::make_shared<LightSource>(LightSource{position, pointsAt, color}));
    }
}
