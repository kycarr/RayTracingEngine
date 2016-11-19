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

    GzLight(int t, const GzVector3 &pos);
    GzLight(int t, const GzVector3 &pos, const GzColor &col);
    GzLight(); // Default constructur; Build a directional light from the direction of (0, 1, 0).
// need extension for area light later.
};
#endif
