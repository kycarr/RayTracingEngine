#ifndef GZDISPLAY_H
#define GZDISPLAY_H
// 
// GzDisplay.h      CS580 Project Display for windows MFC
//

//#include "gz.h"
//
#include "GzConstants.h"
#include "GzColor.h"
#include "GzPixel.h"

class GzDisplay
{
    GzPixel *fbuf;
public:
    short xres, yres;
    GzColor bgColor;
    GzDisplay();
    GzDisplay(int a_xRes, int a_yRes);
    ~GzDisplay();
    int index(int i, int j) const;
    void init(const GzColor &back);
    void putDisplay(int i, int j, const GzPixel &p);
    void putDisplay(int i, int j, const GzColor &c);
    int getDisplay(int i, int j, GzPixel &get) const;
    int flush2File(FILE* outfile) const;
    int flush2FrameBuffer(char* framebuffer) const;
    const static short MAXXRES;
    const static short MAXYRES;
    friend int GzNewDisplay(GzDisplay* & display, int a_xRes, int a_yRes);
};

int GzNewFrameBuffer(char* & framebuffer, int width, int height);


#endif
