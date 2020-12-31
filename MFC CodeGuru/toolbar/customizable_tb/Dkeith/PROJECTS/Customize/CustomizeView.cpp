// CustomizeView.cpp : implementation of the CCustomizeView class
//

#include "stdafx.h"
#include "Customize.h"

#include "CustomizeDoc.h"
#include "CustomizeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeView

IMPLEMENT_DYNCREATE(CCustomizeView, CView)

BEGIN_MESSAGE_MAP(CCustomizeView, CView)
	//{{AFX_MSG_MAP(CCustomizeView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeView construction/destruction

CCustomizeView::CCustomizeView()
{
	// TODO: add construction code here

}

CCustomizeView::~CCustomizeView()
{
}

BOOL CCustomizeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomizeView drawing

void CCustomizeView::OnDraw(CDC* pDC)
{
	CCustomizeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCustomizeView printing

BOOL CCustomizeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCustomizeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCustomizeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCustomizeView diagnostics

#ifdef _DEBUG
void CCustomizeView::AssertValid() const
{
	CView::AssertValid();
}

void CCustomizeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCustomizeDoc* CCustomizeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCustomizeDoc)));
	return (CCustomizeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomizeView message handlers

void CCustomizeView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
		STARTUPINFO			 start;

	start.cb = sizeof(STARTUPINFO);
	start.lpReserved = NULL;
	start.lpDesktop = NULL;
	start.lpTitle = NULL;
	start.dwFlags = STARTF_USESHOWWINDOW;
	start.wShowWindow = SW_SHOW;
	start.cbReserved2 = 0;
	start.lpReserved2 = NULL;

	if (CreateProcess("c:\\dkeith\\projects\\binaryanalyst\\release\\binaryanalyst.exe", NULL, NULL, NULL, FALSE, HIGH_PRIORITY_CLASS,
		NULL, NULL, &start, &process))
	{
		int j = 0;
	}
	CView::OnLButtonDblClk(nFlags, point);
}

void CCustomizeView::OnLButtonDown(UINT nFlags, CPoint point) 
{
}

BOOL CALLBACK MyEnumThreadWndProc(HWND hwnd, LPARAM lParam)
{
	::PostMessage(hwnd, WM_SYSCOMMAND, (WPARAM)SC_RESTORE, 0);
	return TRUE;
}

void CCustomizeView::OnRButtonDown(UINT nFlags, CPoint point) 
{
		WNDENUMPROC		 lpfn = MyEnumThreadWndProc;

	if (EnumThreadWindows(process.dwThreadId, lpfn, 0))
	{
		// the message should have gotten there
	}

	// default processing
	CView::OnLButtonDown(nFlags, point);
}
