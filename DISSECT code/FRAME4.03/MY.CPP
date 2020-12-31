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

IMPLEMENT_DYNAMIC(CMyFrameWnd, CFrameWnd)
IMPLEMENT_DYNAMIC(CMyDoc, CDocument)
IMPLEMENT_DYNAMIC(CMyView, CView)

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

CMyDoc* pMyDoc = new CMyDoc;
CMyView* pMyView = new CMyView;
CWnd* pMyWnd = pApp->m_pMainWnd;

cout << "pMyDoc->IsKindOf(RUNTIME_CLASS(CMyDoc))     " << pMyDoc->IsKindOf(RUNTIME_CLASS(CMyDoc))       << "\n";
cout << "pMyDoc->IsKindOf(RUNTIME_CLASS(CDocument))  " << pMyDoc->IsKindOf(RUNTIME_CLASS(CDocument))    << "\n";
cout << "pMyDoc->IsKindOf(RUNTIME_CLASS(CCmdTarget)) " << pMyDoc->IsKindOf(RUNTIME_CLASS(CCmdTarget))   << "\n";
cout << "pMyDoc->IsKindOf(RUNTIME_CLASS(CObject))    " << pMyDoc->IsKindOf(RUNTIME_CLASS(CObject))      << "\n";
cout << "pMyDoc->IsKindOf(RUNTIME_CLASS(CWinApp))    " << pMyDoc->IsKindOf(RUNTIME_CLASS(CWinApp))      << "\n";
cout << "pMyDoc->IsKindOf(RUNTIME_CLASS(CView))      " << pMyDoc->IsKindOf(RUNTIME_CLASS(CView))        << "\n";

cout << "pMyView->IsKindOf(RUNTIME_CLASS(CView))     " << pMyView->IsKindOf(RUNTIME_CLASS(CView))       << "\n";
cout << "pMyView->IsKindOf(RUNTIME_CLASS(CObject))   " << pMyView->IsKindOf(RUNTIME_CLASS(CObject))     << "\n";
cout << "pMyView->IsKindOf(RUNTIME_CLASS(CWnd))      " << pMyView->IsKindOf(RUNTIME_CLASS(CWnd))        << "\n";
cout << "pMyView->IsKindOf(RUNTIME_CLASS(CFrameWnd)) " << pMyView->IsKindOf(RUNTIME_CLASS(CFrameWnd))   << "\n";

cout << "pMyWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd))  " << pMyWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd))    << "\n";
cout << "pMyWnd->IsKindOf(RUNTIME_CLASS(CWnd))       " << pMyWnd->IsKindOf(RUNTIME_CLASS(CWnd))         << "\n";
cout << "pMyWnd->IsKindOf(RUNTIME_CLASS(CObject))    " << pMyWnd->IsKindOf(RUNTIME_CLASS(CObject))      << "\n";
cout << "pMyWnd->IsKindOf(RUNTIME_CLASS(CDocument))  " << pMyWnd->IsKindOf(RUNTIME_CLASS(CDocument))    << "\n";

}
//------------------------------------------------------------------

