// MeasurePage.cpp : implementation file
//

#include "stdafx.h"
#include "MeasPage.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern long ISU;

/////////////////////////////////////////////////////////////////////////////
// CMeasurePage dialog

BEGIN_MESSAGE_MAP(CMeasurePage, COXDockPropertyPage)
	//{{AFX_MSG_MAP(CMeasurePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CMeasurePage::CMeasurePage(BOOL bDynamic /* =FALSE */)
	: COXDockPropertyPage(IDS_MEASURE, bDynamic)
{
	m_nID = CMeasurePage::IDD;
	//{{AFX_DATA_INIT(CMeasurePage)
	m_bShowSection = TRUE;
	m_bSnapSection = FALSE;
	//}}AFX_DATA_INIT
}


void CMeasurePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMeasurePage)
	DDX_Control(pDX, IDC_SNAP_SECTION, m_snapSection);
	DDX_Control(pDX, IDC_SHOW_SECTION, m_showSection);
	DDX_Control(pDX, IDC_SPINP2P, m_spinP2P);
	DDX_Check(pDX, IDC_SHOW_SECTION, m_bShowSection);
	DDX_Check(pDX, IDC_SNAP_SECTION, m_bSnapSection);
	//}}AFX_DATA_MAP
}

BOOL CMeasurePage::OnInitDialog() 
{
	if (COXDockPropertyPage::OnInitDialog()==FALSE)
		return FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
}


/////////////////////////////////////////////////////////////////////////////
// CMeasurePage message handlers

BOOL CMeasurePage::OnSetActive( )
{
	return COXDockPropertyPage::OnSetActive();;
}

BOOL CMeasurePage::OnKillActive()
{
	return COXDockPropertyPage::OnKillActive();;
}

