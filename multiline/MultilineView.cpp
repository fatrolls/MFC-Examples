// MultilineView.cpp : implementation of the CMultilineView class
//

#include "stdafx.h"
#include "Multiline.h"

#include "MultilineDoc.h"
#include "MultilineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultilineView

IMPLEMENT_DYNCREATE(CMultilineView, CFormView)

BEGIN_MESSAGE_MAP(CMultilineView, CFormView)
	//{{AFX_MSG_MAP(CMultilineView)
	ON_BN_CLICKED(ID_POPULATE, OnPopulate)
	ON_BN_CLICKED(ID_OK, OnOk)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultilineView construction/destruction

CMultilineView::CMultilineView()
	: CFormView(CMultilineView::IDD)
{
	//{{AFX_DATA_INIT(CMultilineView)
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CMultilineView::~CMultilineView()
{
}

void CMultilineView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultilineView)
	//}}AFX_DATA_MAP
}

BOOL CMultilineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMultilineView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	m_ListCtrl.SubclassDlgItem(IDC_LIST, this) ;
	m_ListCtrl.SetNoOfLinesPerRow(2) ;
	m_ListCtrl.SetNoOfColumns(3) ;
	m_ListCtrl.SetNoOfRows(2) ;
	m_ListCtrl.OnInitialUpdate() ;
}

/////////////////////////////////////////////////////////////////////////////
// CMultilineView printing

BOOL CMultilineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMultilineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMultilineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMultilineView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CMultilineView diagnostics

#ifdef _DEBUG
void CMultilineView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMultilineView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMultilineDoc* CMultilineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMultilineDoc)));
	return (CMultilineDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultilineView message handlers

void CMultilineView::OnPopulate() 
{
	// TODO: Add your control notification handler code here
	
}

void CMultilineView::OnOk() 
{
	// TODO: Add your control notification handler code here
	
}
