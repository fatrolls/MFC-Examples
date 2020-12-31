// SurfacePropDialog.cpp : implementation file
//

#include "stdafx.h"
#include "chartdemo.h"
#include "SurfacePropDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSurfacePropDialog dialog


CSurfacePropDialog::CSurfacePropDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSurfacePropDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSurfacePropDialog)
	m_iHorizSurf = -1;
	m_FillStyle = -1;
	//}}AFX_DATA_INIT
}


void CSurfacePropDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSurfacePropDialog)
	DDX_Radio(pDX, IDC_HORIZONTAL_RADIO, m_iHorizSurf);
	DDX_CBIndex(pDX, IDC_FILLSTYLE_COMBO, m_FillStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSurfacePropDialog, CDialog)
	//{{AFX_MSG_MAP(CSurfacePropDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSurfacePropDialog message handlers

BOOL CSurfacePropDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_FillStyle = 0;
	m_iHorizSurf = 0;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSurfacePropDialog::OnOK() 
{
	UpdateData(TRUE);	
	CDialog::OnOK();
}
