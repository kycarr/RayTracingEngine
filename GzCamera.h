#ifndef GZCAMERA_H
#define GZCAMERA_H

// GzCamera.h       The definition of class GzCamera

#include "GzVector3.h"
#include "GzRay.h"
//#include "gz.h"

class GzCamera
{
public:
// attributes
    GzVector3 position, face, up, right;
    float fovScale;
// constructors
    GzCamera(); // Default constructor. Build a camera at (0,0,0) and looking at (0, 0, 1), with worldup as (0, 1, 0) and FOV as 90 degree.
    GzCamera(const GzVector3 &p, const GzVector3 &lookat, const GzVector3 &worldup, float fov);
// methods
    GzRay generateRay(float ndcx, float ndcy) const;
};

GzVector3 schimidt(const GzVector3 &general, const GzVector3 &unit);

#endif
