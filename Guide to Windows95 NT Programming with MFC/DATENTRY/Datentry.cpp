#include "stdafx.h"
#include "datentry.h"
#include "dateDlg.h"
#ifndef _WIN32
#include "ctl3d.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CDatentryApp, CWinApp)
  //{{AFX_MSG_MAP(CDatentryApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
  //}}AFX_MSG
  ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


CDatentryApp::CDatentryApp()
{
}


//the one and only app
CDatentryApp theApp;



BOOL CDatentryApp::InitInstance()
{
  #ifdef _WIN32
    Enable3dControls();
  #else
    Ctl3dRegister(AfxGetInstanceHandle());
    Ctl3dAutoSubclass(AfxGetInstanceHandle());
  #endif

  //initialise the DTime package
  InitDTime();
  BOOL bSuccess = InitDTimeSettings();
    
  //Uncomment the following line to try the german version of DTime
  //SetThreadLocale(MAKELCID(MAKELANGID(LANG_GERMAN, SUBLANG_GERMAN), SORT_DEFAULT));
 
  //bring up the dialog to demo DTime data entry
  CDatentryDlg dlg;
  m_pMainWnd = &dlg;
  int nResponse = dlg.DoModal();
  
  return FALSE;
}

int CDatentryApp::ExitInstance()
{
  #ifndef _WIN32
    Ctl3dUnregister(AfxGetInstanceHandle());
  #endif  
          
  //Close our use of the DTime package so 
  //that statics in DTime classes do not appear
  //as memory leaks
  TermDTime();
  
  return CWinApp::ExitInstance();
}


