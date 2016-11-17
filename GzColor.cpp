#include "color.h"

GzColor::GzColor(float a_r, float a_g, float a_b) :
    r(a_r), g(a_g), b(a_b)
{
}

GzColor::GzColor() : GzColor(0.0f, 0.0f, 0.0f)
{
}

