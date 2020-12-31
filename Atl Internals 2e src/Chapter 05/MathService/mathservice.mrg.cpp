// Created by Microsoft (R) C/C++ Compiler Version 10.00.30319.01
//
// d:\vc++\atl internals 2e src\chapter 05\mathservice\mathservice.mrg.cpp
// compiler-generated file created 06/21/12 at 10:02:29
//
// This C++ source file is intended to be a representation of the
// source code injected by the compiler.  It may not compile or
// run exactly as the original source file.
//

// MathService.cpp : Implementation of WinMain

#include "stdafx.h"
//+++ Start Injected Code
[no_injected_text(true)];      // Suppress injected text, it has already been injected
#pragma warning(disable: 4543) // Suppress warnings about skipping injected text
#pragma warning(disable: 4199) // Suppress warnings from attribute providers

#pragma message("\n\nNOTE: This merged source file should be visually inspected for correctness.\n\n")
//--- End Injected Code


#include "resource.h"

// The module attribute causes WinMain to be automatically implemented for you
[ module(SERVICE, uuid = "{95C54D4C-17F8-43A2-96EE-F0DAB71F06D9}", 
		 name = "MathService", 
		 helpstring = "MathService 1.0 Type Library", 
		 resource_name="IDS_SERVICENAME") ];

//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathservice\\mathservice.cpp"
extern "C" const __declspec(selectany) GUID __LIBID_ = {0x95c54d4c,0x17f8,0x43a2,{0x96,0xee,0xf0,0xda,0xb7,0x1f,0x06,0xd9}};
struct __declspec(uuid("95c54d4c-17f8-43a2-96ee-f0dab71f06d9")) MathService;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathservice\\mathservice.cpp"

class CMathServiceModule;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathservice\\mathservice.cpp"

extern CMathServiceModule _AtlModule;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathservice\\mathservice.cpp"

extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int nShowCmd);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathservice\\mathservice.cpp"

class CMathServiceModule : public CAtlServiceModuleT<CMathServiceModule, IDS_SERVICENAME>
    							
{
public:
    DECLARE_LIBID(__uuidof(MathService))
        									DECLARE_REGISTRY_APPID_RESOURCEID(IDS_SERVICENAME, "{95C54D4C-17F8-43A2-96EE-F0DAB71F06D9}")
        							
};

#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathservice\\mathservice.cpp"

CMathServiceModule _AtlModule;

#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathservice\\mathservice.cpp"

extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int nShowCmd)
    					
{
    return _AtlModule.WinMain(nShowCmd);
}

//--- End Injected Code For Attribute 'module'

