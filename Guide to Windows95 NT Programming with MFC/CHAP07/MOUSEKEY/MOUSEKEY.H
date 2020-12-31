///////////////////////////////////////////////////////////////////
// Module   : MOUSEKEY.H
//
// Purpose  : Application header file for MOUSEKEY.CPP.
///////////////////////////////////////////////////////////////////

#include <afxwin.h>  // MFC core and standard components

///////////////////////////////////////////////////////////////////
// Derive an application class 

class CInputApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance(); 
};

///////////////////////////////////////////////////////////////////
// Derive a frame window class

class CMainWnd : public CFrameWnd
{
public:
   CMainWnd();
   virtual ~CMainWnd();

protected:
   BOOL  m_bLMouseDown;  // Mouse button flag
   int   m_cyPixels;     // Current Y-pixel position for text
   int   m_cyClient;     // Height of the client area
   int   m_cxText;       // Avg width of default text
   int   m_cyText;       // Avg height of default text
   int   m_anTabs[7];    // Array of tab stop values

   // Helper methods
   void ShowKeyInfo(CString str, UINT nChar, UINT nRepCnt, UINT nFlags);
   void ShowLButtonState();

   //
   // Message handlers
   //
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnSize(UINT nType, int cx, int cy);
  
   // Mouse message handlers
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg UINT OnNcHitTest(CPoint point);
   
   // Keyboard message handlers
   afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
   
   DECLARE_MESSAGE_MAP();
};

///////////////////////////////////////////////////////////////////
