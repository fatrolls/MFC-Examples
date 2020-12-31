// Config.cpp : implementation file
//

#include "stdafx.h"
#include "HyperbarDemo.h"
#include "Config.h"

#include "OXHyperBarRender.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfig dialog


CConfig::CConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfig)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfig)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_ZOOM, m_Zoom);
}

BEGIN_MESSAGE_MAP(CConfig, CDialog)
	//{{AFX_MSG_MAP(CConfig)
	ON_WM_HSCROLL()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfig message handlers

void CConfig::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	COXHyperBarRender::m_Focus = m_Zoom.GetPos()/100.0;

	AfxGetMainWnd()->SendMessage(WM_NCACTIVATE, TRUE);
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CConfig::OnInitDialog() 
{
	BOOL ret = CDialog::OnInitDialog();

	if (ret != FALSE)
	{
		m_Zoom.SetRange(5, 40);
		m_Zoom.SetPos(20);
	}
	
	return ret;
}

void CConfig::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	AfxGetMainWnd()->SendMessage(WM_NCACTIVATE, TRUE);
}
