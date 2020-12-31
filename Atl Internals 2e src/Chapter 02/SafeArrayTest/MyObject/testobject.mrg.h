// Created by Microsoft (R) C/C++ Compiler Version 10.00.30319.01
//
// d:\vc++\atl internals 2e src\chapter 02\safearraytest\myobject\testobject.mrg.h
// compiler-generated file created 06/21/12 at 10:24:19
//
// This C++ source file is intended to be a representation of the
// source code injected by the compiler.  It may not compile or
// run exactly as the original source file.
//


//+++ Start Injected Code
[no_injected_text(true)];      // Suppress injected text, it has already been injected
#pragma warning(disable: 4543) // Suppress warnings about skipping injected text
#pragma warning(disable: 4199) // Suppress warnings from attribute providers

#pragma message("\n\nNOTE: This merged source file should be visually inspected for correctness.\n\n")
//--- End Injected Code

// TestObject.h : Declaration of the CTestObject

#pragma once
#include "resource.h"       // main symbols


// ITestObject
[
	object,
	uuid("5D8C02D0-11EC-47C2-8468-BD1909A1627A"),
	oleautomation,	helpstring("ITestObject Interface"),
	pointer_default(unique)
]
__interface ITestObject : IUnknown
{
	[id(1), helpstring("method GetArray")] HRESULT GetArray([out, retval, satype(VARIANT_BOOL)] SAFEARRAY** myArray);
};



// CTestObject

[
	coclass,
	threading("apartment"),
	support_error_info("ITestObject"),
	vi_progid("MyObject.TestObject"),
	progid("MyObject.TestObject.1"),
	version(1.0),
	uuid("2B70187A-8E12-4DDC-BE8D-1A5A151D698F"),
	helpstring("TestObject Class")
]
class ATL_NO_VTABLE CTestObject : 
	public ITestObject
,
    /*+++ Added Baseclass */ public ISupportErrorInfo
{
public:
	CTestObject()
	{
	}


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

	STDMETHOD(GetArray)(SAFEARRAY** myArray);

	//+++ Start Injected Code For Attribute 'support_error_info'
#injected_line 26 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\testobject.h"
    static DWORD* GetOpCodes() 
    {
        static DWORD rgOps[] = 
            					{
            						0x70000000,
            0x30004000,
            0x80000002,
            0x50000000,
            0x3000c000,
            0x80000004,
            0x50000000,
            0x60000000,
            0x60000000,
            0x30014000,
            0x80000002,
            0x50000000,
            0x3000c000,
            0x80000004,
            0x50000000,
            0x60000000,
            0x30018000,
            0x80000001,
            0x50000000,
            0x60000000,
            0x60000000,
            0x1000c000,
            0x3000c000,
            0x50000000,
            0x20010000,
            0x30010000,
            0x80000002,
            0x50000000,
            0x3001c000,
            0x80000001,
            0x50000000,
            0x60000000,
            0x30020000,
            0x80000005,
            0x50000000,
            0x60000000,
            0x20024000,
            0x30024000,
            0x50000000,
            0x60000000,
            0x30028000,
            0x8000000b,
            0x50000000,
            0x8003000d,
            0x60000000,
            0x8003800f,
            0x30040000,
            0x80000011,
            0x50000000,
            0x60000000,
            0x60000000,
            0x60000000,
            0x60000000,
            0
            					};
        return rgOps;
    }
#injected_line 26 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\testobject.h"
    static RGSDWORD* GetOpcodeDWORDVals() 
    {
        static RGSDWORD rgDWORDS[] = 
            					{
            						{0, 0}
            					};
        return rgDWORDS;
    }
#injected_line 26 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\testobject.h"
    static RGSBinary* GetOpcodeBinaryVals() 
    {

        static RGSBinary rgBinary[] = 
            					{
            						{0, 0}
            					};
        return rgBinary;
    }
#injected_line 26 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\testobject.h"
    static RGSStrings* GetOpcodeStringVals() 
    {
        static RGSStrings rgStrings[] = 
            					{
            						{_T(""),0 }, 
            {_T("MyObject.TestObject.1"),0 }, 
            {_T("%FriendlyName%"),1 }, 
            {_T("CLSID"),0 }, 
            {_T("{2B70187A-8E12-4DDC-BE8D-1A5A151D698F}"),0 }, 
            {_T("MyObject.TestObject"),0 }, 
            {_T("CurVer"),0 }, 
            {_T("ProgID"),0 }, 
            {_T("VersionIndependentProgID"),0 }, 
            {_T("Programmable"),0 }, 
            {_T("%MODULETYPE%"),1 }, 
            {_T("%MODULE%"),1 }, 
            {_T("ThreadingModel"),0 }, 
            {_T("apartment"),0 }, 
            {_T("AppID"),0 }, 
            {_T("%APPID%"),1 }, 
            {_T("TypeLib"),0 }, 
            {_T("%MODULEGUID%"),1 }, 
            {NULL, 0}
            					};
        return rgStrings;
    }
#injected_line 26 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\testobject.h"
    static HRESULT WINAPI UpdateRegistry(BOOL bRegister) 
    {
        CRegistryVirtualMachine rvm;
        HRESULT hr;
        if (FAILED(hr = rvm.AddStandardReplacements()))
            return hr;
        rvm.AddReplacement(_T("FriendlyName"), GetObjectFriendlyName());
        return rvm.VMUpdateRegistry(GetOpCodes(), GetOpcodeStringVals(), GetOpcodeDWORDVals(), GetOpcodeBinaryVals(), bRegister);
    }
#injected_line 26 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\testobject.h"
    static const TCHAR* GetObjectFriendlyName() 
    {
        return _T("CTestObject Object");
    }
#injected_line 26 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\testobject.h"
    static const TCHAR* GetProgID() 
    {
        return _T("MyObject.TestObject.1");
    }
#injected_line 26 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\testobject.h"
    static const TCHAR* GetVersionIndependentProgID() 
    {
        return _T("MyObject.TestObject");
    }
#injected_line 26 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\testobject.h"
    BEGIN_COM_MAP(CTestObject)
        COM_INTERFACE_ENTRY(ITestObject)
        COM_INTERFACE_ENTRY(IProvideClassInfo)
        COM_INTERFACE_ENTRY(ISupportErrorInfo)
    END_COM_MAP()
#injected_line 26 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\testobject.h"

    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) 
        					
    {
        static const IID* rgErrorGuids[] = 
            						{
            							&__uuidof(ITestObject)
            						};
        for (int i=0; i < sizeof(rgErrorGuids) / sizeof(rgErrorGuids[0]); i++)
						{
            if (InlineIsEqualGUID(*rgErrorGuids[i],riid))
                return S_OK;
        }
        return S_FALSE;
    } 

	//--- End Injected Code For Attribute 'support_error_info'
};

//+++ Start Injected Code For Attribute 'support_error_info'
#injected_line 26 "d:\\vc++\\atl internals 2e src\\chapter 02\\safearraytest\\myobject\\testobject.h"

				OBJECT_ENTRY_AUTO(__uuidof(CTestObject), CTestObject)
			
//--- End Injected Code For Attribute 'support_error_info'


