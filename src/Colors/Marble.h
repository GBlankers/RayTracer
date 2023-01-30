#ifndef RAYTRACER_MARBLE_H
#define RAYTRACER_MARBLE_H

#include "Color.h"
#include "../Math/Noise.h"

/**
 * Solid texture for a marble texture
 */
class Marble: public Color{
private:
    /**
     * Use the noise class to generate repeatable noise
     */
    Noise n{};
public:
    Vec4 getColor(double u, double v, Vec4 localHit, Vec4 worldHit) override;

    /**
     * The undulate function will apply a mathematical function to the noise
     * @param x the input value
     * @return the result of the function
     */
    static double undulate(double x);
};


#endif //RAYTRACER_MARBLE_H
