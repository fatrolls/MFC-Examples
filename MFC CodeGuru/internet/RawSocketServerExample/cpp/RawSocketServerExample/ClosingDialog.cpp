// ClosingDialog.cpp : implementation file 
//

#include "stdafx.h"
#include "SocketServer.h"
#include "ClosingDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClosingDialog dialog


CClosingDialog::CClosingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CClosingDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClosingDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CClosingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClosingDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClosingDialog, CDialog)
	//{{AFX_MSG_MAP(CClosingDialog)
	//}}AFX_MSG_MAP
	ON_MESSAGE(FINISHClosingDialog, OnFinishClosingDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClosingDialog message handlers
LONG CClosingDialog::OnFinishClosingDialog (UINT,LONG)
{
	EndDialog(IDOK);
	TRACE(_T("End dialog CClosingDialog\n"));
	return 0;
}

BOOL CClosingDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	TRACE(_T("Init dialog CClosingDialog\n"));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
