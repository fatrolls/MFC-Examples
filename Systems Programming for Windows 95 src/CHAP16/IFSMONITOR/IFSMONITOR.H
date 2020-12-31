// IFSMonitor.h -- IFS Monitor application interface
// Copyright (C) 1996 by Walter Oney
// All rights reserved

#ifndef IFSMONITOR_H
#define IFSMONITOR_H

extern CString csprintf(LPCTSTR ctl, ...);

#define COL_FCNNAME		0
#define COL_DRIVE		1
#define COL_RESOURCE	2
#define COL_CODEPAGE	3
#define COL_DATA		4

///////////////////////////////////////////////////////////////////////////////

class CMainFrame;

class CIFSMonitorApp : public CWinApp
{								// CIFSMonitorApp
public:
	CIFSMonitorApp();
	virtual ~CIFSMonitorApp();

	HANDLE		m_vxd;			// VxD device handle

	//{{AFX_VIRTUAL(CIFSMonitorApp)
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
};								// CIFSMonitorApp

///////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CFrameWnd
{								// CMainFrame
public:
	CMainFrame(HANDLE vxd);
	virtual ~CMainFrame();

	CListCtrl			m_ctlList;	// list control that fills our client area
	HANDLE				m_vxd;		// VxD handle
	HANDLE				m_thread;	// handle of monitor thread
	HANDLE				m_evkill;	// event used to kill monitor thread
	int					m_nlog;		// maximum number to record

	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg LRESULT OnRequest(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};								// CMainFrame

#endif // IFSMONITOR_H
