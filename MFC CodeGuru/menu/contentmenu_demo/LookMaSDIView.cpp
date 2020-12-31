// LookMaSDIView.cpp : implementation of the CLookMaSDIView class
//

#include "stdafx.h"
#include "LookMaSDI.h"

#include "LookMaSDIDoc.h"
#include "LookMaSDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLookMaSDIView

IMPLEMENT_DYNCREATE(CLookMaSDIView, CView)

BEGIN_MESSAGE_MAP(CLookMaSDIView, CView)
	//{{AFX_MSG_MAP(CLookMaSDIView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLookMaSDIView construction/destruction

CLookMaSDIView::CLookMaSDIView()
{
	// TODO: add construction code here

}

CLookMaSDIView::~CLookMaSDIView()
{
}

BOOL CLookMaSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLookMaSDIView drawing

void CLookMaSDIView::OnDraw(CDC* pDC)
{
	CLookMaSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CLookMaSDIView printing

BOOL CLookMaSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLookMaSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLookMaSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CLookMaSDIView diagnostics

#ifdef _DEBUG
void CLookMaSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CLookMaSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLookMaSDIDoc* CLookMaSDIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLookMaSDIDoc)));
	return (CLookMaSDIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLookMaSDIView message handlers
