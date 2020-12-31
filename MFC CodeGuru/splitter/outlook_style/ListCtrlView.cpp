// ListCtrlView.cpp : implementation file
//

#include "stdafx.h"
#include "outlookstyle.h"
#include "ListCtrlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlView

IMPLEMENT_DYNCREATE(CListCtrlView, CFormView)

CListCtrlView::CListCtrlView()
	: CFormView(CListCtrlView::IDD)
{
	//{{AFX_DATA_INIT(CListCtrlView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CListCtrlView::~CListCtrlView()
{
}

void CListCtrlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListCtrlView)
	DDX_Control(pDX, IDC_LIST, m_listCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListCtrlView, CFormView)
	//{{AFX_MSG_MAP(CListCtrlView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlView diagnostics

#ifdef _DEBUG
void CListCtrlView::AssertValid() const
{
	CFormView::AssertValid();
}

void CListCtrlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListCtrlView message handlers

void CListCtrlView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CRect rect;
	m_listCtrl.GetClientRect(&rect);

	m_listCtrl.InsertColumn(0, "From", LVCFMT_LEFT, rect.Width()/4);
	m_listCtrl.InsertColumn(1, "Subject", LVCFMT_LEFT, rect.Width()/4);
	m_listCtrl.InsertColumn(2, "Date", LVCFMT_LEFT, rect.Width()/4);
	m_listCtrl.InsertColumn(3, "Size", LVCFMT_LEFT, rect.Width()/4);	
}

void CListCtrlView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CFormView::ShowScrollBar(SB_VERT,FALSE);
	CFormView::ShowScrollBar(SB_HORZ,FALSE);

	if (GetSafeHwnd())
	{
		if (m_listCtrl.GetSafeHwnd())
		{
			CRect rect(0,0,cx,cy);
			m_listCtrl.MoveWindow(&rect);
		}
	}	
}
