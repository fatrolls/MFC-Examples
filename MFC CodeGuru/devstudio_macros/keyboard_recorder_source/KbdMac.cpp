/////////////////////////////////////////////////////////////////////////////
//
//                           Public Domain.
//
/////////////////////////////////////////////////////////////////////////////
//
//
//  File     :   KbdMac.cpp
//
//  Author   :   Darren Richards
//
//  Date     :   25th February 98
//
//  Synopsis :   Main module of KbdMac add-in for DevStudio.
//               (ATL Wizard generated)
//
////////////////

/////////////////////////////////////////////////////////////////////////////
//
//  includes
//
///////////////

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "KbdMac.h"

#include "KbdMac_i.c"
#include <initguid.h>
#include "KMAddIn.h"

/////////////////////////////////////////////////////////////////////////////
//
//  locals
//
///////////////

CComModule _Module;

/////////////////////////////////////////////////////////////////////////////
//
//  ATL CLSID to class map
//
///////////////

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_KMAddIn, CKMAddIn)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
//
//  DLL Entry point
//
///////////////

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, hInstance);
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		_Module.Term();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//
//  COM Entry points
//
///////////////

STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

STDAPI DllRegisterServer(void)
{
	return _Module.RegisterServer(TRUE);
}

STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer();
	return S_OK;
}


