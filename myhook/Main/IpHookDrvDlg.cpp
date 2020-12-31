// IpHookDrvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "IpHookDrvDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIpHookDrvDlg dialog
IMPLEMENT_DYNCREATE(CIpHookDrvDlg, CRootDlg)

CIpHookDrvDlg::CIpHookDrvDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CIpHookDrvDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIpHookDrvDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CIpHookDrvDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIpHookDrvDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIpHookDrvDlg, CRootDlg)
	//{{AFX_MSG_MAP(CIpHookDrvDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIpHookDrvDlg message handlers

BOOL CIpHookDrvDlg::OnInitDialog() 
{
	
}
