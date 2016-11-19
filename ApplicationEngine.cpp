// ApplicationEngine.cpp: implementation of the ApplicationEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RayTracingEngine.h"
#include "ApplicationEngine.h"
#include "gz.h"
//#include "GzDisplay.h"
//#include "GzRender.h"

#include <cstdio>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define INFILE  "rects"
#define OUTFILE "output.ppm"

// Might be useful. But I think we'll have better way.
//extern int tex_fun(float u, float v, GzColor color); // image texture function
//extern int ptex_fun(float u, float v, GzColor color); // procedural texture function

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
    // Tokens need to be redesigned.
    //GzToken		nameListShader[9]; 	    // shader attribute names
    //GzPointer   valueListShader[9];		// shader attribute pointers
    //GzToken     nameListLights[10];		// light info
    //GzPointer   valueListLights[10];
    //int			shaderType, interpStyle;
    //float		specpower;
    int status(GZ_SUCCESS); 

    // m_nWidth and m_nHeight are variables inherited from Application class.
    m_nWidth = 256;		// frame buffer and display width
    m_nHeight = 256;    // frame buffer and display height

    // Initialize frame buffer and display
    status = status || GzNewFrameBuffer(m_pFrameBuffer, m_nWidth, m_nHeight);

    status = status || GzNewDisplay(m_pDisplay, m_nWidth, m_nHeight);

    GzLight lTemp1;
    GzLight lTemp2(1, GzVector3(10.0f, 10.0f, -10));
    GzLight lTemp3(0, GzVector3(10.0f, 10.0f, -10), GzColor::CYAN);
    GzMaterial mTemp1;
    GzMaterial mTemp2(GzColor::RED, GzColor::BLACK, GzColor::WHITE, 15, 0);
    // We'll do AA in renderer directly.
    //
    //**********************
    // Same routine. Set up camera, lights for our renderer
    // in this initialize function, like
    //```
    //renderer.putAttribute(camera);

    //renderer.putAttribute(lights);
    //renderer.putAttribute(AAmethod); //optional
    //renderer.putAttribute(refractionmode); //optional
    //renderer.putAttribute(diffusemode); //optional
    //renderer.putAttribute(arealightmode); //optional
    //```
    // Still need tokens. But might be quite different from original.
    // Pass pointers and boolean values to renderer. And do
    // rendering inside Render() function.
    //************************
    if (status)
    {
        AfxMessageBox(_T("Initiating went wrong!\n"));
    }
    return(status);
}

int ApplicationEngine::Render() 
{
    int status(GZ_SUCCESS); 

    // Initialize Display
    m_pDisplay->init(GzColor(0.4f, 0.8f, 1.0f));

    // Test display
    for (int j = 0; j < m_nHeight/2; ++j)
    {
        for (int i = 0; i < m_nWidth/2; ++i)
        {
            int yj = j + m_nHeight / 4;
            int xi = i + m_nWidth / 4;
            //float ndcx = xi * 2.0f / m_nWidth - 1;
            //float ndcy = -(yj * 2.0f / m_nHeight - 1);
            m_pDisplay->putDisplay(xi, yj, (GzColor::BLUE + GzColor::RED) * 0.25);
        }
    }

    // I/O File open. Temporary
    //
    //FILE *infile;
    //if( (infile  = fopen( INFILE , "r" )) == NULL )
    //{
        //AfxMessageBox( "The input file was not opened\n" );
        //return GZ_FAILURE;
    //}
    //
    FILE *outfile;
    if( (outfile  = std::fopen( OUTFILE , "wb" )) == NULL )
    {
        AfxMessageBox(_T("The output file was not opened\n"));
        return GZ_FAILURE;
    }

    //*******************************
    //constructScene(inFile);
    //renderer.putAttribute(scene);
    //if (renderer.isReady())
    //{
    //  renderer.renderToDisplay();
    //}
    //else
    //{
    //  AfxMessageBox("Rendering went wrong!\n");
    //}
    //*******************************


    //GzFlushDisplay2File(outfile, m_pDisplay); 	/* */
    //GzFlushDisplay2FrameBuffer(m_pFrameBuffer, m_pDisplay);	// write out or update display to frame buffer
    m_pDisplay->flush2File(outfile); //write out or update display to file
    m_pDisplay->flush2FrameBuffer(m_pFrameBuffer); //write out or update display to frame buffer
    // 
    // Close file
    // 

    //if( fclose( infile ) )
        //AfxMessageBox( "The input file was not closed\n" );

    if( fclose( outfile ) )
    {
        AfxMessageBox(_T("The output file was not closed\n"));
    }
    if (status)
    {
        AfxMessageBox(_T("Rendering went wrong!\n"));
    }
    return(status); 
}

void ApplicationEngine::Clean()
{
    // Might need to clean renderer and texture and other objects
    //status |= GzFreeRender(m_pRender); 
    delete m_pDisplay;
    m_pDisplay = nullptr;
    //status |= GzFreeTexture();
}
