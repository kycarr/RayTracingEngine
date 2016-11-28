//
//  GzMatrix.hpp
//  
//
//  Created by Peter Piao on 11/17/16.
//
//

#ifndef GZMATRIX_H
#define GZMATRIX_H
#include "GzVector3.h"
#include "GzConstants.h"

class GzMatrix
{
    // attributes
    float M[COORD4_BOUND][COORD4_BOUND];
    // constructors
public:
    GzMatrix(); // Default constructor. Build an identity matrix in 4-dimensional space.
    GzMatrix(const GzVector3 &v, int type); // Type specifies type of matrix: 0 for translation, 1 for scaling.
    GzMatrix(float angle, int axis); // Build a rotation matrix: rotate arc degree along an axis, 0 for x axis, 1 for y, 2 for z.
    // methods
    GzMatrix& inverseTranspose() const; // Get the inverse transpose matrix for normal transformation. Not necessary immediately.
}
// operator overloads
GzVector3& operator*(const GzMatrix &m, const GzVector3 &v);
GzMatrix& operator*(const GzMatrix &m1, const GzMatrix &m2);

#endif /* GzMatrix_hpp */
