#ifndef GZCOLOR_H
#define GZCOLOR_H
//
// GzColor.h        The definition of class GzColor
//

class GzColor
{
public:
// attributes
    float r, g, b;
// constructors
    GzColor(); // Default constructor, build a black GzColor object
    GzColor(float a_r, float a_g, float a_b);
// methods
    GzColor modulate(const GzColor &other) const;
    GzColor exposure() const;
// static members
    const static GzColor BLACK;
    const static GzColor WHITE;
    const static GzColor RED;
    const static GzColor GREEN;
    const static GzColor BLUE;
    const static GzColor CYAN;
    const static GzColor MAGENTA;
    const static GzColor YELLOW;
};

// operator overloads
GzColor operator+(const GzColor &c1, const GzColor &c2);
GzColor operator*(const GzColor &c1, float s);
GzColor operator*(float s, const GzColor &c1);

#endif
