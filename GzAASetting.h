#ifndef GZAASETTING_H
#define GZAASETTING_H

#include "GzVector3.h"

class GzAASetting
{
public:
    int kernelSize;
    GzVector3 *ker;

    GzAASetting(int k_size, GzVector3 * k_array);
    GzAASetting(int k_size_sqrt);
    ~GzAASetting();
private:
    GzAASetting();
};

#endif

