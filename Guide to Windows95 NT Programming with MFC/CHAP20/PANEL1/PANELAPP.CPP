///////////////////////////////////////////////////////////////////
// Module   : PANEL1.CPP
//
// Purpose  : A small MFC program to test the CPanel3dCtrl class.
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 05-10-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

#include "panel3d.h"

// Control IDs
#define IDC_PANEL3D1  100
#define IDC_PANEL3D2  101
#define IDC_PANEL3D3  102
#define IDC_PANEL3D4  103

///////////////////////////////////////////////////////////////////
// Derive an application class 

class CPanelApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance(); 
};

///////////////////////////////////////////////////////////////////
// Derive a frame window class

class CMainWnd : public CMainFrame
{
public:
   // Four panel controls
   CPanel3dCtrl  m_Panel3d1;
   CPanel3dCtrl  m_Panel3d2;
   CPanel3dCtrl  m_Panel3d3;
   CPanel3dCtrl  m_Panel3d4;

// Operations
   void CreateChildControls();
};

///////////////////////////////////////////////////////////////////
// CPanelApp::CreateChildControls

void CMainWnd::CreateChildControls()
{
   //
   // Initialize the frame window's four panel controls
   //
   
   // Main Panel
   m_Panel3d1.CreatePanel(this, "Panel 1 - Parent", 
      IDC_PANEL3D1, 
      bsRaised, 10, 10, this->GetClientWidth() - 20, 
      this->GetClientHeight() - 20);

   m_Panel3d1.SetText3dFlag(TRUE);
   m_Panel3d1.SetBevelWidth(5);
   m_Panel3d1.SetTextAlignment(taLeftTop);

   INT nWidth  = m_Panel3d1.GetWidth();
   INT nHeight = m_Panel3d1.GetHeight();
   INT nLeft   = (INT)(nWidth * 0.25);
   nWidth      = (INT)(nWidth * 0.75 - 10);
   nHeight     = (nHeight - 40) / 3;

   // Panel 2
   m_Panel3d2.CreatePanel((CWnd*) &m_Panel3d1, 
      "Panel 2 - Inset, normal text", 
      IDC_PANEL3D2, bsInset, 
      nLeft, 10, nWidth, nHeight);

   m_Panel3d2.SetText3dFlag(FALSE);
   m_Panel3d2.SetTextAlignment(taRightTop);

   INT nTop = m_Panel3d1.GetTop() + m_Panel3d2.GetTop() + nHeight;

  // Panel 3
   m_Panel3d3.CreatePanel((CWnd*) &m_Panel3d1, 
      "Panel 3 - Raised, embossed text", 
      IDC_PANEL3D3, bsRaised, 
      nLeft, nTop, nWidth, nHeight);

   m_Panel3d3.SetText3dFlag(TRUE);
   m_Panel3d3.SetTextAlignment(taCenter);

   nTop = m_Panel3d1.GetTop() + m_Panel3d3.GetTop() + nHeight;
 
   // Panel 4
   m_Panel3d4.CreatePanel((CWnd*) &m_Panel3d1, 
      "Panel 4 - No bevel, border, normal text", 
      IDC_PANEL3D4, bsNone, 
      nLeft, nTop, nWidth, nHeight);

   m_Panel3d4.SetText3dFlag(FALSE);
   m_Panel3d4.SetBorderFlag(TRUE);
   m_Panel3d4.SetTextAlignment(taLeftBottom);
}

///////////////////////////////////////////////////////////////////
// CPanelApp::InitInstance - overrides CWinApp::InitInstance

BOOL CPanelApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   pFrame->Create(0, _T("CPanel3dCtrl Test App"), 
                  WS_POPUPWINDOW | WS_DLGFRAME | WS_CLIPCHILDREN,
                  CRect(0, 0, 640, 480));

   // Set the client area back color and center window
   pFrame->SetClientBackColor(COLOR_3DFACE);
   pFrame->CenterWindow();

   // Create 4 panels
   pFrame->CreateChildControls();

   // Show the frame window maximized
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

   return TRUE;
}

// Declare, create, and run the application
CPanelApp MyApp;

////////////////////////////////////////////////////////////////////
