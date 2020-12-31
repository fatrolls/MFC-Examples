// PropertyPageEdit.cpp : implementation file
//

#include "stdafx.h"
#include "CoolControls.h"
#include "PropertyPageEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageEdit property page

IMPLEMENT_DYNCREATE(CPropertyPageEdit, CPropertyPage)

CPropertyPageEdit::CPropertyPageEdit() : CPropertyPage(CPropertyPageEdit::IDD)
{
	//{{AFX_DATA_INIT(CPropertyPageEdit)
	m_bDisable = FALSE;
	//}}AFX_DATA_INIT
}

CPropertyPageEdit::~CPropertyPageEdit()
{
}

void CPropertyPageEdit::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyPageEdit)
	DDX_Control(pDX, IDC_HOTKEY, m_hotKey);
	DDX_Control(pDX, IDC_SPIN_UNATTACHED, m_spinUnattached);
	DDX_Control(pDX, IDC_SPIN_RIGHT, m_spinRight);
	DDX_Control(pDX, IDC_SPIN_LEFT, m_spinLeft);
	DDX_Control(pDX, IDC_RICHEDIT_MULTILINE, m_richeditMultiline);
	DDX_Control(pDX, IDC_EDIT_SPIN_UNATTACHED, m_editSpinUnattached);
	DDX_Control(pDX, IDC_EDIT_SPIN_RIGHT, m_editSpinRight);
	DDX_Control(pDX, IDC_EDIT_SPIN_LEFT, m_editSpinLeft);
	DDX_Control(pDX, IDC_EDIT_PLAIN, m_editPlain);
	DDX_Control(pDX, IDC_EDIT_OX, m_editExtended);
	DDX_Control(pDX, IDC_EDIT_NUMERIC, m_editNumeric);
	DDX_Control(pDX, IDC_EDIT_MULTILINE, m_editMultiline);
	DDX_Control(pDX, IDC_EDIT_MASKED, m_editMasked);
	DDX_Control(pDX, IDC_EDIT_CURRENCY, m_editCurrency);
	DDX_Control(pDX, IDC_CHECK_DISABLE_ALL, m_btnDisable);
	DDX_Check(pDX, IDC_CHECK_DISABLE_ALL, m_bDisable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyPageEdit, CPropertyPage)
	//{{AFX_MSG_MAP(CPropertyPageEdit)
	ON_BN_CLICKED(IDC_CHECK_DISABLE_ALL, OnCheckDisableAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageEdit message handlers

BOOL CPropertyPageEdit::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);

	m_richeditMultiline.SetWindowText(_T("Rich edit control\ntext\ntext\ntext\ntext\ntext\ntext\ntext\ntext\ntext\ntext\ntext"));
	m_spinUnattached.SetRange(0,100);
	m_spinRight.SetRange(0,100);
	m_spinLeft.SetRange(0,100);
	m_editPlain.SetWindowText(_T("Edit control"));
	m_editExtended.SetWindowText(_T("Extended edit control"));
	m_editExtended.SetTextColor(RGB(255,255,0));
	m_editExtended.SetBkColor(RGB(0,0,255));
	m_editNumeric.SetTextColor(RGB(0,0,255));
	m_editNumeric.SetMask(_T("Numeric data: #"));
	m_editMultiline.SetWindowText(_T("Multiline edit control"));
	m_editMasked.SetMask(_T("Phone:(###)###-#### Ext:####"));
	m_editCurrency.SetNegativeTextColor(RGB(255,0,0));
	m_editCurrency.SetMask(_T("Currency data: #"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyPageEdit::OnCheckDisableAll() 
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
