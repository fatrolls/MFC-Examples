// ComboExDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComboExDemo.h"
#include "ComboExDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboExDemoDlg dialog

CComboExDemoDlg::CComboExDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComboExDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComboExDemoDlg)
	//}}AFX_DATA_INIT
}

void CComboExDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComboExDemoDlg)
	DDX_Control(pDX, IDC_COMBO, m_ComboBox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CComboExDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CComboExDemoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboExDemoDlg message handlers

BOOL CComboExDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ComboBox.AddString("Apples");
	m_ComboBox.AddString("bananas");
	m_ComboBox.AddString("oranges");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CComboExDemoDlg::OnOK() 
{
	CString str;
	m_ComboBox.GetWindowText(str);
	AfxMessageBox(str);

	if (m_ComboBox.FindStringExact(-1, str) == CB_ERR)
		m_ComboBox.AddString(str);
}
