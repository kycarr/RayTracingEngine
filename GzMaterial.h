#ifndef MATERIAL_H
#define MATERIAL_H
//
// GzMaterial.h     Represents the material of a Geometry object
// 
#include "GzColor.h"

class GzMaterial
{
public:
    // attributes
    GzColor Kd;   // diffuse color
    GzColor Ka;   // ambient color
    GzColor Ks;   // specular color
	float   s;   //(N*L)^s
                  // add texture component later
                  // add refractive index later
	float reflectiveness;

    // constructors
    GzMaterial(GzColor kd, GzColor ka, GzColor ks, float S,  float r);
};
#endif