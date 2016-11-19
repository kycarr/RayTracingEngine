#ifndef MATERIAL_H
#define MATERIAL_H
//
// GzMaterial.h     Represents the material of a Geometry object
// 
#include "gz.h"

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

// Constructor makes a new material with the given diffuse, ambient, and specular properties
GzMaterial::GzMaterial(GzColor kd, GzColor ka, GzColor ks, float S,  float r)
{
    Kd = kd;
    Ka = ka;
    Ks = ks;
	s  =  S;    // for (N*L)^s , specular
	reflectiveness = r; // reflect ray amplitue
}
#endif