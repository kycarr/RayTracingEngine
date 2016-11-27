#include "stdafx.h"
#include "GzAASetting.h"
#include <cmath>

GzAASetting::GzAASetting(int k_size, GzVector3 * k_array) :
    kernelSize(k_size), ker(k_array)
{
}

GzAASetting::GzAASetting(int k_size_sqrt) : kernelSize(k_size_sqrt * k_size_sqrt)
{
    this->ker = new GzVector3[k_size_sqrt * k_size_sqrt];
    float normal = 0.0f; // For normalization
    for (int kj = 0; kj < k_size_sqrt; ++kj)
    {
        float y_off = (kj + 0.5f - k_size_sqrt / 2.0f) / k_size_sqrt;
        for (int ki = 0; ki < k_size_sqrt; ++ki)
        {
            float x_off = (ki + 0.5f - k_size_sqrt / 2.0f) / k_size_sqrt;
            float mul = (1 - 2 * std::abs(x_off)) * (1 - 2 * std::abs(y_off));
            normal += mul;
            this->ker[kj*k_size_sqrt + ki] = GzVector3(x_off, y_off, mul);
        }
    }
    for (int kj = 0; kj < k_size_sqrt; ++kj)
    {
        for (int ki = 0; ki < k_size_sqrt; ++ki)
        {
            this->ker[kj*k_size_sqrt + ki].z /= normal;
        }
    }
}

GzAASetting::~GzAASetting()
{
    delete[] this->ker;
}

GzAASetting::GzAASetting() : GzAASetting(0, nullptr)
{
}

