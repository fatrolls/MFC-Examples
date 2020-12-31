///////////////////////////////////////////////////////////////////
// Header  : MAST.H
//
// Purpose : Header for the MAST application
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 03-05-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

#include "resource.h"  // Resource IDs

///////////////////////////////////////////////////////////////////
// Derive an application class - CMastApp

class CMastApp : public CWinApp
{
public: 
   virtual BOOL InitInstance(); 
};

///////////////////////////////////////////////////////////////////
// Derive a frame window class - CMainWnd

class CMainWnd : public CMainFrame
{
protected:
   CStatusBar*  m_pwndStatusBar;
   CMenu*       m_pmnuContext;
   HICON        m_hIcon;

   //
   // Message handlers
   //
      
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
   
   // Menu items
   afx_msg void OnMenuFileExit();
   afx_msg void OnMenuFileOpen();
   afx_msg void OnMenuFileSave();
   afx_msg void OnMenuFileSaveAs();
   afx_msg void OnMenuHelpAbout();

   // Context menu stuff
   afx_msg void OnMenuContext1();
   afx_msg void OnMenuContext2();
   afx_msg void OnContextMenu();

   // Custom accelerator message
   afx_msg void OnAccelMessage();

   // Helper method to display string resources in a message box
   void ShowOkMessage(DWORD dwStringTableID);

public:
   CMainWnd();           // constructor
   virtual ~CMainWnd();  // destructor

   DECLARE_MESSAGE_MAP();
};
		                      
///////////////////////////////////////////////////////////////////
// CMainWnd inline methods

inline void CMainWnd::OnAccelMessage()
   { ShowOkMessage(ID_MESSAGE1); }

inline void CMainWnd::OnMenuFileOpen()
   { ShowOkMessage(IDS_FILEOPEN); }

inline void CMainWnd::OnMenuFileSave()
   { ShowOkMessage(IDS_FILESAVE); }

inline void CMainWnd::OnMenuFileSaveAs()
   { ShowOkMessage(IDS_FILESAVEAS); }

void CMainWnd::OnMenuContext1()
   { ShowOkMessage(IDS_CONTEXT1); }

inline void CMainWnd::OnMenuContext2()
   { ShowOkMessage(IDS_CONTEXT2); }

///////////////////////////////////////////////////////////////////
