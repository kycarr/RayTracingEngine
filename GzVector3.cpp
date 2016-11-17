//
//  GzVector3.cpp
//  
//
//  Created by Peter Piao on 11/16/16.
//
//

#include "GzVector3.hpp"
#include <math.h>

GzVector3::GzVector3(float a_x, float a_y, float a_z) :
    x(a_x), y(a_y), z(a_z)
{
}

GzVector3::GzVector3() : GzVector3(0.0f, 0.0f, 0.0f)
{
}
float length() const
{
    return sqrt(x*x + y*y + z*z);
}

GzVector3& normalize() const
{
    float normalLength = this->length();
    if (normalLength == 0) return GzVector3();
    return GzVector3(x/normalLength, y/normalLength, z/normalLength);
}
GzVector3& negate() const
{
    return GzVector3(-x, -y, -z);
}
float dotMultiplay(const GzVector3 &dot) const
{
    return (this->x*dot.x + this->y*dot.y + this->z*dot.z);
}
GzVector3& crossMultiplay(const GzVector3 &cross) const
{
    return GzVector3(this->y*cross.z - this->z*cross.y, this->z*cross.x - this->x*cross.z,
                         this->x*cross.y - this->y*cross.x);
}
GzVector3& operator+(const GzVector3 &add1, const GzVector3 &add2) const
{
    return GzVector3(add1.x+add2.x, add1.y+add2.y, add1.z+add2.z);
}
GzVector3& operator*(float &times, const GzVector3 &v1) const
{
    return GzVector3(v1.x*times, v1.y*times, v1.z*times);
}
GzVector3& operator*(const GzVector3 &v1, float &times)) const
{
    return this->operator*(times, v1);
}
GzVector3& operator/(float &divide) const
{
    if (divide == 0) return GzVector3();
    return GzVector3(this->x/divide, this->y/divide, this->z/divide);
}
