// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__3987ADCC_E657_11D1_B802_0060084C3BF4__INCLUDED_)
#define AFX_MAINFRM_H__3987ADCC_E657_11D1_B802_0060084C3BF4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ToolBarEx.h"
#include "CoolMenu.h"
#include "SystemTray.h"
#include "CaptionPainterEx.h"
#include "StealthFrame.h"

#define WM_TRAY_ICON_NOTIFY		WM_USER + 0x1000



class CMainFrame : public CStealthFrame
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

protected:  // control bar embedded members
	CStatusBar			m_wndStatusBar;
	CToolBarEx			m_wndToolBar;

	CComboBox			m_wndToolBarCombo;

	CSystemTray			m_ctlTrayIcon;
	CCaptionPainterEx	m_ctlCaptionManager;
	CCoolMenuManager	m_ctlMenuManager;

	CSplitterWnd		m_wndSplitter;
	CSplitterWnd		m_wndSplitterEdit;

public:

// Operations
public:
	CString GetMessageText();
	void AddMessageText();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnUpdateSendButton(CCmdUI* pCmdUI);
	afx_msg void OnSendButton();
	afx_msg void OnToolsPropertiesdialog();
	afx_msg void OnToolsPropertiesSheet();
	//}}AFX_MSG
	afx_msg LRESULT OnTrayNotification(WPARAM wParam = 0,LPARAM lParam = 0);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__3987ADCC_E657_11D1_B802_0060084C3BF4__INCLUDED_)
