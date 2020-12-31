// PropertyPageDestination.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenGrabber.h"
#include "PropertyPageDestination.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageDestination property page

//IMPLEMENT_DYNCREATE(CPropertyPageDestination, COXContextHelpPropertyPage)

// array of control IDs and corresponding help IDs
const DWORD CPropertyPageDestination::m_nHelpIDs[] = 
{
	IDC_CHECK_FILE, IDH_CHECK_FILE,
	IDC_CHECK_CLIPBOARD, IDH_CHECK_CLIPBOARD,
	0, 0
};


CPropertyPageDestination::CPropertyPageDestination() : 
	COXContextHelpPropertyPage(CPropertyPageDestination::IDD)
{
	//{{AFX_DATA_INIT(CPropertyPageDestination)
	m_bClipboard = FALSE;
	m_bFile = FALSE;
	//}}AFX_DATA_INIT
}

CPropertyPageDestination::~CPropertyPageDestination()
{
}

void CPropertyPageDestination::DoDataExchange(CDataExchange* pDX)
{
	COXContextHelpPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageDestination)
	DDX_Control(pDX, IDC_CHECK_FILE, m_ctlCheckFile);
	DDX_Control(pDX, IDC_CHECK_CLIPBOARD, m_ctlCheckClipboard);
	DDX_Check(pDX, IDC_CHECK_CLIPBOARD, m_bClipboard);
	DDX_Check(pDX, IDC_CHECK_FILE, m_bFile);
	//}}AFX_DATA_MAP
	// check if all variables are correct
	CheckVars();
}


BEGIN_MESSAGE_MAP(CPropertyPageDestination, COXContextHelpPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPageDestination)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageDestination message handlers

BOOL CPropertyPageDestination::AdjustToolTips()
{
	//Set up the Tooltip
	BOOL result;

	result=m_Tooltip.AddTool(&m_ctlCheckFile,
		_T("Save the captured image into file"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlCheckClipboard,
		_T("Copy the captured image into clipboard"));
	ASSERT(result != 0) ;

	return result;
}



BOOL CPropertyPageDestination::OnInitDialog() 
{
	COXContextHelpPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_LayoutManager.Attach(this);

	CRect rectDialog;
	GetWindowRect(&rectDialog);

	CRect rectItem;

	GetDlgItem(IDC_STATIC_DESTINATION)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_STATIC_DESTINATION, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);
	m_LayoutManager.SetConstraint(IDC_STATIC_DESTINATION, OX_LMS_LEFT, OX_LMT_SAME,  
		rectItem.left-rectDialog.left);

	// check if all variables are correct
	CheckVars();

	UpdateData(FALSE);

	ShowControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageDestination::ShowControls() 
{
}

void CPropertyPageDestination::CheckVars() 
{
}
