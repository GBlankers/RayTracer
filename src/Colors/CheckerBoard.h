#ifndef RAYTRACER_CHECKERBOARD_H
#define RAYTRACER_CHECKERBOARD_H

#include "Color.h"
#include "../settings.h"

/**
 * Solid texture for the checkerboard pattern
 */
class CheckerBoard : public Color{
private:
    /**
     * The 2 colors for the checkerboard
     */
    Vec4 color1, color2;
    /**
     * Size of the squares
     */
    double checkerBoardSize;
public:
    /**
     * Constructor for the checkerboard. Given 2 colors and a size, the checkerboard pattern will be made
     * @param c1 first color
     * @param c2 second color
     * @param size size of the checkerboard squares
     */
    CheckerBoard(Vec4 c1, Vec4 c2, double size);
    Vec4 getColor(double u, double v, Vec4 localHit, Vec4 worldHit) override;
};


#endif //RAYTRACER_CHECKERBOARD_H
