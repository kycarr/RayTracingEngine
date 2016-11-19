#include "stdafx.h"
#include "GzMaterial.h"

// Constructor makes a new material with the given diffuse, ambient, and specular properties
GzMaterial::GzMaterial(GzColor kd, GzColor ka, GzColor ks, float S, float r) :
    Kd(kd), Ka(ka), Ks(ks), s(S), reflectiveness(r)
{
}