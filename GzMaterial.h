#ifndef MATERIAL_H
#define MATERIAL_H
//
// GzMaterial.h     Represents the material of a Geometry object
// 
#include "GzColor.h"
#include "GzTexture.h"

class GzMaterial
{
public:
    // attributes
    GzColor Kd;   // diffuse color
    GzColor Ka;   // ambient color - We might not need Ka at all later for our project. We can keep it now.
    GzColor Ks;   // specular color - Same for Ks. Perhaps Ks could be represented by a reflectiveness coefficient. We can keep it now.
	float   s;    //(R*E)^s, or (N*H)^s in Blinn-Phong lighting
    float r;      // reflective part
    //float f;      // refractive part
    GzTexture texture;

    // constructors
    GzMaterial(const GzColor &kd, const GzColor &ka, const GzColor &ks, float a_s,  float a_r);
    GzMaterial(const GzTexture &tex, float a_s, float a_r);
    GzMaterial();

    // static member
    const static GzMaterial DEFAULT;
};
#endif

