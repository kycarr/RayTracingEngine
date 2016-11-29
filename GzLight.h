#ifndef LIGHT_H
#define LIGHT_H
//
// GzLight.h     Represents a directional or point light
// 
#include "GzConstants.h"
#include "GzVector3.h"
#include "GzColor.h"
#include "GzGeometry.h"

class GzLight
{
public:
    int type;           // DIR_LIGHT for directional, POINT_LIGHT for point, AREA_LIGHT for area
    GzVector3 position; // position if point light, direction if directional light, center point if rectangle area light
    GzColor color;      // the color of the light

    Rec areaRect;       // The rectangle area. Normal direction and material are not useful.

    GzLight(int t, const GzVector3 &pos, const GzColor &col = GzColor::WHITE);
    GzLight(const GzVector3 &base, const GzVector3 &x, const GzVector3 &y, const GzColor &col = GzColor::WHITE);
    GzLight(); // Default constructur; Build a directional light from the direction of (0, 1, 0).

    GzVector3 getLightDir(const GzVector3 &interPos) const;
};
#endif

