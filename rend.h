#ifndef REND_H
#define REND_H

#include "disp.h" /* include your own disp.h file (e.g. hw1)*/

/* Camera defaults */
#define	DEFAULT_FOV	35.0
/* world coords for image plane origin */
#define	DEFAULT_IM_Z	(-10.0)  
#define	DEFAULT_IM_Y	(5.0)    
#define	DEFAULT_IM_X	(-10.0)
/* default look-at point = 0,0,0 */

#define	DEFAULT_AMBIENT	{0.1, 0.1, 0.1}
#define	DEFAULT_DIFFUSE	{0.7, 0.6, 0.5}
#define	DEFAULT_SPECULAR	{0.2, 0.3, 0.4}
#define	DEFAULT_SPEC		32

#define	MATLEVELS	100	/* how many matrix pushes allowed */
#define	MAX_LIGHTS	20	/* how many lights allowed */

#ifndef GZRENDER
#define GZRENDER
typedef struct { /* define a renderer */
    GzDisplay       *display;
    GzCamera        camera;
    short           matlevel; /* top of stack -> current xform */
    GzMatrix        Ximage[MATLEVELS]; /* stack of xforms (Xsm) */
    GzMatrix        Xnorm[MATLEVELS]; /* xforms for norms (Xim) */
    GzMatrix        Xsp; /* NDC to screen (pers-to-screen) */
    GzColor         flatcolor; /* color for flat shaded triangles */
    int             interp_mode;
    int             numlights;
    GzLight         lights[MAX_LIGHTS];
    GzLight         ambientlight;
    GzColor         Ka, Kd, Ks;
    float           spec; /* specular power */
    GzTexture       tex_fun; /* tex_fun(float u, float v, GzColor color) */
    float           xShift, yShift;
} GzRender;
#endif

// Function declaration
// HW2
int GzNewRender(GzRender **render, GzDisplay *display);
int GzFreeRender(GzRender *render);
int GzBeginRender(GzRender	*render);
int GzPutAttribute(GzRender	*render, int numAttributes, GzToken	*nameList, 
        GzPointer *valueList);
int GzPutTriangle(GzRender *render, int	numParts, GzToken *nameList,
        GzPointer *valueList);
short ctoi(float color);
float minIn3(float c1, float c2, float c3);
float maxIn3(float c1, float c2, float c3);
bool insideTriangle(int xcoord, int ycoord, float * A, float * B, float * C);

// HW3
int GzPutCamera(GzRender *render, GzCamera *camera);
int GzPushMatrix(GzRender *render, GzMatrix	matrix);
int GzPopMatrix(GzRender *render);
float deg2Rad(float deg);
float rad2Deg(float rad);
float Q_rsqrt(float number);
int normalize3D(GzCoord v, GzCoord out);
int schmidt2(GzCoord vFrom, GzCoord e, GzCoord out);
int crossProduct(GzCoord v1, GzCoord v2, GzCoord out);
float dotProduct(GzCoord v1, GzCoord v2);
int matrixProduct(GzMatrix left, GzMatrix right, GzMatrix out);
int trans3DVectorByMat(GzMatrix left, GzCoord v3D, GzCoord out);

// Object Transformation
int GzRotXMat(float degree, GzMatrix mat);
int GzRotYMat(float degree, GzMatrix mat);
int GzRotZMat(float degree, GzMatrix mat);
int GzTrxMat(GzCoord translate, GzMatrix mat);
int GzScaleMat(GzCoord scale, GzMatrix mat);

// HW4
float barycentricF(int i, int j, float x, float y, float xi[3], float yi[3]);
int lighting(GzRender *render, GzCoord vert, GzCoord norm, GzColor lightColor[3]);
int gouraudInterp(GzColor lightColors[3][3], GzColor currentK[3], float alpha, float beta, float gamma, short pixelColor[3]);
int phongShading(GzRender *render, GzCoord verts[3], GzCoord norms[3], GzColor currentK[3], float alpha, float beta, float gamma, short pixelColor[3]);

// HW5
int GzFreeTexture();

#endif