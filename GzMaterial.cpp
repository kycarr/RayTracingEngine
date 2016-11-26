#include "stdafx.h"
#include "GzMaterial.h"

// Constructor makes a new material with the given diffuse, ambient, and specular properties
GzMaterial::GzMaterial(const GzColor &kd, const GzColor &ka, const GzColor &ks, float a_s, float a_r) :
    Kd(kd), Ka(ka), Ks(ks), s(a_s), r(a_r), texture(GzTexture())
{
    // Add more code for texture mapping, normal mapping later.
}

GzMaterial::GzMaterial(const GzTexture &tex, float a_s, float a_r) :
    Kd(GzColor::WHITE), Ka(GzColor::WHITE), Ks(GzColor::WHITE), s(a_s), r(a_r), texture(tex)
{
}

GzMaterial::GzMaterial() : GzMaterial(GzColor::WHITE, GzColor::WHITE, GzColor::WHITE, 16.0f, 0.0f)
{
}

const GzMaterial GzMaterial::DEFAULT(GzColor(0.5f, 0.5f, 0.5f), GzColor::BLACK, GzColor(0.5f, 0.5f, 0.5f), 16.0f, 0.5f);
