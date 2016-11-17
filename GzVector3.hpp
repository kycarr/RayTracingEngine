//
//  GzVector3.hpp
//  
//
//  Created by Peter Piao on 11/16/16.
//
//

#ifndef GzVector3_hpp
#define GzVector3_hpp

#include <stdio.h>
class GzVector3
{
public:
    GzVector3();
    GzVector3(float a_x, float a_y, float a_z);
    float length();
    GzVector3& normalize() const;
    GzVector3& negate() const;
    float dotMultiplay(GzVector3 &dot);
    GzVector3& crossMultiplay(GzVector3 &cross) const;
};

//overload operators
GzVector3& operator+(const GzVector3 &add1, const GzVector3 &add2) const;
GzVector3& operator*(float &times, const GzVector3 &v1) const;
GzVector3& operator*(const GzVector3 &v1, float &times) const;
GzVector3& operator/(float &divide) const;

#endif /* GzVector3_hpp */

