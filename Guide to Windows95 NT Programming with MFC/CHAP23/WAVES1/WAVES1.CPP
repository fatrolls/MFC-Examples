///////////////////////////////////////////////////////////////////
// Module   : WAVES1.CPP
//
// Purpose  : Shows how to use user-defined wave resources 
//            in an MFC program.
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 03-26-96
///////////////////////////////////////////////////////////////////

#include "waves1.h"  // application header

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_CREATE()
   ON_COMMAND(IDC_BTN1, OnBtn1Click)
   ON_COMMAND(IDC_BTN2, OnBtn2Click)
   ON_COMMAND(IDC_BTN3, OnBtn3Click)
   ON_COMMAND(IDC_BTN4, OnBtn4Click)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd()

CMainWnd::CMainWnd()
{
   m_pBtn1 = 0;
   m_pBtn2 = 0;
   m_pBtn3 = 0;
   m_pBtn4 = 0;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd()

CMainWnd::~CMainWnd()
{
   if (m_pBtn1) delete (m_pBtn1);
   if (m_pBtn2) delete (m_pBtn2);
   if (m_pBtn3) delete (m_pBtn3);
   if (m_pBtn4) delete (m_pBtn4);
}

//////////////////////////////////////////////////////////////////
// CMainWnd::OnCreate()

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   // Get the icon handle from the resource data
   m_hIcon = (HICON)::LoadImage(AfxGetApp()->m_hInstance, 
                                MAKEINTRESOURCE(IDR_ICON1),
                                IMAGE_ICON, 32, 32, 
                                LR_DEFAULTCOLOR);

   // make the resource icon the default for the frame window
   if (m_hIcon) 
      ::SetClassLong(GetSafeHwnd(), GCL_HICON, (LONG)m_hIcon);
   
   return 0;
}   

///////////////////////////////////////////////////////////////////
// CMainWnd::CreateChildControls()

void CMainWnd::CreateChildControls()
{
   // Allocate the buttons
   m_pBtn1 = new CButton; ASSERT_VALID(m_pBtn1);
   m_pBtn2 = new CButton; ASSERT_VALID(m_pBtn2);
   m_pBtn3 = new CButton; ASSERT_VALID(m_pBtn3);
   m_pBtn4 = new CButton; ASSERT_VALID(m_pBtn4);
 
   // Initialize the buttons
   if (!m_pBtn1->Create(_T("Wave 1"), BS_PUSH, 
      CRect(10, 10, 75, 35), this, IDC_BTN1))
      { TRACE0(_T("Failed to create Button 1\n")); }

   if (!m_pBtn2->Create(_T("Wave 2"), BS_PUSH, 
      CRect(10, 35, 75, 60), this, IDC_BTN2))
      { TRACE0(_T("Failed to create Button 2\n")); }

   if (!m_pBtn3->Create(_T("Wave 3"), BS_PUSH, 
      CRect(10, 60, 75, 85), this, IDC_BTN3))
      { TRACE0(_T("Failed to create Button 3\n")); }

   if (!m_pBtn4->Create(_T("Wave 4"), BS_PUSH, 
      CRect(10, 85, 75, 110), this, IDC_BTN4))
      { TRACE0(_T("Failed to create Button 4\n")); }

   SetChildFonts(IDC_BTN1, IDC_BTN4, "MS Sans Serif", 9);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::PlayWave()

BOOL CMainWnd::PlayWave(LPCTSTR lpszWave)
{                                           
   HRSRC   hRes;      // resource handle to wave file
   HGLOBAL hglbData;
   
   BOOL bOk = FALSE;
   
   // Find the resource data
   HMODULE hm = AfxGetResourceHandle();
   if ((hRes = ::FindResource(hm, lpszWave, _T("WAVE"))) != 0 &&
       (hglbData = ::LoadResource(hm, hRes)) != 0)
   {
      // Ok, we found the resource, now play it!
      bOk = sndPlaySound((LPCTSTR)::LockResource(hglbData),
                         SND_MEMORY|SND_ASYNC|SND_NODEFAULT);
      
      FreeResource(hglbData);  // Free the resource global handle
   }
   else
      AfxMessageBox(_T("Wave resource not found!"), 
                    MB_ICONEXCLAMATION);

   /*------------------------------------------------------------
   //  Note that all of the above statements could be replaced
   //  with just this one line of code:

   BOOL bOk = ::PlaySound(lpszWave, AfxGetResourceHandle(),
                          SND_RESOURCE|SND_ASYNC|SND_NODEFAULT);
   --------------------------------------------------------------*/
   return bOk;
}

///////////////////////////////////////////////////////////////////
// CWaveApp::InitInstance - overrides CWinApp::InitInstance

BOOL CWaveApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   pFrame->Create(0, _T("User-Defined Resources: Wave Data"),
                        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN);

   // Center the frame window and set the client color
   pFrame->CenterWindow();
   pFrame->SetClientBackColor(COLOR_BTNFACE);
  
   // Create the buttons
   pFrame->CreateChildControls();
   
   // Show the frame window
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

   return TRUE;
}

// Declare, create, and run the application
CWaveApp MyWaveApp;

///////////////////////////////////////////////////////////////////
