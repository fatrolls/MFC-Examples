// Created by Microsoft (R) C/C++ Compiler Version 10.00.30319.01
//
// d:\vc++\atl internals 2e src\chapter 05\mathexe\mathexe.mrg.cpp
// compiler-generated file created 06/21/12 at 10:02:46
//
// This C++ source file is intended to be a representation of the
// source code injected by the compiler.  It may not compile or
// run exactly as the original source file.
//

// MathExe.cpp : Implementation of WinMain

#include "stdafx.h"
//+++ Start Injected Code
[no_injected_text(true)];      // Suppress injected text, it has already been injected
#pragma warning(disable: 4543) // Suppress warnings about skipping injected text
#pragma warning(disable: 4199) // Suppress warnings from attribute providers

#pragma message("\n\nNOTE: This merged source file should be visually inspected for correctness.\n\n")
//--- End Injected Code


#include "resource.h"

// The module attribute causes WinMain to be automatically implemented for you
[ module(EXE, uuid = "{F8D5EF98-6A4C-4E92-899F-97A7B8FB31F6}", 
		 name = "MathExe", 
		 helpstring = "MathExe 1.0 Type Library",
		 resource_name = "IDR_MATHEXE") ];

//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathexe\\mathexe.cpp"
extern "C" const __declspec(selectany) GUID __LIBID_ = {0xf8d5ef98,0x6a4c,0x4e92,{0x89,0x9f,0x97,0xa7,0xb8,0xfb,0x31,0xf6}};
struct __declspec(uuid("f8d5ef98-6a4c-4e92-899f-97a7b8fb31f6")) MathExe;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathexe\\mathexe.cpp"

class CMathExeModule;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathexe\\mathexe.cpp"

extern CMathExeModule _AtlModule;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathexe\\mathexe.cpp"

extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int nShowCmd);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathexe\\mathexe.cpp"

class CMathExeModule : public CAtlExeModuleT<CMathExeModule>
    								
{
public:
    DECLARE_LIBID(__uuidof(MathExe))
        										DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MATHEXE, "{F8D5EF98-6A4C-4E92-899F-97A7B8FB31F6}")
        								
};

#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathexe\\mathexe.cpp"

CMathExeModule _AtlModule;

#injected_line 7 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathexe\\mathexe.cpp"

extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int nShowCmd)
    					
{
    return _AtlModule.WinMain(nShowCmd);
}

//--- End Injected Code For Attribute 'module'

