#include "stdafx.h"
#include "DDESrv.h"
#include "MainFrm.h"
#include "DDEDoc.h"
#include "DDEView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDDESrvView, CEditView)

BEGIN_MESSAGE_MAP(CDDESrvView, CEditView)
	//{{AFX_MSG_MAP(CDDESrvView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDDESrvView::CDDESrvView()
{
}

CDDESrvView::~CDDESrvView()
{
}

BOOL CDDESrvView::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);
	cs.style |= ES_READONLY;

	return bPreCreated;
}

void CDDESrvView::OnDraw(CDC* pDC)
{
	CDDESrvDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

#ifdef _DEBUG
void CDDESrvView::AssertValid() const
{
	CEditView::AssertValid();
}

void CDDESrvView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CDDESrvDoc* CDDESrvView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDDESrvDoc)));
	return (CDDESrvDoc*)m_pDocument;
}
#endif

void CDDESrvView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	((CMainFrame *)(AfxGetApp()->m_pMainWnd))->InitializeDDE();
}

void CDDESrvView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
}

void CDDESrvView::OnLButtonDown(UINT nFlags, CPoint point) 
{
}

void CDDESrvView::OnLButtonUp(UINT nFlags, CPoint point) 
{
}

void CDDESrvView::OnMouseMove(UINT nFlags, CPoint point) 
{
}
