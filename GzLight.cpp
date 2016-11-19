#include "stdafx.h"
#include "GzLight.h"

// Constructor makes a general light with the given type, position, and color
// We may want to make sure directional light has the direction as a unit vector
GzLight::GzLight(int t, const GzVector3 &pos, const GzColor &col) :
    type(t), position(pos), color(col)
{
    if (type == 0)
    {
        position = pos.normalize();
    }
}

// Constructor makes a new white light with the given type and position
GzLight::GzLight(int t, const GzVector3 &pos) : GzLight(t, pos, GzColor(1.0f, 1.0f, 1.0f))
{
}

GzLight::GzLight() : GzLight(0, GzVector3(0.0f, 1.0f, 0.0f))
{
}
