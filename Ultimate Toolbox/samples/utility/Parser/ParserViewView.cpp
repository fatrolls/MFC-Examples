// ParserViewView.cpp : implementation of the CParserViewView class
//

#include "stdafx.h"
#include "ParserView.h"

#include "ParserViewDoc.h"
#include "ParseEditView.h"
#include "ParserViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParserViewView

IMPLEMENT_DYNCREATE(CParserViewView, CView)

BEGIN_MESSAGE_MAP(CParserViewView, CView)
	//{{AFX_MSG_MAP(CParserViewView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParserViewView construction/destruction

CParserViewView::CParserViewView()
{
	// TODO: add construction code here

}

CParserViewView::~CParserViewView()
{
}

BOOL CParserViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CParserViewView drawing

void CParserViewView::OnDraw(CDC* /*pDC*/)
{
	CParserViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CParserViewView diagnostics

#ifdef _DEBUG
void CParserViewView::AssertValid() const
{
	CView::AssertValid();
}

void CParserViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CParserViewDoc* CParserViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CParserViewDoc)));
	return (CParserViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CParserViewView message handlers

int CParserViewView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 2, 1))
		return -1;

  // The context information is passed on from the framework
  CCreateContext *pContext = (CCreateContext*)lpCreateStruct->lpCreateParams;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CParseEditView), CSize(100, 100), pContext) ||
		!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CListView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return -1;
	}

    GetListCtrl()->ModifyStyle(0, LVS_REPORT);

	return 0;
}

void CParserViewView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
    CSize Margin(GetSystemMetrics(SM_CXBORDER), GetSystemMetrics(SM_CYBORDER));
    m_wndSplitter.MoveWindow(-Margin.cx,-Margin.cy, cx+2*Margin.cx, cy+2*Margin.cy);	
}
