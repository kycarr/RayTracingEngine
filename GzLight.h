#ifndef LIGHT_H
#define LIGHT_H
//
// GzLight.h     Represents a directional or point light
// 
#include "GzVector3.h"
#include "GzColor.h"

class GzLight
{
public:
    int type;           // 0 for directional, 1 for point
    GzVector3 position; // position if point light, direction if directional light
    GzColor color;      // the color of the light

    GzLight(int t, GzVector3 pos);
    GzLight(int t, GzVector3 pos,  GzColor col);
};
#endif