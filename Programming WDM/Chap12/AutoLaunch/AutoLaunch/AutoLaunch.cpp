// AUTOLAUNCH.CPP -- Main program for AUTOLAUNCH service program
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include "resource.h"

#include <initguid.h>
#include "AutoLaunch.h"

#define arraysize(p) (sizeof(p)/sizeof((p)[0]))
void Log(LPCTSTR info);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Note: The real functionality of this module is embodied in the CAutoLaunch
// member functions that appear at the end of this file. The rest is just plumbing

#define SVCNAME AUTOLAUNCH			// name of service in Win2K systems
#define TSVCNAME _T("AUTOLAUNCH")

///////////////////////////////////////////////////////////////////////////////

void Log(LPCTSTR info)
	{							// Log
	CTime time = CTime::GetCurrentTime();
	static CString timeformat;
	if (timeformat.GetLength() == 0)
		timeformat.LoadString(IDS_TIMEFORMAT);

	CString msg;
	msg.Format(TSVCNAME _T(" - %-10s  %s\n"), time.Format(timeformat), info);
	OutputDebugString(msg);
	}							// Log

//=============================================================================
//=============================================================================
//                        W I N 2 K   S E R V I C E
//=============================================================================
//=============================================================================

#ifdef NTSERVICE

#include "service.h"

void RegisterServices();
void UnregisterServices();

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class CAutoLaunch : public CService
{								// class CAutoLaunch
public:
	CAutoLaunch();
	virtual ~CAutoLaunch();

protected:
	HDEVNOTIFY m_hNotification;
	CStringArray m_devices;			// list of devices we've seen arrive

	VOID EnumerateExistingDevices(const GUID* guid);
	virtual DWORD HandleDeviceChange(DWORD evtype, _DEV_BROADCAST_HEADER *dbhdr);
	virtual DWORD InitService(DWORD argc, TCHAR* argv[]);
	VOID OnNewDevice(const CString& devname, HDEVINFO info, PSP_DEVINFO_DATA devdata);
	virtual void ShutdownService();
};								// class CAutoLaunch

CAutoLaunch theService;
DEFINE_SERVICE_EX(DS, theService);

BEGIN_SERVICE_TABLE(svctable)
	DEFINE_SERVICE_TABLE_ENTRY(DS, _T("AutoLaunch Service"))
END_SERVICE_TABLE()

///////////////////////////////////////////////////////////////////////////////

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
	{							// _tmain
	HINSTANCE hInstance = (HINSTANCE) GetModuleHandle(NULL);
	AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	pModuleState->m_hCurrentInstanceHandle = hInstance;
	pModuleState->m_hCurrentResourceHandle = hInstance;

	// Check for registration or unregistration request

	if (argc > 1)
		if (_tcsicmp(argv[1], _T("-register")) == 0)
			{
			RegisterServices();
			return 0;
			}
		else if (_tcsicmp(argv[1], _T("-unregister")) == 0)
			{
			UnregisterServices();
			return 0;
			}
		else
			{
			TRACE(_T("Invalid argument(s) to service main beginning %s\n"), argv[1]);
			return 0;
			}

	StartServiceCtrlDispatcher(svctable);
	return 0;
	}							// _tmain

///////////////////////////////////////////////////////////////////////////////

void RegisterServices()
	{							// RegisterServices
	TCHAR modname[_MAX_PATH];
	if (GetModuleFileName(NULL, modname, arraysize(modname)) == 0)
		{
		TRACE(_T("Error %d in call to GetModuleFileName\n"), GetLastError());
		return;
		}

	TCHAR fname[_MAX_FNAME];
	_tsplitpath(modname, NULL, NULL, fname, NULL);
	
	SC_HANDLE hsc = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hsc)
		{
		TRACE(_T("Error %d in call to OpenSCManager\n"), GetLastError());
		return;
		}

	// Create service entry in the registry:

	SC_HANDLE hservice = CreateService(hsc, fname, svctable[0].lpServiceName,
		SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START,
		SERVICE_ERROR_NORMAL, modname, NULL, NULL, NULL, NULL, NULL);
	ASSERT(hservice);
	CloseServiceHandle(hservice);
	CloseServiceHandle(hsc);
	}							// RegisterServices

///////////////////////////////////////////////////////////////////////////////

void UnregisterServices()
	{							// UnregisterServices
	TCHAR modname[_MAX_PATH];
	if (GetModuleFileName(NULL, modname, arraysize(modname)) == 0)
		{
		TRACE(_T("Error %d in call to GetModuleFileName\n"), GetLastError());
		return;
		}

	TCHAR fname[_MAX_FNAME];
	_tsplitpath(modname, NULL, NULL, fname, NULL);
	
	SC_HANDLE hsc = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hsc)
		{
		TRACE(_T("Error %d in call to OpenSCManager\n"), GetLastError());
		return;
		}

	// Delete service entry in the service database

	SC_HANDLE hservice = OpenService(hsc, fname, SERVICE_ALL_ACCESS);
	ASSERT(hservice);
	DeleteService(hservice);
	CloseServiceHandle(hservice);
	CloseServiceHandle(hsc);
	}							// UnregisterServices

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

CAutoLaunch::CAutoLaunch() : CService(SERVICE_WIN32_OWN_PROCESS, SERVICE_ACCEPT_STOP)
	{							// CAutoLaunch::CAutoLaunch
	m_hNotification = NULL;
	}							// CAutoLaunch::CAutoLaunch

CAutoLaunch::~CAutoLaunch()
	{							// CAutoLaunch::~CAutoLaunch
	if (m_hNotification)
		UnregisterDeviceNotification(m_hNotification);
	}							// CAutoLaunch::~CAutoLaunch

///////////////////////////////////////////////////////////////////////////////

DWORD CAutoLaunch::InitService(DWORD argc, TCHAR* argv[])
	{							// CAutoLaunch::InitService
	Log(_T("Starting service"));

	DEV_BROADCAST_DEVICEINTERFACE filter = {0};
	filter.dbcc_size = sizeof(filter);
	filter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	filter.dbcc_classguid = GUID_AUTOLAUNCH_NOTIFY;
	
	m_hNotification = RegisterDeviceNotification(m_hService, (PVOID) &filter, DEVICE_NOTIFY_SERVICE_HANDLE);
	if (!m_hNotification)
		TRACE(_T("RegisterDeviceNotification failed - %d\n"), GetLastError());

	// Enumerate all existing devices so we honor AutoLaunch requests for devices that started
	// before this service did.

	EnumerateExistingDevices(&GUID_AUTOLAUNCH_NOTIFY);
	
	return 0;
	}							// CAutoLaunch::InitService

///////////////////////////////////////////////////////////////////////////////

void CAutoLaunch::ShutdownService()
	{							// CAutoLaunch::ShutdownService
	Log(_T("Shutting service down"));
	if (m_hNotification)
		UnregisterDeviceNotification(m_hNotification);
	m_hNotification = NULL;
	}							// CAutoLaunch::ShutdownService

#endif // NTSERVICE

//=============================================================================
//=============================================================================
//                         W I N 9 8   A P P L E T
//=============================================================================
//=============================================================================

#ifndef NTSERVICE

#include "ShutdownDlg.h"

class CAutoLaunchApp : public CWinApp
{								// class CAutoLaunchApp
public:
	virtual int ExitInstance();
	virtual BOOL InitInstance();

	HANDLE m_hMutex;			// mutex object for detecting duplicate invocations
};								// class CAutoLaunchApp

CAutoLaunchApp theApp;

///////////////////////////////////////////////////////////////////////////////

class CAutoLaunch : public CWnd
{								// class CAutoLaunch
public:
	CAutoLaunch();
	virtual ~CAutoLaunch();
	VOID EnumerateExistingDevices(const GUID* guid);

protected:
	CShutdownDlg* m_shutdown;		// shutdown dialog
	CStringArray m_devices;			// list of devices we've seen arrive

	void CreateTrayIcon();
	DWORD HandleDeviceChange(DWORD evtype, _DEV_BROADCAST_HEADER *dbhdr);
	VOID OnNewDevice(const CString& devname, HDEVINFO info, PSP_DEVINFO_DATA devdata);

	afx_msg int OnCreate(LPCREATESTRUCT csp);
	afx_msg void OnDestroy();
	afx_msg BOOL OnDeviceChange(UINT evtype, DWORD dwData);
	afx_msg LRESULT OnNotifyIcon(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT id);

	afx_msg void OnMenuClose();
	virtual void PostNcDestroy();

	DECLARE_MESSAGE_MAP()
};								// class CAutoLaunch

#define PWM_NOTIFYICON (WM_USER + 256)

BEGIN_MESSAGE_MAP(CAutoLaunch, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_DEVICECHANGE()
	ON_MESSAGE(PWM_NOTIFYICON, OnNotifyIcon)
	ON_COMMAND(ID_TRAYPOPUP_CLOSE, OnMenuClose)
	ON_WM_TIMER()
END_MESSAGE_MAP()

CAutoLaunch::CAutoLaunch()
	{
	m_shutdown = NULL;
	}

CAutoLaunch::~CAutoLaunch()
	{
	if (m_shutdown)
		delete m_shutdown;
	}

///////////////////////////////////////////////////////////////////////////////

void CAutoLaunch::CreateTrayIcon()
	{							// CAutoLaunch::CreateTrayIcon
	NOTIFYICONDATA nid = {sizeof(NOTIFYICONDATA)};

	nid.hWnd = m_hWnd;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = PWM_NOTIFYICON;
	nid.hIcon = theApp.LoadIcon(IDI_TRAYICON);
	
	CString traytip;
	traytip.LoadString(IDS_TRAYTIP);
	_tcsncpy(nid.szTip, traytip, arraysize(nid.szTip));

	// When we succeed in registering our tray icon, we know the system is up.
	// Enumerate all existing interfaces to their AutoLaunch's happen

	if (Shell_NotifyIcon(NIM_ADD, &nid))
		{						// tray icon visible
		EnumerateExistingDevices(&GUID_AUTOLAUNCH_NOTIFY);
		return;					// geschafft!
		}						// tray icon visible

	// Shell_NotifyIcon will fail if we call it before the user logs in. This shouldn't
	// normally happen because, by the time we reboot after installing a device that
	// uses us, we should be in the Run list in the registry. But just in case it does
	// happen, retry up to 5 times after a 10-second delay each time.

	static int retries = 0;
	if (retries++ > 5)
		{						// can't create tray icon
		TRACE(TSVCNAME _T(" - Shell_NotifyIcon failed - %d\n"), GetLastError());
		DestroyWindow();
		}						// can't create tray icon

	SetTimer(1, 10000, NULL);
	}							// CAutoLaunch::CreateTrayIcon

///////////////////////////////////////////////////////////////////////////////

int CAutoLaunch::OnCreate(LPCREATESTRUCT csp)
	{							// CAutoLaunch::OnCreate
	Log(_T("Starting service"));

	// Register to receive notifications when device drivers enable a GUID_AUTOLAUNCH_NOTIFY
	// interface. Note that we discard the notification handle because we can't unregister
	// it without making Win98 unstable.

	DEV_BROADCAST_DEVICEINTERFACE filter = {0};
	filter.dbcc_size = sizeof(filter);
	filter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	filter.dbcc_classguid = GUID_AUTOLAUNCH_NOTIFY;
	
	HDEVNOTIFY hNotification = RegisterDeviceNotification(m_hWnd, (PVOID) &filter, DEVICE_NOTIFY_WINDOW_HANDLE);
	if (!hNotification)
		{						// can't register for notifications
		TRACE(TSVCNAME _T(" - RegisterDeviceNotification failed - %d\n"), GetLastError());
		return -1;
		}						// can't register for notifications

	// Create a tray icon to give the end user a way to shut this service down

	CreateTrayIcon();

	// Create an initially invisible modeless dialog for asking permission to
	// close the service. If we were just to call MessageBox in the OnMenuClose
	// function, it wouldn't return the first time if we happen to be launched
	// via WinExec from a device driver. The second or third time the user tries to
	// close the service, the call would return to find this object already deleted,
	// and a crash would ensue. This took a while to figure out, I can tell you!

	m_shutdown = new CShutdownDlg(this);

	return 0;
	}							// CAutoLaunch::OnCreate

///////////////////////////////////////////////////////////////////////////////

void CAutoLaunch::OnDestroy()
	{							// CAutoLaunch::OnDestroy
	Log(_T("Shutting service down"));

	NOTIFYICONDATA nid = {sizeof(NOTIFYICONDATA)};
	nid.hWnd = m_hWnd;
	Shell_NotifyIcon(NIM_DELETE, &nid);

	PostQuitMessage(0);
	CWnd::OnDestroy();
	}							// CAutoLaunch::OnDestroy

///////////////////////////////////////////////////////////////////////////////

BOOL CAutoLaunch::OnDeviceChange(UINT evtype, DWORD dwData)
	{							// CAutoLaunch::OnDeviceChange
	HandleDeviceChange(evtype, (_DEV_BROADCAST_HEADER*) dwData);
	return TRUE;
	}							// CAutoLaunch::OnDeviceChange

///////////////////////////////////////////////////////////////////////////////

LRESULT CAutoLaunch::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
	{							// CAutoLaunch::OnNotifyIcon
	if (lParam == WM_RBUTTONDOWN)
		{						// display context menu
		SetForegroundWindow();	// KB Q135788
		CMenu menu;
		menu.LoadMenu(IDR_CONTEXT);

		CMenu* popup = menu.GetSubMenu(0);
		POINT pt;
		UINT flags = TPM_RIGHTBUTTON;
		GetCursorPos(&pt);
		popup->TrackPopupMenu(flags, pt.x, pt.y, this);
		PostMessage(WM_NULL, 0, 0);	// KB Q135788
		}						// display context menu
	return 0;
	}							// CAutoLaunch::OnNotifyIcon

///////////////////////////////////////////////////////////////////////////////

void CAutoLaunch::OnMenuClose()
	{							// CAutoLaunch::OnMenuClose
	m_shutdown->ShowWindow(SW_SHOW);
	}							// CAutoLaunch::OnMenuClose

///////////////////////////////////////////////////////////////////////////////

void CAutoLaunch::OnTimer(UINT id)
	{							// CAutoLaunch::OnTimer
	KillTimer(id);
	CreateTrayIcon();
	}							// CAutoLaunch::OnTimer

///////////////////////////////////////////////////////////////////////////////

void CAutoLaunch::PostNcDestroy()
	{							// CAutoLaunch::PostNcDestroy
	CWnd::PostNcDestroy();
	delete this;
	}							// CAutoLaunch::PostNcDestroy

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BOOL CAutoLaunchApp::InitInstance()
	{							// CAutoLaunchApp::InitInstance

	// Avoid running two instances of this module

	m_hMutex = CreateMutex(NULL, FALSE, _T("AUTOLAUNCH_MUTEX"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		{						// already running
		CloseHandle(m_hMutex);
		return FALSE;
		}						// already running

	// Create an invisible window to receive WM_DEVICECHANGE messages

	CAutoLaunch* dummy = new CAutoLaunch;
	if (!dummy->CreateEx(0, AfxRegisterWndClass(0), _T("Device Driver Service"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL))
		return FALSE;				// give up if can't create window

	m_pMainWnd = dummy;

	return TRUE;
	}							// CAutoLaunchApp::InitInstance

///////////////////////////////////////////////////////////////////////////////

int CAutoLaunchApp::ExitInstance()
	{							// CAutoLaunchApp::ExitInstance
	CloseHandle(m_hMutex);
	return 0;
	}							// CAutoLaunchApp::ExitInstance

#endif // NOT NTSERVICE

//=============================================================================
//=============================================================================
//                  B O T H   C O N F I G U R A T I O N S                   
//=============================================================================
//=============================================================================

VOID CAutoLaunch::EnumerateExistingDevices(const GUID* guid)
	{							// CAutoLaunch::EnumerateExistingDevices
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

		SP_DEVINFO_DATA devdata = {sizeof(SP_DEVINFO_DATA)};

		if (!SetupDiGetDeviceInterfaceDetail(info, &ifdata, detail, needed, NULL, &devdata))
			{						// can't get detail info
			free((PVOID) detail);
			continue;
			}						// can't get detail info

		CString devname = detail->DevicePath;
		free((PVOID) detail);
		OnNewDevice(devname, info, &devdata);
		}						// for each device

	SetupDiDestroyDeviceInfoList(info);
	}							// CAutoLaunch::EnumerateExistingDevices

///////////////////////////////////////////////////////////////////////////////

DWORD CAutoLaunch::HandleDeviceChange(DWORD evtype, _DEV_BROADCAST_HEADER *dbhdr)
	{							// CAutoLaunch::HandleDeviceChange
	if (!dbhdr || dbhdr->dbcd_devicetype != DBT_DEVTYP_DEVICEINTERFACE)
		return 0;				// ignore all other events

	// Extract symbolic link name of the device that's arrived. In NT, the service always
	// receives the UNICODE version of the notification structure

#ifdef NTSERVICE
	PDEV_BROADCAST_DEVICEINTERFACE_W p = (PDEV_BROADCAST_DEVICEINTERFACE_W) dbhdr;
#else
	PDEV_BROADCAST_DEVICEINTERFACE p = (PDEV_BROADCAST_DEVICEINTERFACE) dbhdr;
#endif

	CString devname = p->dbcc_name;

	// If device is departing, remove its name from our list

	if (evtype == DBT_DEVICEREMOVECOMPLETE)
		{						// device removed
		for (int i = 0; i < m_devices.GetSize(); )
			if (devname.CompareNoCase(m_devices[i]) == 0)
				m_devices.RemoveAt(i);
			else
				++i;
		}						// device removed

	// If device is arriving, check for the need to launch a command automatically

	else if (evtype == DBT_DEVICEARRIVAL)
		{						// interface arrival event
		HDEVINFO info = SetupDiCreateDeviceInfoList(NULL, NULL);
		if (info == INVALID_HANDLE_VALUE)
			return 0;
		SP_DEVICE_INTERFACE_DATA ifdata = {sizeof(SP_DEVICE_INTERFACE_DATA)};
		SP_DEVINFO_DATA devdata = {sizeof(SP_DEVINFO_DATA)};

		if (SetupDiOpenDeviceInterface(info, devname, 0, &ifdata)
			&& (SetupDiGetDeviceInterfaceDetail(info, &ifdata, NULL, 0, NULL, &devdata)
			|| GetLastError() == ERROR_INSUFFICIENT_BUFFER))
			OnNewDevice(devname, info, &devdata);

		SetupDiDestroyDeviceInfoList(info);
		}						// interface arrival event

	return 0;
	}							// CAutoLaunch::HandleDeviceChange

///////////////////////////////////////////////////////////////////////////////

void CAutoLaunch::OnNewDevice(const CString& devname, HDEVINFO info, PSP_DEVINFO_DATA devdata)
	{							// CAutoLaunch::OnNewDevice

	// Prevent duplicate launches

	for (int i = 0; i < m_devices.GetSize(); )
		if (devname.CompareNoCase(m_devices[i]) == 0)
			return;
	m_devices.Add(devname);

	// Open the hardware key for this device

	HKEY hkey = SetupDiOpenDevRegKey(info, devdata, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
	if (!hkey)
		{						// can't open key
		CString msg;
		msg.Format(_T("Can't open registry key for %s"), (LPCTSTR) devname);
		Log(msg);
		return;
		}						// can't open key

	// Get the AutoLaunch parameter from the registry

	DWORD junk;
	TCHAR buffer[_MAX_PATH];
	DWORD size = sizeof(buffer);
	CString Command;

	if (RegQueryValueEx(hkey, _T("AutoLaunch"), NULL, &junk, (LPBYTE) buffer, &size) != 0)
		{						// no AutoLaunch
		CString msg;
		msg.Format(_T("No AutoLaunch parameter for %s"), (LPCTSTR) devname);
		Log(msg);
		RegCloseKey(hkey);
		return;
		}						// no AutoLaunch
	Command = buffer;

	// Determine the device's friendly name

	CString FriendlyName;
	size = sizeof(buffer);
	if (!SetupDiGetDeviceRegistryProperty(info, devdata, SPDRP_FRIENDLYNAME, NULL, (PBYTE) buffer, sizeof(buffer), NULL)
		|| !SetupDiGetDeviceRegistryProperty(info, devdata, SPDRP_DEVICEDESC, NULL, (PBYTE) buffer, sizeof(buffer), NULL))
		buffer[0] = 0;	// no friendly name or description
	FriendlyName.Format(_T("\"%s\""), buffer);

	RegCloseKey(hkey);

	// Format and invoke the command

	ExpandEnvironmentStrings(Command, buffer, arraysize(buffer));
	CString name;
	name.Format(_T("\"%s\""), (LPCTSTR) devname);
	Command.Format(buffer, (LPCTSTR) name, (LPCTSTR) FriendlyName);

	STARTUPINFO si = {sizeof(STARTUPINFO)};
	si.lpDesktop = _T("WinSta0\\Default"); // name of interactive session's desktop
	si.wShowWindow = SW_SHOW;
	
	PROCESS_INFORMATION pi;
	if (CreateProcess(NULL, (LPTSTR) (LPCTSTR) Command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{						// launched okay
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		Log(Command);
		}						// launched okay
	else
		{						// error launching command
		CString msg;
		msg.Format(_T("Error %d trying to execute %s"), GetLastError(), (LPCTSTR) Command);
		Log(msg);
		}						// error launching command
	}							// CAutoLaunch::OnNewDevice
