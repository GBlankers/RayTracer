# RayTracer
Basic ray tracing engine for the I-Computer Graphics course

## Project Structure
`main.cpp` the main file where the opengl initialisation code is located as well as the logic for multithreading, the main loop to check for collisions, reflection, refractions and lighting.


### Assets
Folder with all the png file which can be used for textures, normal mapping and skybox.

### Include
#### Code
In this folder the imported code to read png files can be found.
#### Properties
A folder with an objectProperties.json file. In this file different colors/materials can be defined. These can then be used in the scenes by using the `colorName` and `materialName` keywords.
#### Scenes
This contains 2 types of files. 
- A general.json file. In this file the selected scene can be defined with the `scene` keyword.
- The scene files in json format

### src
All the written code can be found in this folder. Under src, the main classes used for a ray tracing engine can be found such as: camera, collision, ray, scene, general settings and transformation. Further there are sub-folders for:
- Colors. Different possibilities to give a color to an object: using an image, a single color or using a checkerboard pattern. Other solid textures can be added here.
- Math. Math related classes/functions for matrices, vectors and random number generators.
- Normal. Classes used for normal manipulation. This can be done using a roughness parameter, where the normal is adapted based on a random vector. Or using a normal image which gives information about how the normal should be to represent a type of material.
- Objects. All the different shapes can be found here (plane, cube, sphere and cone) as well as light sources, a skybox(what if a ray does not hit anything? -> it gets the color of the skybox) and object properties structs to keep the object classes more clean.


## Features
- Different objects: sphere, cube, plane, cone
- Easily definable camera (position + looks at + up vector angle)
- Light sources with custom intensity, color and location
- Skybox with color or png image
- SDL using json to define the scene
- phong lighting (ambient, diffuse, specular)
- reflection and refraction up to custom depth with definable reflectivity, roughness, transparency and refractive index
- anti-aliasing
- roughness and normal mapping defined with a custom `png` file.
- multi-threading to speed up the rendering.

## Creating a New Scene
### How to?
Create a new json file and place it into the assets' folder. Structure the file as described in [Structure of the scene files](#structure-of-the-scene-files). In the `general.json` file, change the scene file to the newly created one.

### Structure of the scene files
The scene files are json files which need to have certain keywords in order to be correctly interpreted:
- `"Scene" : true`. Indicates that this file is a scene description.
- `Camera` object, which is the 'eye', from where we will look at the scene. This object need to have the following properties:
  - `fov`, indicating the field of view. **A value between 0 and 180**
  - `"pointsAt": [x, y, z]`, give coordinates of a point where we will look at. This will be used to calculate the ray directions.
  - `"location": [x, y, z]`, where is the camera located.
  - **(Optional)**`"angle": [theta, phi]`, we can tilt the camera where theta will be the tilt of the up-vector and phi will be a rotation with respect to the look direction.
- **(Optional)**`"Light"` which is a list of all the light Sources. Every light source is an object defined by:
  - `"position": [x, y, z]`, where the light source is located
  - `"pointsAt": [x, y, z]`, to give directivity to the light source.
  - `"color": [r, g, b]`, color of the light source. **r, g, and b need to be between 0 and 1**
  - **(Optional)**`"intensity": double`, we can dim the light source. **A value between 0 and 1.
- **(Optional)**`"SkyBox"`, which gives the 'sky' a color when no other objects are hit. If this is not defined, a default color will be given to the sky. The skybox is an object with ***1*** of the following properties:
  - `"color": [r, g, b]`, to give the sky a single color. **r, g, and b need to be between 0 and 1**
  - `"path": string`, give the path to a **png** file from where the colors will be taken. This file needs to be located in the assets' folder, the path will be `"../assets/<filename>.png"`
- `"Objects"`, which is a list of all the defined objects in the scene. Every object is defined as a unit object located in the origin and need to have the following properties:
  - `"type": "objecttype"`, where "objectType" can be sphere/plane/cube/cone.
  - **(Optional)**`"transformations"`, a list consisting of transformations, the order of this is the order in which the transformations will be executed. Every transformation is an object with as keyword the transformation name and as argument the parameters. These can be:
    - `"scaling": [x, y, z]`, scale the object in the defined directions.
    - `"translation": [x, y, z]`, move the object.
    - `"rotation"`, a list of the different rotations that need to happen. This need to be a list as the order of rotations is important. Every object in this list contains the axis of rotation as keyword **(x, y, or z)** and the amount of rotation in degrees.
  - *Lighting*, there are 2 ways to define the phong lighting parameters:
    - `"colorName"`, using a predefined color with lighting parameters defined in the `objectProperties.json` file.
    - Defining every parameter independently:
      - `"ambient": double`, ambient light reaching the object. **Needs to be between 0 and 1**
      - `"diffuse": double`, used for shading. **Needs to be between 0 and 1**
      - `"specular": double`, used for specular reflections. **Needs to be between 0 and 1**
      - `"specularExponent": double`, used to refine the specular reflections
  - *Color*, color can be defined in different ways:
    - the color defined in the `"colorName"` object can be used.
    - `"color": [r, g, b]`, define a single color for an object. 
    - `"checkerboard": double`, makes a checkerboard pattern. The size of the tiles can be changed. The color of the checkerboard can be changed with the `"color": [r, g, b]` and the **(Optional)** `"color2": [r, g, b]` keywords. In both cases the **r, g, and b need to be between 0 and 1**.
    - `"path": string`, a path to a **png** file in the assets' folder. Using uv mapping the image will be projected onto the object. This file needs to be located in the assets' folder, the path will be `"../assets/<filename>.png"`
    - `"rainbow": true`, give the object a rainbow color depending on the coordinate of the hit.
    - `"woodGrain": true`, give the object a wood like color with rings. The wood grain parameters can also be defined by specifying these in an array of 4 elements `[M, K, N, B]`.
    - `"marble": double`, give the object a marble texture.
  - *Material*, material properties can be defined in 2 ways.
    - `"materialName`, using predefined material properties defined in the `objectProperties.json` file.
    - Defining every object independently:
      - **(Optional)**`"reflectivity": double`, how reflective is the object. Default is 0. **Needs to be between 0 and 1**
      - **(Optional)**`"roughness": double`, create a rough surface to have non-perfect reflections and refractions. Default is 0. **Needs to be between 0 and 1**
      - **(Optional)**`"transparency": double`, is the object see through. Default is 0. **Needs to be between 0 and 1**
        - `"refractiveIndex": double`, when the object is transparent, we also need to define a refractive index. Default is 1.
  - **(Optional)**`"normalMap"`, use an image to construct the normals of the object. This file needs to be located in the assets' folder, the path will be `"../assets/<filename>.png"`

## Dependencies
- rapidJSON
- lodePNG
