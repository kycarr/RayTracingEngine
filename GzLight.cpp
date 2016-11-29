#include "stdafx.h"
#include "GzLight.h"

// Constructor makes a general light with the given type, position, and color
// We may want to make sure directional light has the direction as a unit vector
GzLight::GzLight(int t, const GzVector3 &pos, const GzColor &col) :
    type(t), position(pos), color(col), areaRect(Rec())
{
    if (type == DIR_LIGHT)
    {
        position = pos.normalize();
    }
}

GzLight::GzLight(const GzVector3 &base, const GzVector3 &x, const GzVector3 &y, const GzColor &col) :
    type(AREA_LIGHT), position(base + 0.5f * x + 0.5f * y), color(col), areaRect(Rec(base, x, y)) 
{
}

GzLight::GzLight() : GzLight(DIR_LIGHT, GzVector3(0.0f, 1.0f, 0.0f))
{
}

GzVector3 GzLight::getLightDir(const GzVector3 &interPos) const
{
    if (this->type == DIR_LIGHT)
    {
        return this->position;
    }
    else
    {
        return (this->position - interPos).normalize();
    }
}

