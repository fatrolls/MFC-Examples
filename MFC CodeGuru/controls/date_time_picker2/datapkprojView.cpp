// datapkprojView.cpp : implementation of the CDatapkprojView class
//

#include "stdafx.h"
#include "datapkproj.h"

#include "datapkprojDoc.h"
#include "datapkprojView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatapkprojView

IMPLEMENT_DYNCREATE(CDatapkprojView, CView)

BEGIN_MESSAGE_MAP(CDatapkprojView, CView)
	//{{AFX_MSG_MAP(CDatapkprojView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatapkprojView construction/destruction

CDatapkprojView::CDatapkprojView()
{
	// TODO: add construction code here

}

CDatapkprojView::~CDatapkprojView()
{
}

BOOL CDatapkprojView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDatapkprojView drawing

void CDatapkprojView::OnDraw(CDC* pDC)
{
	CDatapkprojDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDatapkprojView printing

BOOL CDatapkprojView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDatapkprojView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDatapkprojView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDatapkprojView diagnostics

#ifdef _DEBUG
void CDatapkprojView::AssertValid() const
{
	CView::AssertValid();
}

void CDatapkprojView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDatapkprojDoc* CDatapkprojView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDatapkprojDoc)));
	return (CDatapkprojDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDatapkprojView message handlers

int CDatapkprojView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
  	return 0;
}
