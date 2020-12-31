// PropertyPagePreferences.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenGrabber.h"
#include "PropertyPagePreferences.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyPagePreferences property page

//IMPLEMENT_DYNCREATE(CPropertyPagePreferences, COXContextHelpPropertyPage)

// array of control IDs and corresponding help IDs
const DWORD CPropertyPagePreferences::m_nHelpIDs[] = 
{
	IDC_CHECK_HIDE_ICON, IDH_CHECK_HIDE_ICON,
	IDC_CHECK_NOTIFY_END, IDH_CHECK_NOTIFY_END,
	0, 0
};


CPropertyPagePreferences::CPropertyPagePreferences() : 
	COXContextHelpPropertyPage(CPropertyPagePreferences::IDD)
{
	//{{AFX_DATA_INIT(CPropertyPagePreferences)
	m_bHideIcon = FALSE;
	m_bNotifyEnd = FALSE;
	//}}AFX_DATA_INIT
}

CPropertyPagePreferences::~CPropertyPagePreferences()
{
}

void CPropertyPagePreferences::DoDataExchange(CDataExchange* pDX)
{
	COXContextHelpPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPagePreferences)
	DDX_Control(pDX, IDC_CHECK_NOTIFY_END, m_ctlCheckNotifyEnd);
	DDX_Control(pDX, IDC_CHECK_HIDE_ICON, m_ctlCheckHideIcon);
	DDX_Check(pDX, IDC_CHECK_HIDE_ICON, m_bHideIcon);
	DDX_Check(pDX, IDC_CHECK_NOTIFY_END, m_bNotifyEnd);
	//}}AFX_DATA_MAP
	// check if all variables are correct
	CheckVars();
}


BEGIN_MESSAGE_MAP(CPropertyPagePreferences, COXContextHelpPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPagePreferences)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPagePreferences message handlers

BOOL CPropertyPagePreferences::AdjustToolTips()
{
	//Set up the Tooltip
	BOOL result;

	result=m_Tooltip.AddTool(&m_ctlCheckNotifyEnd,
		_T("Displays dialog box notifying you about end of capturing"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlCheckHideIcon,
		_T("Hide icon when capture"));
	ASSERT(result != 0) ;

	return result;
}

BOOL CPropertyPagePreferences::OnInitDialog() 
{
	COXContextHelpPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_LayoutManager.Attach(this);

	CRect rectDialog;
	GetWindowRect(&rectDialog);

	CRect rectItem;

	GetDlgItem(IDC_STATIC_SETTINGS)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_STATIC_SETTINGS, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);
	m_LayoutManager.SetConstraint(IDC_STATIC_SETTINGS, OX_LMS_LEFT, OX_LMT_SAME,  
		rectItem.left-rectDialog.left);
	
	// check if all variables are correct
	CheckVars();

	UpdateData(FALSE);

	ShowControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPagePreferences::ShowControls() 
{
}

void CPropertyPagePreferences::CheckVars() 
{
}


