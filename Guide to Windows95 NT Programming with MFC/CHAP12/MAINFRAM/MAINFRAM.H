///////////////////////////////////////////////////////////////////
// Header  : MAINFRAM.H
//
// Purpose : Header for class CMainFrame
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 03-05-96
///////////////////////////////////////////////////////////////////

#ifndef __MAINFRAM_H__
#define __MAINFRAM_H__

#ifndef WS_VISCHILD
   #define WS_VISCHILD (WS_VISIBLE | WS_CHILD)
#endif

#include "stdafx.h"   // Master header for PCH
#include "colors.h"   // Lots of predefined RGB colors

///////////////////////////////////////////////////////////////////
// Class   : CMainFrame
//
// Purpose : An new frame window class derived from CFrameWnd

class CMainFrame : public CFrameWnd
{
   DECLARE_DYNCREATE(CMainFrame)

public:
   // Constructor
   CMainFrame();

   void CenterWindow();
   void CenterWindow(CWnd* pWnd);

protected:
   virtual ~CMainFrame();  // Destructor

   // Operations
   UINT GetClientHeight();
   UINT GetClientWidth();
   CString IntToString(INT nNum);
   void SetWndFont(CWnd* pWnd, CString szFont, LONG lSize);
   void SetChildFonts(INT nFirst, INT nLast,
                      CString szFont, LONG lSize);
   void SetClientColorFlag(BOOL bState);
   void ShowWindowsVerInfo();
   INT StringToInt(CString* psNum);

   // Windows Version method
   DWORD GetWindowsVerInfo(DWORD &dwMajor, 
      DWORD &dwMinor, DWORD &dwBuild);

public:
   // Virtual methods
   virtual void CreateChildControls(); 
   virtual void SetClientBackColor(LONG lColor);
   virtual void SetClientColorRGB(COLORREF cr);

protected:
   CFont*   m_pFont;         // Font for child controls
   LOGFONT  m_lf;            // Logical font
   COLORREF m_crClient;      // RGB color for SetClientColorRGB()
   BOOL     m_bUseClientRGB; // Flag for using RGB client color

   // Message handlers
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);

   DECLARE_MESSAGE_MAP();
};              

inline void CMainFrame::SetClientColorFlag(BOOL bState)
   { m_bUseClientRGB = bState; }

#endif // __MAINFRAM_H__

///////////////////////////////////////////////////////////////////
