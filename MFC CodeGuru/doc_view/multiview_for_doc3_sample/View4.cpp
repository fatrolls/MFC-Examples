// View4.cpp : implementation file
//

#include "stdafx.h"
#include "MvTest.h"
#include "View4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CView4

IMPLEMENT_DYNCREATE(CView4, CView)

CView4::CView4()
{
}

CView4::~CView4()
{
}


BEGIN_MESSAGE_MAP(CView4, CView)
	//{{AFX_MSG_MAP(CView4)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CView4 drawing

void CView4::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here

    CString DocName = "This is document: " + pDoc->GetTitle();
	
	CRect rcItem;
    GetClientRect( &rcItem );

    pDC->SetTextColor( RGB( 255, 255, 255 ) );
    pDC->SetBkColor( RGB( 0, 0, 0 ) );
	pDC->FillRect( rcItem, &CBrush( RGB( 0, 0, 0 ) ) );

	pDC->DrawText( DocName, -1, rcItem, DT_CENTER | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP 
				| DT_VCENTER | DT_END_ELLIPSIS );

}

/////////////////////////////////////////////////////////////////////////////
// CView4 diagnostics

#ifdef _DEBUG
void CView4::AssertValid() const
{
	CView::AssertValid();
}

void CView4::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CView4 message handlers

BOOL CView4::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
    return TRUE;	
	return CView::OnEraseBkgnd(pDC);
}
