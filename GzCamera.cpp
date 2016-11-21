#include "stdafx.h" // if testing with console program, comment this line out
#include "GzConstants.h"
#include "GzCamera.h"
#include <cmath>
//#include <iostream>

GzCamera::GzCamera() :
    position(0.0f, 0.0f, 0.0f), face(0.0f, 0.0f, 1.0f), up(0.0f, 1.0f, 0.0f), right(1.0f, 0.0f, 0.0f), fovScale(1.0f)
{
//    std::cout << "Default camera called" << std::endl;
}

GzCamera::GzCamera(const GzVector3 &p, const GzVector3 &lookat, const GzVector3 &worldup, float fov) :
    position(p), face((lookat - p).normalize()), up(schimidt(worldup, this->face)),
    right((this->up).crossMultiply(this->face)), fovScale(static_cast<float>(std::tan(fov * PI / 360)))
{
}

GzRay GzCamera::generateRay(float ndcx, float ndcy) const
{
    GzVector3 r(ndcx * this->fovScale * this->right);
    GzVector3 u(ndcy * this->fovScale * this->up);
    return GzRay(this->position, this->face + r + u);
}

GzVector3 schimidt(const GzVector3 &general, const GzVector3 &unit)
{
    // normalize() throws exception if general is parallel to unit
    return (general - general.dotMultiply(unit) * unit).normalize();
}
