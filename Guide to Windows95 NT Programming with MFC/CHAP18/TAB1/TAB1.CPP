///////////////////////////////////////////////////////////////////
// Module   : TAB1.CPP
//
// Purpose  : Shows the use of Tab, Animate, and Rich Edit 
//            controls.
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 06-15-96
///////////////////////////////////////////////////////////////////

#include "tab1.h" 

///////////////////////////////////////////////////////////////////
// CMainWnd Message Map 

BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_CREATE()
   ON_WM_SIZE()
   ON_NOTIFY(TCN_SELCHANGE, IDC_TABCTRL, OnClickTabCtrl)
END_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////
// CMainWnd::CMainFrame() - constructor

CMainWnd::CMainWnd()
{
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
   // Create the tab control
   if (!m_ctlTab.Create(
          WS_CLIPCHILDREN | WS_VISCHILD | TCS_TABS | TCS_SINGLELINE,
          CRect(10, 10, 400, 300), this, IDC_TABCTRL
        )
      )
      TRACE0(_T("Problem creating tab control!"));
 
   // Initialize the TC_ITEM structures
   TC_ITEM tci;
   
   CString str = "Animate";

   tci.mask       = TCIF_TEXT;    
   tci.pszText    = (LPSTR)(LPCTSTR)str;     
   tci.cchTextMax = str.GetLength();    

   // Add this tab to the tab control
   m_ctlTab.InsertItem(0, &tci);
   
   str = "Rich Edit";

   tci.mask       = TCIF_TEXT;    
   tci.pszText    = (LPSTR)(LPCTSTR)str;     
   tci.cchTextMax = str.GetLength();    

   // Add this tab to the tab control
   m_ctlTab.InsertItem(1, &tci);
   
   // Create the animate control
   if (!m_ctlAnim.Create(
           WS_CHILD | WS_VISIBLE | ACS_AUTOPLAY | ACS_CENTER,
           CRect(45, 45, 350, 230), &m_ctlTab, IDC_ANIMCTRL))
   {
      TRACE0(_T("Problem creating animate control!"));
      return FALSE;
   }
   
   // Create the rich edit control
   if (!m_ctlRichEdit.Create(
         WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
         CRect(0, 0, 0, 0), &m_ctlTab, IDC_RICHEDITCTRL))
   {
      TRACE0(_T("Problem creating rich edit control!"));
      return FALSE;
   }
   
   // Start playing the AVI
   if (m_ctlAnim.Open((LPCTSTR)"spintori.avi"))
   {
      m_ctlAnim.ShowWindow(SW_SHOWNORMAL);
      m_ctlAnim.Play(0, (UINT)-1, (UINT)-1);
   }

   // Set options for this rich edit control
   m_ctlRichEdit.SetOptions(ECOOP_SET, ECO_AUTOWORDSELECTION | 
      ECO_AUTOVSCROLL | ECO_WANTRETURN | ECO_SAVESEL);
   
   m_ctlRichEdit.DragAcceptFiles(TRUE);
   GenerateRichText();
 
   // Hide the rich edit control
   m_ctlRichEdit.ShowWindow(SW_HIDE);

   // Call inherited method
   return CFrameWnd::OnCreate(lpcs);       
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnSize()

void CMainWnd::OnSize(UINT nType, int cx, int cy)
{
   // Resize the tab control
   CRect rc(5, 5, cx - 5, cy - 5);
   m_ctlTab.MoveWindow(&rc, TRUE);

   // Get the tab heights
   CRect rcTab;
   m_ctlTab.GetItemRect(0, (LPRECT)&rcTab);
   
   // Resize the animation control
   CRect rcAnim(5, rcTab.bottom + 5, cx - 15, cy - 15);
   m_ctlAnim.MoveWindow(&rcAnim, TRUE);
   
   // Resize the rich edit control
   CRect rcRichEdit(5, rcTab.bottom + 5, cx - 15, cy - 15);
   m_ctlRichEdit.MoveWindow(&rcRichEdit, TRUE);
   m_ctlRichEdit.SetRect(&rcRichEdit);
} 

///////////////////////////////////////////////////////////////////
// CMainWnd::OnClickTabCtrl()

void  CMainWnd::OnClickTabCtrl(NMHDR* pNotifyStruct, 
                               LRESULT* pResult)
{
   // Get the currently active tab
   int nCurTab = m_ctlTab.GetCurSel();

   // Perform some action in response to the tab becoming active
   switch (nCurTab)
   {
      case 0:
         // If an AVI is open, close it
         m_ctlAnim.Close();
         
         // Open and play the AVI
         if (m_ctlAnim.Open((LPCTSTR)"spintori.avi"))
         {
            m_ctlAnim.ShowWindow(SW_SHOWNORMAL);
            m_ctlAnim.Play(0, (UINT)-1, (UINT)-1);
         }
         // Hide the rich edit control
         m_ctlRichEdit.ShowWindow(SW_HIDE);
         break;

      case 1:
         // Show the rich edit control
         m_ctlRichEdit.ShowWindow(SW_SHOWNORMAL);
 
         // Close the AVI and hide the animate control
         m_ctlAnim.Close();
         m_ctlAnim.ShowWindow(SW_HIDE);
   }
   // Set the return code
   *pResult = 0;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::GenerateRichText()

void CMainWnd::GenerateRichText()    // CRichEditCtrl
{
   // Create some text strings
   CString sHeading1 = "Heading 1";
   CString sHeading2 = "Heading 2";
   CString sNormal   = "This is just some normal text.";
   CString sText;

   // Add them to the rich edit control
   sText.Format(sHeading1 + "\r\n" + sHeading2 + "\r\n" + sNormal);
   m_ctlRichEdit.SetWindowText(sText);

   //
   // Format the strings
   //

   CHARFORMAT cf;

   int nStartPos = 0;
   int nEndPos = sHeading1.GetLength();
              
   // Heading 1
   SetStyleHeading1(cf);
   m_ctlRichEdit.SetSel(nStartPos, nEndPos);
   m_ctlRichEdit.SetSelectionCharFormat(cf);
   
   nStartPos = nEndPos;
   nEndPos += sHeading2.GetLength() + 2;

   // Heading 2
   SetStyleHeading2(cf);
   m_ctlRichEdit.SetSel(nStartPos, nEndPos);
   m_ctlRichEdit.SetSelectionCharFormat(cf);
   
   nStartPos = nEndPos;
   nEndPos += sNormal.GetLength() + 2;
   
   // Normal text
   SetStyleNormal(cf);
   m_ctlRichEdit.SetSel(nStartPos, nEndPos);
   m_ctlRichEdit.SetSelectionCharFormat(cf);
   m_ctlRichEdit.HideSelection(TRUE, FALSE);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::SetStyleHeading1()

void CMainWnd::SetStyleHeading1(CHARFORMAT& cf)
{
   cf.cbSize          = sizeof(CHARFORMAT); 
   cf.dwMask          = CFM_COLOR | CFM_FACE | CFM_SIZE | 
                        CFM_ITALIC | CFM_BOLD;
   cf.dwEffects       = CFE_BOLD | CFE_ITALIC; 
   cf.yHeight         = 500; 
   cf.crTextColor     = crRed; 
   cf.bCharSet        = ANSI_CHARSET;
   cf.bPitchAndFamily = FF_ROMAN;
   
   lstrcpy(cf.szFaceName, "Times New Roman"); 
}

///////////////////////////////////////////////////////////////////
// CMainWnd::SetStyleHeading2()

void CMainWnd::SetStyleHeading2(CHARFORMAT& cf)
{
   cf.cbSize          = sizeof(CHARFORMAT);
   cf.dwMask          = CFM_COLOR | CFM_FACE | CFM_SIZE |
                        CFM_ITALIC | CFM_BOLD;
   cf.dwEffects       = CFE_BOLD | CFE_ITALIC; 
   cf.yHeight         = 400; 
   cf.crTextColor     = crBlue; 
   cf.bCharSet        = ANSI_CHARSET;
   cf.bPitchAndFamily = FF_ROMAN;

   lstrcpy(cf.szFaceName, "Times New Roman");
}   

///////////////////////////////////////////////////////////////////
// CMainWnd::SetStyleNormal()

void CMainWnd::SetStyleNormal(CHARFORMAT& cf)
{
   cf.cbSize          = sizeof(CHARFORMAT);
   cf.dwMask          = CFM_COLOR | CFM_FACE | CFM_SIZE;
   cf.yHeight         = 200; 
   cf.crTextColor     = crBlack; 
   cf.bCharSet        = ANSI_CHARSET;
   cf.bPitchAndFamily = FF_SWISS;   

   lstrcpy(cf.szFaceName, "Arial");
}

///////////////////////////////////////////////////////////////////
// CTestApp::InitInstance - overrides CWinApp::InitInstance

BOOL CTestApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   pFrame->Create(0, _T("Tab, Animate, and Rich Edit Controls"), 
                  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                  CRect(0, 0, 640, 480));

   // Set the client area back color
   pFrame->SetClientBackColor(COLOR_3DFACE);
   pFrame->CenterWindow();

   // Show the frame window
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

   return TRUE;
}

///////////////////////////////////////////////////////////////////
// Declare, create, and run the application

CTestApp MyApp;

///////////////////////////////////////////////////////////////////

