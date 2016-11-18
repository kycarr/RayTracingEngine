#include "stdafx.h" // if testing with console program, comment this line out
#include "GzRay.h"

GzRay::GzRay(const GzVector3 &p, const GzVector3 &d) : origin(p), direction(d.normalize())
{
}

GzRay::GzRay() : origin(0.0f,0.0f,0.0f), direction(0.0f,0.0f,-1.0f)
{
}

GzVector3 GzRay::getPoint(float distance) const
{
    return this->origin + distance * this->direction;
}
