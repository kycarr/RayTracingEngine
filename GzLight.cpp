#include "stdafx.h"
#include "GzLight.h"

// Constructor makes a new white light with the given type and position
GzLight::GzLight(int t, GzVector3 pos) : 
    type(t), position(pos), color(GzColor(1, 1, 1))
{
}

// Constructor makes a new light with the given type, position, and color
GzLight::GzLight(int t, GzVector3 pos, GzColor col) :
    type(t), position(pos), color(col)
{
}