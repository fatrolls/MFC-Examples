// EditCtrlView.cpp : implementation file
//

#include "stdafx.h"
#include "outlookstyle.h"
#include "EditCtrlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditCtrlView

IMPLEMENT_DYNCREATE(CEditCtrlView, CFormView)

CEditCtrlView::CEditCtrlView()
	: CFormView(CEditCtrlView::IDD)
{
	//{{AFX_DATA_INIT(CEditCtrlView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CEditCtrlView::~CEditCtrlView()
{
}

void CEditCtrlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditCtrlView)
	DDX_Control(pDX, IDC_EDIT, m_editCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditCtrlView, CFormView)
	//{{AFX_MSG_MAP(CEditCtrlView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditCtrlView diagnostics

#ifdef _DEBUG
void CEditCtrlView::AssertValid() const
{
	CFormView::AssertValid();
}

void CEditCtrlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEditCtrlView message handlers

void CEditCtrlView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CFormView::ShowScrollBar(SB_VERT,FALSE);
	CFormView::ShowScrollBar(SB_HORZ,FALSE);

	if (GetSafeHwnd())
	{
		if (m_editCtrl.GetSafeHwnd())
		{
			CRect rect(0,0,cx,cy);
			m_editCtrl.MoveWindow(&rect);
		}
	}		
}
