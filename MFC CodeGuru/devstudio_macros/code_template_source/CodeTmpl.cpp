/////////////////////////////////////////////////////////////////////////////
//
//                           Public Domain.
//
/////////////////////////////////////////////////////////////////////////////
//
//
//  File     :   CodeTmpl.cpp
//
//  Author   :   Darren Richards (darrenr@gissing-consulting.co.uk)
//
//  Date     :   20th March 98
//
//  Synopsis :   Code template add-in, provides simple mechanism for gluing
//               commonly used text strings into devstudio editor.
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
#include "CodeTmpl.h"

#include "CodeTmpl_i.c"
#include <initguid.h>
#include "CTAddIn.h"

/////////////////////////////////////////////////////////////////////////////
//
//  locals
//
///////////////

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_CTAddIn, CCTAddIn)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
//
//  DLL/OLE entry points
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
	return TRUE;    // ok
}

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


