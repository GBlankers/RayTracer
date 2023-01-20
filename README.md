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

# Dependencies
- rapidJSON
- lodePNG
