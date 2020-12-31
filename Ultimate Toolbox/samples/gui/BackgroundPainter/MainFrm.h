// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__24987B1B_8DEB_11D2_A792_525400DAF3CE__INCLUDED_)
#define AFX_MAINFRM_H__24987B1B_8DEB_11D2_A792_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXBitmapMenuOrganizer.h"
#include "OXTabClientWnd.h"
#include "OXMenuBar.h"
#include "OXBackgroundPainter.h"

class CMainFrame : public COXMenuBarFrame<CMDIFrameWnd,CDockBar>
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

protected:
	// to show bitmaps in menu
	// just to make the framework look pretty
	COXBitmapMenuOrganizer Organizer;

	// MTI client window
	COXTabClientWnd m_MTIClientWnd;

	// background painter organizer
	COXBackgroundPainterOrganizer m_backPainterOrganizer;

// Operations
public:

	inline COXBackgroundPainterOrganizer* GetPainter() {
		return &m_backPainterOrganizer; 
	}

	virtual void EnableDocking(DWORD dwDockStyle);

protected:
	virtual BOOL OnCreateMenuBar(HMENU hMenu, CFrameWnd* pFrameWnd, 
		DWORD dwStyle, UINT nID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	COXCoolToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewTestdialog();
	afx_msg void OnViewLogodlg();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__24987B1B_8DEB_11D2_A792_525400DAF3CE__INCLUDED_)
