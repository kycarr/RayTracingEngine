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
                  // add texture component later
                  // add refractive index later

    GzMaterial(GzColor d, GzColor a, GzColor s);
};

// Constructor makes a new material with the given diffuse, ambient, and specular properties
GzMaterial::GzMaterial(GzColor d, GzColor a, GzColor s)
{
    Kd = d;
    Ka = a;
    Ks = s;
}