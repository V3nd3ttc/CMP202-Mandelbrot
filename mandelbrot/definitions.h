#include <cstdint>
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// The size of the image to generate.
const int WIDTH = 1280;
const int HEIGHT = 720;

// The number of times to iterate before we assume that a point isn't in the
// Mandelbrot set.
// (You may need to turn this up if you zoom further into the set.)
const int MAX_ITERATIONS = 100;

// The image data.
// Each pixel is represented as 0xRRGGBB.

#endif