#ifndef RAYTRACER_SETTINGS_H
#define RAYTRACER_SETTINGS_H

// Window constants
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
// Virtual screen coordinates
#define W (double)WINDOW_WIDTH
#define H (double)WINDOW_HEIGHT
// Anti alias samples
#define ANTI_ALIAS_SAMPLING 2
// Number of max reflections/refractions
#define REFLECTIONS 2
// Computer error
#define EPSILON 0.000000001
// Number of threads
#define THREADS 4

#endif //RAYTRACER_SETTINGS_H
