#ifndef GZCONSTANTS_H
#define GZCONSTANTS_H

// universal constants

// int values used as status indicators
const int GZ_SUCCESS(0);
const int GZ_FAILURE(1);

// int values used as light type
const int DIR_LIGHT(0);
const int POINT_LIGHT(1);
const int AREA_LIGHT(2);

// for math calculations
const double PI(3.1415926535897932);

// for magic numbers
const int COORD4_BOUND(4);
const float EPSILON0(0.005f);

// for GzMatrix translation, and scaling type
const int TRANSLATION(0);
const int SCALING(1);

// for matrix rotation
const int X(0);
const int Y(1);
const int Z(2);

//***************************
// Discarded old codes
//***************************
//
// name list tokens
//
//#define GZ_NULL_TOKEN        0 // triangle vert attributes
//#define GZ_POSITION          1
//#define GZ_NORMAL            2
//#define GZ_TEXTURE_INDEX     3

//#define AAKERNEL_SIZE 6
//#define GZ_AASHIFTX 44 // antialiasing screen offset
//#define GZ_AASHIFTY 45 // antialiasing screen offset
//
// renderer-state default pixel color
//#define GZ_RGB_COLOR            99
//
//#define GZ_INTERPOLATE 95 /* define interpolation mode */
//
//#define GZ_DIRECTIONAL_LIGHT 79 /* directional light */
//#define GZ_AMBIENT_LIGHT  78 /* ambient light type */
//
//#define GZ_AMBIENT_COEFFICIENT  1001 /* Ka material property */
//#define GZ_DIFFUSE_COEFFICIENT  1002 /* Kd material property */
//#define GZ_SPECULAR_COEFFICIENT  1003 /* Ks material property */
//#define GZ_DISTRIBUTION_COEFFICIENT 1004 /* specular power of material */

//#define GZ_TEXTURE_MAP   1010    /* pointer to texture routine */
/*
 * flags fields for value list attributes
 */

/* select interpolation mode of the shader (only one) */
//#define GZ_FLAT  0  /* flat shading with GZ_RBG_COLOR */
//#define GZ_COLOR   1 /* interpolate vertex color */
//#define GZ_NORMALS   2 /* interpolate normals */

/*
typedef int     GzToken;
typedef void    *GzPointer;
typedef float   GzColor[3];
typedef short   GzIntensity;  // 0 - 4095 in lower 12-bits
typedef float   GzCoord[3];
typedef float   GzTextureIndex[2];
typedef float   GzMatrix[4][4];
typedef int GzDepth;
*/

// Redesign complex typedef's as classes and write proper methods
// We need at least GzVector, GzTextureIndex, GzMatrix, GzColor classes
// And we need to make new classes like GzRay, GzGeometry, GzMaterial etc. --Jialiu

//typedef int (*GzTexture)(float u, float v, GzColor color); /* pointer to texture sampling method */
/* u,v parameters [0,1] are defined tex_fun(float u, float v, GzColor color) */

/*
 * Gz camera definition
 */
//#ifndef GZCAMERA
//#define GZCAMERA
//typedef struct  GzCamera
//{
  //GzMatrix     Xiw;    /* xform from world to image space */
  //GzMatrix     Xpi;    /* perspective projection xform */
  //GzCoord      position;   /* position of image plane origin */
  //GzCoord      lookat;         /* position of look-at-point */
  //GzCoord      worldup;  /* world up-vector (almost screen up) */
  //float        FOV;            /* horizontal field of view */
//} GzCamera;
//#endif

//#ifndef GZLIGHT
//#define GZLIGHT
//typedef struct  GzLight
//{
   //GzCoord    direction;  /* vector from surface to light */
   //GzColor    color;  /* light color intensity */
//} GzLight;
//#endif

//#ifndef GZINPUT
//#define GZINPUT
//typedef struct  GzInput
//{
   //GzCoord            rotation;       /* object rotation */
   //GzCoord   translation; /* object translation */
   //GzCoord   scale;   /* object scaling */
   //GzCamera  camera;   /* camera */
//} GzInput;
//#endif

//#define RED     0        /* array indicies for color vector */
//#define GREEN   1
//#define BLUE    2
//const int COLOR_BOUND(3);

//#define X       0        /* array indicies for position vector*/
//#define Y       1
//#define Z       2
//const int W(3);
//const int COORD3_BOUND(3);

//const int VA(0);
//const int VB(1);
//const int VC(2);
//const int VERT_BOUND(3);

//#define U       0        /* array indicies for texture coords */
//#define V       1
//const int TEX_BOUND(2);

#endif
