#include "stdafx.h"
#include "GzDisplay.h"

const short GzDisplay::MAXXRES(1024);
const short GzDisplay::MAXYRES(1024);

int GzNewFrameBuffer(char* & framebuffer, int width, int height)
{
    if (width > GzDisplay::MAXXRES || width <= 0 || height > GzDisplay::MAXYRES || height <= 0)
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

int GzNewDisplay(GzDisplay* & display, int a_xRes, int a_yRes)
{
    if (a_xRes > GzDisplay::MAXXRES || a_xRes <= 0 || a_yRes > GzDisplay::MAXYRES || a_yRes <= 0)
    {
        return GZ_FAILURE;
    }
    display = new (std::nothrow) GzDisplay(a_xRes, a_yRes);
    // Nothrow version will return nullptr if not able to allocate.
    if (!display || !(display->fbuf))
    {
        return GZ_FAILURE;
    }
    return GZ_SUCCESS;
}

GzDisplay::GzDisplay(int a_xRes, int a_yRes) :
    xres(static_cast<short>(a_xRes)), yres(static_cast<short>(a_yRes))
{
    this->fbuf = new (std::nothrow) GzPixel[xres * yres];
    //if (!this->fbuf)
    //{
        //delete this;
        //this = nullptr; // Not able to assign this to nullptr
    //}
}

GzDisplay::GzDisplay() : GzDisplay(MAXXRES, MAXYRES)
{
}

GzDisplay::~GzDisplay()
{
    delete[] this->fbuf;
}

int GzDisplay::index(int i, int j) const
{
    return i + j * this->yres;
}

void GzDisplay::init(const GzColor &back)
{
    this->bgColor = back;
    //for (int j = 0; j < this->yres; ++j)
    //{
        //for (int i = 0; i < this->xres; ++i)
        //{
            //this->fbuf[index(i, j)].putColor(back);
        //}
    //}
}

void GzDisplay::putDisplay(int i, int j, const GzPixel &p)
{
    if (i >= 0 && i < this->xres && j >= 0 && j < this->yres)
    {
        this->fbuf[index(i, j)] = p;
    }
}

void GzDisplay::putDisplay(int i, int j, const GzColor &c)
{
    if (i >= 0 && i < this->xres && j >= 0 && j < this->yres)
    {
        this->fbuf[index(i, j)].putColor(c);
    }
}

int GzDisplay::getDisplay(int i, int j, GzPixel &get) const
{
    if (i >= 0 && i < this->xres && j >= 0 && j < this->yres)
    {
        get = this->fbuf[index(i, j)];
        return GZ_SUCCESS;
    }
    return GZ_FAILURE;
}

int GzDisplay::flush2File(FILE* outfile) const
{
    int status(GZ_SUCCESS);
    fprintf(outfile, "P6 %d %d 255\r", this->xres, this->yres);
    for (int j = 0; j < this->yres; ++j)
    {
        for (int i = 0; i < this->xres; ++i)
        {
            GzPixel get;
            status = status || this->getDisplay(i, j, get);
            fprintf(outfile, "%c%c%c", (get.red) >> 4, (get.green) >> 4, (get.blue) >> 4);
        }
    }
    return status;
}

int GzDisplay::flush2FrameBuffer(char* framebuffer) const
{
    int status(GZ_SUCCESS);
    for (int j = 0; j < this->yres; ++j)
    {
        for (int i = 0; i < this->xres; ++i)
        {
            GzPixel get;
            status = status || this->getDisplay(i, j, get);
            char *bufferPixel = framebuffer + 3 * index(i, j);
            (*bufferPixel) = (get.blue) >> 4;
            ++bufferPixel;
            (*bufferPixel) = (get.green) >> 4;
            ++bufferPixel;
            (*bufferPixel) = (get.red) >> 4;
        }
    }
    return status;
}
