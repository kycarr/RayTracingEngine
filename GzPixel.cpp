#include "stdafx.h"
#include "GzPixel.h"

GzPixel::GzPixel(unsigned int a_r, unsigned int a_g, unsigned int a_b, unsigned int a_a) :
    red(a_r < 4096u ? static_cast<unsigned short>(a_r) : 4095u),
    green(a_g < 4096u ? static_cast<unsigned short>(a_g) : 4095u),
    blue(a_b < 4096u ? static_cast<unsigned short>(a_b) : 4095u),
    alpha(a_a < 4096u ? static_cast<unsigned short>(a_a) : 4095u)
{
}

GzPixel::GzPixel() : GzPixel(0u, 0u, 0u)
{
}

GzPixel::GzPixel(const GzColor &pixelColor) :
    red(ctoi(pixelColor.r)), green(ctoi(pixelColor.g)),
    blue(ctoi(pixelColor.b)), alpha(4095u)
{
}

void GzPixel::putColor(const GzColor &pixelColor)
{
    this->red = ctoi(pixelColor.r);
    this->green = ctoi(pixelColor.g);
    this->blue = ctoi(pixelColor.b);
    this->alpha = 4095u;
}

unsigned short GzPixel::ctoi(float color)
{
    return static_cast<unsigned short>(color >= 0.0f && color < 1.0f ? color * 4096 : 4095);
}
