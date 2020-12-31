///////////////////////////////////////////////////////////////////
// Module   : MAST.CPP
//
// Purpose  : Implementation of an MFC program that uses Menu,  
//            keyboard Accelerator, and String Table resources.
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 04-05-96
///////////////////////////////////////////////////////////////////

#include "mast.h"

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_CREATE()
   ON_WM_RBUTTONDOWN()
   
   // Menu items
   ON_COMMAND(ID_FILEEXIT, OnMenuFileExit)
   ON_COMMAND(ID_FILEOPEN, OnMenuFileOpen)
   ON_COMMAND(ID_FILESAVE, OnMenuFileSave)
   ON_COMMAND(ID_FILESAVEAS, OnMenuFileSaveAs)
   ON_COMMAND(ID_HELPABOUT, OnMenuHelpAbout)
   
   // Context menu stuff
   ON_COMMAND(ID_CONTEXTMENU1, OnMenuContext1)
   ON_COMMAND(ID_CONTEXTMENU2, OnMenuContext2)
   ON_COMMAND(IDR_CONTEXTMENU, OnContextMenu)

   // custom accelerator message
   ON_COMMAND(ID_MESSAGE1, OnAccelMessage)
END_MESSAGE_MAP()

static UINT auIndicators[] =
{
   ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - constructor

CMainWnd::CMainWnd()
{
   m_pwndStatusBar = new CStatusBar; ASSERT_VALID(m_pwndStatusBar);
   m_pmnuContext   = new CMenu;      ASSERT_VALID(m_pmnuContext);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor

CMainWnd::~CMainWnd()
{
   if (m_pwndStatusBar) 
      delete m_pwndStatusBar;

   if (m_pmnuContext) 
      delete m_pmnuContext; // DestroyMenu is called by MFC
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnCreate()

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   // Call inherited handler
   if (CMainFrame::OnCreate(lpCreateStruct) == -1)
      return -1;
   
   // Create a status bar
   if (!m_pwndStatusBar->Create(this))
     {
      TRACE0("Failed to create status bar\n");
      return -1;    
   }

   if (!m_pwndStatusBar->SetIndicators(auIndicators,
           sizeof(auIndicators)/sizeof(UINT)))
   {
      TRACE0("Failed to set status bar indicators\n");
      return -1;    
   }

   // Load the context menu
   BOOL bMenuLoaded = m_pmnuContext->LoadMenu(IDR_CONTEXTMENU);
   return bMenuLoaded;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnContextMenu()

void CMainWnd::OnContextMenu()
{
   // Show the context menu with upper-left corner at window center
   CPoint pt;
   pt.x = GetClientWidth() / 2;
   pt.y = GetClientHeight() / 2;
   OnRButtonDown(0, pt);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnRButtonDown()

void CMainWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
   // Convert to local coordinates
   ClientToScreen(&point);

   // Can't use a top level menu for a context menu, so we
   //   must get the first sub menu to use as the context menu
   CMenu* pmnuContext =  m_pmnuContext->GetSubMenu(0);
   
   // Draw the popup context menu, and track it 
   if (pmnuContext)
      pmnuContext->TrackPopupMenu(
         TPM_LEFTALIGN | TPM_RIGHTBUTTON,  // Flags
         point.x, point.y,                 // Position
         this,                             // Owner
         NULL);                            // bounds
   
   // Call inherited method
   CFrameWnd::OnRButtonDown(nFlags, point);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnMenuFileExit()

void CMainWnd::OnMenuFileExit()
{
   DestroyWindow();  // kill the window (and the app)
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnMenuHelpAbout()
                                          
void CMainWnd::OnMenuHelpAbout()
{
   // Display a string table message in a message box
   CString str;
   str.LoadString(IDS_HELPABOUT);
   
   ::MessageBeep(MB_ICONASTERISK);
  
   MessageBox(str, _T("About"), MB_ICONINFORMATION | MB_OK);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::ShowOkMessage()

void CMainWnd::ShowOkMessage(DWORD dwStringTableID)
{
   CString str;
   str.LoadString(dwStringTableID);
   
   // display the resource string inside a message box
   ::MessageBeep(MB_ICONASTERISK); 
   AfxMessageBox(_T(str), MB_ICONINFORMATION | MB_OK);
}

///////////////////////////////////////////////////////////////////
// CMastApp::InitInstance - overrides  CWinApp::InitInstance

BOOL CMastApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   if (!pFrame->LoadFrame(IDR_MAINFRAME))
      return FALSE;

   // Show the frame window maximized
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Declare, create, and run the application

CMastApp MyApp;

/////////////////////////////////////////////////////////////////////////////
