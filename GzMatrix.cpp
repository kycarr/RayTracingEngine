//
//  GzMatrix.cpp
//  
//
//  Created by Peter Piao on 11/17/16.
//
//
#include "GzMatrix.h"
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
    if (type == TRANSLATION)
    {
        M[0][3] = v.x;
        M[1][3] = v.y;
        M[2][3] = v.z;
    }
    else if (type == SCALING)
    {
        M[0][0] = v.x;
        M[1][1] = v.y;
        M[2][2] = v.z;
    }
}
GzMatrix::GzMatrix(float angle, int axis) : GzMatrix()
{
    float rad = angle * PI / 180;
    if (axis == X)
    {
        M[1][1] = std::cos(rad);
        M[2][2] = std::cos(rad);
        M[2][1] = -std::sin(rad);
        M[1][2] = std::sin(rad);
    }
    if (axis == Y)
    {
        M[0][0] = std::cos(rad);
        M[2][2] = std::cos(rad);
        M[2][0] = std::sin(rad);
        M[0][2] = -std::sin(rad);
    }
    if (axis == Z)
    {
        M[0][0] = std::cos(rad);
        M[1][1] = std::cos(rad);
        M[1][0] = -std::sin(rad);
        M[0][1] = std::sin(rad);
    }
}
GzMatrix GzMatrix::inverseTranspose() const
{
    GzMatrix temp;
    float detA;
    detA = M[0][0]*M[1][1]*M[2][2] + M[1][0]*M[2][1]*M[0][2]
    + M[2][0]*M[0][1]*M[1][2] - M[0][0]*M[2][1]*M[1][2]
    - M[2][0]*M[1][1]*M[0][2] - M[1][0]*M[0][1]*M[2][2];
    if (detA == 0.0f) return temp;
    temp.M[0][0] = M[1][1]*M[2][2] - M[1][2]*M[2][1];
    temp.M[0][1] = M[1][2]*M[2][0] - M[1][0]*M[2][2];
    temp.M[0][2] = M[1][0]*M[2][1] - M[1][1]*M[2][0];
    temp.M[1][0] = M[0][2]*M[2][1] - M[0][1]*M[2][2];
    temp.M[1][1] = M[0][0]*M[2][2] - M[0][2]*M[2][0];
    temp.M[1][2] = M[0][1]*M[2][0] - M[0][0]*M[2][1];
    temp.M[2][0] = M[0][1]*M[1][2] - M[0][2]*M[1][1];
    temp.M[2][1] = M[0][2]*M[1][0] - M[0][0]*M[1][2];
    temp.M[2][2] = M[0][0]*M[1][1] - M[0][1]*M[1][0];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            temp.M[i][j] = temp.M[i][j] / detA;
        }
    }
    return temp;
}
GzVector3 operator*(const GzMatrix &m, const GzVector3 &v)
{
    float a, b, c, d;
    a = m.M[0][0]*v.x + m.M[0][1]*v.y + m.M[0][2]*v.z + m.M[0][3];
    b = m.M[1][0]*v.x + m.M[1][1]*v.y + m.M[1][2]*v.z + m.M[1][3];
    c = m.M[2][0]*v.x + m.M[2][1]*v.y + m.M[2][2]*v.z + m.M[2][3];
    d = m.M[3][0]*v.x + m.M[3][1]*v.y + m.M[3][2]*v.z + m.M[3][3];
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
                result.M[i][j] += m1.M[i][k] * m2.M[k][j];
            }
        }
    }
    return result;
}
