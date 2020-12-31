// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__73A06A3D_E209_11D2_A7ED_525400DAF3CE__INCLUDED_)
#define AFX_MAINFRM_H__73A06A3D_E209_11D2_A7ED_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXMenuBar.h"
#include "OXFrameWndDock.h"
#include "OXSizeDockBar.h"
#include "OXCustomizeManager.h"

#include "TabViewBar.h"
#include "3DTabViewBar.h"

#ifdef _MDI_INTERFACE
#define CMainFrameWindow COXMDIFrameWndSizeDock
#else
#define CMainFrameWindow COXFrameWndSizeDock
#endif

#include "OXEdit.h"
#include "..\..\..\INCLUDE\OXRegistryItem.h"	// Added by ClassView


#define ID_CB_EDIT					1000
#define ID_CB_COMBO					1001
#define ID_CB_STATIC				1002
#define ID_CB_BUTTON				1003
#define ID_CB_CHECKBOX				1004
#define ID_CB_COMBOEX				1005
#define ID_CB_IPADDRESS				1006
#define ID_CB_PROGRESS				1007
#define ID_CB_SLIDER				1008
#define ID_CB_DTP					1009
#define ID_CB_RICHEDIT				1010
#define ID_CB_HOTKEY				1011

class CCustomTBExtendedEdit : public COXCustomTBButtonWnd<COXEdit>
{
public:
	virtual COXCustomTBButtonTemplate* CBCreateNewInstance() const;
	virtual void CBCopyContents(COXCustomTBButtonTemplate* pCBTemplate) const;
};


//////////////////////////////////////////////////////////////////////////

class CMainFrame : public COXMenuBarFrame<CMainFrameWindow,COXSizeDockBar>
{
	DECLARE_DYNCREATE(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

	void LoadWorkspace();
	void SaveWorkspace();

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
//	CStandardToolBar    m_wndToolBar;
	COXCoolToolBar    m_wndToolBar;
	COXCoolToolBar    m_wndToolBarWindow;

	CTabViewBar m_tabViewBar;
	C3DTabViewBar m_3DTabViewBar;

	// customize manager
	COXCustomizeManager	m_customizeManager;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnViewCustomize();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
    afx_msg void OnShowControlBars(UINT nID);
	afx_msg void OnUpdateCustomButton(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__73A06A3D_E209_11D2_A7ED_525400DAF3CE__INCLUDED_)
