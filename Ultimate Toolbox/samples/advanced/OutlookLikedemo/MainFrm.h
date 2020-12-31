// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__DA7AA82C_2C67_11D2_88E3_0080C859A484__INCLUDED_)
#define AFX_MAINFRM_H__DA7AA82C_2C67_11D2_88E3_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXBitmapMenuOrganizer.h"
#include "OXCoolToolBar.h"
#include "OXSkinnedComboBox.h"
#include "OXMenuBar.h"
#include "XStatus4.h"

class CMyToolBar : public COXCoolToolBar
{
public:
	CComboBox m_combo;
	CFont m_font;
};

class CMainFrame : public COXMenuBarFrame<CFrameWnd, COXSizeDockBar>
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

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
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	COXStatusBar  m_wndStatusBar;
	CMyToolBar  m_wndToolBar;

	CSplitterWnd m_wndSplitter1;
	CSplitterWnd m_wndSplitter2;

	COXBitmapMenuOrganizer m_menuOrganizer;

	// Custom buttons for the toolbar
	int m_iCombo;
	COXCustomTBComboBox<COXSkinnedComboBox> m_Combo;

// Generated message map functions
protected:
	afx_msg void OnDropDown(NMHDR* pNotifyStruct, LRESULT* pResult);

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__DA7AA82C_2C67_11D2_88E3_0080C859A484__INCLUDED_)
