// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "addressbook.h"
#include "OptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog


COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDlg)
	m_sCaption = _T("");
	m_sDest = _T("");
	m_sEntry = _T("");
	m_bChk1 = FALSE;
	m_bChk2 = FALSE;
	m_bChk3 = FALSE;
	//}}AFX_DATA_INIT
	m_bDefault=TRUE;
	m_nSel1=0;
	m_nSel2=0;
	m_nSel3=0;
}


void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDlg)
	DDX_Control(pDX, IDC_EDIT3, m_edt3);
	DDX_Control(pDX, IDC_EDIT2, m_edt2);
	DDX_Control(pDX, IDC_EDIT1, m_edt1);
	DDX_Control(pDX, IDC_COMBO3, m_cmb3);
	DDX_Control(pDX, IDC_COMBO2, m_cmb2);
	DDX_Control(pDX, IDC_COMBO1, m_cmb1);
	DDX_Text(pDX, IDC_EDIT_CAPTION, m_sCaption);
	DDX_Text(pDX, IDC_EDIT_DEST, m_sDest);
	DDX_Text(pDX, IDC_EDIT_ENTRY, m_sEntry);
	DDX_Check(pDX, IDC_CHECK1, m_bChk1);
	DDX_Check(pDX, IDC_CHECK2, m_bChk2);
	DDX_Check(pDX, IDC_CHECK3, m_bChk3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	//{{AFX_MSG_MAP(COptionsDlg)
	ON_BN_CLICKED(IDC_RADIO_DEFAULT, OnRadioDefault)
	ON_BN_CLICKED(IDC_RADIO_CUSTOM, OnRadioCustom)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelchangeCombo3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg message handlers

void COptionsDlg::OnRadioDefault() 
{
	m_bDefault=TRUE;
	UpdateControls();	
}

void COptionsDlg::OnRadioCustom() 
{
	m_bDefault=FALSE;
	UpdateControls();
}

void COptionsDlg::OnCheck1() 
{
	UpdateData();
	if (!m_bChk1)
	{
		m_bChk2=m_bChk3=FALSE;
		UpdateData(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
	}
	UpdateControls();
	
}

void COptionsDlg::OnCheck2() 
{
	UpdateData();
	if (!m_bChk2)
	{
		m_bChk3=FALSE;
		UpdateData(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
	}
	else
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);

	UpdateControls();
	
}

void COptionsDlg::OnCheck3() 
{
	UpdateControls();
	
}

void COptionsDlg::OnSelchangeCombo1() 
{
	//UpdateControls();
	
}

void COptionsDlg::OnSelchangeCombo2() 
{
	//UpdateControls();
	
}

void COptionsDlg::OnSelchangeCombo3() 
{
	//UpdateControls();
	
}

BOOL COptionsDlg::IsFirstEnabled()
{
	UpdateData();
	if (!m_bDefault && m_bChk1)
		return TRUE;
	else
		return FALSE;
}

BOOL COptionsDlg::IsSecondEnabled()
{
	if (!m_bDefault && m_bChk2 && IsFirstEnabled())
		return TRUE;
	else
		return FALSE;


}

BOOL COptionsDlg::IsThirdEnabled()
{
	if (!m_bDefault && m_bChk3 && IsSecondEnabled())
		return TRUE;
	else
		return FALSE;

}


BOOL COptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CButton* pButton;
	if (m_bDefault)
		pButton=(CButton*) GetDlgItem(IDC_RADIO_DEFAULT);
	else
		pButton=(CButton*) GetDlgItem(IDC_RADIO_CUSTOM);
	ASSERT(pButton);
	pButton->SetCheck(1);
	m_cmb1.SetCurSel(0);
	m_cmb2.SetCurSel(0);
	m_cmb3.SetCurSel(0);
	if (m_bChk1)
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
	if (m_bChk2)
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
	m_cmb1.SetCurSel(m_nSel1);
	m_cmb2.SetCurSel(m_nSel2);
	m_cmb3.SetCurSel(m_nSel3);
	m_edt1.SetWindowText((LPCTSTR) m_sEdit1);
	m_edt2.SetWindowText((LPCTSTR) m_sEdit2);
	m_edt3.SetWindowText((LPCTSTR) m_sEdit3);
	
	UpdateControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsDlg::UpdateControls()
{
	UpdateData();
	BOOL bEnable;

	if (IsFirstEnabled())
		bEnable=TRUE;
	else
		bEnable=FALSE;
	m_cmb1.EnableWindow(bEnable);
	m_edt1.EnableWindow(bEnable);

	if (IsSecondEnabled())
		bEnable=TRUE;
	else
		bEnable=FALSE;
	m_cmb2.EnableWindow(bEnable);
	m_edt2.EnableWindow(bEnable);

	if (IsThirdEnabled())
		bEnable=TRUE;
	else
		bEnable=FALSE;
	m_cmb3.EnableWindow(bEnable);
	m_edt3.EnableWindow(bEnable);
	
	
}

void COptionsDlg::OnOK() 
{
	UpdateData(TRUE);
	m_nSel1=m_cmb1.GetCurSel();
	m_nSel2=m_cmb2.GetCurSel();
	m_nSel3=m_cmb3.GetCurSel();
	m_options.ulType1=m_bChk1?(m_bDefault?MAPI_TO:m_nSel1+1):NULL;
	m_options.ulType2=m_bChk2?(m_bDefault?MAPI_CC:m_nSel2+1):NULL;
	m_options.ulType3=m_bChk3?(m_bDefault?MAPI_BCC:m_nSel3+1):NULL;

	
	m_edt1.GetWindowText(m_sEdit1);
	m_edt2.GetWindowText(m_sEdit2);
	m_edt3.GetWindowText(m_sEdit3);
	m_options.sType1=m_sEdit1;
	m_options.sType2=m_sEdit2;
	m_options.sType3=m_sEdit3;
	m_options.sCaption=m_sCaption;
	m_options.sDest=m_sDest;
	m_options.sNewEntry=m_sEntry;

	CDialog::OnOK();
}
