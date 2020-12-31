///////////////////////////////////////////////////////////////////
//  Module   : CTRLBAR1.CPP
//
//  Purpose  : Implementation of a minimal program with a toolbar, 
//             status bar, and tool tips.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 06-08-96
///////////////////////////////////////////////////////////////////

#include "ctrlbar1.h"

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_CREATE()                       
   ON_WM_MOUSEMOVE() 
   ON_WM_SIZE()
   ON_COMMAND(IDC_TBBUTTON1, OnButton1Click)
   ON_COMMAND(IDC_TBBUTTON2, OnButton2Click)
   ON_COMMAND(IDC_TBBUTTON3, OnButton3Click)
   ON_COMMAND(IDC_TBBUTTON4, OnButton4Click)
   ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify) // Tooltip method
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - constructor

CMainWnd::CMainWnd()
{ 
   for (int i = 0; i < NUM_TBBUTTONS; i++)
   {
      // Initialize common TBBUTTON structure members
      m_atbb[i].iBitmap = NULL; 
      m_atbb[i].fsState = TBSTATE_ENABLED; 
      m_atbb[i].fsStyle = TBSTYLE_BUTTON; 
      m_atbb[i].dwData  = 0; 
      m_atbb[i].iString = i; 
   }

   // Initialize the command IDs for each
   m_atbb[0].idCommand = IDC_TBBUTTON1;
   m_atbb[1].idCommand = IDC_TBBUTTON2;
   m_atbb[2].idCommand = IDC_TBBUTTON3;
   m_atbb[3].idCommand = IDC_TBBUTTON4;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor

CMainWnd::~CMainWnd()
{  
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnCreate() 

int CMainWnd::OnCreate(LPCREATESTRUCT lpcs)
{
   CFrameWnd::OnCreate(lpcs);

   // Create a status bar with a sizing grip in the corner
   if (!m_ctlStatus.Create(
      WS_CHILD | CCS_BOTTOM | WS_VISIBLE | SBARS_SIZEGRIP, 
      CRect(0, 0, 0, 0), this, IDC_STATUS))
   {
      TRACE0("Failed to create status bar\n");
      return -1;    
   }

   // Create a single status bar pane
   int nRight = -1;
   m_ctlStatus.SetParts(1, &nRight);

   // Create the toolbar
   if (!m_ctlToolBar.Create(
      WS_CHILD | CCS_TOP | TBSTYLE_TOOLTIPS | WS_VISIBLE | WS_BORDER, 
      CRect(0, 0, 0, 0), this, IDC_TOOLBAR))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;    
   }

   // Initialize the toolbar buttons
   LPCTSTR lpszString = "Button1 \0Button2 \0Button3 \0Close \0\0";
   m_ctlToolBar.AddStrings(lpszString);
   m_ctlToolBar.AddButtons(NUM_TBBUTTONS, m_atbb);
   
   // Create the tooltip control
   if (!m_ctlToolTip.Create(this, 
      TTS_ALWAYSTIP | WS_CHILD | WS_VISIBLE))
   {
      TRACE0("Failed to create tool tip control\n");
      return -1;    
   }
   
   // Add status bar string for tooltip
   m_ctlToolTip.AddTool(&m_ctlStatus, "Status Bar");
   
   return 0;
}  

///////////////////////////////////////////////////////////////////
// CMainWnd::OnMouseMove() 

void CMainWnd::OnMouseMove(UINT nFlags, CPoint point)
{
   // Display the current mouse position in the status bar
   CString str;
   str.Format("Cursor Position: %ld, %ld", point.x, point.y);
   m_ctlStatus.SetText((LPCTSTR) str, 0, SBT_NOBORDERS);

   // Show tool tip
   m_ctlToolTip.Activate(TRUE);
   
   // Call the inherited method
   CFrameWnd::OnMouseMove(nFlags, point);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnSize() 

void CMainWnd::OnSize(UINT nType, int cx, int cy)
{
   // Resize the toolbar to parent window
   m_ctlToolBar.AutoSize();
   
   // Resize the status bar to parent window
   CRect rc;
   m_ctlStatus.GetWindowRect(&rc);
   m_ctlStatus.MoveWindow(0, cy - rc.Height(), cx, rc.Height());
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnToolTipNotify() 

BOOL CMainWnd::OnToolTipNotify(UINT id, NMHDR* pNMHDR, 
                               LRESULT* pResult)
{
   // Get a pointer to the TOOLTIPTEXT structure
   TOOLTIPTEXT *pTTT = (TOOLTIPTEXT*) pNMHDR;

   // Get the ID of the control that sent the notification
   UINT nID = pNMHDR->idFrom;

   //
   // See if TTF_IDISHWND is present, which indicates that the
   // uId member is the window handle to the tool. If not, uId
   // is the control ID of the tool...
   //

   if (pTTT->uFlags & TTF_IDISHWND) // ID is hWnd
   {
      // pNMHDR->idFrom is control's HWND; get control's ID
      nID = ::GetDlgCtrlID((HWND)nID);

      if (nID == 0)
         return FALSE;
   }

   //
   // Determine which toolbar button called us here and supply 
   // a text string for the tool tip... 
   //
   
   switch (nID)
   {
      case IDC_TBBUTTON1:
         pTTT->lpszText = "Button 1";
         break;

      case IDC_TBBUTTON2:
         pTTT->lpszText = "Button 2";
         break;

      case IDC_TBBUTTON3:
         pTTT->lpszText = "Button 3";
         break;

      case IDC_TBBUTTON4:
         pTTT->lpszText = "Close";
   }
   return TRUE;
}

///////////////////////////////////////////////////////////////////
// Toolbar Button Handlers

void CMainWnd::OnButton1Click()
   { AfxMessageBox("You clicked Button1!"); }

void CMainWnd::OnButton2Click()
   { AfxMessageBox("You clicked Button2!"); }

void CMainWnd::OnButton3Click()
   { AfxMessageBox("You clicked Button3!"); }

void CMainWnd::OnButton4Click()
   { DestroyWindow(); }

///////////////////////////////////////////////////////////////////
// CMainWnd::PreTranslateMessage()
   
BOOL CMainWnd::PreTranslateMessage(MSG* pMsg)
{
   // Pass message to tooltip control for status bar tip
   m_ctlToolTip.RelayEvent(pMsg);

   // Call inherited handler
   return CFrameWnd::PreTranslateMessage(pMsg);
}

///////////////////////////////////////////////////////////////////
// CMyApp::InitInstance - overrides virtual CWinApp::InitInstance

BOOL CMyApp::InitInstance()
{
	// Allocate a new frame window object
	CMainWnd* pFrame = new CMainWnd;

	// Initialize the frame window
   pFrame->Create(0, _T("Control Bars and Tool Tips"));

	// Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

	// Show the frame window maximized
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   return TRUE;
}

///////////////////////////////////////////////////////////////////
// Declare, create, and run the application

CMyApp MyApp;

///////////////////////////////////////////////////////////////////
