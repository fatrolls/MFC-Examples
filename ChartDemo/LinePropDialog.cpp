// LinePropDialog.cpp : implementation file
//

#include "stdafx.h"
#include "chartdemo.h"
#include "LinePropDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinePropDialog dialog


CLinePropDialog::CLinePropDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLinePropDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinePropDialog)
	m_iLineWidth = 0;
	m_iPenStyle = -1;
	//}}AFX_DATA_INIT
}


void CLinePropDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinePropDialog)
	DDX_Text(pDX, IDC_LINEWIDTH_EDIT, m_iLineWidth);
	DDX_CBIndex(pDX, IDC_PENSTYLE_COMBO, m_iPenStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinePropDialog, CDialog)
	//{{AFX_MSG_MAP(CLinePropDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinePropDialog message handlers

BOOL CLinePropDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_iLineWidth = 1;
	m_iPenStyle = 0;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLinePropDialog::OnOK() 
{
	UpdateData(TRUE);
	
	CDialog::OnOK();
}
