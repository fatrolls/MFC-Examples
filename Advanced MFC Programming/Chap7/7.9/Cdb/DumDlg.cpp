#include "stdafx.h"
#include "CDB.h"
#include "DumDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MCDummyDlg::MCDummyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MCDummyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MCDummyDlg)
	//}}AFX_DATA_INIT
}


void MCDummyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MCDummyDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MCDummyDlg, CDialog)
	//{{AFX_MSG_MAP(MCDummyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
