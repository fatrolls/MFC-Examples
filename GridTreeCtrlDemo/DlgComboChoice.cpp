/*****************************************************************************
    COPYRIGHT (C) 2000-2001, Ken Bertelson <kbertelson@yahoo.com>


*****************************************************************************/
#include "stdafx.h"
#include "GridTreeCtrlDemo.h"
#include "DlgComboChoice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgComboChoice dialog


CDlgComboChoice::CDlgComboChoice(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgComboChoice::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgComboChoice)
	m_iRadio = 0;
	//}}AFX_DATA_INIT
}


void CDlgComboChoice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgComboChoice)
	DDX_Radio(pDX, IDC_RADIO1, m_iRadio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgComboChoice, CDialog)
	//{{AFX_MSG_MAP(CDlgComboChoice)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgComboChoice message handlers
