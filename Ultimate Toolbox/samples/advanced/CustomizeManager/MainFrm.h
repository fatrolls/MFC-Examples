// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__84AC7585_BE42_4A2A_AE55_76F3BF8B34E6__INCLUDED_)
#define AFX_MAINFRM_H__84AC7585_BE42_4A2A_AE55_76F3BF8B34E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXCustomizeManager.h"
#include "OXCoolToolBar.h"
#include "xstatus4.h"

// STEP 6d: Commands Page - Derive your main frame class from COXMenuBarFrame<...> for the menus
// to be customizable.
class CMainFrame : public COXMenuBarFrame<CMDIFrameWnd, COXSizeDockBar>
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// STEP 1: Add an instance of COXCustomizeManager to you main frame class.
	COXCustomizeManager	m_CM;

protected:  // control bar embedded members

	// STEP 6e, 12c: Commands Page, Toolbars Page - Use an instance of COXCoolToolBar
	// instead of CToolBar.
	COXCoolToolBar m_wndToolBar;
	
	COXStatusBar m_wndStatusBar;
	COXCustomTBComboBox<COXSkinnedComboBox> m_Combo;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitToolBar();

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__84AC7585_BE42_4A2A_AE55_76F3BF8B34E6__INCLUDED_)
