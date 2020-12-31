// IFSMonitor.cpp -- IFS Monitor application
// Copyright (C) 1996 by Walter Oney
// All rights reserved

#include "stdafx.h"
#pragma hdrstop

#include "IFSMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CIFSMonitorApp theApp;
CMainFrame* mainframe;

DWORD __stdcall DoMonitor(CMainFrame* frame);
void WINAPI callback(PMONINFO mip);

///////////////////////////////////////////////////////////////////////////////
// Global helper functions

CString csprintf(LPCTSTR ctl, ...)
	{							// csprintf
	char buffer[256];
	va_list(ap);
	va_start(ap, ctl);
	_vsnprintf(buffer, sizeof(buffer), ctl, ap);
	va_end(ap);
	return buffer;
	}							// csprintf

///////////////////////////////////////////////////////////////////////////////

CIFSMonitorApp::CIFSMonitorApp()
	{							// CIFSMonitorApp::CIFSMonitorApp
	m_vxd = INVALID_HANDLE_VALUE;
	}							// CIFSMonitorApp::CIFSMonitorApp

CIFSMonitorApp::~CIFSMonitorApp()
	{							// CIFSMonitorApp::~CIFSMonitorApp
	if (m_vxd != INVALID_HANDLE_VALUE)
		{						// deregister with our VxD
		DWORD pnull = 0;
		DeviceIoControl(m_vxd, REQMON_SETMONITORADDRESS,
			&pnull, sizeof(pnull), NULL, 0, NULL, NULL);
		CloseHandle(m_vxd);
		}						// deregister with our VxD
	}							// CIFSMonitorApp::~CIFSMonitorApp

BOOL CIFSMonitorApp::InitInstance()
	{							// CIFSMonitorApp::InitInstance
	m_vxd = CreateFile("\\\\.\\MYVXD.VXD", 0, 0, NULL, 0,
		FILE_FLAG_DELETE_ON_CLOSE, NULL);

	if (m_vxd == INVALID_HANDLE_VALUE)
		{						// VxD not loaded
		mainframe->MessageBox("MYVXD.VXD not loaded");
		return FALSE;
		}						// VxD not loaded

	mainframe = new CMainFrame(m_vxd);
	m_pMainWnd = mainframe;
	mainframe->ShowWindow(m_nCmdShow);
	mainframe->UpdateWindow();

	return TRUE;
	}							// CIFSMonitorApp::InitInstance

///////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER+256, OnRequest)
END_MESSAGE_MAP()

CMainFrame::CMainFrame(HANDLE vxd)
	{							// CMainFrame::CMainFrame
	Create(AfxRegisterWndClass(0, theApp.LoadCursor(IDC_ARROW),
		(HBRUSH) GetStockObject(WHITE_BRUSH)),
		"File System Monitor");
	m_vxd = vxd;

//	m_menu.LoadMenu(MAINMENU);
//	SetMenu(&m_menu);

	m_evkill = CreateEvent(NULL, FALSE, FALSE, NULL); // create auto-reset event
	m_nlog = 100;				// default
	m_thread = NULL;
	}							// CMainFrame::CMainFrame

CMainFrame::~CMainFrame()
	{							// CMainFrame::~CMainFrame	
	SetEvent(m_evkill);
	CloseHandle(m_evkill);
	}							// CMainFrame::~CMainFrame

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
	{							// CMainFrame::OnCreateClient

	CRect rc;
	GetClientRect(rc);

	m_ctlList.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_NOSORTHEADER | LVS_SINGLESEL,
		rc, this, 100);

	TEXTMETRIC tm;
	CClientDC dc(this);
	dc.GetTextMetrics(&tm);

	int cx = tm.tmAveCharWidth;
	m_ctlList.InsertColumn(COL_FCNNAME, "Function", LVCFMT_LEFT, 24 * cx, COL_FCNNAME);
	m_ctlList.InsertColumn(COL_DRIVE, "Drive", LVCFMT_LEFT, 8 * cx, COL_DRIVE);
	m_ctlList.InsertColumn(COL_RESOURCE, "ResType", LVCFMT_LEFT, 8 * cx, COL_RESOURCE);
	m_ctlList.InsertColumn(COL_CODEPAGE, "Code Page", LVCFMT_LEFT, 10 * cx, COL_CODEPAGE);
	m_ctlList.InsertColumn(COL_DATA, "Data", LVCFMT_LEFT, 10000, COL_DATA);

	DWORD junk;				// to receive thread id
	m_thread = ::CreateThread(NULL, 4096, (DWORD (__stdcall *)(void *)) DoMonitor, this, 0, &junk);
	return TRUE;
	}							// CMainFrame::OnCreateClient

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
	{							// CMainFrame::OnSize
	CWnd::OnSize(nType, cx, cy);
	m_ctlList.MoveWindow(0, 0, cx, cy);
	}							// CMainFrame::OnSize

LRESULT CMainFrame::OnRequest(WPARAM wParam, LPARAM lParam)
	{						// CMainFrame::OnRequest
	static char* fcnnames[] = {
		"READ",
		"WRITE",
		"FINDNEXT",
		"FCNNEXT",
		NULL, NULL, NULL, NULL, NULL, NULL,
		"SEEK",
		"CLOSE",
		"COMMIT",
		"FILELOCKS",
		"FILETIMES",
		"PIPEREQUEST",
		"HANDLEINFO",
		"ENUMHANDLE",
		"FINDCLOSE",
		"FCNCLOSE",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		"CONNECT",
		"DELETE",
		"DIR",
		"FILEATTRIB",
		"FLUSH",
		"GETDISKINFO",
		"OPEN",
		"RENAME",
		"SEARCH",
		"QUERY",
		"DISCONNECT",
		"UNCPIPEREQ",
		"IOCTL16DRIVE",
		"GETDISKPARMS",
		"FINDOPEN",
		"DASDIO",
		};

	if (m_ctlList.GetItemCount() >= m_nlog)
		m_ctlList.DeleteItem(0);	// make room for new item
	
	PMONINFO mip = (PMONINFO) lParam;

	char *fcnname;
	if (mip->fcn < 0 || mip->fcn >= arraysize(fcnnames) || fcnnames[mip->fcn] == NULL)
		fcnname = "<unknown>";
	else
		fcnname = fcnnames[mip->fcn];
	int row = m_ctlList.InsertItem(m_ctlList.GetItemCount(), fcnname);
	
	m_ctlList.SetItemText(row, COL_DRIVE, csprintf("%c:", mip->drive + ('A' - 1)));
	
	CString restype;
	char *comma = "";
	if (mip->flags & IFSFH_RES_UNC)
		restype += comma, restype += "UNC", comma = ", ";
	if (mip->flags & IFSFH_RES_NETWORK)
		restype += comma, restype += "NET", comma = ", ";
	if (mip->flags & IFSFH_RES_LOCAL)
		restype += comma, restype += "LCL", comma = ", ";
	if (mip->flags & IFSFH_RES_CFSD)
		restype += comma, restype += "CFSD", comma = ", ";
	m_ctlList.SetItemText(row, COL_RESOURCE, restype);

	m_ctlList.SetItemText(row, COL_CODEPAGE, mip->cp == BCS_WANSI ? "ANSI" : "OEM");

	CString data;

	if (mip->path1[0])
		data = mip->path1;
	if (mip->path2[0])
		data += ' ', data += mip->path2;

	switch (mip->fcn)
		{						// develop function-dependent data

	case IFSFN_READ:
		data += csprintf("%X %X bytes at %X into %8.8X", mip->req.ir_sfn, mip->req.ir_length, mip->req.ir_pos, mip->req.ir_data);
		if (mip->req.ir_options & R0_NO_CACHE)
			data += " NO_CACHE";
		if (mip->req.ir_options & R0_SWAPPER_CALL)
			data += " SWAPPER";
		if (mip->req.ir_options & R0_MM_READ_WRITE)
			data += " MM";
		break;

	case IFSFN_WRITE:
		data += csprintf("%X %X bytes at %X from %8.8X", mip->req.ir_sfn, mip->req.ir_length, mip->req.ir_pos, mip->req.ir_data);
		if (mip->req.ir_options & R0_NO_CACHE)
			data += " NO_CACHE";
		if (mip->req.ir_options & R0_SWAPPER_CALL)
			data += " SWAPPER";
		if (mip->req.ir_options & R0_MM_READ_WRITE)
			data += " MM";
		break;

	case IFSFN_FINDNEXT:
		data += csprintf("%8.8X", mip->req.ir_fh);
		break;

	case IFSFN_SEEK:
		{						// IFSFN_SEEK
		static char *methods[] = {"BEGIN", "CURRENT", "END"};
		data += csprintf("%X to %X from %s", mip->req.ir_sfn, mip->req.ir_pos, methods[mip->req.ir_flags]);
		break;
		}						// IFSFN_SEEK

	case IFSFN_CLOSE:
		data += csprintf("%X", mip->req.ir_sfn);
		if (mip->req.ir_options & FILE_NO_LAST_ACCESS_DATE)
			data += " NO_LAST_ACCESS_DATE";
		if (mip->req.ir_options & FILE_CLOSE_FOR_LEVEL4_LOCK)
			data += " CLOSE_FOR_LEVEL4_LOCK";
		break;

	case IFSFN_COMMIT:
		data += csprintf("%X", mip->req.ir_sfn);
		if (mip->req.ir_options & FILE_NO_LAST_ACCESS_DATE)
			data += " NO_LAST_ACCESS_DATE";
		if (mip->req.ir_options & FILE_COMMIT_ASYNC)
			data += " COMMIT_ASNYNC";
		break;

	case IFSFN_FILELOCKS:
		if (mip->req.ir_flags == LOCK_REGION)
			data += "LOCK ";
		else
			data += "UNLOCK ";
		data += csprintf("%X %X at %X", mip->req.ir_sfn, mip->req.ir_locklen, mip->req.ir_pos);
		if (mip->req.ir_options & LOCKF_RD)
			data += " RD";
		if (mip->req.ir_options & LOCKF_NW)
			data += " NW";
		break;

	case IFSFN_FILETIMES:
		{						// IFSFN_FILETIMES
		static char* types[] = {
			"GET_MODIFY_DATETIME",
			"SET_MODIFY_DATETIME",
			"unknown", "unknown", "unknown",
			"GET_LAST_ACCESS_DATETIME",
			"SET_LAST_ACCESS_DATETIME",
			"GET_CREATION_DATETIME",
			"SET_CREATION_DATETIME",
			};
		data += csprintf("%X %s", mip->req.ir_sfn, types[mip->req.ir_flags]);
		break;
		}						// IFSFN_FILETIMES

	case IFSFN_DIR:
		{						// IFSFN_DIR
		static char* types[] = {
			"CREATE_DIR",
			"DELETE_DIR",
			"CHECK_DIR",
			"QUERY83_DIR",
			"QUERYLONG_DIR",
			};
		data += ' ';
		data += types[mip->req.ir_flags];
		if (mip->req.ir_attr & FILE_FLAG_LONG_PATH)
			data += " LONG_PATH";
		if (mip->req.ir_attr & FILE_FLAG_KEEP_CASE)
			data += " KEEP_CASE";
		if (mip->req.ir_attr & FILE_FLAG_HAS_DOT)
			data += " HAS_DOT";
		if (mip->req.ir_attr & FILE_FLAG_IS_LFN)
			data += " IS_LFN";
		break;
		}						// IFSFN_DIR
	
	case IFSFN_FINDCLOSE:
		data += csprintf("%8.8X", mip->req.ir_fh);
		break;

		}						// develop function-dependent data

	m_ctlList.SetItemText(row, COL_DATA, data);
	
	m_ctlList.EnsureVisible(row, FALSE); // partially visible not okay
	
	DeviceIoControl(m_vxd, REQMON_RETURNBLOCK, &lParam, sizeof(lParam),
		NULL, 0, NULL, NULL);
	return 0;
	}						// CMainFrame::OnRequest

DWORD __stdcall DoMonitor(CMainFrame* frame)
	{						// DoMonitor
	mainframe = frame;
	void (WINAPI *acallback)(PMONINFO) = callback;
	if (!DeviceIoControl(frame->m_vxd, REQMON_SETMONITORADDRESS,
		&acallback, sizeof(acallback), NULL, 0, NULL, NULL))
		{					// can't establish callback
		return 1;
		}					// can't establish callback
	while (WaitForSingleObjectEx(frame->m_evkill, INFINITE, TRUE) == WAIT_IO_COMPLETION)
		;					// until told to quit
	acallback = NULL;
	DeviceIoControl(frame->m_vxd, REQMON_SETMONITORADDRESS,
		&acallback, sizeof(acallback), NULL, 0, NULL, NULL);
	frame->m_thread = NULL;	// we're out of here
	return 0;
	}						// DoMonitor

void WINAPI callback(PMONINFO mip)
	{						// callback
	PostMessage(mainframe->m_hWnd, WM_USER+256, 0, (LPARAM) mip);
	}						// callback
