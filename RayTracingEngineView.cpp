
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
#include "ApplicationEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRayTracingEngineView

IMPLEMENT_DYNCREATE(CRayTracingEngineView, CView)

BEGIN_MESSAGE_MAP(CRayTracingEngineView, CView)
    ON_COMMAND(ID_RENDER, &CRayTracingEngineView::OnRender)
END_MESSAGE_MAP()

// CRayTracingEngineView construction/destruction

CRayTracingEngineView::CRayTracingEngineView()
{
    // TODO: add construction code here
    m_pApplication = nullptr;
}

CRayTracingEngineView::~CRayTracingEngineView()
{
    delete m_pApplication;
}

BOOL CRayTracingEngineView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

// CRayTracingEngineView drawing

void CRayTracingEngineView::OnDraw(CDC* pDC)
{
    CRayTracingEngineDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: add draw code for native data here
    if (m_pApplication != nullptr)
        DrawFrameBuffer(pDC);
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

void CRayTracingEngineView::DrawFrameBuffer(CDC *pDC)
{
    if (m_pApplication->m_pFrameBuffer == nullptr)
    {
        return;
    }

    HDC hdc;
    hdc = ::CreateCompatibleDC(pDC->m_hDC);
    HBITMAP m_bitmap;

    // Display the current image
    char buffer[sizeof(BITMAPINFO)];
    BITMAPINFO* binfo = (BITMAPINFO*)buffer;
    memset(binfo, 0, sizeof(BITMAPINFOHEADER));
    binfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

    // Create the bitmap
    BITMAPINFOHEADER* bih = &binfo->bmiHeader;
    bih->biBitCount = 3 * 8;
    bih->biWidth = m_pApplication->m_nWidth;
    bih->biHeight = m_pApplication->m_nHeight;
    bih->biPlanes = 1;
    bih->biCompression = BI_RGB;
    bih->biSizeImage = 0;

    m_bitmap = CreateDIBSection(hdc, binfo, 0, 0, 0, DIB_RGB_COLORS);

    int colors = DIB_RGB_COLORS;

    ::SelectObject(hdc, m_bitmap);
    binfo->bmiHeader.biBitCount = 0;
    GetDIBits(hdc, m_bitmap, 0, 0, 0, binfo, colors);
    binfo->bmiHeader.biBitCount = 24;
    binfo->bmiHeader.biHeight = -abs(binfo->bmiHeader.biHeight);
    SetDIBits(hdc, m_bitmap, 0, m_pApplication->m_nHeight, m_pApplication->m_pFrameBuffer, binfo, colors);

    ::SetStretchBltMode(pDC->m_hDC, COLORONCOLOR);
    CRect client;
    GetClientRect(&client);
    ::BitBlt(pDC->m_hDC, 0, 0, m_pApplication->m_nWidth, m_pApplication->m_nHeight,
        hdc, 0, 0, SRCCOPY);
    ::DeleteDC(hdc);
    DeleteObject(m_bitmap);
}

void CRayTracingEngineView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO: Add your specialized code here and/or call the base class

    // Assign Application 5
    if (m_pApplication == nullptr)
    {
        m_pApplication = new ApplicationEngine;
    }

    // Initialize and begin renderer
    ((ApplicationEngine *)m_pApplication)->Initialize();
}
/*
void CRayTracingEngineView::OnRender()
{
    // TODO: Add your command handler code here
    if (m_pApplication != nullptr)
        ((ApplicationEngine *)m_pApplication)->Render();
    else
        AfxMessageBox("Application was not allocated\n");

    // Set window size
    CRect clientRect, windowRect;
    int x_offset, y_offset;

    GetClientRect(&clientRect);
    AfxGetMainWnd()->GetWindowRect(&windowRect);

    x_offset = windowRect.Width() - clientRect.Width();
    y_offset = windowRect.Height() - clientRect.Height();

    AfxGetMainWnd()->SetWindowPos(NULL, 0, 0, x_offset + m_pApplication->m_nWidth, y_offset + m_pApplication->m_nHeight, NULL);

    Invalidate(true);
}
*/


void CRayTracingEngineView::OnRender()
{
    // TODO: Add your command handler code here
    if (m_pApplication != nullptr)
        ((ApplicationEngine *)m_pApplication)->Render();
    else
        AfxMessageBox(_T("Application was not allocated\n"));

    // Set window size
    CRect clientRect, windowRect;
    int x_offset, y_offset;

    GetClientRect(&clientRect);
    AfxGetMainWnd()->GetWindowRect(&windowRect);

    x_offset = windowRect.Width() - clientRect.Width();
    y_offset = windowRect.Height() - clientRect.Height();

    AfxGetMainWnd()->SetWindowPos(NULL, 0, 0, x_offset + m_pApplication->m_nWidth, y_offset + m_pApplication->m_nHeight, NULL);

    Invalidate(true);
}
