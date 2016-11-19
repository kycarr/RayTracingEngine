#ifndef GZRAY_H
#define GZRAY_H

// GzRay.h          The definition of class GzRay

#include "GzVector3.h"

class GzRay
{
public:
// attributes
    GzVector3 origin, direction;
// constructors
    GzRay(); // Default constructor. Build a ray starting from (0,0,0), going to (0, 0, -1)
    GzRay(const GzVector3 &p, const GzVector3 &d);
// methods
    GzVector3 getPoint(float distance) const;
};

/*
class IntersectResult{
	public:
   float distance ;
   GzVector position;
   GzVector normal; 
   Gzobj * intersect_obj;
};
void IntersectResult::IntersectResult(GzVector p, float d, GzVector n,  GzObject * obj ){position=p;  normal = n.normalize(); distance=d; 
 intersect_ojb =obj;
}
*/

#endif
