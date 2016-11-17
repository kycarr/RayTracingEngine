#ifndef GZVECTOR3_H
#define GZVECTOR3_H

//  GzVector3.h

//  Created by Peter Piao on 11/16/16.

class GzVector3
{
public:
    float x, y, z;

    GzVector3(); // Default constructor. Build a zero vector in 3-dimensional space.
    GzVector3(float a_x, float a_y, float a_z);
    float length() const;
    GzVector3& normalize() const; // Return the normalized vector, without changing this object. If this vector is zero, return a zero vector.
    GzVector3& negate() const; // Return the negative of this vector.
    float dotMultiply(const GzVector3 &dot) const;
    GzVector3& crossMultiply(const GzVector3 &cross) const;
}
// operator overloads
GzVector3& operator+(const GzVector3 &add1, const GzVector3 &add2);
GzVector3& operator-(const GzVector3 &minus1, const GzVector3 &minus2);
GzVector3& operator*(const GzVector3 &v1, float times);
GzVector3& operator*(float times, const GzVector3 &v1);

#endif

