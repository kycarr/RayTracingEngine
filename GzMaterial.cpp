#include "stdafx.h"
#include "GzMaterial.h"

// Constructor makes a new material with the given diffuse, ambient, and specular properties
GzMaterial::GzMaterial(const GzColor &kd, const GzTexture &norm, float a_s, float a_n, float a_r, float a_f) :
    Kd(kd), s(a_s), n(a_n), r(a_r), f(a_f), texture(GzTexture()), normal(norm)
{
}

GzMaterial::GzMaterial(const GzTexture &tex, const GzTexture &norm, float a_s, float a_n, float a_r, float a_f) :
    Kd(GzColor::WHITE), s(a_s), n(a_n), r(a_r), f(a_f), texture(tex), normal(norm)
{
}

GzMaterial::GzMaterial(const GzColor &kd, float a_s, float a_n, float a_r, float a_f) :
    Kd(kd), s(a_s), n(a_n), r(a_r), f(a_f), texture(GzTexture()), normal(GzTexture())
{
}

GzMaterial::GzMaterial(const GzTexture &tex, float a_s, float a_n, float a_r, float a_f) :
    Kd(GzColor::WHITE), s(a_s), n(a_n), r(a_r), f(a_f), texture(tex), normal(GzTexture())
{
}

GzMaterial::GzMaterial(const GzColor &kd, const GzTexture &norm, float a_r) :
    Kd(kd), s(16.0f), n(1.0f), r(a_r), f(0.0f), texture(GzTexture()), normal(norm)
{
}

GzMaterial::GzMaterial(const GzTexture &tex, const GzTexture &norm, float a_r) :
    Kd(GzColor::WHITE), s(16.0f), n(1.0f), r(a_r), f(0.0f), texture(tex), normal(norm)
{
}


GzMaterial::GzMaterial(const GzColor &kd, float a_r) :
    Kd(kd), s(16.0f), n(1.0f), r(a_r), f(0.0f), texture(GzTexture()), normal(GzTexture())
{
}

GzMaterial::GzMaterial(const GzTexture &tex, float a_r) :
    Kd(GzColor::WHITE), s(16.0f), n(1.0f), r(a_r), f(0.0f), texture(tex), normal(GzTexture())
{
}

GzMaterial::GzMaterial() : GzMaterial(GzColor::WHITE, 16.0f, 1.0f, 0.0f, 0.0f)
{
}

const GzMaterial GzMaterial::DEFAULT(GzColor(0.5f, 0.5f, 0.5f), 16.0f, 1.0f, 0.0f, 0.0f);
