#ifndef GEOMETRY_H
#define GEOMETRY_H
//#include Color.h      // GzColor
//#include Vector.h     // GzVector
//#include<algorithm>
#include "Ray.h"
#include "Light.h"
class GzObject
{
public:
  virtual IntersectResult intersect(GzRay ray)=0;
   GzMaterial material;
};

class Sphere: public GzObject {
	 IntersectResult intersect(GzRay * ray);
     GzVector center;
     float radius ;
     float radiusSqr;
};
Sphere::Sphere ( GzVector v,float r) {center=v; radius=r; radiusSqr=r*r;}

intersect : function (GzRay *ray) {
    GzVector  v = ray->origin.subtract(this->center);
    float dDotV = ray->direction.dotMultiply(v);
    if (dDotV <= 0) {
      float delta = dDotV * dDotV - v.lengthSqr() + this->radiusSqr;
      if (delta >= 0) {
        float distance = -dDotV - Math.sqrt(delta);
        GzVector position = ray->getPoint(distance);
        GzVector normal = position.subtract(this->center).normalize();
        return new IntersectResult((GzObject *)this, distance, position, normal);
      }
    }
    return IntersectResult( NULL, distance, ray->getPoint(distance), this->normal);
 }

class Plane: public GzObject {
	IntersectResult intersect(GzRay * ray);
	GzVector normal;
	GzVector position;
};
Plane::Plane (GzVector n, GzVector p)   { normal=n.normalize(); position=p; }
IntersectResult Plane::intersect(GzRay ray) {
    float a = ray->direction.dotMultiply(this->normal);
    float b = ray->origin.subtract(this->position).dotMultiply(this->normal);
    if (a >= 0 || b <= 0) {
      return IntersectResult( NULL, distance, ray->getPoint(distance), this->normal);
    }

    float distance = -b / a;
    return IntersectResult( (GzObject *) this, distance, ray->getPoint(distance), this->normal);
  }

#endif
