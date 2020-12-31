
#include "stdafx.h"
#include "FTPexample.h"
#include "FTPexampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CFTPexampleApp theApp;

BEGIN_MESSAGE_MAP(CFTPexampleApp, CWinApp)
   ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CFTPexampleApp::CFTPexampleApp()
{
}

BOOL CFTPexampleApp::InitInstance()
{
   InitCommonControls();

   CWinApp::InitInstance();

   AfxEnableControlContainer();

   VERIFY( AfxInitRichEdit() );

   CFTPexampleDlg dlg;
   m_pMainWnd = &dlg;
   INT_PTR nResponse = dlg.DoModal();
   if (nResponse == IDOK)
   {
   }
   else if (nResponse == IDCANCEL)
   {
   }

   return FALSE;
}
