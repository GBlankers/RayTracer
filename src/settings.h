#ifndef RAYTRACER_SETTINGS_H
#define RAYTRACER_SETTINGS_H

// Window constants
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
// Virtual screen coordinates
const double W = (double)WINDOW_WIDTH;
const double H = (double)WINDOW_HEIGHT;
// Anti alias samples
#define ANTI_ALIAS_SAMPLING 2
// Number of max reflections/refractions
#define BOUNCES 3
// Computer error
#define EPSILON 0.000000001
// Number of threads
#define THREADS 6

#endif //RAYTRACER_SETTINGS_H
