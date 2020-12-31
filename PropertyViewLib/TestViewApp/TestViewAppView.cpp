// CTestViewAppView.cpp : implementation file
//

#include "stdafx.h"
#include "TestViewApp.h"
#include "TestViewAppDoc.h"
#include "TestViewAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestViewAppView

IMPLEMENT_DYNCREATE(CTestViewAppView, EPropView)

CTestViewAppView::CTestViewAppView()
{
}

CTestViewAppView::~CTestViewAppView()
{
}


BEGIN_MESSAGE_MAP(CTestViewAppView, EPropView)
	//{{AFX_MSG_MAP(CTestViewAppView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestViewAppView drawing

void CTestViewAppView::OnDraw(CDC* pDC)
{
	CTestViewAppDoc* pDoc = GetDoc();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CTestViewAppView diagnostics

#ifdef _DEBUG
void CTestViewAppView::AssertValid() const
{
	EPropView::AssertValid();
}

void CTestViewAppView::Dump(CDumpContext& dc) const
{
	EPropView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestViewAppView message handlers


void CTestViewAppView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if( lHint == HINT_SET_PROPERTY_HOST )
	{
		SetPropertyHost( GetDoc()->m_pCurrentHost );
	}
}

void CTestViewAppView::OnInitialUpdate() 
{
	m_PropCtrl.EnableCommentPane(true);
	m_PropCtrl.SetPropertyHost( GetDoc()->m_pCurrentHost );
}
