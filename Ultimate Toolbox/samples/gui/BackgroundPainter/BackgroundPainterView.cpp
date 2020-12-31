// BackgroundPainterView.cpp : implementation of the CBackgroundPainterView class
//

#include "stdafx.h"
#include "BackgroundPainter.h"

#include "BackgroundPainterDoc.h"

#include "MainFrm.h"
#include "BackgroundPainterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackgroundPainterView

IMPLEMENT_DYNCREATE(CBackgroundPainterView, CView)

BEGIN_MESSAGE_MAP(CBackgroundPainterView, CView)
	//{{AFX_MSG_MAP(CBackgroundPainterView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackgroundPainterView construction/destruction

CBackgroundPainterView::CBackgroundPainterView()
{
	// TODO: add construction code here

}

CBackgroundPainterView::~CBackgroundPainterView()
{
}

BOOL CBackgroundPainterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBackgroundPainterView drawing

void CBackgroundPainterView::OnDraw(CDC* pDC)
{
	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(rect);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(_T("Almost all windows' background in this MDI application was painted using COXBackgroundPainter object!\nCheck out in 'View' menu 'Dialog with image viewer' and 'Test About Dialog' options!"),
		rect,DT_CENTER|DT_WORDBREAK);
}

/////////////////////////////////////////////////////////////////////////////
// CBackgroundPainterView printing

BOOL CBackgroundPainterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBackgroundPainterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBackgroundPainterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBackgroundPainterView diagnostics

#ifdef _DEBUG
void CBackgroundPainterView::AssertValid() const
{
	CView::AssertValid();
}

void CBackgroundPainterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBackgroundPainterDoc* CBackgroundPainterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBackgroundPainterDoc)));
	return (CBackgroundPainterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBackgroundPainterView message handlers

int CBackgroundPainterView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	((CMainFrame*)AfxGetMainWnd())->GetPainter()->Attach(this,IDB_WALLPAPER);

	return 0;
}
