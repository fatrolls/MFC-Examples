#include "my.h"

CMyWinApp theApp;  // global object

BOOL CMyWinApp::InitInstance()
{
    cout << "CMyWinApp::InitInstance \n";
    m_pMainWnd = new CMyFrameWnd;
    return TRUE;
}

CMyFrameWnd::CMyFrameWnd()
{
    Create();
}

BEGIN_MESSAGE_MAP(CMyWinApp, CWinApp)
ON_COMMAND(CMyWinAppid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
ON_COMMAND(CMyFrameWndid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
ON_COMMAND(CMyDocid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyView, CView)
ON_COMMAND(CMyViewid, 0)
END_MESSAGE_MAP()

void  printlpEntries(AFX_MSGMAP_ENTRY* lpEntry)
{
struct {
  int classid;
  char* classname;
} classinfo[] = {
                    CCmdTargetid ,  "CCmdTarget   ",
                    CWinThreadid ,  "CWinThread   ",
                    CWinAppid    ,  "CWinApp      ",
                    CMyWinAppid  ,  "CMyWinApp    ",
                    CWndid       ,  "CWnd         ",
                    CFrameWndid  ,  "CFrameWnd    ",
                    CMyFrameWndid,  "CMyFrameWnd  ",
                    CViewid      ,  "CView        ",
                    CMyViewid    ,  "CMyView      ",
                    CDocumentid  ,  "CDocument    ",
                    CMyDocid     ,  "CMyDoc       ",
                    0            ,  "             "
                };

    for (int i=0; classinfo[i].classid != 0; i++)
    {
        if (classinfo[i].classid == lpEntry->nID)
        {
            cout << lpEntry->nID << "    ";
            cout << classinfo[i].classname << endl;
            break;
        }
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
    CFrameWnd* pMyFrame = (CFrameWnd*)pApp->m_pMainWnd;
    pMyFrame->m_pViewActive = pMyView;
    pMyView->m_pDocument = pMyDoc;

    // test Message Routing
    cout << endl << "pMyFrame receive WM_CREATE, ";
    cout << "routing path and call stack:" << endl;
    AfxWndProc(0, WM_CREATE, 0, 0, pMyFrame);

    cout << endl << "pMyView receive WM_PAINT, ";
    cout << "routing path and call stack:" << endl;
    AfxWndProc(0, WM_PAINT, 0, 0, pMyView);

    cout << endl << "pMyView receive WM_COMMAND, ";
    cout << "routing path and call stack:" << endl;
    AfxWndProc(0, WM_COMMAND, 0, 0, pMyView);

    cout << endl << "pMyFrame receive WM_COMMAND, ";
    cout << "routing path and call stack:" << endl;
    AfxWndProc(0, WM_COMMAND, 0, 0, pMyFrame);
}
