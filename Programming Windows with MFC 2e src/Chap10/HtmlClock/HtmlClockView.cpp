// HtmlClockView.cpp : implementation of the CHtmlClockView class
//

#include "stdafx.h"
#include "HtmlClock.h"

#include "HtmlClockDoc.h"
#include "HtmlClockView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHtmlClockView

IMPLEMENT_DYNCREATE(CHtmlClockView, CHtmlView)

BEGIN_MESSAGE_MAP(CHtmlClockView, CHtmlView)
	//{{AFX_MSG_MAP(CHtmlClockView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHtmlClockView construction/destruction

CHtmlClockView::CHtmlClockView()
{
}

CHtmlClockView::~CHtmlClockView()
{
}

BOOL CHtmlClockView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHtmlClockView drawing

void CHtmlClockView::OnDraw(CDC* pDC)
{
	CHtmlClockDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CHtmlClockView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	TCHAR szPath[MAX_PATH];
	::GetModuleFileName (NULL, szPath, sizeof (szPath) / sizeof (TCHAR));

	CString string = szPath;
	int nIndex = string.ReverseFind (_T ('\\'));
	ASSERT (nIndex != -1);
	string = string.Left (nIndex + 1) + _T ("Clock.htm");
	Navigate (string);
}

/////////////////////////////////////////////////////////////////////////////
// CHtmlClockView diagnostics

#ifdef _DEBUG
void CHtmlClockView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CHtmlClockView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CHtmlClockDoc* CHtmlClockView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHtmlClockDoc)));
	return (CHtmlClockDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHtmlClockView message handlers

void CHtmlClockView::OnTitleChange(LPCTSTR lpszText) 
{
	CHtmlView::OnTitleChange(lpszText);
	AfxGetMainWnd ()->SetWindowText (lpszText);
}
