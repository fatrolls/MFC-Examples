// View1.cpp : implementation file
//

#include "stdafx.h"
#include "MvTest.h"
#include "View1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CView1

IMPLEMENT_DYNCREATE(CView1, CView)

CView1::CView1()
{
}

CView1::~CView1()
{
}


BEGIN_MESSAGE_MAP(CView1, CView)
	//{{AFX_MSG_MAP(CView1)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CView1 drawing

void CView1::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here

    CString DocName = "This is document: " + pDoc->GetTitle();
	
	CRect rcItem;
    GetClientRect( &rcItem );

    pDC->SetTextColor( RGB( 255, 0, 0 ) );
    pDC->SetBkColor( RGB( 0, 0, 0 ) );
	pDC->FillRect( rcItem, &CBrush( RGB( 0, 0, 0 ) ) );

	pDC->DrawText( DocName, -1, rcItem, DT_CENTER | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP 
				| DT_VCENTER | DT_END_ELLIPSIS );

}

/////////////////////////////////////////////////////////////////////////////
// CView1 diagnostics

#ifdef _DEBUG
void CView1::AssertValid() const
{
	CView::AssertValid();
}

void CView1::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CView1 message handlers

BOOL CView1::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
    return TRUE;	
	return CView::OnEraseBkgnd(pDC);
}
