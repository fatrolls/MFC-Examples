// Created by Microsoft (R) C/C++ Compiler Version 10.00.30319.01
//
// d:\vc++\atl internals 2e src\chapter 05\mathdll\cocalc.mrg.h
// compiler-generated file created 06/21/12 at 10:02:05
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

// CoCalc.h : Declaration of the CCalc

#pragma once
#include "resource.h"       // main symbols


// ICalc
[
	object,
	uuid("D4A66BDB-EF09-4968-A8AA-7BA5C48AF6BD"),
	dual,	helpstring("ICalc Interface"),
	pointer_default(unique)
]
__interface ICalc : IDispatch
{
};


static const GUID CATID_ATLINTERNALS_SAMPLES = 
{0xd22ff22, 0x28cc, 0x11d2, {0xab, 0xdd, 0x0, 0xa0, 0xc9, 0xc8, 0xe5, 0xd}};

static const GUID CATID_IMPLEMENTED_1 = 
{ 0x24344b98, 0xd4df, 0x4313, { 0x99, 0x57, 0xce, 0x6c, 0xae, 0xf4, 0xe9, 0x2c } };

static const GUID CATID_REQUIRED_1 = 
{ 0x35a3ddfa, 0x1ee5, 0x472b, { 0x9b, 0xa8, 0x1a, 0xb8, 0x72, 0x90, 0x35, 0x43 } };



// CCalc

[
	coclass,
	threading("apartment"),
	vi_progid("MathDll.Calc"),
	progid("MathDll.Calc.1"),
	version(1.0),
	uuid("7A077EBD-04CC-41BA-995C-C62DC6EE61D7"),
//	implements_category("CATID_ATLINTERNALS_SAMPLES"),
	helpstring("Calc Class")
]
class ATL_NO_VTABLE CCalc : 
	public ICalc
,
    /*+++ Added Baseclass */ public IProvideClassInfoImpl<&__uuidof(CCalc)>
{
public:
	CCalc()
	{
	}

	BEGIN_CATEGORY_MAP(CCalc)
		IMPLEMENTED_CATEGORY(CATID_IMPLEMENTED_1)
		REQUIRED_CATEGORY(CATID_REQUIRED_1)
	END_CATEGORY_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:


	//+++ Start Injected Code For Attribute 'coclass'
#injected_line 33 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathdll\\cocalc.h"
    virtual HRESULT STDMETHODCALLTYPE ICalc::Invoke(
                /* [in] */ DISPID dispIdMember,
                /* [in] */ REFIID riid,
                /* [in] */ LCID lcid,
                /* [in] */ WORD wFlags,
                /* [out][in] */ DISPPARAMS *pDispParams,
                /* [out] */ VARIANT *pVarResult,
                /* [out] */ EXCEPINFO *pExcepInfo,
                /* [out] */ UINT *puArgErr) 
    {
        (void) riid;
        (void) dispIdMember;
        (void) lcid;
        (void) wFlags;
        (void) pExcepInfo;
        (void) puArgErr;
        HRESULT hr = S_OK;
        if (pDispParams == 0) {
            return DISP_E_BADVARTYPE;
        }
        if (pDispParams->cArgs > 0) {
            return DISP_E_BADPARAMCOUNT;
        }
        if (pVarResult != 0) {
            ::VariantInit(pVarResult);
        }
        return DISP_E_MEMBERNOTFOUND;
    }
    virtual HRESULT STDMETHODCALLTYPE ICalc::GetIDsOfNames(
                /* [in] */ REFIID riid,
                /* [size_is][in] */ LPOLESTR *rgszNames,
                /* [in] */ UINT cNames,
                /* [in] */ LCID lcid,
                /* [size_is][out] */ DISPID *rgDispId) 
    {
        (void) riid;
        (void) rgszNames;
        (void) cNames;
        (void) lcid;
        (void) rgDispId;
        return DISP_E_UNKNOWNNAME;
    }
    HRESULT TypeInfoHelper(REFIID iidDisp, LCID /*lcid*/, ITypeInfo** ppTypeInfo) 
    {
        if (ppTypeInfo == NULL) {
            return E_POINTER;
        }
        *ppTypeInfo = NULL;
        TCHAR szModule1[_MAX_PATH];
        int nLen = ::GetModuleFileName(_AtlBaseModule.GetModuleInstance(), szModule1, _MAX_PATH);
        if (nLen == 0 || nLen == _MAX_PATH) {
            return E_FAIL;
        }
        USES_CONVERSION_EX;
        LPOLESTR pszModule = T2OLE_EX(szModule1, _ATL_SAFE_ALLOCA_DEF_THRESHOLD);
#ifndef _UNICODE
        if (pszModule == NULL) {
            return E_OUTOFMEMORY;
        }
#endif
        CComPtr<ITypeLib> spTypeLib;
        HRESULT hr = LoadTypeLib(pszModule, &spTypeLib);
        if (SUCCEEDED(hr)) {
            CComPtr<ITypeInfo> spTypeInfo;
            hr = spTypeLib->GetTypeInfoOfGuid(iidDisp, &spTypeInfo);
            if (SUCCEEDED(hr)) {
                *ppTypeInfo = spTypeInfo.Detach();
            }
        }
        return hr;
    }
    virtual HRESULT STDMETHODCALLTYPE ICalc::GetTypeInfoCount(unsigned int*  pctinfo) 
    {
        if (pctinfo == NULL) {
            return E_POINTER;
        }
        CComPtr<ITypeInfo> spTypeInfo;
        *pctinfo = 
                       (SUCCEEDED(TypeInfoHelper(__uuidof(ICalc), 0, &spTypeInfo))) ? 1 : 0;
        return S_OK;
    }
    virtual HRESULT STDMETHODCALLTYPE ICalc::GetTypeInfo(unsigned int iTInfo, LCID lcid, ITypeInfo** ppTInfo) 
    {
        if (iTInfo != 0) {
            return DISP_E_BADINDEX;
        }
        return TypeInfoHelper(__uuidof(ICalc), lcid, ppTInfo);
    }
#injected_line 33 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathdll\\cocalc.h"
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
#injected_line 33 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathdll\\cocalc.h"
    static RGSDWORD* GetOpcodeDWORDVals() 
    {
        static RGSDWORD rgDWORDS[] = 
            					{
            						{0, 0}
            					};
        return rgDWORDS;
    }
#injected_line 33 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathdll\\cocalc.h"
    static RGSBinary* GetOpcodeBinaryVals() 
    {

        static RGSBinary rgBinary[] = 
            					{
            						{0, 0}
            					};
        return rgBinary;
    }
#injected_line 33 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathdll\\cocalc.h"
    static RGSStrings* GetOpcodeStringVals() 
    {
        static RGSStrings rgStrings[] = 
            					{
            						{_T(""),0 }, 
            {_T("MathDll.Calc.1"),0 }, 
            {_T("%FriendlyName%"),1 }, 
            {_T("CLSID"),0 }, 
            {_T("{7A077EBD-04CC-41BA-995C-C62DC6EE61D7}"),0 }, 
            {_T("MathDll.Calc"),0 }, 
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
#injected_line 33 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathdll\\cocalc.h"
    static HRESULT WINAPI UpdateRegistry(BOOL bRegister) 
    {
        CRegistryVirtualMachine rvm;
        HRESULT hr;
        if (FAILED(hr = rvm.AddStandardReplacements()))
            return hr;
        rvm.AddReplacement(_T("FriendlyName"), GetObjectFriendlyName());
        return rvm.VMUpdateRegistry(GetOpCodes(), GetOpcodeStringVals(), GetOpcodeDWORDVals(), GetOpcodeBinaryVals(), bRegister);
    }
#injected_line 33 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathdll\\cocalc.h"
    static const TCHAR* GetObjectFriendlyName() 
    {
        return _T("CCalc Object");
    }
#injected_line 33 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathdll\\cocalc.h"
    static const TCHAR* GetProgID() 
    {
        return _T("MathDll.Calc.1");
    }
#injected_line 33 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathdll\\cocalc.h"
    static const TCHAR* GetVersionIndependentProgID() 
    {
        return _T("MathDll.Calc");
    }
#injected_line 33 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathdll\\cocalc.h"
    BEGIN_COM_MAP(CCalc)
        COM_INTERFACE_ENTRY(ICalc)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(IProvideClassInfo)
    END_COM_MAP()

	//--- End Injected Code For Attribute 'coclass'
};

//+++ Start Injected Code For Attribute 'coclass'
#injected_line 33 "d:\\vc++\\atl internals 2e src\\chapter 05\\mathdll\\cocalc.h"

				OBJECT_ENTRY_AUTO(__uuidof(CCalc), CCalc)
			
//--- End Injected Code For Attribute 'coclass'


