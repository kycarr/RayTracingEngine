// Application.cpp: implementation of the Application class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RayTracingEngine.h"
#include "Application.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Application::Application()
{
	m_pDisplay = nullptr; // the display
	m_pRender = nullptr; // the renderer
	//m_pUserInput = nullptr;
	m_pFrameBuffer = nullptr;
}

Application::~Application()
{
	delete m_pFrameBuffer;
	//if(m_pUserInput != nullptr)
		//delete m_pUserInput;
}

