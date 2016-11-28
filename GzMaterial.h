#ifndef GZMATERIAL_H
#define GZMATERIAL_H
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
    float s;   //(R*E)^s, or (N*H)^s in Blinn-Phong lighting
    float n; // refractive index
    float r; // reflective part
    float f; // refractive part
    GzTexture texture; // texture component
    GzTexture normal;

    // constructors
    GzMaterial(const GzColor &kd, const GzTexture &norm, float a_s, float a_n, float a_r, float a_f);
    GzMaterial(const GzTexture &tex, const GzTexture &norm, float a_s, float a_n, float a_r, float a_f);
    GzMaterial(const GzColor &kd, float a_s, float a_n, float a_r, float a_f);
    GzMaterial(const GzTexture &tex, float a_s, float a_n, float a_r, float a_f);
    GzMaterial(const GzColor &kd, const GzTexture &norm, float a_r);
    GzMaterial(const GzTexture &tex, const GzTexture &norm, float a_r);
    GzMaterial(const GzColor &kd, float a_r);
    GzMaterial(const GzTexture &tex, float a_r);

    GzMaterial();

    // static member
    const static GzMaterial DEFAULT;
};
#endif

