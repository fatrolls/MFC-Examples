// Test21cDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ex21b.h"
#include "Test21cDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest21cDialog dialog


CTest21cDialog::CTest21cDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTest21cDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTest21cDialog)
	m_dInput = 0.0;
	m_dOutput = 0.0;
	//}}AFX_DATA_INIT
}


void CTest21cDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTest21cDialog)
	DDX_Text(pDX, IDC_INPUT, m_dInput);
	DDX_Text(pDX, IDC_OUTPUT, m_dOutput);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTest21cDialog, CDialog)
	//{{AFX_MSG_MAP(CTest21cDialog)
	ON_BN_CLICKED(IDC_COMPUTE, OnCompute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest21cDialog message handlers

void CTest21cDialog::OnCompute() 
{
	UpdateData(TRUE);
	m_dOutput = Ex21cSquareRoot(m_dInput);
	UpdateData(FALSE);
}
