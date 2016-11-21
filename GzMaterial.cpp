#include "stdafx.h"
#include "GzMaterial.h"

// Constructor makes a new material with the given diffuse, ambient, and specular properties
GzMaterial::GzMaterial(const GzColor &kd, const GzColor &ka, const GzColor &ks, float a_s, float a_r) :
    Kd(kd), Ka(ka), Ks(ks), s(a_s), reflectiveness(a_r)
{
    // Add more code for texture mapping, normal mapping later.
}

GzMaterial::GzMaterial() : GzMaterial(GzColor::BLACK, GzColor::BLACK, GzColor::WHITE, 16.0f, 0.0f)
{
}

const GzMaterial GzMaterial::DEFAULT(GzColor(0.5f, 0.5f, 0.5f), GzColor::BLACK, GzColor(0.5f, 0.5f, 0.5f), 16.0f, 0.5f);
