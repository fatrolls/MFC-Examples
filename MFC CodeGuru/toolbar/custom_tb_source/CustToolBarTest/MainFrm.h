// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__761D39E0_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_)
#define AFX_MAINFRM_H__761D39E0_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "bcgtoolbar.h"
#include "BCGToolBarImages.h"

class CMainFrame : public CMDIFrameWnd
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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar			m_wndStatusBar;
	CBCGToolBar			m_wndToolBar;
	CBCGToolBar			m_wndUserToolBar;

	CBCGToolBarImages	m_StandardImages;	// Resource images
	CBCGToolBarImages	m_UserImages;		// Disk images

	BOOL				m_bIsTlbCustMode;	// Is toolbar customization mode?

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewUserToobar();
	afx_msg void OnUpdateViewUserToobar(CCmdUI* pCmdUI);
	afx_msg void OnViewCustomize();
	afx_msg void OnClose();
	afx_msg void OnUserConfiguration();
	afx_msg void OnPopupOne();
	afx_msg void OnPopupTwo();
	//}}AFX_MSG
	afx_msg LRESULT OnToolbarContextMenu(WPARAM,LPARAM);
	afx_msg LRESULT OnToolbarCustomize(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__761D39E0_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_)
