// View3.cpp : implementation file
//

#include "stdafx.h"
#include "MvTest.h"
#include "View3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CView3

IMPLEMENT_DYNCREATE(CView3, CView)

CView3::CView3()
{
}

CView3::~CView3()
{
}


BEGIN_MESSAGE_MAP(CView3, CView)
	//{{AFX_MSG_MAP(CView3)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CView3 drawing

void CView3::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here

    CString DocName = "This is document: " + pDoc->GetTitle();
	
	CRect rcItem;
    GetClientRect( &rcItem );

    pDC->SetTextColor( RGB( 0, 0, 255 ) );
    pDC->SetBkColor( RGB( 0, 0, 0 ) );
	pDC->FillRect( rcItem, &CBrush( RGB( 0, 0, 0 ) ) );

	pDC->DrawText( DocName, -1, rcItem, DT_CENTER | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP 
				| DT_VCENTER | DT_END_ELLIPSIS );

}

/////////////////////////////////////////////////////////////////////////////
// CView3 diagnostics

#ifdef _DEBUG
void CView3::AssertValid() const
{
	CView::AssertValid();
}

void CView3::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CView3 message handlers

BOOL CView3::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
    return TRUE;	
	return CView::OnEraseBkgnd(pDC);
}
