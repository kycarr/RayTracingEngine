// ApplicationEngine.cpp: implementation of the ApplicationEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RayTracingEngine.h"
#include "ApplicationEngine.h"
#include "gz.h"
#include "GzDisplay.h"
//#include "rend.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define INFILE  "rects"
#define OUTFILE "output.ppm"


//extern int tex_fun(float u, float v, GzColor color); /* image texture function */
//extern int ptex_fun(float u, float v, GzColor color); /* procedural texture function */

//void shade(GzCoord norm, GzCoord color);
//float AAFilter[AAKERNEL_SIZE][3] /* X-shift, Y-shift, weight */
//{
    //-0.52, 0.38, 0.128,         0.41, 0.56, 0.119,      0.27, 0.08, 0.294,
        //-0.17, -0.29, 0.249,        0.58, -0.55, 0.104,     -0.31, -0.71, 0.106
//};
//GzDisplay *AAdisplays_list[AAKERNEL_SIZE];
//GzRender *AArenders_list[AAKERNEL_SIZE];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ApplicationEngine::ApplicationEngine()
{

}

ApplicationEngine::~ApplicationEngine()
{
    Clean();
}

int ApplicationEngine::Initialize()
{
    //GzCamera	camera;  
    //int		    xRes, yRes;	/* display parameters */ 


    //GzToken		nameListShader[9]; 	    /* shader attribute names */
    //GzPointer   valueListShader[9];		/* shader attribute pointers */
    //GzToken     nameListLights[10];		/* light info */
    //GzPointer   valueListLights[10];
    //int			shaderType, interpStyle;
    //float		specpower;
    int status(GZ_SUCCESS); 

    /* 
     * Allocate memory for user input
     */
    //m_pUserInput = new GzInput;

    /* 
     * initialize the display and the renderer 
     */ 
    m_nWidth = 256;		// frame buffer and display width
    m_nHeight = 256;    // frame buffer and display height

    //Only need one framebuffer, but AAKERNEL_SIZE displays and renderers
    status = status || GzNewFrameBuffer(m_pFrameBuffer, m_nWidth, m_nHeight);

    status = status || GzNewDisplay(m_pDisplay, m_nWidth, m_nHeight);

    //for (int i = 0; i < AAKERNEL_SIZE; ++i)
    //{
        //status |= GzNewDisplay(AAdisplays_list + i, m_nWidth, m_nHeight);
        //status |= GzGetDisplayParams(m_pDisplay, &xRes, &yRes); 
        //status |= GzGetDisplayParams(AAdisplays_list[i], &xRes, &yRes);
        //status |= GzNewRender(&m_pRender, m_pDisplay);
        //status |= GzNewRender(AArenders_list + i, AAdisplays_list[i]);
    //}

    /* Translation matrix */
    /*
    GzMatrix	scale =
    {
        3.25,	0.0,	0.0,	0.0,
        0.0,	3.25,	0.0,	-3.25,
        0.0,	0.0,	3.25,	3.5,
        0.0,	0.0,	0.0,	1.0
    };

    GzMatrix	rotateX =
    {
        1.0,	0.0,	0.0,	0.0,
        0.0,	.7071,	.7071,	0.0,
        0.0,	-.7071,	.7071,	0.0,
        0.0,	0.0,	0.0,	1.0
    };

    GzMatrix	rotateY =
    {
        .866,	0.0,	-0.5,	0.0,
        0.0,	1.0,	0.0,	0.0,
        0.5,	0.0,	.866,	0.0,
        0.0,	0.0,	0.0,	1.0
    };
    */

//#if 1 	/* set up app-defined camera if desired, else use camera defaults */
    /*
    camera.position[X] = -3;
    camera.position[Y] = -25;
    camera.position[Z] = -4;

    camera.lookat[X] = 7.8;
    camera.lookat[Y] = 0.7;
    camera.lookat[Z] = 6.5;

    camera.worldup[X] = -0.2;
    camera.worldup[Y] = 1.0;
    camera.worldup[Z] = 0.0;

    camera.FOV = 63.7;              // degrees
    */

    //status |= GzPutCamera(m_pRender, &camera);
    //for (int i = 0; i < AAKERNEL_SIZE; ++i)
    //{
        //status |= GzPutCamera(AArenders_list[i], &camera);
    //}
//#endif 

    /* Start Renderer */
    //status |= GzBeginRender(m_pRender);
    //for (int i = 0; i < AAKERNEL_SIZE; ++i)
    //{
        //status |= GzBeginRender(AArenders_list[i]);
    //}

    /* Light */
    //GzLight	light1 = { {-0.7071, 0.7071, 0}, {0.5, 0.5, 0.9} };
    //GzLight	light2 = { {0, -0.7071, -0.7071}, {0.9, 0.2, 0.3} };
    //GzLight	light3 = { {0.7071, 0.0, -0.7071}, {0.2, 0.7, 0.3} };
    //GzLight	ambientlight = { {0, 0, 0}, {0.3, 0.3, 0.3} };

    /* Material property */
    //GzColor specularCoefficient = { 0.3, 0.3, 0.3 };
    //GzColor ambientCoefficient = { 0.1, 0.1, 0.1 };
    //GzColor diffuseCoefficient = { 0.7, 0.7, 0.7 };

    /*
       renderer is ready for frame --- define lights and shader at start of frame
       */

    /*
     * Tokens associated with light parameters
     */
    //nameListLights[0] = GZ_DIRECTIONAL_LIGHT;
    //valueListLights[0] = (GzPointer)&light1;
    //nameListLights[1] = GZ_DIRECTIONAL_LIGHT;
    //valueListLights[1] = (GzPointer)&light2;
    //nameListLights[2] = GZ_DIRECTIONAL_LIGHT;
    //valueListLights[2] = (GzPointer)&light3;
    //status |= GzPutAttribute(m_pRender, 3, nameListLights, valueListLights);
    //for (int i = 0; i < AAKERNEL_SIZE; ++i)
    //{
        //status |= GzPutAttribute(AArenders_list[i], 3, nameListLights, valueListLights);
    //}

    //nameListLights[0] = GZ_AMBIENT_LIGHT;
    //valueListLights[0] = (GzPointer)&ambientlight;
    //status |= GzPutAttribute(m_pRender, 1, nameListLights, valueListLights);
    //for (int i = 0; i < AAKERNEL_SIZE; ++i)
    //{
        //status |= GzPutAttribute(AArenders_list[i], 1, nameListLights, valueListLights);
    //}

    /*
     * Tokens associated with shading
     */
    //nameListShader[0] = GZ_DIFFUSE_COEFFICIENT;
    //valueListShader[0] = (GzPointer)diffuseCoefficient;

    /*
     * Select either GZ_COLOR or GZ_NORMALS as interpolation mode
     */
    //nameListShader[1] = GZ_INTERPOLATE;
    //interpStyle = GZ_NORMALS;         /* Phong shading */
    //valueListShader[1] = (GzPointer)&interpStyle;

    //nameListShader[2] = GZ_AMBIENT_COEFFICIENT;
    //valueListShader[2] = (GzPointer)ambientCoefficient;
    //nameListShader[3] = GZ_SPECULAR_COEFFICIENT;
    //valueListShader[3] = (GzPointer)specularCoefficient;
    //nameListShader[4] = GZ_DISTRIBUTION_COEFFICIENT;
    //specpower = 32;
    //valueListShader[4] = (GzPointer)&specpower;

    //nameListShader[5] = GZ_TEXTURE_MAP;
//#if 0   /* set up null texture function or valid pointer */
    //valueListShader[5] = (GzPointer)0;
//#else
    //valueListShader[5] = (GzPointer)(tex_fun);	/* or use ptex_fun */
//#endif
    //status |= GzPutAttribute(m_pRender, 6, nameListShader, valueListShader);

    //status |= GzPushMatrix(m_pRender, scale);
    //status |= GzPushMatrix(m_pRender, rotateY);
    //status |= GzPushMatrix(m_pRender, rotateX);
    //for (int i = 0; i < AAKERNEL_SIZE; ++i)
    //{
        //nameListShader[6] = GZ_AASHIFTX;
        //valueListShader[6] = (GzPointer) &(AAFilter[i][X]);
        //nameListShader[7] = GZ_AASHIFTY;
        //valueListShader[7] = (GzPointer) &(AAFilter[i][Y]);
        //status |= GzPutAttribute(AArenders_list[i], 8, nameListShader, valueListShader);
        //status |= GzPushMatrix(AArenders_list[i], scale);
        //status |= GzPushMatrix(AArenders_list[i], rotateY);
        //status |= GzPushMatrix(AArenders_list[i], rotateX);
    //}

    if (status)
    {
        AfxMessageBox("Initiating went wrong!\n");
    }
    return(status);
}

int ApplicationEngine::Render() 
{
    //GzToken		nameListTriangle[3]; 	/* vertex attribute names */
    //GzPointer	valueListTriangle[3]; 	/* vertex attribute pointers */
    //GzCoord		vertexList[3];	/* vertex position coordinates */ 
    //GzCoord		normalList[3];	/* vertex normals */ 
    //GzTextureIndex  	uvList[3];		/* vertex texture map indices */ 
    //char		dummy[256]; 
    int status(GZ_SUCCESS); 


    // Initialize Display
    m_pDisplay->init(GzColor(0.4f, 0.8f, 1.0f));
    //status |= GzInitDisplay(m_pDisplay); 
    //for (int i = 0; i < AAKERNEL_SIZE; ++i)
    //{
        //status |= GzInitDisplay(AAdisplays_list[i]); 
    //}

    /* 
     * Tokens associated with triangle vertex values 
     */ 
    //nameListTriangle[0] = GZ_POSITION; 
    //nameListTriangle[1] = GZ_NORMAL; 
    //nameListTriangle[2] = GZ_TEXTURE_INDEX;  

    // I/O File open
    /*
    FILE *infile;
    if( (infile  = fopen( INFILE , "r" )) == NULL )
    {
        AfxMessageBox( "The input file was not opened\n" );
        return GZ_FAILURE;
    }
    */
    FILE *outfile;
    if( (outfile  = fopen( OUTFILE , "wb" )) == NULL )
    {
        AfxMessageBox( "The output file was not opened\n" );
        return GZ_FAILURE;
    }
    /*
    int	ulx, uly, lrx, lry, r, g, b;
    while( fscanf(infile, "%d %d %d %d %d %d %d", &ulx, &uly, &lrx, &lry, &r, &g, &b) == 7) { 
        for (int j = uly; j <= lry; j++) {
            for (int i = ulx; i <= lrx; i++) {
                status |= GzPutDisplay(m_pDisplay, i, j, r, g, b, 1, 0);
            }
        }
    }*/

    /* 
     * Walk through the list of triangles, set color 
     * and render each triangle 
     */ 
    //while( fscanf(infile, "%s", dummy) == 1) { 	/* read in tri word */
        //fscanf(infile, "%f %f %f %f %f %f %f %f", 
                //&(vertexList[0][0]), &(vertexList[0][1]),  
                //&(vertexList[0][2]), 
                //&(normalList[0][0]), &(normalList[0][1]), 	
                //&(normalList[0][2]), 
                //&(uvList[0][0]), &(uvList[0][1]) ); 
        //fscanf(infile, "%f %f %f %f %f %f %f %f", 
                //&(vertexList[1][0]), &(vertexList[1][1]), 	
                //&(vertexList[1][2]), 
                //&(normalList[1][0]), &(normalList[1][1]), 	
                //&(normalList[1][2]), 
                //&(uvList[1][0]), &(uvList[1][1]) ); 
        //fscanf(infile, "%f %f %f %f %f %f %f %f", 
                //&(vertexList[2][0]), &(vertexList[2][1]), 	
                //&(vertexList[2][2]), 
                //&(normalList[2][0]), &(normalList[2][1]), 	
                //&(normalList[2][2]), 
                //&(uvList[2][0]), &(uvList[2][1]) ); 

        /* 
         * Set the value pointers to the first vertex of the 	
         * triangle, then feed it to the renderer 
         * NOTE: this sequence matches the nameList token sequence
         */ 
        //valueListTriangle[0] = (GzPointer)vertexList; 
        //valueListTriangle[1] = (GzPointer)normalList; 
        //valueListTriangle[2] = (GzPointer)uvList; 
        //GzPutTriangle(m_pRender, 3, nameListTriangle, valueListTriangle); 
        //for (int i = 0; i < AAKERNEL_SIZE; ++i)
        //{
            //status |= GzPutTriangle(AArenders_list[i], 3, nameListTriangle, valueListTriangle); 
        //}
    //} 

    //for (int yj = 0; yj < m_nHeight; ++yj)
    //{
        //for (int xi = 0; xi < m_nWidth; ++xi)
        //{
            //GzIntensity r = 0, g = 0, b = 0, a = 0;
            //for (int i = 0; i < AAKERNEL_SIZE; ++i)
            //{
                //GzIntensity pR, pG, pB, pA;
                //GzDepth pZTemp;
                //GzGetDisplay(AAdisplays_list[i], xi, yj, &pR, &pG, &pB, &pA, &pZTemp);
                //r += (int) (pR * AAFilter[i][2]);
                //g += (int) (pG * AAFilter[i][2]);
                //b += (int) (pB * AAFilter[i][2]);
                //a += (int) (pA * AAFilter[i][2]);
            //}
            //GzPutDisplay(m_pDisplay, xi, yj, r, g, b, a, INT_MAX);
        //}
    //}

    //GzFlushDisplay2File(outfile, m_pDisplay); 	/* write out or update display to file*/
    //GzFlushDisplay2FrameBuffer(m_pFrameBuffer, m_pDisplay);	// write out or update display to frame buffer
    m_pDisplay->flush2File(outfile);
    m_pDisplay->flush2FrameBuffer(m_pFrameBuffer);
    /* 
     * Close file
     */ 

    //if( fclose( infile ) )
        //AfxMessageBox( "The input file was not closed\n" );

    //if( fclose( outfile ) )
        //AfxMessageBox( "The output file was not closed\n" );
    if (status)
    {
        AfxMessageBox("Rendering went wrong!\n");
    }
    return(status); 
}

int ApplicationEngine::Clean()
{
    /* 
     * Clean up and exit 
     */ 
    int	status(GZ_SUCCESS); 

    //for (int i = 0; i < AAKERNEL_SIZE; ++i)
    //{
        //status |= GzFreeRender(AArenders_list[i]); 
        //status |= GzFreeDisplay(AAdisplays_list[i]);
    //}
    //status |= GzFreeRender(m_pRender); 
    //status |= GzFreeDisplay(m_pDisplay);
    delete m_pDisplay;
    m_pDisplay = nullptr;
    //status |= GzFreeTexture();

    return(status);
}
