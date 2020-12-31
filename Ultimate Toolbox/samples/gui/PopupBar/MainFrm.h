// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__95493CE9_F252_11D1_B475_B0D808C10000__INCLUDED_)
#define AFX_MAINFRM_H__95493CE9_F252_11D1_B475_B0D808C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXBitmapMenuOrganizer.h"
#include "OXCoolToolBar.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
protected:

public:
	BOOL m_bModal;

// Operations
public:

	COXCoolToolBar* GetCustomizeToolBar() { return &m_wndToolBarCustomize; }

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
	COXCoolToolBar m_wndToolBarFile;
	COXCoolToolBar m_wndToolBarWindow;
	COXCoolToolBar m_wndToolBarCustomize;

	int m_nFirstBorderStyleImage;

	// to show bitmaps in menu
	// just to make the framework look pretty
	COXBitmapMenuOrganizer Organizer;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateCustomizeButtons(CCmdUI* pCmdUI);
	afx_msg void OnWindowModal();
	afx_msg void OnUpdateWindowModal(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnUpdateViewToolbars(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbars(UINT nID);
	afx_msg void OnDropDownFileOpen(NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropDownCustomizeToolbar(NMHDR* pNotifyStruct, LRESULT* pResult);
#if _MFC_VER>=0x0420
	// reflect custom draw notification
	afx_msg void OnCustomDraw(NMHDR* pNotifyStruct, LRESULT* result);
#endif
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__95493CE9_F252_11D1_B475_B0D808C10000__INCLUDED_)
