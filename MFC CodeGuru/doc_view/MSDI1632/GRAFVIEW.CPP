// grafview.cpp : implementation of the CGrafView class
//

#include "stdafx.h"
#include "msdi.h"

#include "msdidoc.h"
#include "grafview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrafView

IMPLEMENT_DYNCREATE(CGrafView, CView)

BEGIN_MESSAGE_MAP(CGrafView, CView)
	//{{AFX_MSG_MAP(CGrafView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrafView construction/destruction

CGrafView::CGrafView()
{
	// TODO: add construction code here
}

CGrafView::~CGrafView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGrafView drawing

void CGrafView::OnDraw(CDC* pDC)
{
	CMsdiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

	CRect rect; GetClientRect(&rect);		// a litle drawing
	pDC->MoveTo(rect.left, rect.top);
	pDC->LineTo(rect.right, rect.bottom);
}

/////////////////////////////////////////////////////////////////////////////
// CGrafView printing

BOOL CGrafView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGrafView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGrafView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGrafView diagnostics

#ifdef _DEBUG
void CGrafView::AssertValid() const
{
	CView::AssertValid();
}

void CGrafView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMsdiDoc* CGrafView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMsdiDoc)));
	return (CMsdiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGrafView message handlers
