
// RayTracingEngine.h : main header file for the RayTracingEngine application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRayTracingEngineApp:
// See RayTracingEngine.cpp for the implementation of this class
//

class CRayTracingEngineApp : public CWinApp
{
public:
    CRayTracingEngineApp();


    // Overrides
public:
    virtual BOOL InitInstance();

    // Implementation
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
};

extern CRayTracingEngineApp theApp;
