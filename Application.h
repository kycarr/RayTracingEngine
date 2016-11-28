// Application.h: interface for the Application class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "gz.h"
#include "GzDisplay.h"
//#include "rend.h"

class Application  
{
public:
	Application();
	virtual ~Application();
	
public:
	GzDisplay* m_pDisplay; // the display
	GzRender* m_pRender; // the renderer
	//GzInput*   m_pUserInput;
	char* m_pFrameBuffer; // Frame Buffer
	int   m_nWidth; // width of Frame Buffer
	int   m_nHeight; // height of Frame Buffer

	virtual int Render()=0; // Pass user input data and call renderer
};
