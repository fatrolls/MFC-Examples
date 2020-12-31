// TabView.cpp : implementation of the CTabView class
//

#include "stdafx.h"
#include "Tab.h"

#include "TabDoc.h"
#include "TabView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabView

IMPLEMENT_DYNCREATE(CTabView, CListView)

BEGIN_MESSAGE_MAP(CTabView, CListView)
	//{{AFX_MSG_MAP(CTabView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabView construction/destruction

CTabView::CTabView()
{
	// TODO: add construction code here

}

CTabView::~CTabView()
{
}

BOOL CTabView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style|=LVS_REPORT|WS_VISIBLE; 

	TRACE("hscroll=%d, vscroll=%d\n", cs.style & WS_HSCROLL, cs.style & WS_VSCROLL);
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTabView drawing

void CTabView::OnDraw(CDC* pDC)
{
	CTabDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTabView printing

BOOL CTabView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTabView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTabView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTabView diagnostics

#ifdef _DEBUG
void CTabView::AssertValid() const
{
	CListView::AssertValid();
}

void CTabView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CTabDoc* CTabView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTabDoc)));
	return (CTabDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabView message handlers

void CTabView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	GetListCtrl().InsertColumn(0,"aaaaaaaaaa", LVCFMT_LEFT, 200);
	GetListCtrl().InsertColumn(1,"bbbbbbbbbb", LVCFMT_LEFT, 200);
	
	
	for (int i=0; i<10; i++)
	{
		char tmp[100];
		sprintf(tmp, "Item %d", rand());
		GetListCtrl().InsertItem(0,tmp);
	}
}
