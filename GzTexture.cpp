#include "stdafx.h"
#include "GzTexture.h"

// Constructor makes a new texture with the given texture function and file
GzTexture::GzTexture(const char* &_texfile, GzColor(GzTexture::*func)(float, float), int scale) :
    tex_file(_texfile), tex_fun(func), tex_scale(scale)
{
    loadFile(_texfile);
}

GzTexture::GzTexture(GzColor(GzTexture::*func)(float, float), int scale) : 
    tex_file(NULL), tex_fun(func), tex_scale(scale)
{
}

GzTexture::GzTexture() : tex_file(NULL), tex_fun(NULL), tex_scale(1)
{
}

void GzTexture::loadFile(const char* &file)
{
    GzColor color = GzColor();
    unsigned char		pixel[3];
    unsigned char     dummy;
    char  		foo[8];
    int   		i, j;
    FILE			*fd;

    tex_file = file;
    fd = fopen(tex_file, "rb");
    if (fd == NULL) {
        fprintf(stderr, "texture file not found\n");
        exit(-1);
    }
    fscanf(fd, "%s %d %d %c", foo, &xs, &ys, &dummy);
    image = (GzColor*)malloc(sizeof(GzColor)*(xs + 1)*(ys + 1));
    if (image == NULL) {
        fprintf(stderr, "malloc for texture image failed\n");
        exit(-2);
    }

    for (i = 0; i < xs*ys; i++) {	/* create array of GzColor values */
        fread(pixel, sizeof(pixel), 1, fd);
        image[i] = GzColor((float)((int)pixel[0]) * (1.0 / 255.0), (float)((int)pixel[1]) * (1.0 / 255.0), (float)((int)pixel[2]) * (1.0 / 255.0));
    }

    fclose(fd);
}

bool GzTexture::hasTexture() const
{
    return tex_fun != NULL;
}

/* Call this function to do the texture mapping for this texture */
GzColor GzTexture::tex_map(float u, float v)
{
    return (*this.*tex_fun)(u, v);
}

/* Image mapping texture function */
GzColor GzTexture::image_tex_func(float u, float v)
{
    GzColor color = GzColor();

    if (image == NULL)
        loadFile(tex_file);

    /* bounds-test u,v to make sure nothing will overflow image array bounds */
    u = max(0, u);
    u = min(u, 1);
    v = max(0, v);
    v = min(v, 1);

    /* determine texture cell corner values and perform bilinear interpolation */
    // scale uv range to xy texture image size: [0, 1] -> [0, xs-1], [0, ys-1]
    u = u * (xs - 1);
    v = v * (ys - 1);
    // abcd are pixel RGB colors at neighboring integer-coord texels
    int a = floor(u);
    int b = ceil(u);
    int c = floor(v);
    int d = ceil(v);
    // st are fractional distances [0, 1]
    float s = u - a;
    float t = v - c;

    color = s * t * image[b + d * xs] +
        (1 - s) * t * image[a + d * xs] +
        s * (1 - t) * image[b + c * xs] +
        (1 - s) * (1 - t) * image[a + c * xs];

    return color;
}

/* Checkerboard procedural texture function */
GzColor GzTexture::checker_ptex_func(float u, float v)
{
    float x_size = tex_scale == 0 ? 0 : 1.0f / tex_scale;
    float y_size = tex_scale == 0 ? 0 : 1.0f / tex_scale;

    // tex_scale = the # of rows/cols of checkers
    int x = floor((u * tex_scale) / x_size);
    int y = floor((v * tex_scale) / y_size);

    if ((x + y) % 2 == 0)
        return GzColor::BLACK;
    else
        return GzColor::WHITE;
}

GzColor GzTexture::checker_ptex_func2(float u, float v)
{
	int scale =1;
	//u = max(0, u);
	//u = min(u, 1);
	//v = max(0, v);
	//v = min(v, 1);

	int x = floor(u * scale);
	int y = floor(v * scale);

	if ((x + y) % 2 == 0)
		return GzColor::RED;
	else
		return GzColor::YELLOW;
}
