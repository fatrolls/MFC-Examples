#if !defined(AFX_MAINFRM_H__D1C586AA_3E3F_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_MAINFRM_H__D1C586AA_3E3F_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include "ToolBar.h"

#define FRAME_WINDOW			"Frame Window"
#define WINDOW_POSITION			"Window Position"
#define WINDOW_STATUS			"Window Status"
#define SPLITTER_SIZE			"Splitter Window Size"
#define TOOL_BAR				"Tool Bar"
#define WINDOW_STATUS_ICONIC	0
#define WINDOW_STATUS_ZOOMED	1
#define WINDOW_STATUS_NORMAL	2

class CMainFrame : public CFrameWnd
{
protected:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
	CSplitterWnd m_wndSplitter;

public:
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CStatusBar m_wndStatusBar;
	CToolBarEx m_wndToolBar;

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MAINFRM_H__D1C586AA_3E3F_11D1_9C9A_444553540000__INCLUDED_)
