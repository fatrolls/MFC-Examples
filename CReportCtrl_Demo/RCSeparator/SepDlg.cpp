// SepDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RCSeparator.h"
#include "SepDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSepDlg dialog


CSepDlg::CSepDlg(BOOL bNoSep, LPCTSTR lpSep, CWnd* pParent /*=NULL*/)
	: CDialog(CSepDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSepDlg)
	m_bNoSep = FALSE;
	m_sSep = _T("");
	//}}AFX_DATA_INIT
	m_bNoSep = bNoSep;
	if (!m_bNoSep)
		m_sSep = lpSep;
}


void CSepDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSepDlg)
	DDX_Control(pDX, IDC_EDIT1, m_wndSep);
	DDX_Check(pDX, IDC_CHECK1, m_bNoSep);
	DDX_Text(pDX, IDC_EDIT1, m_sSep);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSepDlg, CDialog)
	//{{AFX_MSG_MAP(CSepDlg)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSepDlg message handlers

BOOL CSepDlg::UseSep() const
{
	return !m_bNoSep;
}

CString CSepDlg::GetSep() const
{
	return m_sSep;
}

BOOL CSepDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_wndSep.EnableWindow(!m_bNoSep);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSepDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_wndSep.EnableWindow(!m_bNoSep);
}
