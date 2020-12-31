#include "stdafx.h"
#include "Sender.h"
#include "Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CSenderApp, CWinApp)
	//{{AFX_MSG_MAP(CSenderApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CSenderApp::CSenderApp()
{
}

CSenderApp theApp;

BOOL CSenderApp::InitInstance()
{
#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

	CSenderDlg dlg;
	m_pMainWnd=&dlg;
	int nResponse=dlg.DoModal();
	if(nResponse == IDOK)
	{
	}
	else if(nResponse == IDCANCEL)
	{
	}
	return FALSE;
}
