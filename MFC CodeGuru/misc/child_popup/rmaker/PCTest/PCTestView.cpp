// PCTestView.cpp : implementation of the CPCTestView class
//

#include "stdafx.h"
#include "PCTest.h"

#include "PCTestDoc.h"
#include "PCTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCTestView

IMPLEMENT_DYNCREATE(CPCTestView, CView)

BEGIN_MESSAGE_MAP(CPCTestView, CView)
	//{{AFX_MSG_MAP(CPCTestView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPCTestView construction/destruction

CPCTestView::CPCTestView()
{
	// TODO: add construction code here

}

CPCTestView::~CPCTestView()
{
}

BOOL CPCTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPCTestView drawing

void CPCTestView::OnDraw(CDC* pDC)
{
	CPCTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPCTestView printing

BOOL CPCTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPCTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPCTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPCTestView diagnostics

#ifdef _DEBUG
void CPCTestView::AssertValid() const
{
	CView::AssertValid();
}

void CPCTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPCTestDoc* CPCTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPCTestDoc)));
	return (CPCTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPCTestView message handlers

int CPCTestView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect(0, 0, 50, 50);
	m_pcWnd.Create(GetSafeHwnd(), rect, TRUE); 
		
	return 0;
}

void CPCTestView::OnDestroy() 
{
	CView::OnDestroy();
	
	m_pcWnd.Destroy();	
}
