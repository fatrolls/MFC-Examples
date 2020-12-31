///////////////////////////////////////////////////////////////////
//  Module   : DLLTEST1.CPP
//
//  Purpose  : Implementation of an application that calls DLLs.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 06-02-96
///////////////////////////////////////////////////////////////////

#include "dlltest1.h"

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_COMMAND(ID_FILE_EXIT, OnFileExit)
   ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
   ON_COMMAND(ID_FILE_CALLSDKDLL, OnFileCallSdkDll)
   ON_COMMAND(ID_FILE_CALLREGULARDLL, OnFileCallRegularDll)
   ON_COMMAND(ID_FILE_CALLEXTENSIONDLL, OnFileCallExtensionDll)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - constructor

CMainWnd::CMainWnd()
{ 
}

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor

CMainWnd::~CMainWnd()
{  
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnFileCallSdkDll()

void CMainWnd::OnFileCallSdkDll() 
{
   LONG      lResult;
   HINSTANCE hModule;
  
   // Create a new function pointer data type
   typedef LONG (MULTIPLY2LONGSPROC)(LONG, LONG);
   
   MULTIPLY2LONGSPROC* pfuncMultiply2Longs = 0;
   
   // Load the DYNLINK1.DLL
   VERIFY(hModule = ::LoadLibrary("dynlink1.dll"));

   // Get the address of the Multiply2Longs() function 
   VERIFY(
      pfuncMultiply2Longs = 
         (MULTIPLY2LONGSPROC*)::GetProcAddress(
            (HMODULE) hModule, "Multiply2Longs")
   );
   
   // Test the DLL's Multiply2Longs() function
   LONG l1 = 10;
   LONG l2 = 20;

   lResult = (*pfuncMultiply2Longs)(l1, l2);

   // Display the result of the test
   CString sMsg;
   sMsg.Format("According to Multiply2Longs: %ld * %ld = %ld", 
               l1, l2, lResult);

   ::MessageBeep(MB_OK);
   MessageBox(sMsg, "Multiply2Longs()", MB_OK | MB_ICONINFORMATION);

   // Unload the library
   FreeLibrary(hModule);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnFileCallRegularDll()

void CMainWnd::OnFileCallRegularDll()
{
   FLOAT f1 = 25.3f; 
   FLOAT f2 = 13.5f;

   FLOAT fResult = Multiply2Floats(f1, f2);

   // Display the result of the test
   CString sMsg;
   sMsg.Format("According to Multiply2Floats: %0.2f * %0.2f = %0.2f",
               f1, f2, fResult);

   ::MessageBeep(MB_OK);
   MessageBox(sMsg, "Multiply2Floats()", MB_OK | MB_ICONINFORMATION);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnFileCallExtensionDll()

void CMainWnd::OnFileCallExtensionDll() 
{
   CDllDialog dll;  // This class declared in DYNLINK3.DLL
   dll.DoModal();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnFileExit()

void CMainWnd::OnFileExit() 
{
   DestroyWindow();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnHelpAbout()

void CMainWnd::OnHelpAbout() 
{
   CAboutDlg dlgAbout;
   dlgAbout.DoModal();
}

///////////////////////////////////////////////////////////////////
// CMyApp::InitInstance - overrides virtual CWinApp::InitInstance

BOOL CMyApp::InitInstance()
{
	// Allocate a new frame window object
	CMainWnd* pFrame = new CMainWnd;

	// Initialize the frame window
   pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW, 
      (CMainWnd*)this);

	// Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

   // Show the frame window, centered
   pFrame->CenterWindow();
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   return TRUE;
}

///////////////////////////////////////////////////////////////////
// Declare, create, and run the application

CMyApp MyApp;

///////////////////////////////////////////////////////////////////
