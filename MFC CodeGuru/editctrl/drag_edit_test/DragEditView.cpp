// DragEditView.cpp : implementation of the CDragEditView class
//

#include "stdafx.h"
#include "DragEdit.h"

#include "DragEditDoc.h"
#include "DragEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragEditView

IMPLEMENT_DYNCREATE(CDragEditView, CView)

BEGIN_MESSAGE_MAP(CDragEditView, CView)
	//{{AFX_MSG_MAP(CDragEditView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragEditView construction/destruction

CDragEditView::CDragEditView()
{
	// TODO: add construction code here

}

CDragEditView::~CDragEditView()
{
}

BOOL CDragEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDragEditView drawing

void CDragEditView::OnDraw(CDC* pDC)
{
	CDragEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDragEditView printing

BOOL CDragEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDragEditView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDragEditView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDragEditView diagnostics

#ifdef _DEBUG
void CDragEditView::AssertValid() const
{
	CView::AssertValid();
}

void CDragEditView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDragEditDoc* CDragEditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDragEditDoc)));
	return (CDragEditDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDragEditView message handlers
