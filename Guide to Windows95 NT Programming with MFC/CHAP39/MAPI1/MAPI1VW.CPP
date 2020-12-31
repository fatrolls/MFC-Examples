// Mapi1Vw.cpp : implementation of the CMapi1View class
//

#include "stdafx.h"
#include "Mapi1.h"

#include "Mapi1Doc.h"
#include "Mapi1Vw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapi1View

IMPLEMENT_DYNCREATE(CMapi1View, CEditView)

BEGIN_MESSAGE_MAP(CMapi1View, CEditView)
	//{{AFX_MSG_MAP(CMapi1View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapi1View construction/destruction

CMapi1View::CMapi1View()
{
	// TODO: add construction code here

}

CMapi1View::~CMapi1View()
{
}

BOOL CMapi1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CMapi1View drawing

void CMapi1View::OnDraw(CDC* pDC)
{
	CMapi1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMapi1View printing

BOOL CMapi1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CMapi1View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMapi1View::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CMapi1View diagnostics

#ifdef _DEBUG
void CMapi1View::AssertValid() const
{
	CEditView::AssertValid();
}

void CMapi1View::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMapi1Doc* CMapi1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapi1Doc)));
	return (CMapi1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapi1View message handlers
