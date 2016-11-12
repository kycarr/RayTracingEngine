#ifndef MATERIAL_H
#define MATERIAL_H
// I'm unsure how our design will look (whether these will all be in one file or several files),
// but if in several files the color class will need to be included here - Kayla

//#include Color.h      // GzColor

// Represents the material of a Geometry object
class GzMaterial
{
public:
    GzColor Kd;   // diffuse color
    GzColor Ka;   // ambient color
    GzColor Ks;   // specular color
	float   s;   //(N*L)^s
                  // add texture component later
                  // add refractive index later
	float reflectiveness;

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