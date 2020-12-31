// RndBtnDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RndBtnDemo.h"
#include "RndBtnDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRndBtnDemoDlg dialog

CRndBtnDemoDlg::CRndBtnDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRndBtnDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRndBtnDemoDlg)
	//}}AFX_DATA_INIT
}

void CRndBtnDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRndBtnDemoDlg)
	DDX_Control(pDX, IDBUTTON1,  m_Button1);
	DDX_Control(pDX, IDBUTTON2,  m_Button2);
	DDX_Control(pDX, IDBUTTON3,  m_Button3);
	DDX_Control(pDX, IDCANCEL,   m_Button5);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRndBtnDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CRndBtnDemoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRndBtnDemoDlg message handlers

BOOL CRndBtnDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE  unless you set the focus to a control
}
