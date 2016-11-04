
// RayTracingEngineView.cpp : implementation of the CRayTracingEngineView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RayTracingEngine.h"
#endif

#include "RayTracingEngineDoc.h"
#include "RayTracingEngineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRayTracingEngineView

IMPLEMENT_DYNCREATE(CRayTracingEngineView, CView)

BEGIN_MESSAGE_MAP(CRayTracingEngineView, CView)
END_MESSAGE_MAP()

// CRayTracingEngineView construction/destruction

CRayTracingEngineView::CRayTracingEngineView()
{
	// TODO: add construction code here

}

CRayTracingEngineView::~CRayTracingEngineView()
{
}

BOOL CRayTracingEngineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRayTracingEngineView drawing

void CRayTracingEngineView::OnDraw(CDC* /*pDC*/)
{
	CRayTracingEngineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CRayTracingEngineView diagnostics

#ifdef _DEBUG
void CRayTracingEngineView::AssertValid() const
{
	CView::AssertValid();
}

void CRayTracingEngineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRayTracingEngineDoc* CRayTracingEngineView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRayTracingEngineDoc)));
	return (CRayTracingEngineDoc*)m_pDocument;
}
#endif //_DEBUG


// CRayTracingEngineView message handlers
