// AutoPanView.cpp : implementation of the CAutoPanView class
//

#include "stdafx.h"
#include "AutoPan.h"

#include "AutoPanDoc.h"
#include "AutoPanView.h"
#include "mfxWhlPan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoPanView

IMPLEMENT_DYNCREATE(CAutoPanView, CScrollView)

BEGIN_MESSAGE_MAP(CAutoPanView, CScrollView)
	//{{AFX_MSG_MAP(CAutoPanView)
	ON_WM_MBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoPanView construction/destruction

CAutoPanView::CAutoPanView()
{
	// TODO: add construction code here

}

CAutoPanView::~CAutoPanView()
{
}

BOOL CAutoPanView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAutoPanView drawing

void CAutoPanView::OnDraw(CDC* pDC)
{
	CAutoPanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    // Get the invalidated rectangle of the view, or in the case
    // of printing, the clipping region of the printer dc.
    CRect rectClip;
    CRect rectCloud;
    pDC->GetClipBox(&rectClip);
    pDC->LPtoDP(&rectClip);
    rectClip.InflateRect(1, 1); // avoid rounding to nothing
    
    // Note: CScrollView::OnPaint() will have already adjusted the
    // viewport origin before calling OnDraw(), to reflect the
    // currently scrolled position.
	for(int x=0; x<800; x+=50)
	{
		for(int y=0; y<600; y+=50)
		{
			CRect rc(x,y, x+40, y+40);
			pDC->FillSolidRect(rc, RGB(x,y,x*y));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAutoPanView diagnostics

#ifdef _DEBUG
void CAutoPanView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CAutoPanView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CAutoPanDoc* CAutoPanView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAutoPanDoc)));
	return (CAutoPanDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAutoPanView message handlers

void CAutoPanView::OnInitialUpdate() 
{
    SetScrollSizes(MM_TEXT, CSize(800,600));    
	CScrollView::OnInitialUpdate();
}

void CAutoPanView::OnMButtonDown(UINT nFlags, CPoint point) 
{
	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;
	if(!bCtl && nFlags == MK_MBUTTON)
	{
		MfxTrackAutoPan(this);
	}
	else
	{
		CScrollView::OnMButtonDown(nFlags, point);
	}
}
