// LeftPaneView.cpp : implementation file
//

#include "stdafx.h"
#include "outlookstyle.h"
#include "LeftPaneView.h"
#include "RightPaneFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftPaneView

IMPLEMENT_DYNCREATE(CLeftPaneView, CFormView)

CLeftPaneView::CLeftPaneView()
	: CFormView(CLeftPaneView::IDD)
{
	//{{AFX_DATA_INIT(CLeftPaneView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CLeftPaneView::~CLeftPaneView()
{
}

void CLeftPaneView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLeftPaneView)
	DDX_Control(pDX, IDC_TREE, m_treeCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLeftPaneView, CFormView)
	//{{AFX_MSG_MAP(CLeftPaneView)
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftPaneView diagnostics

#ifdef _DEBUG
void CLeftPaneView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLeftPaneView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftPaneView message handlers

void CLeftPaneView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_ImageList.Create(IDB_IMAGES, 16, 1, RGB(255, 0, 255));	
	m_treeCtrl.SetImageList(&m_ImageList, LVSIL_NORMAL);

	m_hSplitterView = m_treeCtrl.InsertItem("Splitter View", 0, 0);
	m_hListCtrlView = m_treeCtrl.InsertItem("ListCtrl View", 1, 1);
	m_hEditView     = m_treeCtrl.InsertItem("EditCtrl View", 2, 2);
}

void CLeftPaneView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(&rect);
		if (m_treeCtrl.GetSafeHwnd())
			m_treeCtrl.MoveWindow(&rect);
	}	
}

void CLeftPaneView::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	UINT	    nView         = 0;
	HTREEITEM hSelectedItem = m_treeCtrl.GetSelectedItem();

	if (hSelectedItem == m_hSplitterView)
		nView = VIEW_SPLITTER;
	else
	if (hSelectedItem == m_hListCtrlView)
		nView = VIEW_LISTCTRL;
	else
	if (hSelectedItem == m_hEditView)
		nView = VIEW_EDIT;

	if (nView) m_pRightPaneFrame->SwitchToView(nView);

	*pResult = 0;
}
