#include "stdafx.h"
#include "GzMaterial.h"

// Constructor makes a new material with the given diffuse, ambient, and specular properties
GzMaterial::GzMaterial(const GzColor &kd, float a_s, float a_n, float a_r, float a_f) :
    Kd(kd), s(a_s), n(a_n), r(a_r), f(a_f), texture(GzTexture())
{
    // Add more code for texture mapping, normal mapping later.
}

GzMaterial::GzMaterial(const GzTexture &tex, float a_s, float a_n, float a_r, float a_f) :
    Kd(GzColor::WHITE), s(a_s), n(a_n), r(a_r), f(a_f), texture(tex)
{
}

GzMaterial::GzMaterial(const GzColor &kd, float a_r) :
    Kd(kd), s(16.0f), n(1.0f), r(a_r), f(0.0f), texture(GzTexture())
{
}

GzMaterial::GzMaterial(const GzTexture &tex, float a_r) :
    Kd(GzColor::WHITE), s(16.0f), n(1.0f), r(a_r), f(0.0f), texture(tex)
{
}

GzMaterial::GzMaterial() : GzMaterial(GzColor::WHITE, 16.0f, 1.0f, 0.0f, 0.0f)
{
}

const GzMaterial GzMaterial::DEFAULT(GzColor(0.5f, 0.5f, 0.5f), 16.0f, 1.0f, 0.0f, 0.0f);
