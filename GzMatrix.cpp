//
//  GzMatrix.cpp
//  
//
//  Created by Peter Piao on 11/17/16.
//
//

#include "GzMatrix.hpp"
#include <cmath>

GzMatrix::GzMatrix()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == j) M[i][j] = 1.0f;
            else M[i][j] = 0.0f;
        }
    }
}
GzMatrix::GzMatrix(const GzVector3 &v, int type) : GzMatrix()
{
    if (type == 0)
    {
        M[0][3] = v.x;
        M[1][3] = v.y;
        M[2][3] = v.z;
    }
    else if (type == 1)
    {
        M[0][0] = v.x;
        M[1][1] = v.y;
        M[2][2] = v.z;
    }
}
GzMatrix::GzMatrix(float arc, int axis) : GzMatrix()
{
    float rad = arc * PI / 180;
    if (axis == 0)
    {
        M[1][1] = cos(rad);
        M[2][2] = cos(rad);
        M[2][1] = -sin(rad);
        M[1][2] = sin(rad);
    }
    if (axis == 1)
    {
        M[0][0] = cos(rad);
        M[3][3] = cos(rad);
        M[2][0] = sin(rad);
        M[0][2] = -sin(rad);
    }
    if (axis == 2)
    {
        M[0][0] = cos(rad);
        M[1][1] = cos(rad);
        M[1][0] = -sin(rad);
        M[0][1] = sin(rad);
    }
}
GzMatrix GzMatrix::inverseTranspose() const
{
    GzMatrix temp;
    float detA;
    detA = M[0][0]*M[1][1]*M[2][2] + M[1][0]*M[2][1]*M[0][2]
    + M[2][0]*M[0][1]*M[1][2] - M[0][0]*M[2][1]*M[1][2]
    - M[2][0]*M[1][1]*M[0][2] - M[1][0]*M[0][1]*M[2][2];
    if (deta == 0.0f) return M;
    temp[0][0] = M[1][1]*M[2][2] - M[1][2]*M[2][1];
    temp[1][0] = M[1][2]*M[2][0] - M[1][0]*M[2][2];
    temp[2][0] = M[1][0]*M[2][1] - M[1][1]*M[2][0];
    temp[0][1] = M[0][2]*M[2][1] - M[0][1]*M[2][2];
    temp[1][1] = M[0][0]*M[2][2] - M[0][2]*M[2][0];
    temp[2][1] = M[0][1]*M[2][0] - M[0][0]*M[2][1];
    temp[0][2] = M[0][1]*M[1][2] - M[0][2]*M[1][1];
    temp[1][2] = M[0][2]*M[1][0] - M[0][0]*M[1][2];
    temp[2][2] = M[0][0]*M[1][1] - M[0][1]*M[1][0];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            temp[i][j] = temp[i][j] / detA;
        }
    }
    return temp;
}
GzVector3 operator*(const GzMatrix &m, const GzVector3 &v)
{
    flaot a, b, c, d;
    a = m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z + m[0][3];
    b = m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z + m[1][3];
    c = m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z + m[2][3];
    d = m[3][0]*v.x + m[3][1]*v.y + m[3][2]*v.z + m[3][3];
    if (d == 0.0f) return GzVector3();
    return GzVector3(a/d, b/d, c/d);
}
GzMatrix operator*(const GzMatrix &m1, const GzMatrix &m2)
{
    GzMatrix result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return result;
}
