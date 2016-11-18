#include "stdafx.h"
#include "GzGisplay.h"

int GzNewFrameBuffer(char* & framebuffer, int width, int height)
{
    if (width > MAXXRES || width <= 0 || height > MAXYRES || height <= 0)
    {
        return GZ_FAILURE;
    }
    // Allocate array space for Windows frame buffer.
    // Within the part I know, the frame buffer will not be free-ed
    framebuffer = new (std::nothrow) char [3*width*height];
    // Nothrow version will return NULL if not able to allocate.
    if (!framebuffer)
    {
        return GZ_FAILURE;
    }
    return GZ_SUCCESS;
}
