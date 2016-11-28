#ifndef GZPIXEL_H
#define GZPIXEL_H
//
// GzPixel.h        Class definition for one pixel.

#include "GzColor.h"

class GzPixel
{
public:
    unsigned short red, green, blue, alpha;
    // We don't need z-buffer at all for our ray tracing engine
    GzPixel(); // Default constructor. Build a black pixel.
    GzPixel(unsigned int a_r, unsigned int a_g, unsigned int a_b, unsigned int a_a = 4095u); // With a default alpha parameter, you can build a pixel with 3 or 4 integer inputs.
    GzPixel(const GzColor &pixelColor);
    void putColor(const GzColor &pixelColor);
    static unsigned short ctoi(float color);
};

#endif
