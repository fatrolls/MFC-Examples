// Test21dDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ex21b.h"
#include "Test21dDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest21dDialog dialog


CTest21dDialog::CTest21dDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTest21dDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTest21dDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nState = OFF;
	Ex21dEntry(); // Make sure DLL gets loaded
}


void CTest21dDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTest21dDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTest21dDialog, CDialog)
	//{{AFX_MSG_MAP(CTest21dDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_CONTROL(0, IDC_RYG, OnClickedRyg) // Notification code is 0
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest21dDialog message handlers

void CTest21dDialog::OnClickedRyg()
{
	switch(m_nState) {
	case OFF:
		m_nState = RED;
		break;
	case RED:
		m_nState = YELLOW;
		break;
	case YELLOW:
		m_nState = GREEN;
		break;
	case GREEN:
		m_nState = OFF;
		break;
	}
	GetDlgItem(IDC_RYG)->SendMessage(RYG_SETSTATE, m_nState);
	return;
}
