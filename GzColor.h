#ifndef COLOR_H
#define COLOR_H
//
// color.h      The definition of class GzColor
//
#include "gz.h"

class GzColor
{
public:
    float r, g, b;

    GzColor(); // Default constructor, build a black GzColor object
    GzColor(float a_r, float a_g, float a_b);

    // This class automatically has a copy constructor. For example,
    // you can use `GzColor anyVar(blue)` where blue is already a
    // color object.
    // But try to avoid using copy constructor when possible.
    friend GzColor operator+(const GzColor &c1, const GzColor &c2);
    friend GzColor operator*(const GzColor &c1, float s);
    GzColor modulate(GzColor);

    /*
    static GzColor black;
    static GzColor white;
    static GzColor red;
    static GzColor green;
    static GzColor blue;
    static GzColor cyan;
    static GzColor magenta;
    static GzColor yellow;
    */
};
#endif
