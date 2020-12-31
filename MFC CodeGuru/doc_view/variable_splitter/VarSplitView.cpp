// VarSplitView.cpp : implementation of the CVarSplitView class
//

#include "stdafx.h"
#include "VarSplit.h"

#include "VarSplitDoc.h"
#include "VarSplitView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVarSplitView

IMPLEMENT_DYNCREATE(CVarSplitView, CView)

BEGIN_MESSAGE_MAP(CVarSplitView, CView)
	//{{AFX_MSG_MAP(CVarSplitView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVarSplitView construction/destruction

CVarSplitView::CVarSplitView()
{
	// TODO: add construction code here
	TRACE0("COSTRUTTORE CVarSplitView\n");

}

CVarSplitView::~CVarSplitView()
{
	TRACE0("DISTRUTTORE CVarSplitView\n");
}

BOOL CVarSplitView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVarSplitView drawing

void CVarSplitView::OnDraw(CDC* pDC)
{
	CVarSplitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
		pDC->TextOut(0,0,"DefaultView");

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CVarSplitView printing

BOOL CVarSplitView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVarSplitView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVarSplitView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CVarSplitView diagnostics

#ifdef _DEBUG
void CVarSplitView::AssertValid() const
{
	CView::AssertValid();
}

void CVarSplitView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVarSplitDoc* CVarSplitView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVarSplitDoc)));
	return (CVarSplitDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVarSplitView message handlers

void CVarSplitView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
TRACE0("INITIAL UPDATE 	CVarSplitView\n");
}
