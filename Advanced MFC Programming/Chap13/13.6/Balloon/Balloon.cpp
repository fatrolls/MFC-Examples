#include "stdafx.h"
#include "Balloon.h"
#include "Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CBalloonApp, CWinApp)
	//{{AFX_MSG_MAP(CBalloonApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CBalloonApp::CBalloonApp()
{
}

CBalloonApp theApp;

BOOL CBalloonApp::InitInstance()
{
	CBalloonDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
	return FALSE;
}
