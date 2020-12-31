// ex05bView.cpp : implementation of the CEx05bView class
//

#include "stdafx.h"
#include "ex05b.h"

#include "ex05bDoc.h"
#include "ex05bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx05bView

IMPLEMENT_DYNCREATE(CEx05bView, CView)

BEGIN_MESSAGE_MAP(CEx05bView, CView)
	//{{AFX_MSG_MAP(CEx05bView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx05bView construction/destruction

CEx05bView::CEx05bView()
{
	// TODO: add construction code here

}

CEx05bView::~CEx05bView()
{
}

BOOL CEx05bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx05bView drawing

void CEx05bView::OnDraw(CDC* pDC)
{
	CFont fontTest1, fontTest2, fontTest3, fontTest4;

	fontTest1.CreateFont(50, 0, 0, 0, 400, FALSE, FALSE, 0,
	                     ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                     CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                     DEFAULT_PITCH | FF_SWISS, "Arial");
	CFont* pOldFont = pDC->SelectObject(&fontTest1);
	TraceMetrics(pDC);
	pDC->TextOut(0, 0, "This is Arial, default width");

	fontTest2.CreateFont(50, 0, 0, 0, 400, FALSE, FALSE, 0,
	                     ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                     CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                     DEFAULT_PITCH | FF_MODERN, "Courier"); // not TrueType
	pDC->SelectObject(&fontTest2);
	TraceMetrics(pDC);
	pDC->TextOut(0, 100, "This is Courier, default width");

	fontTest3.CreateFont(50, 10, 0, 0, 400, FALSE, FALSE, 0,
	                     ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                     CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                     DEFAULT_PITCH | FF_ROMAN, NULL);
	pDC->SelectObject(&fontTest3);
	TraceMetrics(pDC);
	pDC->TextOut(0, 200, "This is generic Roman, variable width");

	fontTest4.CreateFont(50, 0, 0, 0, 400, FALSE, FALSE, 0,
	                     ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                     CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                     DEFAULT_PITCH | FF_MODERN, "LinePrinter");
	pDC->SelectObject(&fontTest4);
	TraceMetrics(pDC);
	pDC->TextOut(0, 300, "This is LinePrinter, default width");
	pDC->SelectObject(pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
// CEx05bView diagnostics

#ifdef _DEBUG
void CEx05bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx05bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx05bDoc* CEx05bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx05bDoc)));
	return (CEx05bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx05bView message handlers

void CEx05bView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	CRect clientRect;

	GetClientRect(clientRect);
	pDC->SetMapMode(MM_ANISOTROPIC); // +y = down
	pDC->SetWindowExt(400,450);
	pDC->SetViewportExt(clientRect.right, clientRect.bottom);
	pDC->SetViewportOrg(0, 0);
}

void CEx05bView::TraceMetrics(CDC* pDC)
{
	TEXTMETRIC tm;
	char       szFaceName[100];

	pDC->GetTextMetrics(&tm);
	pDC->GetTextFace(99, szFaceName);
	TRACE("font = %s, tmHeight = %d, tmInternalLeading = %d,"
	      " tmExternalLeading = %d\n", szFaceName, tm.tmHeight,
	      tm.tmInternalLeading, tm.tmExternalLeading);
}
