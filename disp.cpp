#include "stdafx.h"
#include "gz.h"
#include "disp.h"

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

//
//  New GzDisplay struct used by the program to process pixels. Refer to the definition of GzDisplay struct in disp.h.
//  @param display is a pointer to the to-be-allocated GzDisplay data. If I wrote the code, I would name it as pDisplay. Sad.
//
/*
int GzNewDisplay(GzDisplay **display, int xRes, int yRes)
{
    if (xRes > MAXXRES || xRes <= 0 || yRes > MAXYRES || yRes <= 0)
    {
  return GZ_FAILURE;
    }
 // Allocate space for GzDisplay and GzPixel array. Free this in GzFreeDisplay.
    *display = new (std::nothrow) GzDisplay;
 // Nothrow version will return NULL if not able to allocate.
 if (*display == NULL)
 {
  return GZ_FAILURE;
 }
    (*display)->xres = xRes;
    (*display)->yres = yRes;
 (*display)->fbuf = new (std::nothrow) GzPixel [xRes * yRes];
 // Nothrow version will return NULL if not able to allocate.
 if ((*display)->fbuf == NULL)
 {
  return GZ_FAILURE;
 }
 return GZ_SUCCESS;
}
*/

//
    //Free the space allocated for display (GzDisplay struct).
//
/*
int GzFreeDisplay(GzDisplay *display)
{
    delete [] (display->fbuf);
    delete display;
 return GZ_SUCCESS;
}
*/

//
//  Pass back resolution values for a display. Used in Application, although not really helpful.
//
/*
int GzGetDisplayParams(GzDisplay *display, int *xRes, int *yRes)
{
    if (display == NULL)
    {
        return GZ_FAILURE;
    }
    *xRes = (display->xres);
    *yRes = (display->yres);
 return GZ_SUCCESS;
}
*/

/*
    Initialize fbuf content of display. In fact, this is used to assign a background color.
int GzInitDisplay(GzDisplay *display)
{
 // Because params xres and yres are already set, only need to set a
 // default/background color here.
    for (int j = 0; j < display->yres; ++j)
    {
        for (int i = 0; i < display->xres; ++i)
        {
            // ARRAY(i, j) is a macro definition which actually depends on (display->xres). Whenever use ARRAY(i, j), you need to make sure display->xres is available.
            GzPixel *pixel = display->fbuf + (ARRAY(i, j));
            // Set the background color to light blue
            pixel->red = 1632;
            pixel->green = 3264;
            pixel->blue = 4080;
            // Alpha not useful yet.
            pixel->alpha = 0;
            // In order to utilize z-buffer, need to initialize every pixel's z to INT_MAX
            pixel->z = INT_MAX;
        }
    }
 return GZ_SUCCESS;
}
*/

/*
    Write RGBA and z to a pixel in display. Discard pixels out of the display area.
    @param r, g, b, a are GzIntensity type, which is defined in gz.h as same to short.
    However, due to the usage of this function in Application1, where int values
    were assigned to r, g, b, a, we need to treat them as unsigned short values.
    @param z is GzDepth type, which is defined in gz.h as same to int.
int GzPutDisplay(GzDisplay *display, int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
 // OK to assign int values to GzIntensity(short) types if less than 65536.
 // Check bounds
 if (i >= 0 && i < display->xres && j >= 0 && j < display->yres)
 {
  GzPixel *pixel = display->fbuf + (ARRAY(i, j));
  pixel->red = (r >= 0 && r < 4095 ? r : 4095);// clamp to 12 bits value
  pixel->green = (g >= 0 && g < 4095 ? g : 4095);
  pixel->blue = (b >= 0 && b < 4095 ? b: 4095);
  pixel->alpha = (a >= 0 && a < 4095 ? a: 4095);
  pixel->z = z;
 }
 return GZ_SUCCESS;
}
*/

/*
    Pass back a pixel value to the display
int GzGetDisplay(GzDisplay *display, int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
 // Check bounds. If out of bounds, return fail.
 if (i >= 0 && i < display->xres && j >= 0 && j < display->yres)
 {
  GzPixel *pixel = display->fbuf + (ARRAY(i, j));
  *r = pixel->red;
  *g = pixel->green;
  *b = pixel->blue;
  *a = pixel->alpha;
  *z = pixel->z;
  return GZ_SUCCESS;
 }
 return GZ_FAILURE;
}
*/

/*
    Write the pixels in the GzDisplay struct into a ppm file (not plain ppm as P3).
    @param outfile is already opened in Application.
int GzFlushDisplay2File(FILE* outfile, GzDisplay *display)
{
 fprintf(outfile, "P6 %d %d 255\r", display->xres, display->yres);
    // Only need to write every pixels in order (the pixels are stored in fbuf
    // as lines in x direction without break between lines).
 for (int i = 0; i < display->xres * display->yres; ++i)
 {
  GzPixel *pixel = (display->fbuf + i);
        // Before writing, it is necessary to make color intensities as 8 bit data.
  fprintf(outfile, "%c%c%c", (pixel->red) >> 4, (pixel->green) >> 4, (pixel->blue) >> 4);
 }
 return GZ_SUCCESS;
}
*/

/*
    Write the pixels in the GzDisplay struct to framebuffer.
 - CAUTION: when storing the pixels into the frame buffer, the order is blue, green, and red 
 - NOT red, green, and blue !!!
    @param framebuffer is a char array
int GzFlushDisplay2FrameBuffer(char* framebuffer, GzDisplay *display)
{
 for (int i = 0; i < display->xres * display->yres; ++i)
 {
  // Iterate over pixels, but need to write three color separately.
  GzPixel *pixel = display->fbuf + i;
  char *bufferPixel = framebuffer + 3 * i;
        // The same idea as writing to file, shift right to make 8 bit data.
  (*bufferPixel) = (pixel->blue) >> 4;
  ++bufferPixel;
  (*bufferPixel) = (pixel->green) >> 4;
  ++bufferPixel;
  (*bufferPixel) = (pixel->red) >> 4;
 }
 return GZ_SUCCESS;
}
*/
