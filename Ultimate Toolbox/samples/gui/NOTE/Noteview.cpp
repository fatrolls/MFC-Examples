// noteView.cpp : implementation of the CNoteView class
//

#include "stdafx.h"
#include "note.h"

#include "noteDoc.h"
#include "noteView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoteView

IMPLEMENT_DYNCREATE(CNoteView, CView)

BEGIN_MESSAGE_MAP(CNoteView, CView)
	//{{AFX_MSG_MAP(CNoteView)
	ON_COMMAND(ID_STICKNOTE_SHOW, OnStickyNoteShow)
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoteView construction/destruction

CNoteView::CNoteView()
{
}

CNoteView::~CNoteView()
{
	for(int i=0; i<m_arrNoteWnd.GetSize(); i++)
	{
		delete m_arrNoteWnd.GetAt(i);
	}
}

BOOL CNoteView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CNoteView drawing

void CNoteView::OnDraw(CDC* pDC)
{
	CNoteDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	UNREFERENCED_PARAMETER(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CNoteView diagnostics

#ifdef _DEBUG
void CNoteView::AssertValid() const
{
	CView::AssertValid();
}

void CNoteView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNoteDoc* CNoteView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNoteDoc)));
	return (CNoteDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNoteView message handlers

void CNoteView::OnStickyNoteShow() 
{
	CNoteWnd* pNoteWnd=new CNoteWnd(this);

	CRect rect;
	pNoteWnd->GetWindowRect(&rect);
	int nXScreen=::GetSystemMetrics(SM_CXSCREEN);
	int nYScreen=::GetSystemMetrics(SM_CYSCREEN);
	nXScreen-=rect.Width();
	nYScreen-=rect.Height();
	srand((unsigned)time(NULL));
	CPoint point;
	point.x=rand()*3%nXScreen;
	point.y=rand()*2%nYScreen;
	pNoteWnd->SetWindowPos(NULL,point.x,point.y,0,0,SWP_NOZORDER|SWP_NOSIZE);

	m_arrNoteWnd.Add(pNoteWnd);
}

