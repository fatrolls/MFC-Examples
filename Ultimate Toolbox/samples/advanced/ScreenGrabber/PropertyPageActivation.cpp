// PropertyPageActivation.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ScreenGrabber.h"
#include "PropertyPageActivation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageActivation dialog

//IMPLEMENT_DYNCREATE(CPropertyPageActivation, COXContextHelpPropertyPage)

// array of control IDs and corresponding help IDs
const DWORD CPropertyPageActivation::m_nHelpIDs[] = 
{
	IDC_STATIC_HOT_KEY, IDH_STATIC_HOT_KEY,
	IDC_COMBO_HOT_KEY, IDH_COMBO_HOT_KEY,
	IDC_CHECK_INITIAL_DELAY, IDH_CHECK_INITIAL_DELAY,
	IDC_EDIT_INITIAL_DELAY, IDH_EDIT_INITIAL_DELAY,
	IDC_SPIN_INITIAL_DELAY, IDH_SPIN_INITIAL_DELAY,
	0, 0
};


CPropertyPageActivation::CPropertyPageActivation()
	: COXContextHelpPropertyPage(CPropertyPageActivation::IDD)
{
	//{{AFX_DATA_INIT(CPropertyPageActivation)
	m_sHotKey = _T("");
	m_nInitialDelay = 0;
	m_bInitialDelay = FALSE;
	//}}AFX_DATA_INIT
}

CPropertyPageActivation::~CPropertyPageActivation()
{
}

void CPropertyPageActivation::DoDataExchange(CDataExchange* pDX)
{
	COXContextHelpPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageActivation)
	DDX_Control(pDX, IDC_CHECK_INITIAL_DELAY, m_ctlCheckInitialDelay);
	DDX_Control(pDX, IDC_STATIC_HOT_KEY, m_ctlStaticHotKey);
	DDX_Control(pDX, IDC_SPIN_INITIAL_DELAY, m_ctlSpinInitialDelay);
	DDX_Control(pDX, IDC_EDIT_INITIAL_DELAY, m_ctlEditInitialDelay);
	DDX_Control(pDX, IDC_COMBO_HOT_KEY, m_ctlComboHotKey);
	DDX_CBString(pDX, IDC_COMBO_HOT_KEY, m_sHotKey);
	DDX_Text(pDX, IDC_EDIT_INITIAL_DELAY, m_nInitialDelay);
	DDV_MinMaxUInt(pDX, m_nInitialDelay, 1, 60);
	DDX_Check(pDX, IDC_CHECK_INITIAL_DELAY, m_bInitialDelay);
	//}}AFX_DATA_MAP
	// check if all variables are correct
	CheckVars();
}


BEGIN_MESSAGE_MAP(CPropertyPageActivation, COXContextHelpPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPageActivation)
	ON_BN_CLICKED(IDC_CHECK_INITIAL_DELAY, OnCheckInitialDelay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageActivation message handlers

BOOL CPropertyPageActivation::AdjustToolTips()
{
	//Set up the Tooltip
	BOOL result;

	result=m_Tooltip.AddTool(&m_ctlStaticHotKey,
		_T("Define the hot key to start capturing"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlCheckInitialDelay,
		_T("Define delay in seconds before capture"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlSpinInitialDelay,
		_T("Change value of initial delay from 1 to 60 seconds"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlEditInitialDelay,
		_T("Change value of initial delay from 1 to 60 seconds"));
	ASSERT(result != 0) ;
	result=m_Tooltip.AddTool(&m_ctlComboHotKey,
		_T("Pick hot key to start capturing"));
	ASSERT(result != 0) ;

	return result;
}

BOOL CPropertyPageActivation::OnInitDialog() 
{
	COXContextHelpPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_LayoutManager.Attach(this);

	CRect rectDialog;
	GetWindowRect(&rectDialog);

	CRect rectItem;

	GetDlgItem(IDC_STATIC_TIMING)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_STATIC_TIMING, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);
	m_LayoutManager.SetConstraint(IDC_STATIC_TIMING, OX_LMS_LEFT, OX_LMT_SAME,  
		rectItem.left-rectDialog.left);

	GetDlgItem(IDC_SPIN_INITIAL_DELAY)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_SPIN_INITIAL_DELAY, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);

	GetDlgItem(IDC_EDIT_INITIAL_DELAY)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_EDIT_INITIAL_DELAY, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);

	GetDlgItem(IDC_CHECK_INITIAL_DELAY)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_CHECK_INITIAL_DELAY, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);
	m_LayoutManager.SetConstraint(IDC_CHECK_INITIAL_DELAY, OX_LMS_LEFT, OX_LMT_SAME,  
		rectItem.left-rectDialog.left);

	GetDlgItem(IDC_COMBO_HOT_KEY)->GetWindowRect(&rectItem);
	m_LayoutManager.SetConstraint(IDC_COMBO_HOT_KEY, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectItem.right-rectDialog.right);
	m_LayoutManager.SetConstraint(IDC_COMBO_HOT_KEY, OX_LMS_LEFT, OX_LMT_SAME,  
		rectItem.left-rectDialog.left);

	// Define array of possible hot keys
	m_ctlComboHotKey.AddString(_T("F1"));
	m_ctlComboHotKey.AddString(_T("F2"));
	m_ctlComboHotKey.AddString(_T("F3"));
	m_ctlComboHotKey.AddString(_T("F4"));
	m_ctlComboHotKey.AddString(_T("F5"));
	m_ctlComboHotKey.AddString(_T("F6"));
	m_ctlComboHotKey.AddString(_T("F7"));
	m_ctlComboHotKey.AddString(_T("F8"));
	m_ctlComboHotKey.AddString(_T("F9"));
	m_ctlComboHotKey.AddString(_T("F10"));

	// check if all variables are correct
	CheckVars();

	// Set the COXSpinCtrl object, which is mapped to a common Spin Control.
	m_ctlSpinInitialDelay.SetBuddy(&m_ctlEditInitialDelay);
	m_ctlSpinInitialDelay.SetRange(ID_MIN_INITIAL_DELAY,ID_MAX_INITIAL_DELAY);
	m_ctlSpinInitialDelay.SetPos(m_nInitialDelay);

	// Set a default COXSpinCtrl method of delta value computation 
	// (Delta pixel = Delta value).
	m_ctlSpinInitialDelay.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);

	UpdateData(FALSE);
	ShowControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageActivation::OnCheckInitialDelay() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	ShowControls();
}

void CPropertyPageActivation::ShowControls() 
{
	if(m_bInitialDelay)
	{
		m_ctlEditInitialDelay.EnableWindow(TRUE);
		m_ctlSpinInitialDelay.EnableWindow(TRUE);
	}
	else
	{
		m_ctlEditInitialDelay.EnableWindow(FALSE);
		m_ctlSpinInitialDelay.EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

void CPropertyPageActivation::CheckVars() 
{
	if(m_nInitialDelay<ID_MIN_INITIAL_DELAY || m_nInitialDelay>ID_MAX_INITIAL_DELAY)
	{
		m_nInitialDelay=ID_MIN_INITIAL_DELAY;
	}
	if(m_ctlComboHotKey.FindStringExact(-1,m_sHotKey)==CB_ERR)
	{
		if(m_ctlComboHotKey.GetCount()>0)
		{
			m_ctlComboHotKey.GetLBText(0,m_sHotKey);
		}
	}
}
