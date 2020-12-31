// testDlg.cpp : implementation file
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "Helper.h"

#include <initguid.h>
#include <wdmguid.h>
#include "..\..\pnpevent\sys\guids.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT ThreadProc(CTestDlg* dlg);

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hevent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hevkill = CreateEvent(NULL, FALSE, FALSE, NULL);
}

CTestDlg::~CTestDlg()
	{
	CloseHandle(m_hevent);
	}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Control(pDX, IDC_EVENTS, m_ctlEvents);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(PWM_EVENT, OnEvent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	AfxBeginThread((AFX_THREADPROC) ThreadProc, this);
	theHelper.Register(&GUID_INTERFACE_PNPEVENT, m_hevent);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDlg::OnCancel() 
	{							// CTestDlg::OnCancel
	theHelper.Unregister(&GUID_INTERFACE_PNPEVENT);
	SetEvent(m_hevkill);
	CDialog::OnCancel();
	}							// CTestDlg::OnCancel

LRESULT CTestDlg::OnEvent(WPARAM wParam, LPARAM lParam)
	{							// CTestDlg::OnEvent
	GUID guid;
	GUID event;
	CString linkname;
	DWORD datasize;
	LONG textoffset;
	BYTE data[256];

	while (theHelper.GetEvent(guid, event, linkname, datasize, textoffset, data))
		{						// for each event
		CString evtype;
		typedef enum NFYTYPE {OTHER, INTERFACE, TARGET, CUSTOM};
		enum NFYTYPE nfytype;

		if (event == GUID_DEVICE_INTERFACE_ARRIVAL)
			evtype = _T("Interface Arrival"), nfytype = INTERFACE;
		else if (event == GUID_DEVICE_INTERFACE_REMOVAL)
			evtype = _T("Interface Removal"), nfytype = INTERFACE;
		else if (event == GUID_TARGET_DEVICE_QUERY_REMOVE)
			evtype = _T("Target Query Remove"), nfytype = TARGET;
		else if (event == GUID_TARGET_DEVICE_REMOVE_CANCELLED)
			evtype = _T("Target Remove Cancelled"), nfytype = TARGET;
		else if (event == GUID_TARGET_DEVICE_REMOVE_COMPLETE)
			evtype = _T("Target Remove Complete"), nfytype = TARGET;
		else if (event == GUID_PNPEVENT_EVENT)
			evtype = _T("Custom PNPEVENT Event"), nfytype = CUSTOM;
		else
			evtype = _T("Unknown Event"), nfytype = OTHER;

		CString msg;

		switch (nfytype)
			{					// get notification-dependent data

		case INTERFACE:
			{					// INTERFACE
			CString objtype;
			if (guid == GUID_INTERFACE_PNPEVENT)
				objtype = _T("PNPEVENT Device");
			else
				objtype = _T("Unknown Object");

			msg.Format(_T("%s for %s, %s"), (LPCTSTR) evtype, (LPCTSTR) objtype, (LPCTSTR) linkname);
			}					// INTERFACE

		case TARGET:
			{					// TARGET
			msg.Format(_T("%s for %s"), (LPCTSTR) evtype, (LPCTSTR) linkname);
			break;
			}					// TARGET

		case CUSTOM:
			{					// CUSTOM
			typedef struct _RANDOM_NOTIFICATION {
				DWORD bindata;
				WCHAR text[14];
				} RANDOM_NOTIFICATION, *PRANDOM_NOTIFICATION;
			PRANDOM_NOTIFICATION nfy = (PRANDOM_NOTIFICATION) data;
			CString text = nfy->text;
			msg.Format(_T("%s (%d, %s) for %s\n"), evtype, nfy->bindata, (LPCTSTR) text, (LPCTSTR) linkname);
			break;
			}					// CUSTOM

		default:
			msg = evtype;
			break;
			}					// get notification-dependent data

		m_ctlEvents.AddString(msg);
		}						// for each event

	return 0;
	}							// CTestDlg::OnEvent

///////////////////////////////////////////////////////////////////////////////

UINT ThreadProc(CTestDlg* dlg)
	{							// ThreadProc
	HANDLE events[] = {dlg->m_hevkill, dlg->m_hevent};

	while (TRUE)
		{						// until told to quit
		UINT code = WaitForMultipleObjects(2, events, FALSE, INFINITE);
		if (code != WAIT_OBJECT_0 + 1)
			break;
		dlg->PostMessage(PWM_EVENT);
		}						// until told to quit

	return 0;
	}							// ThreadProc
