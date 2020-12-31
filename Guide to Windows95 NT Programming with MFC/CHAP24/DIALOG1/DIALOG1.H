///////////////////////////////////////////////////////////////////
//  Header  : DIALOG1.H
//
//  Purpose : Header for the DIALOG1 program.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 02-23-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

#include "colors.h"     // Lots of custom COLORREF colors
#include "resource.h"

///////////////////////////////////////////////////////////////////
// Application class 

class CMyApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance();
};

///////////////////////////////////////////////////////////////////
// Frame window class 

class CMainWnd : public CMainFrame
{ 
   DECLARE_DYNCREATE(CMainWnd)

public:
   CMainWnd(); // protected constructor used by dynamic creation
   virtual ~CMainWnd(); // destructor

protected:
   COLORREF             m_crBackColor;
   CStatusBar           m_wndStatusBar;
   CFindReplaceDialog*  m_pdlgFindReplace;   

   void InitFindReplace(BOOL bFind);

   // Message map methods
   afx_msg int OnCreate(LPCREATESTRUCT lpCS);
   afx_msg void OnFileColor();
   afx_msg void OnFileExit();
   afx_msg void OnFileFind();
   afx_msg void OnFileFont();
   afx_msg void OnFileOpen();
   afx_msg void OnFilePrint();
   afx_msg void OnFilePrintSetup();
   afx_msg void OnFileReplace();
   afx_msg void OnFileSaveAs();
   afx_msg void OnFilePageSetup();
   afx_msg void OnHelpAbout();

   // Special registered message handler for find/replace
   afx_msg LONG OnFindReplace(WPARAM wParam, LPARAM lParam);
   
   DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////
