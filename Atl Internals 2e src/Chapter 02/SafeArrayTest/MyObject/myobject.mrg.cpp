// Created by Microsoft (R) C/C++ Compiler Version 10.00.30319.01
//
// d:\vc++\atl internals 2e src\chapter 02\safearraytest\myobject\myobject.mrg.cpp
// compiler-generated file created 06/21/12 at 10:20:01
//
// This C++ source file is intended to be a representation of the
// source code injected by the compiler.  It may not compile or
// run exactly as the original source file.
//

// MyObject.cpp : Implementation of DLL Exports.

#include "stdafx.h"
//+++ Start Injected Code
[no_injected_text(true)];      // Suppress injected text, it has already been injected
#pragma warning(disable: 4543) // Suppress warnings about skipping injected text
#pragma warning(disable: 4199) // Suppress warnings from attribute providers

#pragma message("\n\nNOTE: This merged source file should be visually inspected for correctness.\n\n")
//--- End Injected Code


#include "resource.h"

// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
[ module(dll, uuid = "{12C2969A-1E90-4FA7-AC88-A2D1C402AD40}", 
		 name = "MyObject", 
		 helpstring = "MyObject 1.0 Type Library",
		 resource_name = "IDR_MYOBJECT") ];

//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"
extern "C" const __declspec(selectany) GUID __LIBID_ = {0x12c2969a,0x1e90,0x4fa7,{0xac,0x88,0xa2,0xd1,0xc4,0x02,0xad,0x40}};
struct __declspec(uuid("12c2969a-1e90-4fa7-ac88-a2d1c402ad40")) MyObject;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"

class CMyObjectModule;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"

extern CMyObjectModule _AtlModule;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"

#ifndef DLLMAIN_HINSTANCE
	#ifndef _WIN32_WCE
		#define DLLMAIN_HINSTANCE	HINSTANCE
	#else
		#define DLLMAIN_HINSTANCE	HANDLE
	#endif
#endif
				
//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"
extern "C" STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"
extern "C" STDAPI DllRegisterServer(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"
extern "C" STDAPI DllUnregisterServer(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"
extern "C" STDAPI DllCanUnloadNow(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"
BOOL WINAPI DllMain(DLLMAIN_HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"

class CMyObjectModule : public CAtlDllModuleT<CMyObjectModule>
    								
{
public:
    DECLARE_LIBID(__uuidof(MyObject))
        										DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MYOBJECT, "{12C2969A-1E90-4FA7-AC88-A2D1C402AD40}")
        								
};

#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"

CMyObjectModule _AtlModule;

#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"
extern "C" STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) 
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"
extern "C" STDAPI DllRegisterServer(void) 
{
    return _AtlModule.DllRegisterServer();
}
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"
extern "C" STDAPI DllUnregisterServer(void) 
{
    return _AtlModule.DllUnregisterServer();
}
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"
extern "C" STDAPI DllCanUnloadNow(void) 
{
    return _AtlModule.DllCanUnloadNow();
}
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"

#pragma managed(push, off)
BOOL WINAPI DllMain(DLLMAIN_HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) 
{
    hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved);
}
#pragma managed(pop)
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\myobject.cpp"

#if defined(_M_IX86)
#pragma comment(linker, "/EXPORT:DllRegisterServer=_DllRegisterServer@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllUnregisterServer=_DllUnregisterServer@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject=_DllGetClassObject@12,PRIVATE")
#pragma comment(linker, "/EXPORT:DllCanUnloadNow=_DllCanUnloadNow@0,PRIVATE")
#elif defined(_M_IA64) || defined(_M_AMD64)
#pragma comment(linker, "/EXPORT:DllRegisterServer,PRIVATE")
#pragma comment(linker, "/EXPORT:DllUnregisterServer,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject,PRIVATE")
#pragma comment(linker, "/EXPORT:DllCanUnloadNow,PRIVATE")
#endif	

//--- End Injected Code For Attribute 'module'

