#ifndef GZDISPLAY_H
#define GZDISPLAY_H
// 
// GzDisplay.h      CS580 Project Display for windows MFC
//

#include "gz.h"
#include "GzPixel.h"

class GzDisplay
{
    const static short MAXXRES;
    const static short MAXYRES;
    short xres, yres;
public:
    GzDisplay();
    GzDisplay(int a_xRes, int a_yRes);
    ~GzDisplay();
};

int GzNewFrameBuffer(char* & framebuffer, int width, int height);

#endif
