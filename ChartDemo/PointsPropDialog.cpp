// PointsPropDialog.cpp : implementation file
//

#include "stdafx.h"
#include "chartdemo.h"
#include "PointsPropDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointsPropDialog dialog


CPointsPropDialog::CPointsPropDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPointsPropDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPointsPropDialog)
	m_iPointsHeight = 0;
	m_iPointsWidth = 0;
	m_iPointsType = -1;
	//}}AFX_DATA_INIT
}


void CPointsPropDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPointsPropDialog)
	DDX_Text(pDX, IDC_POINTHEIGHT_EDIT, m_iPointsHeight);
	DDV_MinMaxInt(pDX, m_iPointsHeight, 0, 20);
	DDX_Text(pDX, IDC_POINTWIDTH_EDIT, m_iPointsWidth);
	DDV_MinMaxInt(pDX, m_iPointsWidth, 0, 20);
	DDX_CBIndex(pDX, IDC_POINTTYPE_COMBO, m_iPointsType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPointsPropDialog, CDialog)
	//{{AFX_MSG_MAP(CPointsPropDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointsPropDialog message handlers

void CPointsPropDialog::OnCancel() 
{
	
}

void CPointsPropDialog::OnOK() 
{
	UpdateData(TRUE);
	
	CDialog::OnOK();
}

BOOL CPointsPropDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_iPointsWidth = m_iPointsHeight = 5;
	m_iPointsType = 0;
	UpdateData(FALSE);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
