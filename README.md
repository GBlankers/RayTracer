# RayTracer
Basic ray tracing engine for the I-Computer Graphics course

# Project Structure
`main.cpp` the main file where the opengl initialisation code is located as well as the logic for multithreading, the main loop to check for collisions, reflection, refractions and lighting.


## Assets
Folder with all the png file which can be used for textures, normal mapping and skybox.

## Include
### Code
In this folder the imported code to read png files can be found.
### Properties
A folder with an objectProperties.json file. In this file different colors/materials can be defined. These can then be used in the scenes by using the `colorName` and `materialName` keywords.
### Scenes
This contains 2 types of files. 
- A general.json file. In this file the selected scene can be defined with the `scene` keyword.
- The scene files in json format

## src
All the written code can be found in this folder. Under src, the main classes used for a ray tracing engine can be found such as: camera, collision, ray, scene, general settings and transformation. Further there are sub-folders for:
- Colors. Different possibilities to give a color to an object: using an image, a single color or using a checkerboard pattern. Other solid textures can be added here.
- Math. Math related classes/functions for matrices, vectors and random number generators.
- Normal. Classes used for normal manipulation. This can be done using a roughness parameter, where the normal is adapted based on a random vector. Or using a normal image which gives information about how the normal should be to represent a type of material.
- Objects. All the different shapes can be found here (plane, cube, sphere and cone) as well as light sources, a skybox(what if a ray does not hit anything? -> it gets the color of the skybox) and object properties structs to keep the object classes more clean.


# Features
- Different objects: sphere, cube, plane, cone
- Easily definable camera (position + looks at + up vector angle)
- Light sources with custom intensity, color and location
- Skybox with color or png image
- SDL using json to define the scene
- phong lighting (ambient, diffuse, specular)
- reflection and refraction up to custom depth with definable reflectivity, roughness, transparency and refractive index
- anti-aliasing

# Creating a New Scene
## Structure of the scene files
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
- `"Objects"`, which is a list of all the defined objects in the scene. Every object needs to have the following properties:
  - `"type": "objecttype"`, where "objectType" can be sphere/plane/cube/cone.

# Dependencies
- rapidJSON
- lodePNG
