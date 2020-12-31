// Created by Microsoft (R) C/C++ Compiler Version 10.00.30319.01
//
// d:\vc++\atl internals 2e src\chapter 07\demagogue\demagogue\codemagogue.mrg.h
// compiler-generated file created 06/21/12 at 15:12:18
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

// CoDemagogue.h : Declaration of the CDemagogue

#pragma once
#include "resource.h"       // main symbols


// IDemagogue
[
	object,
	uuid("02C6F955-986D-4358-8ECB-04553F1D7D32"),
	oleautomation,	helpstring("IDemagogue Interface"),
	pointer_default(unique)
]
__interface IDemagogue : IUnknown
{
};



// CDemagogue

[
	coclass,
	threading("apartment"),
	support_error_info("IDemagogue"),
	vi_progid("Demagogue.Demagogue"),
	progid("Demagogue.Demagogue.1"),
	version(1.0),
	uuid("8FB5429F-5457-4ED7-8093-EDA710A68EB8"),
	helpstring("Demagogue Class")
]
class ATL_NO_VTABLE CDemagogue : 
	public IDemagogue,
	public IPersistPropertyBagImpl<CDemagogue>
,
    /*+++ Added Baseclass */ public ISupportErrorInfo
{
public:
	CDemagogue()
	{
	}
   //BEGIN_COM_MAP(CDemagogue)
   //   COM_INTERFACE_ENTRY(IDemagogue)
   //   COM_INTERFACE_ENTRY2(IPersist, IPersistPropertyBag)
   //   COM_INTERFACE_ENTRY(IPersistPropertyBag)
   //END_COM_MAP()

   //BEGIN_PROP_MAP(CDemagogue)
   //   PROP_DATA_ENTRY("Volume", m_dVolume, VT_R8)
   //END_PROP_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
	bool m_bRequiresSave;

	//+++ Start Injected Code For Attribute 'support_error_info'
#injected_line 25 "d:\\vc++\\atl internals 2e src\\chapter 07\\demagogue\\demagogue\\codemagogue.h"
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
#injected_line 25 "d:\\vc++\\atl internals 2e src\\chapter 07\\demagogue\\demagogue\\codemagogue.h"
    static RGSDWORD* GetOpcodeDWORDVals() 
    {
        static RGSDWORD rgDWORDS[] = 
            					{
            						{0, 0}
            					};
        return rgDWORDS;
    }
#injected_line 25 "d:\\vc++\\atl internals 2e src\\chapter 07\\demagogue\\demagogue\\codemagogue.h"
    static RGSBinary* GetOpcodeBinaryVals() 
    {

        static RGSBinary rgBinary[] = 
            					{
            						{0, 0}
            					};
        return rgBinary;
    }
#injected_line 25 "d:\\vc++\\atl internals 2e src\\chapter 07\\demagogue\\demagogue\\codemagogue.h"
    static RGSStrings* GetOpcodeStringVals() 
    {
        static RGSStrings rgStrings[] = 
            					{
            						{_T(""),0 }, 
            {_T("Demagogue.Demagogue.1"),0 }, 
            {_T("%FriendlyName%"),1 }, 
            {_T("CLSID"),0 }, 
            {_T("{8FB5429F-5457-4ED7-8093-EDA710A68EB8}"),0 }, 
            {_T("Demagogue.Demagogue"),0 }, 
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
#injected_line 25 "d:\\vc++\\atl internals 2e src\\chapter 07\\demagogue\\demagogue\\codemagogue.h"
    static HRESULT WINAPI UpdateRegistry(BOOL bRegister) 
    {
        CRegistryVirtualMachine rvm;
        HRESULT hr;
        if (FAILED(hr = rvm.AddStandardReplacements()))
            return hr;
        rvm.AddReplacement(_T("FriendlyName"), GetObjectFriendlyName());
        return rvm.VMUpdateRegistry(GetOpCodes(), GetOpcodeStringVals(), GetOpcodeDWORDVals(), GetOpcodeBinaryVals(), bRegister);
    }
#injected_line 25 "d:\\vc++\\atl internals 2e src\\chapter 07\\demagogue\\demagogue\\codemagogue.h"
    static const TCHAR* GetObjectFriendlyName() 
    {
        return _T("CDemagogue Object");
    }
#injected_line 25 "d:\\vc++\\atl internals 2e src\\chapter 07\\demagogue\\demagogue\\codemagogue.h"
    static const TCHAR* GetProgID() 
    {
        return _T("Demagogue.Demagogue.1");
    }
#injected_line 25 "d:\\vc++\\atl internals 2e src\\chapter 07\\demagogue\\demagogue\\codemagogue.h"
    static const TCHAR* GetVersionIndependentProgID() 
    {
        return _T("Demagogue.Demagogue");
    }
#injected_line 25 "d:\\vc++\\atl internals 2e src\\chapter 07\\demagogue\\demagogue\\codemagogue.h"
    BEGIN_COM_MAP(CDemagogue)
        COM_INTERFACE_ENTRY(IDemagogue)
        COM_INTERFACE_ENTRY(IPersistPropertyBag)
        COM_INTERFACE_ENTRY(IPersist)
        COM_INTERFACE_ENTRY(IProvideClassInfo)
        COM_INTERFACE_ENTRY(ISupportErrorInfo)
    END_COM_MAP()
#injected_line 25 "d:\\vc++\\atl internals 2e src\\chapter 07\\demagogue\\demagogue\\codemagogue.h"

    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) 
        					
    {
        static const IID* rgErrorGuids[] = 
            						{
            							&__uuidof(IDemagogue)
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
#injected_line 25 "d:\\vc++\\atl internals 2e src\\chapter 07\\demagogue\\demagogue\\codemagogue.h"

				OBJECT_ENTRY_AUTO(__uuidof(CDemagogue), CDemagogue)
			
//--- End Injected Code For Attribute 'support_error_info'


