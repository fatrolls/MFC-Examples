// msdiview.cpp : implementation of the CMsdiView class
//

#include "stdafx.h"
#include "msdi.h"

#include "msdidoc.h"
#include "msdiview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsdiView

IMPLEMENT_DYNCREATE(CMsdiView, CFormView)

BEGIN_MESSAGE_MAP(CMsdiView, CFormView)
	//{{AFX_MSG_MAP(CMsdiView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsdiView construction/destruction

CMsdiView::CMsdiView()
	: CFormView(CMsdiView::IDD)
{
	//{{AFX_DATA_INIT(CMsdiView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here
}

CMsdiView::~CMsdiView()
{
}

void CMsdiView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMdiView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CMsdiView printing

BOOL CMsdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMsdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMsdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMsdiView::OnPrint(CDC* pDC, CPrintInfo*)
{
	// TODO: add code to print the controls
}

/////////////////////////////////////////////////////////////////////////////
// CMsdiView diagnostics

#ifdef _DEBUG
void CMsdiView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMsdiView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMsdiDoc* CMsdiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMsdiDoc)));
	return (CMsdiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMsdiView message handlers
