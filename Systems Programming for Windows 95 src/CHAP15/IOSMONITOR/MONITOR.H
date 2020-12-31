// Monitor.h -- Interfaces for IOS Monitor Application
// Copyright (C) 1995 by Walter Oney
// All rights reserved

#ifndef MONITOR_H
#define MONITOR_H

#include "resource.h"
#include "RequestLog.h"

typedef pDDB PDDB;

extern CString csprintf(LPCTSTR ctl, ...);
extern CString DriveName(PIOSDCB dcb);

extern CRITICAL_SECTION csLogDevList;

///////////////////////////////////////////////////////////////////////////////

class CMainFrame;

class CMonitorApp : public CWinApp
{								// CMonitorApp
public:
	CMonitorApp();
	virtual ~CMonitorApp();

	HANDLE			m_reqmon;		// REQMON.VXD device handle

	//{{AFX_VIRTUAL(CMonitorApp)
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
};								// CMonitorApp

///////////////////////////////////////////////////////////////////////////////

class CTreePane;
class CDataPane;

class CMainFrame : public CFrameWnd
{								// CMainFrame
public:
	CMainFrame();
	virtual ~CMainFrame();

	CSplitterWnd	m_splitter;		// frame for main window
	CMenu			m_menu;			// application menu
	BOOL			m_changepending; // change in data structures pending
	BOOL			m_monitoring;	// TRUE if monitoring requests
	CRequestLog		m_log;			// request log (modeless dialog)

	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMainFrame)
	afx_msg void OnFileExit();
	afx_msg LRESULT OnDeviceChange(WPARAM wParam, LPARAM lParam);
	afx_msg void OnRequestsMonitor();
	afx_msg void OnRequestsOptions();
	afx_msg void OnUpdateRequestsMonitor(CCmdUI* pCmdUI);
	afx_msg void OnRequestsClearlog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};								// CMainFrame

///////////////////////////////////////////////////////////////////////////////

class CTreePane : public CWnd
{								// CTreePane
	DECLARE_DYNCREATE(CTreePane)
public:
	CTreePane();
	virtual ~CTreePane();

	CTreeCtrl		m_ctlTree;		// the tree control
	HTREEITEM		m_root;			// the root of the tree
	HTREEITEM		m_volumes;		// volumes branch
	HTREEITEM		m_drives;		// physical drives branch
	HTREEITEM		m_drivers;		// device drivers branch

	void			UpdateAll();
	void			UpdateDriverInfo();
	void			AddDriver(_DVT* dvt);
	void			UpdateDriveInfo();
	void			AddDrive(PIOSDCB dcb, HTREEITEM parent);
	void			UpdateVolumeInfo();
	void			AddVolume(PVRP vrp, HTREEITEM parent);
	void			DiscardChildren(HTREEITEM item);

	//{{AFX_VIRTUAL(CTreePane)
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTreePane)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelChanged(NMHDR* nfy, LRESULT* result);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};								// CTreePane

///////////////////////////////////////////////////////////////////////////////

typedef struct {DWORD bit; char *name;} BITNAME;
#define MAKENAME(x,y) x##_##y
#define CATS(x,y) #x"_"#y
#define MAKESTRING(x,y) CATS(x,y)
#define BNTStart(name) static BITNAME name[] = {
#define bn(name) {PFX()##_##name, MAKESTRING(PFX(), name)},
#define BNTEnd() {0, NULL}};

class CDataPane : public CWnd
{								// CDataPane
	DECLARE_DYNCREATE(CDataPane)
public:
	CDataPane();
	virtual ~CDataPane();

	CListCtrl		m_ctlList;		// the list control

	void			ClearContents();
	void			ShowFlags(DWORD flags, const BITNAME* bnp);
	void			AddParameter(const char* name, const CString value);

	//{{AFX_VIRTUAL(CDataPane)
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDataPane)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};								// CDataPane

///////////////////////////////////////////////////////////////////////////////

class CIosObject
{
public:
	CIosObject(){}
	HTREEITEM		m_treeitem;	// item in tree
	void			Add(const CString name, HTREEITEM parent);
	virtual void	Show() = 0;
	void			AddParameter(const char* name, const CString value) const;
	void			ShowFlags(DWORD flags, const BITNAME* bnp) const;
};

class CDriver : public CIosObject
{
public:
	CDriver(_DVT* dvt){m_dvt = dvt;}
	_DVT*			m_dvt;		// DVT for this driver
	virtual void	Show();
};

class CDdb : public CIosObject
{
public:
	CDdb(PDDB ddb){m_ddb = ddb;}
	PDDB			m_ddb;		// DDB for a device
	virtual void	Show();
};

class CDrive : public CIosObject
{
public:
	CDrive(PIOSDCB dcb){m_dcb = dcb;}
	PIOSDCB			m_dcb;		// DCB for this drive
	virtual void	Show();
};

class CIda : public CIosObject
{
public:
	CIda(pIDA ida){m_ida = ida;}
	pIDA			m_ida;		// IOS data area pointer
	virtual void	Show();
};

class CCalldown : public CIosObject
{
public:
	CCalldown(DCB_cd_entry* cdp){m_cdp = cdp;}
	DCB_cd_entry*	m_cdp;		// calldown stack entry
	virtual void	Show();
};

class CVolume : public CIosObject
{
public:
	CVolume(PVRP vrp){m_vrp = vrp;}
	PVRP			m_vrp;		// volume descriptor
	virtual void	Show();
};

#endif
