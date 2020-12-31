// ex05aView.cpp : implementation of the CEx05aView class
//

#include "stdafx.h"
#include "ex05a.h"

#include "ex05aDoc.h"
#include "ex05aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx05aView

IMPLEMENT_DYNCREATE(CEx05aView, CView)

BEGIN_MESSAGE_MAP(CEx05aView, CView)
	//{{AFX_MSG_MAP(CEx05aView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx05aView construction/destruction

CEx05aView::CEx05aView()
{
	// TODO: add construction code here

}

CEx05aView::~CEx05aView()
{
}

BOOL CEx05aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx05aView drawing

void CEx05aView::OnDraw(CDC* pDC)
{
	int nPosition = 0;

	for (int i = 6; i <= 24; i += 2) {
		ShowFont(pDC, nPosition, i);
	}
	TRACE("LOGPIXELSX = %d, LOGPIXELSY = %d\n",
	      pDC->GetDeviceCaps(LOGPIXELSX),
	      pDC->GetDeviceCaps(LOGPIXELSY));
	TRACE("HORZSIZE = %d, VERTSIZE = %d\n",
	      pDC->GetDeviceCaps(HORZSIZE),
	      pDC->GetDeviceCaps(VERTSIZE));
	TRACE("HORZRES = %d, VERTRES = %d\n",
	      pDC->GetDeviceCaps(HORZRES),
	      pDC->GetDeviceCaps(VERTRES));
}

/////////////////////////////////////////////////////////////////////////////
// CEx05aView diagnostics

#ifdef _DEBUG
void CEx05aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx05aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx05aDoc* CEx05aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx05aDoc)));
	return (CEx05aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx05aView message handlers

void CEx05aView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(1440, 1440);
	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),
	                   -pDC->GetDeviceCaps(LOGPIXELSY));
}

void CEx05aView::ShowFont(CDC* pDC, int& nPos, int nPoints)
{
	TEXTMETRIC tm;
	CFont      fontText;
	CString    strText;
	CSize      sizeText;

	fontText.CreateFont(-nPoints * 20, 0, 0, 0, 400, FALSE, FALSE, 0,
	                    ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                    DEFAULT_PITCH | FF_SWISS, "Arial");
	CFont* pOldFont = (CFont*) pDC->SelectObject(&fontText);
	pDC->GetTextMetrics(&tm);
	TRACE("points = %d, tmHeight = %d, tmInternalLeading = %d,"
	      " tmExternalLeading = %d\n", nPoints, tm.tmHeight,
	      tm.tmInternalLeading, tm.tmExternalLeading);
	strText.Format("This is %d-point Arial", nPoints);
	sizeText = pDC->GetTextExtent(strText);
	TRACE("string width = %d, string height = %d\n", sizeText.cx,
	      sizeText.cy);
	pDC->TextOut(0, nPos, strText);
	pDC->SelectObject(pOldFont);
	nPos -= tm.tmHeight + tm.tmExternalLeading;
}
