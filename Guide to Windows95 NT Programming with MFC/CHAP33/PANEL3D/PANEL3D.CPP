///////////////////////////////////////////////////////////////////
//  Module  : PANEL3D.CPP
//
//  Purpose : Implementation of CPanel3dApp and DLL registration.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 07-10-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Panel3d.h"

const GUID CDECL BASED_CODE _tlid =
{ 
   0x4d85cc81, 0xd9c6, 0x11cf, 
   { 
      0xa3, 0xbc, 0x44, 0x45, 0x53, 0x54, 0, 0 
   }
};

const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

///////////////////////////////////////////////////////////////////
// CPanel3dApp::InitInstance - DLL initialization

BOOL CPanel3dApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// Could add special module initialization code here...
	}

	return bInit;
}

///////////////////////////////////////////////////////////////////
// CPanel3dApp::ExitInstance - DLL termination

int CPanel3dApp::ExitInstance()
{
	// Could add module termination code here...

	return COleControlModule::ExitInstance();
}

///////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}

///////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}

///////////////////////////////////////////////////////////////////
// The application (DLLS) object

CPanel3dApp CtrlApp;

///////////////////////////////////////////////////////////////////
