#include <iostream>
#include "GzVector3.h"
#include "GzCamera.h"

void printVector(GzVector3 v)
{
    std::cout << v.x << " " << v.y << " " << v.z << std::endl;
    return;
}

int main()
{
    GzVector3 a;
    GzVector3 b(0.0f, 1.0f, 0.0f);
    //GzVector3 c;
    //c = b;
    GzCamera ca(a, GzVector3(0.0f, 0.0f, -1.0f), b, 120);
   //printVector(c);
    return 0;
}
