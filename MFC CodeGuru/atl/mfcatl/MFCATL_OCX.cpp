// MFCATL_OCX.cpp : Implementation of CMFCATL_OCXApp and DLL registration.

#include "stdafx.h"

#include "MFCATL_TLib.h"
#include "MFCATL_TLib_i.c"

#include "MFCATL_OCX.h"
#include "MyATLObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CMFCATL_OCXApp NEAR theApp;
CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_MyATLObject, CMyATLObject)
END_OBJECT_MAP()

const GUID CDECL _tlid = LIBID_MFCATL_OCXLib;
		//{ 0xa9ee6e81, 0x5f04, 0x11d1, { 0x93, 0x4c, 0xe4, 0xcf, 0xda, 0, 0, 0 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXApp::InitInstance - DLL initialization

BOOL CMFCATL_OCXApp::InitInstance()
{
	_Module.Init(ObjectMap, m_hInstance);

   BOOL bInit = super::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CMFCATL_OCXApp::ExitInstance - DLL termination

int CMFCATL_OCXApp::ExitInstance()
{
	// TODO: Add your own module termination code here.
	_Module.Term();

	return super::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return _Module.RegisterServer(TRUE);
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return _Module.UnregisterServer();
}
/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	if( CLSID_MyATLObject == rclsid )
   {
      return _Module.GetClassObject(rclsid, riid, ppv);
   }

   AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}
