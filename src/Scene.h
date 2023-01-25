#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include "Objects/Shape.h"
#include "Objects/objectProperties.h"
#include "Objects/Sphere.h"
#include "Objects/Cube.h"
#include "Objects/Plane.h"
#include "Objects/Cone.h"
#include "Camera.h"
#include "settings.h"

#include "rapidjson/document.h"
#include "Objects/SkyBox.h"
#include "Colors/Color.h"
#include "Colors/SingleColor.h"
#include "Colors/ImageColor.h"
#include "Colors/CheckerBoard.h"
#include "Normal/normalImage.h"

#include <memory>
#include <vector>
#include <fstream>
#include <sstream>

#define DEG_TO_RADIANS(X) (X*M_PI/180)

/**
 * The scene class will keep track of the whole scene. This includes the camera, all the objects, all the light sources and
 * the skybox. This class also includes the json parser used to create scenes form scene files. Further, methods to get
 * all the different scene elements are present.
 */
class Scene {
private:
    /*
     * Shared pointers are used, these will create a small decrease in performance:
     * Memory overhead as they keep track of some properties.
     * Time overhead as they need to initialize all these properties and make use this creation is atomic. However, this
     * overhead is only present in creation, destruction and assignment. The de-referencing is as fast as normal pointers.
     * Creation of the scene is the only place where these time overhead methods are used, only once. Therefore, there will
     * be no noticeable performance decrease.
     */
    std::vector<std::shared_ptr<Shape>> objectVector;
    std::vector<std::shared_ptr<LightSource>> lightVector;
    Camera camera{};
    SkyBox sky;
    // Material and color components
    std::unordered_map<std::string, Material> materialMap;
    std::unordered_map<std::string, LightComponents> colorMap;

    std::shared_ptr<Shape> getObject(rapidjson::Value &v);
public:
    explicit Scene();
    void fillScene(const std::string& filename);

    const std::vector<std::shared_ptr<Shape>> &getObjectVector() const;
    const std::vector<std::shared_ptr<LightSource>> &getLightVector() const;
    const Camera &getCamera() const;
    Vec4 getSkyColor(Vec4 direction) const;
};


#endif //RAYTRACER_SCENE_H
