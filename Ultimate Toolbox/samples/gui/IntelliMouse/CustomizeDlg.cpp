// CustomizeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "multipad.h"
#include "CustomizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeDlg dialog


CCustomizeDlg::CCustomizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomizeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomizeDlg)
	m_bCustomizable = FALSE;
	m_bFlat = FALSE;
	m_bGripper = FALSE;
	m_bList = FALSE;
	m_bSeparator = FALSE;
	m_bText = FALSE;
	m_nRows = 0;
	m_nWidth = 0;
	m_nToolbar = -1;
	m_nTextType = -1;
	m_nIndent = 0;
	//}}AFX_DATA_INIT
}


void CCustomizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizeDlg)
//	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_RADIO_PLAIN, m_ctlRadioTextType);
	DDX_Control(pDX, IDC_EDIT_WIDTH, m_ctlEditWidth);
	DDX_Control(pDX, IDC_EDIT_ROWS, m_ctlEditRows);
	DDX_Control(pDX, IDC_COMBO_TOOLBAR, m_ctlComboToolbar);
	DDX_Check(pDX, IDC_CHECK_CUSTOMIZABLE, m_bCustomizable);
	DDX_Check(pDX, IDC_CHECK_FLAT, m_bFlat);
	DDX_Check(pDX, IDC_CHECK_GRIPPER, m_bGripper);
	DDX_Check(pDX, IDC_CHECK_LIST, m_bList);
	DDX_Check(pDX, IDC_CHECK_SEPARATOR, m_bSeparator);
	DDX_Check(pDX, IDC_CHECK_TEXT, m_bText);
	DDX_Text(pDX, IDC_EDIT_ROWS, m_nRows);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nWidth);
	DDX_CBIndex(pDX, IDC_COMBO_TOOLBAR, m_nToolbar);
	DDX_Radio(pDX, IDC_RADIO_PLAIN, m_nTextType);
	DDX_Text(pDX, IDC_EDIT_INDENT, m_nIndent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizeDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomizeDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_TOOLBAR, OnSelchangeComboToolbar)
	ON_BN_CLICKED(IDC_CHECK_TEXT, OnCheckText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeDlg message handlers

BOOL CCustomizeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctlComboToolbar.AddString(_T("File"));
	m_ctlComboToolbar.AddString(_T("Edit"));
	m_ctlComboToolbar.AddString(_T("Window"));

	m_nToolbar=0;
	m_nOldToolbar=0;

//	m_ok.SetButtonStyle(m_ok.GetButtonStyle()|BS_BOTTOM);

	GetVars();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomizeDlg::GetVars()
{
	m_bCustomizable=arrCustomize[m_nToolbar].bCustomizable;
	m_bFlat=arrCustomize[m_nToolbar].bFlat;
	m_bGripper=arrCustomize[m_nToolbar].bGripper;
	m_bList=arrCustomize[m_nToolbar].bList;
	m_bSeparator=arrCustomize[m_nToolbar].bSeparator;
	m_bText=arrCustomize[m_nToolbar].bText;
	m_nTextType=arrCustomize[m_nToolbar].nTextType;
	m_nRows=arrCustomize[m_nToolbar].nRows;
	m_nWidth=arrCustomize[m_nToolbar].nWidth;
	m_nIndent=arrCustomize[m_nOldToolbar].nIndent;

	UpdateData(FALSE);

	ShowControls();
}

void CCustomizeDlg::SetVars()
{
	UpdateData();

	arrCustomize[m_nOldToolbar].bCustomizable=m_bCustomizable;
	arrCustomize[m_nOldToolbar].bFlat=m_bFlat;
	arrCustomize[m_nOldToolbar].bGripper=m_bGripper;
	arrCustomize[m_nOldToolbar].bList=m_bList;
	arrCustomize[m_nOldToolbar].bSeparator=m_bSeparator;
	arrCustomize[m_nOldToolbar].bText=m_bText;
	arrCustomize[m_nOldToolbar].nTextType=m_nTextType;
	arrCustomize[m_nOldToolbar].nRows=m_nRows;
	arrCustomize[m_nOldToolbar].nWidth=m_nWidth;
	arrCustomize[m_nOldToolbar].nIndent=m_nIndent;

	m_nOldToolbar=m_nToolbar;

	ShowControls();
}

void CCustomizeDlg::OnOK() 
{
	// TODO: Add extra validation here

	SetVars();
	
	CDialog::OnOK();
}

void CCustomizeDlg::OnSelchangeComboToolbar() 
{
	// TODO: Add your control notification handler code here

	SetVars();
	GetVars();
}

void CCustomizeDlg::OnCheckText() 
{
	// TODO: Add your control notification handler code here

	ShowControls();
}

void CCustomizeDlg::ShowControls() 
{
	UpdateData(TRUE);

	m_ctlEditRows.EnableWindow(m_bText);
	m_ctlEditWidth.EnableWindow(m_bText);
	m_ctlRadioTextType.EnableWindow(m_bText);
	GetDlgItem(IDC_RADIO_TOOLTIP)->EnableWindow(m_bText);
	GetDlgItem(IDC_RADIO_MENU)->EnableWindow(m_bText);

	UpdateData(FALSE);
}

