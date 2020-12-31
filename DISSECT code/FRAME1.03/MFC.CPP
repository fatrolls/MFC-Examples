#include "my.h"  // it should be mfc.h, but for CMyWinApp definition, so...

extern CMyWinApp theApp;

CWinApp* AfxGetApp()
{
  return theApp.m_pCurrentWinApp;
}

