// ex26aView.cpp : implementation of the CEx26aView class
//

#include "stdafx.h"
#include "ex26a.h"

#include "ex26aDoc.h"
#include "ex26aView.h"
#include "thread.h" // for readthread and writethread

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx26aView

IMPLEMENT_DYNCREATE(CEx26aView, CView)

BEGIN_MESSAGE_MAP(CEx26aView, CView)
	//{{AFX_MSG_MAP(CEx26aView)
	ON_COMMAND(ID_STORAGE_READ, OnStorageRead)
	ON_COMMAND(ID_STORAGE_WRITE, OnStorageWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx26aView construction/destruction

CEx26aView::CEx26aView()
{
	// TODO: add construction code here

}

CEx26aView::~CEx26aView()
{
}

BOOL CEx26aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx26aView drawing

void CEx26aView::OnDraw(CDC* pDC)
{
	CEx26aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDC->TextOut(0, 0, "Run from the debugger");
}

/////////////////////////////////////////////////////////////////////////////
// CEx26aView diagnostics

#ifdef _DEBUG
void CEx26aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx26aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx26aDoc* CEx26aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx26aDoc)));
	return (CEx26aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx26aView message handlers

void CEx26aView::OnStorageRead() 
{
	CWinThread* pThread = AfxBeginThread(ReadThreadProc, GetSafeHwnd());
}

void CEx26aView::OnStorageWrite() 
{
	CWinThread* pThread = AfxBeginThread(WriteThreadProc, GetSafeHwnd());
}
