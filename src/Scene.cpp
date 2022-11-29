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

Vec4 Scene::getSkyColor(Vec4 direction) const{
    return sky.getColor(direction);
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
    std::ifstream sceneFile("../include/scenes/"+sceneFileName);

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

    // Object property file
    std::ifstream propertiesFile("../include/scenes/objectProperties.json");
    std::stringstream buffer3;
    buffer3 << propertiesFile.rdbuf();
    std::string tempString3 = buffer3.str();
    const char* jsonPropertiesString = tempString3.c_str();
    rapidjson::Document p;
    p.Parse(jsonPropertiesString);
    assert(p.IsObject());

    // Temporary Variables
    rapidjson::Value value, valueArray;
    Vec4 position{}, pointsAt{}, color{};
    Transformation temp;
    double fov;
    bool useColor;
    std::string path, normalMapPath;
    LightComponents lightComponents;
    Material material;

    // Material and color components
    std::unordered_map<std::string, Material> materialMap;
    std::unordered_map<std::string, LightComponents> colorMap;
    // Fill up the maps using the objectProperties file
    if(p.HasMember("lightComponents")){
        for(auto& v : p["lightComponents"].GetArray()){
            LightComponents tempLightComponent;
            tempLightComponent.name = v["name"].GetString();
            valueArray = v["color"].GetArray();
            tempLightComponent.color = {valueArray[0].GetDouble(), valueArray[1].GetDouble(), valueArray[2].GetDouble(), 0};
            tempLightComponent.ambient = v["ambient"].GetDouble();
            tempLightComponent.diffuse = v["diffuse"].GetDouble();
            tempLightComponent.specular = v["specular"].GetDouble();
            tempLightComponent.specularExponent = v["specularExponent"].GetDouble();
            colorMap[v["name"].GetString()] = tempLightComponent;
        }
    }
    if(p.HasMember("materials")){
        for(auto& v : p["materials"].GetArray()){
            Material tempMaterial;
            tempMaterial.name = v["name"].GetString();
            tempMaterial.reflectivity = v["reflectivity"].GetDouble();
            tempMaterial.roughness = v["roughness"].GetDouble();
            tempMaterial.transparency = v["transparency"].GetDouble();
            tempMaterial.refractiveIndex = v["refractiveIndex"].GetDouble();
            materialMap[v["name"].GetString()] = tempMaterial;
        }
    }

    // Add the camera
    assert(s.HasMember("Camera"));
    value = s["Camera"];
    assert(value.HasMember("fov"));
    fov = value["fov"].GetDouble();
    assert(value.HasMember("pointsAt"));
    valueArray = value["pointsAt"].GetArray();
    pointsAt = Vec4(valueArray[0].GetDouble(), valueArray[1].GetDouble(), valueArray[2].GetDouble(), 1);
    assert(value.HasMember("location"));
    valueArray = value["location"].GetArray();
    position = Vec4(valueArray[0].GetDouble(), valueArray[1].GetDouble(), valueArray[2].GetDouble(), 1);
    if(value.HasMember("angle")){
        valueArray = value["angle"].GetArray();
        camera = Camera(fov, pointsAt, position, valueArray[0].GetDouble(), valueArray[1].GetDouble());
    } else {
        camera = Camera(fov, pointsAt, position);
    }

    // Add the objects
    assert(s.HasMember("Objects"));
    for(auto& v : s["Objects"].GetArray()){
        temp.clear();
        lightComponents.reset();
        material.reset();
        useColor = true;
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

        // Check if a default color is used and if this is present in the color map
        if(v.HasMember("colorName") and colorMap.count(v["colorName"].GetString())>0){
            lightComponents = colorMap[v["colorName"].GetString()];
        } else {
            assert(v.HasMember("ambient"));
            lightComponents.ambient = v["ambient"].GetDouble();
            assert(v.HasMember("diffuse"));
            lightComponents.diffuse = v["diffuse"].GetDouble();
            assert(v.HasMember("specular"));
            lightComponents.specular = v["specular"].GetDouble();
            assert(v.HasMember("specularExponent"));
            lightComponents.specularExponent = v["specularExponent"].GetDouble();
        }

        // Check color/path to png file
        if(v.HasMember("color")){
            valueArray = v["color"];
            assert(valueArray.IsArray());
            lightComponents.color = {valueArray[0].GetDouble(), valueArray[1].GetDouble(), valueArray[2].GetDouble(), 0};
        } else if(v.HasMember("path")){
            useColor = false;
            path = v["path"].GetString();
        }

        // Check if a default material is used and if this material is present in the material map
        if(v.HasMember("materialName") and materialMap.count(v["materialName"].GetString())>0){
            material = materialMap[v["materialName"].GetString()];
        } else {
            if(v.HasMember("reflectivity")){
                material.reflectivity = v["reflectivity"].GetDouble();
            } else {
                material.reflectivity = 0;
            }
            if(v.HasMember("roughness")){
                material.roughness = v["roughness"].GetDouble();
            } else {
                material.roughness = 0;
            }
            if(v.HasMember("transparency")){
                material.transparency = v["transparency"].GetDouble();
                assert(v.HasMember("refractiveIndex"));
                material.refractiveIndex = v["refractiveIndex"].GetDouble();
            } else {
                material.transparency = 0;
                material.refractiveIndex = 1;
            }
        }

        if(v.HasMember("normalMap")){
            normalMapPath = v["normalMap"].GetString();
        }

        // Check object type
        assert(v.HasMember("type"));
        if(strcmp(v["type"].GetString(), "cube") == 0){
            objectVector.push_back(std::make_shared<Cube>(Cube(temp, lightComponents, material, normalMapPath)));
        } else if(strcmp(v["type"].GetString(), "sphere") == 0){
            if(useColor){
                objectVector.push_back(std::make_shared<Sphere>(Sphere(temp, lightComponents, material, normalMapPath)));
            }else{
                objectVector.push_back(std::make_shared<Sphere>(Sphere(temp, path, lightComponents, material, normalMapPath)));
            }
        } else if(strcmp(v["type"].GetString(), "plane") == 0){
            if(useColor){
                Plane tempPlane(temp, lightComponents, material, normalMapPath);
                if(v.HasMember("checkerBoard")){
                    tempPlane.setCheckerBoardPattern(true, v["checkerBoard"].GetInt());
                }
                if(v.HasMember("size")) {
                    valueArray = v["size"].GetArray();
                    tempPlane.setSize(valueArray[0].GetDouble(), valueArray[1].GetDouble());
                }
                objectVector.push_back(std::make_shared<Plane>(tempPlane));
            } else {
                Plane tempPlane(temp, path, lightComponents, material, normalMapPath);
                if(v.HasMember("size")){
                    valueArray = v["size"].GetArray();
                    tempPlane.setSize(valueArray[0].GetDouble(), valueArray[1].GetDouble());
                }
                objectVector.push_back(std::make_shared<Plane>(tempPlane));
            }
        } else if(strcmp(v["type"].GetString(), "cone") == 0){
            objectVector.push_back(std::make_shared<Cone>(Cone(temp, lightComponents, material, normalMapPath)));
        } else {
            perror("Unknown object type in json file");
        }
    }

    // Add the lightSources
    if(s.HasMember("Light")){
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

            if(v.HasMember("intensity")){
                lightVector.push_back(std::make_shared<LightSource>(LightSource{position, pointsAt, color, v["intensity"].GetDouble()}));
            } else {
                lightVector.push_back(std::make_shared<LightSource>(LightSource{position, pointsAt, color, 1}));
            }
        }
    }

    // Add skybox
    if(s.HasMember("SkyBox")){
        value = s["SkyBox"];
        if(value.HasMember("color")){
            valueArray = value["color"].GetArray();
            sky = SkyBox(Vec4{valueArray[0].GetDouble(), valueArray[1].GetDouble(), valueArray[2].GetDouble(), 1});
        } else if(value.HasMember("path")){
            sky = SkyBox(std::string(value["path"].GetString()));
        } else {
            sky = SkyBox();
        }
    } else {
        sky = SkyBox();
    }
}
