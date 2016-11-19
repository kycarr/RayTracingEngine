#ifndef LIGHT_H
#define LIGHT_H
//
// GzLight.h     Represents a directional or point light
// 
#include "gz.h"

class GzLight
{
public:
    int type;           // 0 for directional, 1 for point
    GzVector3 position; // position if point light, direction if directional light
    GzColor color;      // the color of the light

    GzLight(int t, GzVector3 pos);
    GzLight(int t, GzVector3 pos,  GzColor col);
};

// Constructor makes a new white light with the given type and position
GzLight::GzLight(int t, GzVector3 pos)
{
    type = t;
    position = pos;
    color = GzColor(1, 1, 1);
}

// Constructor makes a new light with the given type, position, and color
GzLight::GzLight(int t, GzVector3 pos, GzColor col)
{
    type = t;
    position = pos;
    color = col;
}
#endif