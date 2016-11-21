#ifndef GZVECTOR3_H
#define GZVECTOR3_H

//#include <iostream>
// GzVector3.h

// Created by Peter Piao on 11/16/16.
#include "GzException.h"

class GzVector3
{
public:
    float x, y, z;

    GzVector3(float a_x, float a_y, float a_z);


    GzVector3();

//    GzVector3(const GzVector3 &vc) :
//        x(vc.x), y(vc.y), z(vc.z)
//    {
//        std::cout << "Copy called" << std::endl;
//    }

    //GzVector3& operator=(const GzVector3 &vc);

    float lengthSqr() const;
    float length() const;
    GzVector3 normalize() const; // Return the normalized vector, without changing this object. If this vector is zero, throw an exception of type GzException.
    GzVector3 flip() const; // Return the negative of this vector.
    float dotMultiply(const GzVector3 &dot) const;
    GzVector3 crossMultiply(const GzVector3 &cross) const;
};
// operator overloads
GzVector3 operator+(const GzVector3 &add1, const GzVector3 &add2);
GzVector3 operator-(const GzVector3 &minus1, const GzVector3 &minus2);
GzVector3 operator*(const GzVector3 &v1, float times);
GzVector3 operator*(float times, const GzVector3 &v1);

#endif

