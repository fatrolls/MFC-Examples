// testDlg.cpp : implementation file
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"

typedef DWORD ULONG_PTR;
typedef DWORD DWORD_PTR;
#include "setupapi.h"
#pragma comment(lib, "setupapi")

#define _SYS_GUID_OPERATORS_
#include <initguid.h>
#include "..\sys\guids.h"
#include <winioctl.h>
#include "..\sys\ioctls.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL win98;

///////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
	{							// CTestDlg::CTestDlg
	//{{AFX_DATA_INIT(CTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hInterfaceNotification = NULL;
	m_hHandleNotification = NULL;
	m_hDevice = INVALID_HANDLE_VALUE;

	OSVERSIONINFO vi = {sizeof(OSVERSIONINFO)};
	GetVersionEx(&vi);
	win98 = vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS;
	}							// CTestDlg::CTestDlg

CTestDlg::~CTestDlg()
	{							// CTestDlg::CTestDlg
	if (m_hInterfaceNotification && !win98)
		UnregisterDeviceNotification(m_hInterfaceNotification);
	if (m_hHandleNotification && !win98)
		UnregisterDeviceNotification(m_hHandleNotification);
	if (m_hDevice != INVALID_HANDLE_VALUE)
		CloseHandle(m_hDevice);
	}							// CTestDlg::CTestDlg

void CTestDlg::DoDataExchange(CDataExchange* pDX)
	{							// CTestDlg::DoDataExchange
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Control(pDX, IDB_SENDEVENT, m_ctlSendevent);
	DDX_Control(pDX, IDC_EVENTS, m_ctlEvents);
	//}}AFX_DATA_MAP
	}							// CTestDlg::DoDataExchange

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDB_SENDEVENT, OnSendevent)
	ON_WM_DEVICECHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////

VOID CTestDlg::EnumerateExistingDevices(const GUID* guid)
	{							// CTestDlg::EnumerateExistingDevices
	HDEVINFO info = SetupDiGetClassDevs(guid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
	if (info == INVALID_HANDLE_VALUE)
		return;

	SP_INTERFACE_DEVICE_DATA ifdata;
	ifdata.cbSize = sizeof(ifdata);
	DWORD devindex;
	for (devindex = 0; SetupDiEnumDeviceInterfaces(info, NULL, guid, devindex, &ifdata); ++devindex)
		{						// for each device
		DWORD needed;
		SetupDiGetDeviceInterfaceDetail(info, &ifdata, NULL, 0, &needed, NULL);

		PSP_INTERFACE_DEVICE_DETAIL_DATA detail = (PSP_INTERFACE_DEVICE_DETAIL_DATA) malloc(needed);
		if (!detail)
			continue;
		detail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
		if (!SetupDiGetDeviceInterfaceDetail(info, &ifdata, detail, needed, NULL, NULL))
			{						// can't get detail info
			free((PVOID) detail);
			continue;
			}						// can't get detail info

		CString devname = detail->DevicePath;
		free((PVOID) detail);
		OnNewDevice(devname, guid);
		}						// for each device

	SetupDiDestroyDeviceInfoList(info);
	}							// CTestDlg::EnumerateExistingDevices

///////////////////////////////////////////////////////////////////////////////

BOOL CTestDlg::HandleDeviceChange(DWORD evtype, PDEV_BROADCAST_DEVICEINTERFACE dip)
	{							// CTestDlg::HandleDeviceChange
	CString devname = dip->dbcc_name;

	switch (evtype)
		{						// process device interface notification

	case DBT_DEVICEARRIVAL:
		OnNewDevice(devname, &dip->dbcc_classguid);
		break;

	case DBT_DEVICEREMOVECOMPLETE:
		{						// DBT_DEVICEREMOVECOMPLETE
		CString msg;
		msg.Format(_T("Device %s removed"), (LPCTSTR) devname);
		m_ctlEvents.AddString(msg);
		break;
		}						// DBT_DEVICEREMOVECOMPLETE

		}						// process device interface notification

	return TRUE;
	}							// CTestDlg::HandleDeviceChange

///////////////////////////////////////////////////////////////////////////////


BOOL CTestDlg::HandleDeviceChange(DWORD evtype, PDEV_BROADCAST_HANDLE dhp)
	{							// CTestDlg::HandleDeviceChange

	if (dhp->dbch_handle != m_hDevice)
		return TRUE;			// notification for some other handle

	switch (evtype)
		{						// process handle notification

	case DBT_DEVICEQUERYREMOVE:
		if (MessageBox(_T("Okay to remove the device?"), _T("Removal Query"), MB_YESNO) != IDYES)
			return BROADCAST_QUERY_DENY;

	case DBT_DEVICEREMOVECOMPLETE:
	case DBT_DEVICEREMOVEPENDING:
		MessageBox(_T("Closing Handle"));

		if (m_hHandleNotification && !win98)
			UnregisterDeviceNotification(m_hHandleNotification);
		m_hHandleNotification = NULL;

		if (m_hDevice != INVALID_HANDLE_VALUE)
			CloseHandle(m_hDevice);
		m_hDevice = INVALID_HANDLE_VALUE;
		
		m_ctlSendevent.EnableWindow(FALSE);
		break;
		
		}						// process handle notification

	return TRUE;
	}							// CTestDlg::HandleDeviceChange

///////////////////////////////////////////////////////////////////////////////

BOOL CTestDlg::OnDeviceChange(UINT nEventType, DWORD dwData)
	{							// CTestDlg::OnDeviceChange
	if (!dwData)
		return TRUE;

	_DEV_BROADCAST_HEADER* p = (_DEV_BROADCAST_HEADER*) dwData;

	if (p->dbcd_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
		return HandleDeviceChange(nEventType, (PDEV_BROADCAST_DEVICEINTERFACE) p);
	else if (p->dbcd_devicetype == DBT_DEVTYP_HANDLE)
		return HandleDeviceChange(nEventType, (PDEV_BROADCAST_HANDLE) p);
	else
		return TRUE;
	}							// CTestDlg::OnDeviceChange

///////////////////////////////////////////////////////////////////////////////

BOOL CTestDlg::OnInitDialog()
	{							// CTestDlg::OnInitDialog
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	DEV_BROADCAST_DEVICEINTERFACE filter;
	filter.dbcc_size = sizeof(filter);
	filter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	filter.dbcc_classguid = GUID_INTERFACE_PNPEVENT;
	m_hInterfaceNotification = RegisterDeviceNotification(m_hWnd, &filter, 0);

	EnumerateExistingDevices(&GUID_INTERFACE_PNPEVENT);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
	}							// CTestDlg::OnInitDialog

///////////////////////////////////////////////////////////////////////////////

VOID CTestDlg::OnNewDevice(const CString& devname, const GUID* guid)
	{							// CTestDlg::OnNewDevice
	CString msg;

	if (m_hDevice != INVALID_HANDLE_VALUE)
		{						// only supports 1 instance
		msg.Format(_T("This test program can only handle one instance of PNPEVENT at a time.\n"
			"Therefore, the arrival of a new instance named \n%s is being ignored."),
			(LPCTSTR) devname);
		MessageBox(msg, "Warning", MB_OK | MB_ICONEXCLAMATION);
		return;
		}						// only supports 1 instance

	msg.Format(_T("Device %s arrived"), (LPCTSTR) devname);
	m_ctlEvents.AddString(msg);

	msg = devname;

	msg.SetAt(2, _T('.'));

	m_hDevice = CreateFile(msg, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (m_hDevice == INVALID_HANDLE_VALUE)
		{
		MessageBox("Unable to open handle to device", "Error", MB_OK | MB_ICONHAND);
		return;
		}

	DEV_BROADCAST_HANDLE filter = {0};
	filter.dbch_size = sizeof(filter);
	filter.dbch_devicetype = DBT_DEVTYP_HANDLE;
	filter.dbch_handle = m_hDevice;
	m_hHandleNotification = RegisterDeviceNotification(m_hWnd, &filter, 0);
	
	m_ctlSendevent.EnableWindow(TRUE);
	}							// CTestDlg::OnNewDevice

///////////////////////////////////////////////////////////////////////////////
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint() 
	{							// CTestDlg::OnPaint
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
		CDialog::OnPaint();
	}							// CTestDlg::OnPaint

///////////////////////////////////////////////////////////////////////////////

HCURSOR CTestDlg::OnQueryDragIcon()
	{							// CTestDlg::OnQueryDragIcon
	return (HCURSOR) m_hIcon;
	}							// CTestDlg::OnQueryDragIcon

///////////////////////////////////////////////////////////////////////////////

void CTestDlg::OnSendevent() 
	{							// CTestDlg::OnSendevent
	if (m_hDevice == INVALID_HANDLE_VALUE)
		return;
	DWORD junk;
	DeviceIoControl(m_hDevice, IOCTL_GENERATE_EVENT, NULL, 0, NULL, 0, &junk, NULL);
	}							// CTestDlg::OnSendevent
