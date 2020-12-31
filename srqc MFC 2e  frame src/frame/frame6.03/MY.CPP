#include "my.h"

CMyWinApp theApp;

BOOL CMyWinApp::InitInstance()
{
    m_pMainWnd = new CMyFrameWnd;
    return TRUE;
}

CMyFrameWnd::CMyFrameWnd()
{
    cout << "CMyFrameWnd Constructor \n";
    Create();
}

IMPLEMENT_DYNCREATE(CMyFrameWnd, CFrameWnd)
IMPLEMENT_DYNCREATE(CMyDoc, CDocument)
IMPLEMENT_DYNCREATE(CMyView, CView)

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

  //Test Dynamic Creation
  CRuntimeClass* pClassRef;
  CObject* pOb;
  while(1)
  {
    if ((pClassRef = CRuntimeClass::Load()) == NULL)
        break;

    pOb = pClassRef->CreateObject();
    if (pOb != NULL)
        pOb->SayHello();
  }
}
//------------------------------------------------------------------

