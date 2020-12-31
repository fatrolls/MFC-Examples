// ex26cView.cpp : implementation of the CEx26cView class
//

#include "stdafx.h"
#include "ex26c.h"

#include "ex26cDoc.h"
#include "ex26cView.h"
#include "Thread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx26cView

IMPLEMENT_DYNCREATE(CEx26cView, CView)

BEGIN_MESSAGE_MAP(CEx26cView, CView)
	//{{AFX_MSG_MAP(CEx26cView)
	ON_COMMAND(ID_STORAGE_READ, OnStorageRead)
	ON_COMMAND(ID_STORAGE_WRITE, OnStorageWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx26cView construction/destruction

CEx26cView::CEx26cView()
{
	// TODO: add construction code here

}

CEx26cView::~CEx26cView()
{
}

BOOL CEx26cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx26cView drawing

void CEx26cView::OnDraw(CDC* pDC)
{
	CEx26cDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDC->TextOut(0, 0, "Run from the debugger");
}

/////////////////////////////////////////////////////////////////////////////
// CEx26cView diagnostics

#ifdef _DEBUG
void CEx26cView::AssertValid() const
{
	CView::AssertValid();
}

void CEx26cView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx26cDoc* CEx26cView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx26cDoc)));
	return (CEx26cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx26cView message handlers

void CEx26cView::OnStorageRead() 
{
	CWinThread* pThread = AfxBeginThread(ReadThreadProc, GetSafeHwnd());
}

void CEx26cView::OnStorageWrite() 
{
	CWinThread* pThread = AfxBeginThread(WriteThreadProc, GetSafeHwnd());
}
