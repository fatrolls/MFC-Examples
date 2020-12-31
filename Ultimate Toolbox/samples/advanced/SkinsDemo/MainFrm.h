// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__9EA6FFD0_CCDE_464F_A19C_497208BF4ECC__INCLUDED_)
#define AFX_MAINFRM_H__9EA6FFD0_CCDE_464F_A19C_497208BF4ECC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXCoolToolbar.h"
#include "OXFrameWndDock.h"
#include "OXMenuBar.h"
#include "OXSizeDockBar.h"

#include "OXSkinnedComboBox.h"
#include "OXBitmapMenuOrganizer.h"
#include "WorkspaceBar.h"
#include "FoldersBar.h"
#include "OXTabClientWnd.h"
#include "XStatus4.h"
#include "PropertiesBar.h"

// STEP 2 - Derive you main frame window from COXMenuBarFrame<CMDIFrameWnd, COXSizeDockBar>.
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
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
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

	CWorkspaceBar m_WorkspaceBar;
	CFoldersBar m_FoldersBar;
	CPropertiesBar m_PropertiesBar;

	// STEP 4 - Derive or instantiate your toolbars from COXCoolToolBar instead of CToolBar.
	COXCoolToolBar m_wndToolBar;
	COXCoolToolBar m_wndToolBar2;

	// STEP 5 - Add an instance of COXBitmapMenuOrganizer to your main frame class. This will
	//			enable your menus to show bitmaps.
	COXBitmapMenuOrganizer m_BMO;

	// STEP 6 - Add an instance of COXTabClientWnd to your main frame class. This will
	//			enable the MDI tabs.
	COXTabClientWnd m_MTIClientWnd;

	// STEP 7 - Derive or instantiate your status bar from COXStatusBar instead of CStatusBar.
	COXStatusBar m_wndStatusBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChecked();
	afx_msg void OnUpdateChecked(CCmdUI* pCmdUI);
	afx_msg void OnMail();
	afx_msg void OnFilePopupItem1();
	afx_msg void OnClose();
	afx_msg void OnViewFolders();
	afx_msg void OnUpdateViewFolders(CCmdUI* pCmdUI);
	afx_msg void OnViewProperties();
	afx_msg void OnUpdateViewProperties(CCmdUI* pCmdUI);
	afx_msg void OnViewWorkspace();
	afx_msg void OnUpdateViewWorkspace(CCmdUI* pCmdUI);
	//}}AFX_MSG
	void OnToolbar2(UINT nID);
	void OnUpdateToolbar2(CCmdUI* pCmdUI);
	void OnDropDown(NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnSelChangeCombo();
	DECLARE_MESSAGE_MAP()

private:
	void InitToolBar2();
	void InitToolBar();
	BOOL m_bChecked;
	CImageList m_ilToolBar2Normal;
	CImageList m_ilToolBar2Hot;
	CImageList m_ilToolBar2Disabled;

	// Custom buttons for the toolbar
	COXCustomTBComboBox<COXSkinnedComboBox> m_Combo;
	COXCustomTBButtonWnd< COXSkinnedWnd<CEdit> > m_Edit;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__9EA6FFD0_CCDE_464F_A19C_497208BF4ECC__INCLUDED_)
