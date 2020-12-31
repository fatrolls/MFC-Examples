///////////////////////////////////////////////////////////////////
//  Module   : CURVES.CPP
//
//  Purpose  : Implementation of the CURVES program.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 06-20-96
///////////////////////////////////////////////////////////////////

#include "curvthrd.h"
#include "curves.h"

// Global mutex object using default constructor values
CMutex  g_Mutex;       

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor

CMainWnd::~CMainWnd()
{
   if (m_pThread1) delete m_pThread1;
   if (m_pThread2) delete m_pThread2;
   if (m_pThread3) delete m_pThread3;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::StartThreads()

void CMainWnd::StartThreads()
{
   // Get a standard window handle for the child threads to use
   HWND hwnd = GetSafeHwnd();

   //
   // Construct and create 3 additional CCurveThread threads.
   // Random movement for the curves is bounded by the numbers
   // supplied in the constructors below...
   //
   m_pThread1 = new CCurveThread(hwnd, 3);
   m_pThread2 = new CCurveThread(hwnd, 5);
   m_pThread3 = new CCurveThread(hwnd, 7);

   m_pThread1->CreateThread();
   m_pThread2->CreateThread();
   m_pThread3->CreateThread();
}

///////////////////////////////////////////////////////////////////
// CMyApp::InitInstance - overrides CWinApp::InitInstance()

BOOL CMyApp::InitInstance()
{
	// Allocate a new frame window object
	CMainWnd* pFrame = new CMainWnd;

	// Initialize the frame window
   pFrame->Create(0, _T("Multi-Threaded Bezier Curves"),
      WS_OVERLAPPEDWINDOW, CRect(0, 0, 640, 480));

	// Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

	// Show the frame window maximized
   pFrame->SetClientColorRGB(crBlack);
   pFrame->CenterWindow();
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   // Start the curve threads
   pFrame->StartThreads();

   return TRUE;
}

///////////////////////////////////////////////////////////////////
// Declare, create, and run the application

CMyApp MyApp;

///////////////////////////////////////////////////////////////////
