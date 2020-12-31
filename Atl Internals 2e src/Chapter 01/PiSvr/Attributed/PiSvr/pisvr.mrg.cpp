// Created by Microsoft (R) C/C++ Compiler Version 10.00.30319.01
//
// d:\vc++\atlinternals-src\chapter 01\pisvr\attributed\pisvr\pisvr.mrg.cpp
// compiler-generated file created 06/19/12 at 10:14:24
//
// This C++ source file is intended to be a representation of the
// source code injected by the compiler.  It may not compile or
// run exactly as the original source file.
//

// PiSvr.cpp : Implementation of DLL Exports.

#include "stdafx.h"
//+++ Start Injected Code
[no_injected_text(true)];      // Suppress injected text, it has already been injected
#pragma warning(disable: 4543) // Suppress warnings about skipping injected text
#pragma warning(disable: 4199) // Suppress warnings from attribute providers

#pragma message("\n\nNOTE: This merged source file should be visually inspected for correctness.\n\n")
//--- End Injected Code


#include "resource.h"

// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
[ module(dll, uuid = "{4D7B835B-E5A9-47C4-B48F-E359FFC464BB}", 
		 name = "PiSvr", 
		 helpstring = "PiSvr 1.0 Type Library",
		 resource_name = "IDR_PISVR") ];

//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"
extern "C" const __declspec(selectany) GUID __LIBID_ = {0x4d7b835b,0xe5a9,0x47c4,{0xb4,0x8f,0xe3,0x59,0xff,0xc4,0x64,0xbb}};
struct __declspec(uuid("4d7b835b-e5a9-47c4-b48f-e359ffc464bb")) PiSvr;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"

class CPiSvrModule;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"

extern CPiSvrModule _AtlModule;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"

#ifndef DLLMAIN_HINSTANCE
	#ifndef _WIN32_WCE
		#define DLLMAIN_HINSTANCE	HINSTANCE
	#else
		#define DLLMAIN_HINSTANCE	HANDLE
	#endif
#endif
				
//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"
extern "C" STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"
extern "C" STDAPI DllRegisterServer(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"
extern "C" STDAPI DllUnregisterServer(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"
extern "C" STDAPI DllCanUnloadNow(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"
BOOL WINAPI DllMain(DLLMAIN_HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"

class CPiSvrModule : public CAtlDllModuleT<CPiSvrModule>
    								
{
public:
    DECLARE_LIBID(__uuidof(PiSvr))
        										DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PISVR, "{4D7B835B-E5A9-47C4-B48F-E359FFC464BB}")
        								
};

#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"

CPiSvrModule _AtlModule;

#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"
extern "C" STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) 
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"
extern "C" STDAPI DllRegisterServer(void) 
{
    return _AtlModule.DllRegisterServer();
}
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"
extern "C" STDAPI DllUnregisterServer(void) 
{
    return _AtlModule.DllUnregisterServer();
}
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"
extern "C" STDAPI DllCanUnloadNow(void) 
{
    return _AtlModule.DllCanUnloadNow();
}
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"

#pragma managed(push, off)
BOOL WINAPI DllMain(DLLMAIN_HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) 
{
    hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved);
}
#pragma managed(pop)
#injected_line 7 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\pisvr.cpp"

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

