// mymenuView.cpp : implementation of the CMymenuView class
//

#include "stdafx.h"
#include "mymenu.h"
#include "MainFrm.h"
#include "mymenuDoc.h"
#include "mymenuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMymenuView

IMPLEMENT_DYNCREATE(CMymenuView, CView)

BEGIN_MESSAGE_MAP(CMymenuView, CView)
	//{{AFX_MSG_MAP(CMymenuView)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMymenuView construction/destruction

CMymenuView::CMymenuView()
{
}

CMymenuView::~CMymenuView()
{
}

BOOL CMymenuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMymenuView drawing

void CMymenuView::OnDraw(CDC* pDC)
{
	CMymenuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMymenuView printing

BOOL CMymenuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMymenuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMymenuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMymenuView diagnostics

#ifdef _DEBUG
void CMymenuView::AssertValid() const
{
	CView::AssertValid();
}

void CMymenuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMymenuDoc* CMymenuView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMymenuDoc)));
	return (CMymenuDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMymenuView message handlers

void CMymenuView::OnRButtonDown(UINT nFlags, CPoint point) 
{
  BCMenu popmenu;
  popmenu.LoadCheckmarkBitmap(IDB_CHECKU,IDB_CHECKS);
  popmenu.LoadMenu(IDR_RIGHT_CLICK);
  popmenu.ModifyODMenu(NULL,ID_EDIT_CUT,IDR_MAINFRAME);
  popmenu.ModifyODMenu(NULL,ID_EDIT_COPY,IDR_MAINFRAME);
  popmenu.ModifyODMenu(NULL,ID_EDIT_PASTE,IDR_MAINFRAME);
  popmenu.ModifyODMenu(NULL,ID_ZOOM,IDB_ZOOM);
  ClientToScreen(&point);
  BCMenu *psub = (BCMenu *)popmenu.GetSubMenu(0);
  psub->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
}
