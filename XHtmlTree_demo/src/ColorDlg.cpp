// ColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorDlg dialog

BEGIN_MESSAGE_MAP(CColorDlg, CDialog)
	//{{AFX_MSG_MAP(CColorDlg)
	ON_BN_CLICKED(IDC_RESET_COLORS, OnResetColors)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CColorDlg::CColorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorDlg)
	//}}AFX_DATA_INIT
	m_rgbText = GetSysColor(COLOR_WINDOWTEXT);
	m_rgbBackground = GetSysColor(COLOR_WINDOW);
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorDlg)
	DDX_Control(pDX, IDC_TEXT_COLOR, m_btnTextColor);
	DDX_Control(pDX, IDC_BACKGROUND_COLOR, m_btnBackgroundColor);
	//}}AFX_DATA_MAP

	DDX_ColorPicker(pDX, IDC_TEXT_COLOR, m_rgbText);
	DDX_ColorPicker(pDX, IDC_BACKGROUND_COLOR, m_rgbBackground);
}

/////////////////////////////////////////////////////////////////////////////
// CColorDlg message handlers

BOOL CColorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CColorDlg::OnOK() 
{
	UpdateData(TRUE);
	CDialog::OnOK();
}

void CColorDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CColorDlg::OnResetColors() 
{
	m_rgbText = GetSysColor(COLOR_WINDOWTEXT);
	m_rgbBackground = GetSysColor(COLOR_WINDOW);
	UpdateData(FALSE);
}
