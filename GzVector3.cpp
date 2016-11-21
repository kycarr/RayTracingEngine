#include "stdafx.h"
//
//  GzVector3.cpp
//
//
//  Created by Peter Piao on 11/16/16.
//
//

#include "GzVector3.h"
#include <cmath>

GzVector3::GzVector3(float a_x, float a_y, float a_z) :
    x(a_x), y(a_y), z(a_z)
{
//    std::cout << "Constructor called" << std::endl;
}

GzVector3::GzVector3() : GzVector3(0.0f, 0.0f, 0.0f)
{
//    std::cout << "Default constructor called" << std::endl;
}

//GzVector3& GzVector3::operator=(const GzVector3 &vc)
//{
//    this->x = vc.x;
//    this->y = vc.y;
//    this->z = vc.z;
//    //std::cout << "Assign called" << std::endl;
//    return *this;
//}

float GzVector3::lengthSqr() const
{
    return x * x + y * y + z * z;
}

float GzVector3::length() const
{
    return std::sqrt(this->lengthSqr());
}

GzVector3 GzVector3::normalize() const
{
    float normalLength = this->length();
    if (normalLength == 0.0f) throw GzException();
    return GzVector3(x/normalLength, y/normalLength, z/normalLength);
}
GzVector3 GzVector3::flip() const
{
    return GzVector3(-x, -y, -z);
}
float GzVector3::dotMultiply(const GzVector3 &dot) const
{
    return (this->x*dot.x + this->y*dot.y + this->z*dot.z);
}
GzVector3 GzVector3::crossMultiply(const GzVector3 &cross) const
{
    return GzVector3(this->y*cross.z - this->z*cross.y, this->z*cross.x - this->x*cross.z,
                         this->x*cross.y - this->y*cross.x);
}
GzVector3 operator+(const GzVector3 &add1, const GzVector3 &add2)
{
    return GzVector3(add1.x+add2.x, add1.y+add2.y, add1.z+add2.z);
}
GzVector3 operator-(const GzVector3 &minus1, const GzVector3 &minus2)
{
    return GzVector3(minus1.x-minus2.x, minus1.y-minus2.y, minus1.z-minus2.z);
}
GzVector3 operator*(float times, const GzVector3 &v1)
{
    return GzVector3(v1.x*times, v1.y*times, v1.z*times);
}
GzVector3 operator*(const GzVector3 &v1, float times)
{
    return times * v1;
}
