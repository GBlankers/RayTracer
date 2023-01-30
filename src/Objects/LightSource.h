#ifndef RAYTRACER_LIGHTSOURCE_H
#define RAYTRACER_LIGHTSOURCE_H

#include "../Math/Vec4.h"
#include "../Math/Matrix4.h"

/**
 * Assume perfect point source
 */
class LightSource {
private:
    Vec4 position; // Position of the light source
    Vec4 color{}; // color of the light source
    double intensity = 1; // assume default full intensity
public:
    /**
     * Light source constructor. Using a position, a direction, a color and the intensity, a light source will be constructed
     * @param position the position of the source
     * @param pointsAt direction
     * @param color the color of the light source
     * @param intensity the intensity of the light source
     */
    LightSource(const Vec4 &position, const Vec4 &pointsAt, Vec4 color, double intensity);


    /**
     * Calculate the amount of diffuse color this light source will give to an object with given normal and hit point
     * @param normal the normal of the object that was hit
     * @param hitPoint the hit point of the object that was hit
     * @return the amount of diffuse light this light source gives to the object with given normal and hit point
     */
    double calculateDiffuse(Vec4 normal, Vec4 hitPoint);

    /**
     * Calculate the amount of specular color this light source will give to an object with the given normal, view direction
     * and hit point
     * @param normal the normal of the object that was hit
     * @param viewDirection the view direction of the ray that has initially hit the object
     * @param hitPoint the hit point of the object that was hit
     * @return the amount of specular light this light source gives to the object with given normal, hit point and the
     * view direction of the camera
     */
    double calculateSpecular(Vec4 normal, Vec4 viewDirection, Vec4 hitPoint);

    /**
     * Get the position of the light source
     * @return the position of the light source
     */
    const Vec4 &getPosition() const;

    /**
     * Get the color of the light source
     * @return the color of the light source
     */
    const Vec4 &getColor() const;

    /**
     * Get the intensity of the light source
     * @return the intensity of the light source
     */
    double getIntensity() const;
};


#endif //RAYTRACER_LIGHTSOURCE_H
