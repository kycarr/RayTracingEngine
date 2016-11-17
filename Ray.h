#ifndef RAY_H
#define RAY_H
//#include Color.h      // GzColor
//#include Vector.h     // GzVector

// Represents a directional or point light

class GzRay
{
public:
   
    GzVector origin;  // position if point light, direction if directional light
	GzVector direction;
    GzRay(GzVector p, GzVector d);
	GzVector getPoint(float distance);
};
// vector need 
// normalize(), multiply( float multiplier), add(Gzvector vector to be add in) , substract(GzVector vector to substract), float dotMutiply()
// Ray construction
void GzRay::GzRay(GzVector p, GzVector d){origin=p;  direction = d.normalize();}
GzVector GzRay::getPoint(float distance){  return (direction.multiply(distance)).add(this->origin);}

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
#endif