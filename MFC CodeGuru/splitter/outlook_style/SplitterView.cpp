// SplitterView.cpp : implementation file
//

#include "stdafx.h"
#include "outlookstyle.h"
#include "SplitterView.h"

#include "ListCtrlView.h"
#include "EditCtrlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitterView

IMPLEMENT_DYNCREATE(CSplitterView, CView)

CSplitterView::CSplitterView()
{
}

CSplitterView::~CSplitterView()
{
}


BEGIN_MESSAGE_MAP(CSplitterView, CView)
	//{{AFX_MSG_MAP(CSplitterView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitterView drawing

void CSplitterView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CSplitterView diagnostics

#ifdef _DEBUG
void CSplitterView::AssertValid() const
{
	CView::AssertValid();
}

void CSplitterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplitterView message handlers

int CSplitterView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_wndSplitter.CreateStatic(this, 2, 1);

	CCreateContext *pContext = (CCreateContext*) lpCreateStruct->lpCreateParams;

	m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CListCtrlView), CSize(150,0), pContext);
	m_wndSplitter.CreateView(1,0,RUNTIME_CLASS(CEditCtrlView), CSize(0,0), pContext);
	
	return 0;
}

void CSplitterView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_wndSplitter.MoveWindow(-2,-2,cx+4,cy+4);
	m_wndSplitter.SetRowInfo(0, cy-(cy/4), 0);
	m_wndSplitter.SetRowInfo(1, cy/4, 20);
	m_wndSplitter.RecalcLayout();
}
