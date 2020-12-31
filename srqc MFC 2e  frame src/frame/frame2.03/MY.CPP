#include "my.h"

CMyWinApp theApp;

BOOL CMyWinApp::InitInstance()
{
    cout << "CMyWinApp::InitInstance \n";
    m_pMainWnd = new CMyFrameWnd;
    return TRUE;
}

CMyFrameWnd::CMyFrameWnd()
{
    cout << "CMyFrameWnd::CMyFrameWnd \n";
    Create();
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
}
//------------------------------------------------------------------

