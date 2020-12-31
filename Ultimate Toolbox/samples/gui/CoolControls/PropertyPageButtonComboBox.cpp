// PropertyPageButtonComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "CoolControls.h"
#include "PropertyPageButtonComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageButtonComboBox property page

IMPLEMENT_DYNCREATE(CPropertyPageButtonComboBox, CPropertyPage)

CPropertyPageButtonComboBox::CPropertyPageButtonComboBox() : CPropertyPage(CPropertyPageButtonComboBox::IDD)
{
	//{{AFX_DATA_INIT(CPropertyPageButtonComboBox)
	m_bDisable = FALSE;
	//}}AFX_DATA_INIT
}

CPropertyPageButtonComboBox::~CPropertyPageButtonComboBox()
{
}

void CPropertyPageButtonComboBox::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageButtonComboBox)
	DDX_Control(pDX, IDC_BUTTON_PUSH3, m_btnPush3);
	DDX_Control(pDX, IDC_BUTTON_PUSH2, m_btnPush2);
	DDX_Control(pDX, IDC_RADIO1, m_radio1);
	DDX_Control(pDX, IDC_RADIO2, m_radio2);
	DDX_Control(pDX, IDC_RADIO3, m_radio3);
	DDX_Control(pDX, IDC_RADIO_PUSHLIKE1, m_radioPushlike1);
	DDX_Control(pDX, IDC_RADIO_PUSHLIKE2, m_radioPushlike2);
	DDX_Control(pDX, IDC_RADIO_PUSHLIKE3, m_radioPushlike3);
	DDX_Control(pDX, IDC_COMBO_SIMPLE, m_comboSimple);
	DDX_Control(pDX, IDC_COMBO_DROPDOWNLIST, m_comboDropdownlist);
	DDX_Control(pDX, IDC_COMBO_DROPDOWN, m_comboDropdown);
	DDX_Control(pDX, IDC_CHECK_RIGHT, m_btnCheckRight);
	DDX_Control(pDX, IDC_CHECK_PUSHLIKE, m_btnCheckPushlike);
	DDX_Control(pDX, IDC_CHECK_LEFT, m_btnCheckLeft);
	DDX_Control(pDX, IDC_CHECK_DISABLE_ALL, m_btnDisable);
	DDX_Control(pDX, IDC_BUTTON_PUSH1, m_btnPush1);
	DDX_Control(pDX, IDC_BUTTON_DEFAULT, m_btnDefault);
	DDX_Check(pDX, IDC_CHECK_DISABLE_ALL, m_bDisable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyPageButtonComboBox, CPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPageButtonComboBox)
	ON_BN_CLICKED(IDC_CHECK_DISABLE_ALL, OnCheckDisableAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageButtonComboBox message handlers

void CPropertyPageButtonComboBox::OnCheckDisableAll() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();

	CWnd* pChildWnd=GetWindow(GW_CHILD);
	while(pChildWnd!=NULL)
	{
		if(pChildWnd!=&m_btnDisable)
			pChildWnd->EnableWindow(!m_bDisable);
		pChildWnd=pChildWnd->GetWindow(GW_HWNDNEXT);
	}
}

BOOL CPropertyPageButtonComboBox::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);

	m_comboDropdown.SetCurSel(0);
	m_comboDropdownlist.SetCurSel(0);
	m_comboSimple.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
