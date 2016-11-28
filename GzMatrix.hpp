//
//  GzMatrix.hpp
//  
//
//  Created by Peter Piao on 11/17/16.
//
//

#ifndef GzMatrix_hpp
#define GzMatrix_hpp

#include "gz.h"
class GzVector4
{
public:
    float a, b, c, d;
    
    GzVector4(float a_a, float a_b, float a_c, float a_d);
    
    GzVector4();
    
    
};

class GzMatrix
{
    // attributes
    float M[COORD4_BOUND][COORD4_BOUND];
    // constructors
public:
    GzMatrix(); // Default constructor. Build an identity matrix in 4-dimensional space.
    GzMatrix(const GzVector3 &v, int type); // Type specifies type of matrix: 0 for translation, 1 for scaling.
    GzMatrix(float arc, int axis); // Build a rotation matrix: rotate arc degree along an axis, 0 for x axis, 1 for y, 2 for z.
    // methods
    GzMatrix& inverseTranspose() const; // Get the inverse transpose matrix for normal transformation. Not necessary immediately.
}
// operator overloads
GzVector3& operator*(const GzMatrix &m, const GzVector3 &v);
GzMatrix& operator*(const GzMatrix &m1, const GzMatrix &m2);

#endif /* GzMatrix_hpp */
