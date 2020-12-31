// demo_toolbarView.cpp : implementation of the CDemo_toolbarView class
//

#include "stdafx.h"
#include "demo_toolbar.h"

#include "demo_toolbarDoc.h"
#include "demo_toolbarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemo_toolbarView

IMPLEMENT_DYNCREATE(CDemo_toolbarView, CEditView)

BEGIN_MESSAGE_MAP(CDemo_toolbarView, CEditView)
	//{{AFX_MSG_MAP(CDemo_toolbarView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo_toolbarView construction/destruction

CDemo_toolbarView::CDemo_toolbarView()
{
	// TODO: add construction code here

}

CDemo_toolbarView::~CDemo_toolbarView()
{
}

BOOL CDemo_toolbarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_toolbarView drawing

void CDemo_toolbarView::OnDraw(CDC* pDC)
{
	CDemo_toolbarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_toolbarView printing

BOOL CDemo_toolbarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CDemo_toolbarView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CDemo_toolbarView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_toolbarView diagnostics

#ifdef _DEBUG
void CDemo_toolbarView::AssertValid() const
{
	CEditView::AssertValid();
}

void CDemo_toolbarView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CDemo_toolbarDoc* CDemo_toolbarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemo_toolbarDoc)));
	return (CDemo_toolbarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemo_toolbarView message handlers
