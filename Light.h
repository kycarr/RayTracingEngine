#ifndef LIGHT_H
#define LIGHT_H
// I'm unsure how our design will look (whether these will all be in one file or several files),
// but if in several files the color and vector classes will need to be included here - Kayla

//#include Color.h      // GzColor
//#include Vector.h     // GzVector

// Represents a directional or point light
class GzLight
{
public:
    int type;           // 0 for directional, 1 for point
    GzVector position;  // position if point light, direction if directional light
    GzColor color;      // the color of the light

    GzLight(int t, GzVector pos);
    GzLight(int t, GzVector pos,  GzColor col);
};

// Constructor makes a new white light with the given type and position
GzLight::GzLight(int t, GzVector pos)
{
    type = t;
    position = pos;
    color = new GzColor(1, 1, 1);
}

// Constructor makes a new light with the given type, position, and color
GzLight::GzLight(int t, GzVector pos, GzColor col)
{
    type = t;
    position = pos;
    color = col;
}
#endif