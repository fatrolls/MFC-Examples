// CustomizeRulersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RulerBar.h"
#include "CustomizeRulersDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeRulersDlg dialog


CCustomizeRulersDlg::CCustomizeRulersDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomizeRulersDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomizeRulersDlg)
	m_bShowHorz = FALSE;
	m_bShowVert = FALSE;
	m_nUnit = -1;
	m_nSize = 0;
	//}}AFX_DATA_INIT
}


void CCustomizeRulersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizeRulersDlg)
	DDX_Check(pDX, IDC_CHECK_HORZ, m_bShowHorz);
	DDX_Check(pDX, IDC_CHECK_VERT, m_bShowVert);
	DDX_CBIndex(pDX, IDC_COMBO_UNIT, m_nUnit);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_nSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizeRulersDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomizeRulersDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeRulersDlg message handlers

BOOL CCustomizeRulersDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
