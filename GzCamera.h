#ifndef GZCAMERA_H
#define GZCAMERA_H

// GzCamera.h       The definition of class GzCamera

#include "gz.h"

class GzCamera
{
public:
// attributes
    GzVector3 position, front, up, right;
    float fovScale;
// constructors
    GzCamera(); // Default constructor. Build a camera at (0,0,0) and looking at (0, 0, -1), with FOV as 90 degree.
    GzCamera(const GzVector3 &p, const GzVector3 &lookat, const GzVector3 &worldup, float fov);
// methods
    //GzRay& generateRay(float ndcx, float ndcy) const;
};

#endif
