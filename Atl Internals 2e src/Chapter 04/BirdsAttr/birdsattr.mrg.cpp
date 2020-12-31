// Created by Microsoft (R) C/C++ Compiler Version 10.00.30319.01
//
// d:\vc++\atlinternals-src\chapter 04\birdsattr\birdsattr.mrg.cpp
// compiler-generated file created 06/20/12 at 09:38:19
//
// This C++ source file is intended to be a representation of the
// source code injected by the compiler.  It may not compile or
// run exactly as the original source file.
//

// BirdsAttr.cpp : Implementation of DLL Exports.

#include "stdafx.h"
//+++ Start Injected Code
[no_injected_text(true)];      // Suppress injected text, it has already been injected
#pragma warning(disable: 4543) // Suppress warnings about skipping injected text
#pragma warning(disable: 4199) // Suppress warnings from attribute providers

#pragma message("\n\nNOTE: This merged source file should be visually inspected for correctness.\n\n")
//--- End Injected Code


#include "resource.h"

// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
[ module(dll, uuid = "{1D172D25-115D-42C8-B8BD-B001B23AA715}", 
		 name = "BirdsAttr", 
		 helpstring = "BirdsAttr 1.0 Type Library",
		 resource_name = "IDR_BIRDSATTR") ];

//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"
extern "C" const __declspec(selectany) GUID __LIBID_ = {0x1d172d25,0x115d,0x42c8,{0xb8,0xbd,0xb0,0x01,0xb2,0x3a,0xa7,0x15}};
struct __declspec(uuid("1d172d25-115d-42c8-b8bd-b001b23aa715")) BirdsAttr;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"

class CBirdsAttrModule;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"

extern CBirdsAttrModule _AtlModule;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"

#ifndef DLLMAIN_HINSTANCE
	#ifndef _WIN32_WCE
		#define DLLMAIN_HINSTANCE	HINSTANCE
	#else
		#define DLLMAIN_HINSTANCE	HANDLE
	#endif
#endif
				
//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"
extern "C" STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"
extern "C" STDAPI DllRegisterServer(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"
extern "C" STDAPI DllUnregisterServer(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"
extern "C" STDAPI DllCanUnloadNow(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"
BOOL WINAPI DllMain(DLLMAIN_HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"

class CBirdsAttrModule : public CAtlDllModuleT<CBirdsAttrModule>
    								
{
public:
    DECLARE_LIBID(__uuidof(BirdsAttr))
        										DECLARE_REGISTRY_APPID_RESOURCEID(IDR_BIRDSATTR, "{1D172D25-115D-42C8-B8BD-B001B23AA715}")
        								
};

#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"

CBirdsAttrModule _AtlModule;

#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"
extern "C" STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) 
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"
extern "C" STDAPI DllRegisterServer(void) 
{
    return _AtlModule.DllRegisterServer();
}
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"
extern "C" STDAPI DllUnregisterServer(void) 
{
    return _AtlModule.DllUnregisterServer();
}
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"
extern "C" STDAPI DllCanUnloadNow(void) 
{
    return _AtlModule.DllCanUnloadNow();
}
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"

#pragma managed(push, off)
BOOL WINAPI DllMain(DLLMAIN_HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) 
{
    hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved);
}
#pragma managed(pop)
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\birdsattr.cpp"

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

