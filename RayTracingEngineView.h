
// RayTracingEngineView.h : interface of the CRayTracingEngineView class
//

#pragma once

#include "Application.h"

class CRayTracingEngineView : public CView
{
protected: // create from serialization only
    CRayTracingEngineView();
    DECLARE_DYNCREATE(CRayTracingEngineView)

    // Attributes
public:
    CRayTracingEngineDoc* GetDocument() const;
    Application* m_pApplication;
    // Operations
public:
    void DrawFrameBuffer(CDC *pDC);
    // Overrides
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnInitialUpdate();
protected:

    // Implementation
public:
    virtual ~CRayTracingEngineView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    afx_msg void OnRender();
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RayTracingEngineView.cpp
inline CRayTracingEngineDoc* CRayTracingEngineView::GetDocument() const
{
    return reinterpret_cast<CRayTracingEngineDoc*>(m_pDocument);
}
#endif

