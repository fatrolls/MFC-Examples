// DockPropView.cpp : implementation of the CDockPropView class
//

#include "stdafx.h"
#include "DockProp.h"

#include "DockPropDoc.h"
#include "DockPropView.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDockPropView

IMPLEMENT_DYNCREATE(CDockPropView, CFormView)

BEGIN_MESSAGE_MAP(CDockPropView, CFormView)
	//{{AFX_MSG_MAP(CDockPropView)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDockPropView construction/destruction

CDockPropView::CDockPropView()
	: CFormView(CDockPropView::IDD)
{
	//{{AFX_DATA_INIT(CDockPropView)
	m_nSetActive = 0;
	m_nDelPage = 0;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CDockPropView::~CDockPropView()
{
}

void CDockPropView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDockPropView)
	DDX_Text(pDX, IDC_EDIT1, m_nSetActive);
	DDX_Text(pDX, IDC_EDIT2, m_nDelPage);
	//}}AFX_DATA_MAP
}

BOOL CDockPropView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDockPropView printing

BOOL CDockPropView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDockPropView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDockPropView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDockPropView::OnPrint(CDC* pDC, CPrintInfo*)
{
	// TODO: add code to print the controls
	UNREFERENCED_PARAMETER(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CDockPropView diagnostics

#ifdef _DEBUG
void CDockPropView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDockPropView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDockPropDoc* CDockPropView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDockPropDoc)));
	return (CDockPropDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDockPropView message handlers

void CDockPropView::OnButton1() 
{
	if (UpdateData(TRUE))
		((CMainFrame*)AfxGetMainWnd())->m_wndMeasureBar.SetActivePage(m_nSetActive);
	
}

void CDockPropView::OnButton2() 
{
	if (UpdateData(TRUE))
		((CMainFrame*)AfxGetMainWnd())->m_wndMeasureBar.RemovePage(m_nDelPage);
	
}

void CDockPropView::OnButton3() 
{
	((CMainFrame*)AfxGetMainWnd())->m_wndMeasureBar.AddOnePage();
	((CMainFrame*)AfxGetMainWnd())->
		m_wndMeasureBar.SetActivePage(((CMainFrame*)AfxGetMainWnd())->
		m_wndMeasureBar.GetPageCount()-1);
}

void CDockPropView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	ResizeParentToFit(FALSE);
	
}
