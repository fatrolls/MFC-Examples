// WorkspaceGraphPropView.cpp : implementation file
//

#include "stdafx.h"
#include "WorkspaceDemo.h"

#include "WorkspaceGraphDoc.h"
#include "WorkspaceGraphPropView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceGraphPropView

IMPLEMENT_DYNCREATE(CWorkspaceGraphPropView, CFormView)

CWorkspaceGraphPropView::CWorkspaceGraphPropView()
: CFormView(CWorkspaceGraphPropView::IDD)
	{
	//{{AFX_DATA_INIT(CWorkspaceGraphPropView)
	m_sSides = _T("");
	m_sColor = _T("");
	//}}AFX_DATA_INIT
	}

CWorkspaceGraphPropView::~CWorkspaceGraphPropView()
	{
	}

void CWorkspaceGraphPropView::DoDataExchange(CDataExchange* pDX)
	{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorkspaceGraphPropView)
	DDX_Control(pDX, IDC_SIDES_SPIN, m_wndSidesSpin);
	DDX_Text(pDX, IDC_SIDES, m_sSides);
	DDX_Text(pDX, IDC_COLOR, m_sColor);
	//}}AFX_DATA_MAP
	}


BEGIN_MESSAGE_MAP(CWorkspaceGraphPropView, CFormView)
	//{{AFX_MSG_MAP(CWorkspaceGraphPropView)
	ON_BN_CLICKED(IDC_COLOR_BROWSE, OnColorBrowse)
	ON_EN_CHANGE(IDC_SIDES, OnChangeSides)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceGraphPropView diagnostics

#ifdef _DEBUG
void CWorkspaceGraphPropView::AssertValid() const
	{
	CFormView::AssertValid();
	}

void CWorkspaceGraphPropView::Dump(CDumpContext& dc) const
	{
	CFormView::Dump(dc);
	}

CWorkspaceGraphDoc* CWorkspaceGraphPropView::GetDocument() // non-debug version is inline
	{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorkspaceGraphDoc)));
	return (CWorkspaceGraphDoc*)m_pDocument;
	}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceGraphPropView message handlers

void CWorkspaceGraphPropView::OnInitialUpdate() 
	{
	CFormView::OnInitialUpdate();
	
	m_wndSidesSpin.SetRange(3, 20);
	
	// Fit frame around view
	ResizeParentToFit(FALSE);
	}

void CWorkspaceGraphPropView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
	{
	UNREFERENCED_PARAMETER(pSender);
	UNREFERENCED_PARAMETER(lHint);
	UNREFERENCED_PARAMETER(pHint);

	COLORREF color = GetDocument()->GetColor();
	int nSides = GetDocument()->GetSides();
	m_sSides.Format(_T("%i"), nSides);
	m_sColor.Format(_T("%i"), color);
	UpdateData(FALSE);
	}

void CWorkspaceGraphPropView::OnColorBrowse() 
	{
	if (!UpdateData(TRUE))
		return;

	// Use color common dialog
	CColorDialog colorDlg(_ttoi(m_sColor));
	if (colorDlg.DoModal() == IDOK)
		{
		m_sColor.Format(_T("%i"), colorDlg.GetColor());
		}
	UpdateData(FALSE);

	if (GetDocument()->SetColor(colorDlg.GetColor()))
		GetDocument()->UpdateAllViews(this);
	}

void CWorkspaceGraphPropView::OnChangeSides() 
	{
	// ... Check whether OnInitialUpdate has been completed
	if (m_wndSidesSpin.m_hWnd == NULL)
		return;

	if (!UpdateData(TRUE))
		return;

	if (GetDocument()->SetSides(_ttoi(m_sSides)))
		GetDocument()->UpdateAllViews(this);

	UpdateData(FALSE);
	}
