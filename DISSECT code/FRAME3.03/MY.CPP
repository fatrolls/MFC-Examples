#include "my.h"

CMyWinApp theApp;

BOOL CMyWinApp::InitInstance()
{
    m_pMainWnd = new CMyFrameWnd;
    return TRUE;
}

CMyFrameWnd::CMyFrameWnd()
{
    Create();
}

void PrintAllClasses()
{
    CRuntimeClass* pClass;

    // just walk through the simple list of registered classes
    for (pClass = CRuntimeClass::pFirstClass; pClass != NULL;
            pClass = pClass->m_pNextClass)
    {
        cout << pClass->m_lpszClassName << "\n";
        cout << pClass->m_nObjectSize << "\n";
        cout << pClass->m_wSchema << "\n";
    }
}
//------------------------------------------------------------------
// main
//------------------------------------------------------------------
void main()
{
  CWinApp* pApp = AfxGetApp();

  pApp->InitApplication();
  pApp->InitInstance();
  pApp->Run();

  PrintAllClasses();
}
//------------------------------------------------------------------

