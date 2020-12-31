// powcpl.cpp -- Sample power-management property page provider
// Copyright (C) 1998 by Walter Oney
// All rights reserved

// This sample DLL illustrates how to provide a custom property page to augment
// the Power Management control panel applet. Since Windows 98 doesn't generate
// the normal SYSTEM_CONTROL I/O requests for idle timeouts and wakeup enabling,
// you'd have to provide your own mechanism to control those features. A property
// page DLL like this one and a set of IOCTLs would be a big part of your solution.

// The skeleton for this DLL was created, by the way, using the FreeWare shell
// extension wizard you can find at http://www.oneysoft.com. All of the code in
// this particular source file is actually boilerplate -- the code you'd want to
// heavily adapt is in Page.cpp.

#include "stdafx.h"
#include "powcpl.h"

#pragma comment(lib, "rpcrt4.lib")

#define APSTUDIO_INVOKED		// to get _APS_NEXT_COMMAND_VALUE
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CShellxApp theApp;
IMalloc* pMalloc;
UINT cfFilename;

BOOL DeleteSubkey(HKEY basekey, const CString subkey, const CString keyname);
BOOL DeleteSubkey(HKEY basekey, const CString subkey);
CString MakeObjectKeyName(REFIID iid, const CString subkey);
CString MakeObjectKeyName(REFIID iid);
HKEY OpenObjectKey(HKEY basekey, const CString subkey, REFIID iid);
BOOL SetSubkey(HKEY basekey, LPCTSTR subkey, LPCTSTR value);
BOOL SetSubkeyValue(HKEY basekey, LPCTSTR subkey, LPCTSTR valname, LPCTSTR value);
BOOL SetSubkeyValue(HKEY basekey, LPCTSTR subkey, LPCTSTR valname, LPBYTE value, DWORD nbytes);

#define DLLFRIENDLYNAME _T("WdmidleDeviceShellExtension")
#define REGPATH_APPROVED_EXTENSIONS _T("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved")

///////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CShellxApp, CWinApp)
	//{{AFX_MSG_MAP(CShellxApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////

BOOL CShellxApp::InitInstance() 
	{							// CShellxApp::InitInstance
	COleObjectFactory::RegisterAll();
	if (!(SUCCEEDED(SHGetMalloc(&pMalloc))))
		return FALSE;
	cfFilename = RegisterClipboardFormat(_T("Filename"));
	return TRUE;
	}							// CShellxApp::InitInstance

int CShellxApp::ExitInstance()
	{							// CShellxApp::ExitInstance
	if (pMalloc)
		pMalloc->Release();
	return 0;
	}							// CShellxApp::ExitInstance

///////////////////////////////////////////////////////////////////////////////

STDAPI DllGetClassObject(REFCLSID clsid, REFIID iid, LPVOID* ppv)
	{							// DllGetClassObject
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(clsid, iid, ppv);
	}							// DllGetClassObject

STDAPI DllCanUnloadNow()
	{							// DllCanUnloadNow
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
	}							// DllCanUnloadNow

// Registration functions for use with REGSVR32

STDAPI DllRegisterServer()
	{							// DllRegisterServer
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ASSERT(theApp.m_hInstance);

	// Add a CLSID pointing to this module

	HKEY hkey = OpenObjectKey(HKEY_CLASSES_ROOT, _T("CLSID"), CShellExtension::guid);
	if (!hkey)
		return E_FAIL;
	RegSetValue(hkey, NULL, REG_SZ, DLLFRIENDLYNAME, sizeof(DLLFRIENDLYNAME));
	TCHAR filename[_MAX_PATH];
	GetModuleFileName(theApp.m_hInstance, filename, arraysize(filename));
	_tcslwr(filename);

	SetSubkey(hkey, _T("InprocServer32"), filename);
	SetSubkeyValue(hkey, _T("InprocServer32"), _T("ThreadingModel"), _T("Apartment"));
	RegCloseKey(hkey);

	// Register the shell extension(s) supported by this DLL

	CString idname = MakeObjectKeyName(CShellExtension::guid);

	SetSubkey(HKEY_LOCAL_MACHINE, _T(REGSTR_PATH_CONTROLSFOLDER)
		_T("\\Power\\shellex\\PropertySheetHandlers\\") DLLFRIENDLYNAME, idname);

	// If running under NT, add our CLSID to the list of approved servers

	SetSubkeyValue(HKEY_LOCAL_MACHINE, REGPATH_APPROVED_EXTENSIONS, idname, DLLFRIENDLYNAME);

	return S_OK;
	}							// DllRegisterServer

STDAPI DllUnregisterServer()
	{							// DllUnregisterServer
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// Deregister our shell extensions
	RegDeleteKey(HKEY_LOCAL_MACHINE, _T(REGSTR_PATH_CONTROLSFOLDER)
		_T("\\Power\\shellex\\PropertySheetHandlers\\") DLLFRIENDLYNAME);

	HKEY hkey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, REGPATH_APPROVED_EXTENSIONS, 0, KEY_ALL_ACCESS, &hkey) == 0)
		{						// remove from approved list
		RegDeleteValue(hkey, MakeObjectKeyName(CShellExtension::guid));
		RegCloseKey(hkey);
		}						// remove from approved list
	
	// Remove the CLSID pointer to this DLL. Note that NT won't delete a key unless there
	// aren't any subkeys below it

	CString keyname = MakeObjectKeyName(CShellExtension::guid, _T("CLSID"));
	DeleteSubkey(HKEY_CLASSES_ROOT, keyname, _T("InprocServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, keyname);
	return S_OK;
	}							// DllUnregisterServer

// Registration functions for use with RUNDLL32

STDAPI RegisterServer(DWORD unknown1, HMODULE hModule, LPTSTR lpArgs, DWORD unknown2)
	{							// RegisterServer
	return DllRegisterServer();
	}							// RegisterServer

STDAPI UnregisterServer(DWORD unknown1, HMODULE hModule, LPTSTR lpArgs, DWORD unknown2)
	{							// UnregisterServer
	return DllUnregisterServer();
	}							// UnregisterServer

///////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CShellExtension, CCmdTarget)

#pragma warning(disable:4355)	// "this" used in base initializer

CShellExtension::CShellExtension() :
	m_page1(this),
	m_sig('XLHS')
	{							// CShellExtension::CShellExtension
	EnableAutomation();
	AfxOleLockApp();
	m_data = NULL;
	m_hkey = NULL;
	}							// CShellExtension::CShellExtension

#pragma warning(default:4355)

CShellExtension::~CShellExtension()
	{							// CShellExtension::~CShellExtension
	AssertValid();
	m_sig = 0;
	if (m_data)
		m_data->Release();
	if (m_hkey)
		RegCloseKey(m_hkey);
	AfxOleUnlockApp();
	}							// CShellExtension::~CShellExtension

#ifdef _DEBUG

void CShellExtension::AssertValid()
	{							// CShellExtension::AssertValid
	ASSERT(AfxIsValidAddress(this, sizeof(CShellExtension)));
	ASSERT(m_sig == 'XLHS');
	}							// CShellExtension::AssertValid

#endif

BEGIN_MESSAGE_MAP(CShellExtension, CCmdTarget)
	//{{AFX_MSG_MAP(CShellExtension)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_INTERFACE_MAP(CShellExtension, CCmdTarget)
	INTERFACE_PART(CShellExtension, IID_IShellExtInit, ShellExtInit)
	INTERFACE_PART(CShellExtension, IID_IShellPropSheetExt, ShellPropSheetExt)
END_INTERFACE_MAP()

// {2d3dd4c0-3bd7-11d2-821e-444553540000}
IMPLEMENT_OLECREATE(CShellExtension, "POWCPL.SHELLEXTENSION", 0x2d3dd4c0, 0x3bd7, 0x11d2, 0x82, 0x1e, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00)

///////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DUAL_INTERFACE_IUNKNOWN(CShellExtension, ShellExtInit)

HRESULT CShellExtension::XShellExtInit::Initialize(LPCITEMIDLIST idlist, LPDATAOBJECT lpdo, HKEY hkey)
	{							// CShellExtension::XShellExtInit::Initialize
	METHOD_PROLOGUE(CShellExtension, ShellExtInit)
	ASSERT_THIS_VALID();

	// Since Initialize can be called more than once, cleanup after any
	// previous invocation.

	if (pThis->m_data)
		pThis->m_data->Release();
	pThis->m_data = NULL;
	if (pThis->m_hkey)
		RegCloseKey(pThis->m_hkey);
	pThis->m_hkey = NULL;

	if (!CPage1::DevicesPresent())
		return E_FAIL;

	// Make copies of parameters

	pThis->m_data = lpdo;
	if (hkey)
		RegOpenKeyEx(hkey, NULL, 0, MAXIMUM_ALLOWED, &pThis->m_hkey);
	pThis->m_idlist = idlist;
	
	if (lpdo)
		lpdo->AddRef();

	return 0;
	}							// CShellExtension::XShellExtInit::Initialize

///////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DUAL_INTERFACE_IUNKNOWN(CShellExtension, ShellPropSheetExt)

HRESULT CShellExtension::XShellPropSheetExt::AddPages(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
	{							// CShellExtension::XShellPropSheetExt::AddPages
	METHOD_PROLOGUE(CShellExtension, ShellPropSheetExt)
	ASSERT_THIS_VALID();
	pThis->m_page1.AddPage(lpfnAddPage, lParam);
	return 0;
	}							// CShellExtension::XShellPropSheetExt::AddPages

HRESULT CShellExtension::XShellPropSheetExt::ReplacePage(UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam)
	{							// CShellExtension::XShellPropSheetExt::ReplacePage
	METHOD_PROLOGUE(CShellExtension, ShellPropSheetExt)
	ASSERT_THIS_VALID();
	return 0;
	}							// CShellExtension::XShellPropSheetExt::ReplacePage

UINT CALLBACK PropPageCallbackProc(HWND hwnd, UINT message, LPPROPSHEETPAGE ppsp)
	{							// PropPageCallbackProc
	CShellPropPage* page = STATIC_DOWNCAST(CShellPropPage, (CObject*) ppsp->lParam);

	switch (message)
		{						// process message
	case PSPCB_CREATE:
		{						// PSPCB_CREATE
		if (page->m_callback)
			return (*page->m_callback)(hwnd, message, ppsp);
		else
			return TRUE;
		}						// PSPCB_CREATE

	case PSPCB_RELEASE:
		{						// PSPCB_RELEASE
		UINT result = page->m_callback ? (*page->m_callback)(hwnd, message, ppsp) : 0;
		page->m_parent->ExternalRelease();
		return result;
		}						// PSPCB_RELEASE

		}						// process messsage

	return 0;					// should never be reached
	}							// PropPageCallbackProc

IMPLEMENT_DYNAMIC(CShellPropPage, CPropertyPage)

CShellPropPage::CShellPropPage(CCmdTarget* parent, UINT id) : CPropertyPage(id)
	{							// CShellPropPage::CShellPropPage
	m_parent = parent;

	if (m_psp.dwFlags & PSP_USECALLBACK)
		m_callback = m_psp.pfnCallback;
	m_psp.pfnCallback = PropPageCallbackProc;
	}							// CShellPropPage::CShellPropPage

CShellPropPage::~CShellPropPage()
	{							// CShellPropPage::~CShellPropPage
	}							// CShellPropPage::~CShellPropPage

HRESULT CShellPropPage::AddPage(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
	{							// CShellPropPage::AddPage
	HPROPSHEETPAGE hPage = CreatePropertySheetPage((LPCPROPSHEETPAGE) &m_psp);
	if (hPage)
		if ((*lpfnAddPage)(hPage, lParam))
			m_parent->ExternalAddRef();	// required to prevent premature unloading of extension DLL
		else
			DestroyPropertySheetPage(hPage);
	return NOERROR;
	}							// CShellPropPage::AddPage

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BOOL DeleteSubkey(HKEY basekey, const CString subkey, const CString keyname)
	{							// DeleteSubkey
	return RegDeleteKey(basekey, keyname + _T('\\') + subkey) == 0;
	}							// DeleteSubkey

BOOL DeleteSubkey(HKEY basekey, const CString subkey)
	{							// DeleteSubkey
	return RegDeleteKey(basekey, subkey) == 0;
	}							// DeleteSubkey

///////////////////////////////////////////////////////////////////////////////

CString MakeObjectKeyName(REFIID iid, const CString subkey)
	{							// MakeObjectKeyName
	return subkey + _T('\\') + _T('{') + UuidToCString(iid) + _T('}');
	}							// MakeObjectKeyName

CString MakeObjectKeyName(REFIID iid)
	{							// MakeObjectKeyName
	return _T('{') + UuidToCString(iid) + _T('}');
	}							// MakeObjectKeyName

///////////////////////////////////////////////////////////////////////////////

HKEY OpenObjectKey(HKEY basekey, const CString subkey, REFIID iid)
	{							// OpenObjectKey
	DWORD junk;
	HKEY hkey;
	DWORD code = RegCreateKeyEx(basekey, MakeObjectKeyName(iid, subkey),
		0, _T(""), 0, KEY_ALL_ACCESS, NULL, &hkey, &junk);
	if (code == 0)
		return hkey;
	return NULL;
	}							// OpenObjectKey

///////////////////////////////////////////////////////////////////////////////

BOOL SetSubkey(HKEY basekey, LPCTSTR subkey, LPCTSTR value)
	{							// SetSubkey
	HKEY hkey;
	DWORD junk;
	if (RegCreateKeyEx(basekey, subkey, 0, _T(""), 0, KEY_ALL_ACCESS,
		NULL, &hkey, &junk) != 0)
		return FALSE;
	DWORD code = RegSetValueEx(hkey, NULL, 0, REG_SZ, (const BYTE*) value,
		(_tcslen(value) + 1) * sizeof(TCHAR));
	RegCloseKey(hkey);
	return code == 0;
	}							// SetSubkey

///////////////////////////////////////////////////////////////////////////////

BOOL SetSubkeyValue(HKEY basekey, LPCTSTR subkey, LPCTSTR valname, LPCTSTR value)
	{							// SetSubkeyValue
	HKEY hkey;
	DWORD junk;
	if (RegCreateKeyEx(basekey, subkey, 0, _T(""), 0, KEY_ALL_ACCESS,
		NULL, &hkey, &junk) != 0)
		return FALSE;
	DWORD code = RegSetValueEx(hkey, valname, 0, REG_SZ, (const BYTE*) value,
		(_tcslen(value) + 1) * sizeof(TCHAR));
	RegCloseKey(hkey);
	return code == 0;
	}							// SetSubkeyValue

BOOL SetSubkeyValue(HKEY basekey, LPCTSTR subkey, LPCTSTR valname, LPBYTE value, DWORD nbytes)
	{							// SetSubkeyValue
	HKEY hkey;
	DWORD junk;
	if (RegCreateKeyEx(basekey, subkey, 0, _T(""), 0, KEY_ALL_ACCESS,
		NULL, &hkey, &junk) != 0)
		return FALSE;
	DWORD code = RegSetValueEx(hkey, valname, 0, REG_BINARY, (const BYTE*) value, nbytes);
	RegCloseKey(hkey);
	return code == 0;
	}							// SetSubkeyValue
