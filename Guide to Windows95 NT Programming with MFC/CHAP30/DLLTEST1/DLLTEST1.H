///////////////////////////////////////////////////////////////////
//  Header  : DLLTEST1.H
//
//  Purpose : Header for the DLLTEST1 program.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 06-02-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

#include "resource.h"   // Resource IDs
#include "dlldlg.h"     // DYNLINK3.DLL interface

#define DllImport  __declspec(dllimport)

// Import global function from DYNLINK2.DLL
extern "C" DllImport FLOAT Multiply2Floats(FLOAT f1, FLOAT f2);

///////////////////////////////////////////////////////////////////
// Derive an application class 

class CMyApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance();
};

///////////////////////////////////////////////////////////////////
// Derive a frame window class 

class CMainWnd : public CMainFrame
{ 
protected:

public: 
   CMainWnd();
   ~CMainWnd();

   // Message handlers
   afx_msg void OnFileExit();
   afx_msg void OnHelpAbout();
   afx_msg void OnFileCallSdkDll();
   afx_msg void OnFileCallRegularDll();
   afx_msg void OnFileCallExtensionDll();

   DECLARE_MESSAGE_MAP();
};

///////////////////////////////////////////////////////////////////
// CAboutDlg dialog

class CAboutDlg : public CDialog
{
// Construction
public:
   CAboutDlg(CWnd* pParent = NULL);   // standard constructor
   enum { IDD = IDD_ABOUTBOX };
};

// Inline constructor
inline CAboutDlg::CAboutDlg(CWnd* pParent) : 
   CDialog(CAboutDlg::IDD, pParent) { }

///////////////////////////////////////////////////////////////////
