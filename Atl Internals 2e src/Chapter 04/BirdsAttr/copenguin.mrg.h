// Created by Microsoft (R) C/C++ Compiler Version 10.00.30319.01
//
// d:\vc++\atlinternals-src\chapter 04\birdsattr\copenguin.mrg.h
// compiler-generated file created 06/20/12 at 09:38:19
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

// CoPenguin.h : Declaration of the CPenguin

#pragma once
#include "resource.h"       // main symbols


// IPenguin
[
	object,
	dual,
	uuid("3C093AF2-1EFC-4FE9-B602-D5A23D967B77"),
	helpstring("IPenguin Interface"),
	pointer_default(unique)
]
__interface IPenguin : IDispatch
{
	[propget, id(1)] HRESULT Name([out, retval] BSTR* pVal);
	[propput, id(1)] HRESULT Name([in] BSTR newVal);
	[id(2)] HRESULT StraightenTie(void);
};

// IBird
[
	object,
	dual,
	uuid("92247816-FA98-4861-83AB-56FD45F37991"),
	helpstring("IBird Interface"),
	pointer_default(unique)
]
__interface IBird : IDispatch
{
	[propget, id(1)] HRESULT Wingspan([out, retval] LONG* pVal);
	[propput, id(1)] HRESULT Wingspan([in] LONG newVal);
	[id(2)] HRESULT Fly(void);
};

// CPenguin

[
	coclass,
	threading("single"),
	vi_progid("BirdsAttr.Penguin"),
	progid("BirdsAttr.Penguin.1"),
	version(1.0),
	uuid("F591F114-57D0-45DA-B627-5E859AB62248"),
	helpstring("Penguin Class")
]
class ATL_NO_VTABLE CPenguin : 
	public IPenguin,
	public IBird
,
    /*+++ Added Baseclass */ public IProvideClassInfoImpl<&__uuidof(CPenguin)>
{
public:
	CPenguin()
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

	// IPenguin
	STDMETHOD(get_Name)(BSTR* pVal);
	STDMETHOD(put_Name)(BSTR newVal);
	STDMETHOD(StraightenTie)(void);

	// IBird
	STDMETHOD(get_Wingspan)(LONG* pVal);
	STDMETHOD(put_Wingspan)(LONG newVal);
	STDMETHOD(Fly)(void);

	//+++ Start Injected Code For Attribute 'coclass'
#injected_line 40 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\copenguin.h"
    virtual HRESULT STDMETHODCALLTYPE IPenguin::Invoke(
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
        if (pDispParams->cArgs > 1) {
            return DISP_E_BADPARAMCOUNT;
        }
        if (pVarResult != 0) {
            ::VariantInit(pVarResult);
        }
        ATL::CComVariant rgVars[1];
        VARIANT* rgpVars[1];
        UINT index = 0;
        for (; index < pDispParams->cArgs; ++index) {
            rgpVars[index] = &pDispParams->rgvarg[index];
        }
        VARIANT v0;
        VARIANT* v;
        switch (dispIdMember) {
        case 1:
            {
                if (wFlags & 2) {
                    if (pDispParams->cArgs != 0) {
                        return DISP_E_BADPARAMCOUNT;
                    }
                    BSTR i1;
                    hr = ((::IPenguin*) this)->get_Name(&i1);
                    if (pVarResult != 0) {
                        V_VT(pVarResult) = VT_BSTR;
                        V_BSTR(pVarResult) = (BSTR) i1;
                    }
                    break;
                }
                else 
        if (wFlags & 4) {
                    if (pDispParams->cArgs != 1) {
                        return DISP_E_BADPARAMCOUNT;
                    }
                    v = rgpVars[0];
                    if (v->vt != VT_BSTR)
            {
                        rgVars[0] = *rgpVars[0];
                        v = &rgVars[0];
                        if (FAILED(__VariantChangeType(v, &v0, VT_BSTR))) {
                            if (puArgErr != 0) {
                                *puArgErr = 0;
                            }
                            return DISP_E_TYPEMISMATCH;
                        }
                    }
                    BSTR i1 = (BSTR) V_BSTR(v);
                    hr = ((::IPenguin*) this)->put_Name(i1);
                    break;
                }
            }
        case 2:
            {
                if (pDispParams->cArgs != 0) {
                    return DISP_E_BADPARAMCOUNT;
                }
                hr = ((::IPenguin*) this)->StraightenTie();
                break;
            }
        default:
            return DISP_E_MEMBERNOTFOUND;
        }
        if (FAILED(hr) && pExcepInfo != NULL)
        {
            AtlExcepInfoFromErrorInfo(hr, pExcepInfo);
        }
        return hr;
    }
    virtual HRESULT STDMETHODCALLTYPE IPenguin::GetIDsOfNames(
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
        static LPOLESTR names[] = { L"Name", L"pVal", L"get_Name", L"put_Name", L"StraightenTie" };
        static DISPID dids[] = { 1, 0, 1, 1, 2 };
        for (unsigned int i = 0; i < cNames; ++i) {
            int fFoundIt = 0;
            for (unsigned int j = 0; j < sizeof(names)/sizeof(LPOLESTR); ++j) {
                if (_wcsicmp(rgszNames[i], names[j]) == 0) {
                    fFoundIt = 1;
                    rgDispId[i] = dids[j];
                    break;
                }
            }
            if (fFoundIt == 0) {
                return DISP_E_UNKNOWNNAME;
            }
        }
        return S_OK;
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
    virtual HRESULT STDMETHODCALLTYPE IPenguin::GetTypeInfoCount(unsigned int*  pctinfo) 
    {
        if (pctinfo == NULL) {
            return E_POINTER;
        }
        CComPtr<ITypeInfo> spTypeInfo;
        *pctinfo = 
                       (SUCCEEDED(TypeInfoHelper(__uuidof(IPenguin), 0, &spTypeInfo))) ? 1 : 0;
        return S_OK;
    }
    virtual HRESULT STDMETHODCALLTYPE IPenguin::GetTypeInfo(unsigned int iTInfo, LCID lcid, ITypeInfo** ppTInfo) 
    {
        if (iTInfo != 0) {
            return DISP_E_BADINDEX;
        }
        return TypeInfoHelper(__uuidof(IPenguin), lcid, ppTInfo);
    }
#injected_line 40 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\copenguin.h"
    virtual HRESULT STDMETHODCALLTYPE IBird::Invoke(
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
        if (pDispParams->cArgs > 1) {
            return DISP_E_BADPARAMCOUNT;
        }
        if (pVarResult != 0) {
            ::VariantInit(pVarResult);
        }
        ATL::CComVariant rgVars[1];
        VARIANT* rgpVars[1];
        UINT index = 0;
        for (; index < pDispParams->cArgs; ++index) {
            rgpVars[index] = &pDispParams->rgvarg[index];
        }
        VARIANT v0;
        VARIANT* v;
        switch (dispIdMember) {
        case 1:
            {
                if (wFlags & 2) {
                    if (pDispParams->cArgs != 0) {
                        return DISP_E_BADPARAMCOUNT;
                    }
                    long i1;
                    hr = ((::IBird*) this)->get_Wingspan(&i1);
                    if (pVarResult != 0) {
                        V_VT(pVarResult) = VT_I4;
                        V_I4(pVarResult) = i1;
                    }
                    break;
                }
                else 
        if (wFlags & 4) {
                    if (pDispParams->cArgs != 1) {
                        return DISP_E_BADPARAMCOUNT;
                    }
                    v = rgpVars[0];
                    if (v->vt != VT_I4)
            {
                        rgVars[0] = *rgpVars[0];
                        v = &rgVars[0];
                        if (FAILED(__VariantChangeType(v, &v0, VT_I4))) {
                            if (puArgErr != 0) {
                                *puArgErr = 0;
                            }
                            return DISP_E_TYPEMISMATCH;
                        }
                    }
                    long i1 = V_I4(v);
                    hr = ((::IBird*) this)->put_Wingspan(i1);
                    break;
                }
            }
        case 2:
            {
                if (pDispParams->cArgs != 0) {
                    return DISP_E_BADPARAMCOUNT;
                }
                hr = ((::IBird*) this)->Fly();
                break;
            }
        default:
            return DISP_E_MEMBERNOTFOUND;
        }
        if (FAILED(hr) && pExcepInfo != NULL)
        {
            AtlExcepInfoFromErrorInfo(hr, pExcepInfo);
        }
        return hr;
    }
    virtual HRESULT STDMETHODCALLTYPE IBird::GetIDsOfNames(
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
        static LPOLESTR names[] = { L"Wingspan", L"pVal", L"get_Wingspan", L"put_Wingspan", L"Fly" };
        static DISPID dids[] = { 1, 0, 1, 1, 2 };
        for (unsigned int i = 0; i < cNames; ++i) {
            int fFoundIt = 0;
            for (unsigned int j = 0; j < sizeof(names)/sizeof(LPOLESTR); ++j) {
                if (_wcsicmp(rgszNames[i], names[j]) == 0) {
                    fFoundIt = 1;
                    rgDispId[i] = dids[j];
                    break;
                }
            }
            if (fFoundIt == 0) {
                return DISP_E_UNKNOWNNAME;
            }
        }
        return S_OK;
    }
    virtual HRESULT STDMETHODCALLTYPE IBird::GetTypeInfoCount(unsigned int*  pctinfo) 
    {
        if (pctinfo == NULL) {
            return E_POINTER;
        }
        CComPtr<ITypeInfo> spTypeInfo;
        *pctinfo = 
                       (SUCCEEDED(TypeInfoHelper(__uuidof(IBird), 0, &spTypeInfo))) ? 1 : 0;
        return S_OK;
    }
    virtual HRESULT STDMETHODCALLTYPE IBird::GetTypeInfo(unsigned int iTInfo, LCID lcid, ITypeInfo** ppTInfo) 
    {
        if (iTInfo != 0) {
            return DISP_E_BADINDEX;
        }
        return TypeInfoHelper(__uuidof(IBird), lcid, ppTInfo);
    }
#injected_line 40 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\copenguin.h"
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
            0x80030000,
            0x60000000,
            0x8003400e,
            0x3003c000,
            0x80000010,
            0x50000000,
            0x60000000,
            0x60000000,
            0x60000000,
            0x60000000,
            0
            					};
        return rgOps;
    }
#injected_line 40 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\copenguin.h"
    static RGSDWORD* GetOpcodeDWORDVals() 
    {
        static RGSDWORD rgDWORDS[] = 
            					{
            						{0, 0}
            					};
        return rgDWORDS;
    }
#injected_line 40 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\copenguin.h"
    static RGSBinary* GetOpcodeBinaryVals() 
    {

        static RGSBinary rgBinary[] = 
            					{
            						{0, 0}
            					};
        return rgBinary;
    }
#injected_line 40 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\copenguin.h"
    static RGSStrings* GetOpcodeStringVals() 
    {
        static RGSStrings rgStrings[] = 
            					{
            						{_T(""),0 }, 
            {_T("BirdsAttr.Penguin.1"),0 }, 
            {_T("%FriendlyName%"),1 }, 
            {_T("CLSID"),0 }, 
            {_T("{F591F114-57D0-45DA-B627-5E859AB62248}"),0 }, 
            {_T("BirdsAttr.Penguin"),0 }, 
            {_T("CurVer"),0 }, 
            {_T("ProgID"),0 }, 
            {_T("VersionIndependentProgID"),0 }, 
            {_T("Programmable"),0 }, 
            {_T("%MODULETYPE%"),1 }, 
            {_T("%MODULE%"),1 }, 
            {_T("ThreadingModel"),0 }, 
            {_T("AppID"),0 }, 
            {_T("%APPID%"),1 }, 
            {_T("TypeLib"),0 }, 
            {_T("%MODULEGUID%"),1 }, 
            {NULL, 0}
            					};
        return rgStrings;
    }
#injected_line 40 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\copenguin.h"
    static HRESULT WINAPI UpdateRegistry(BOOL bRegister) 
    {
        CRegistryVirtualMachine rvm;
        HRESULT hr;
        if (FAILED(hr = rvm.AddStandardReplacements()))
            return hr;
        rvm.AddReplacement(_T("FriendlyName"), GetObjectFriendlyName());
        return rvm.VMUpdateRegistry(GetOpCodes(), GetOpcodeStringVals(), GetOpcodeDWORDVals(), GetOpcodeBinaryVals(), bRegister);
    }
#injected_line 40 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\copenguin.h"
    static const TCHAR* GetObjectFriendlyName() 
    {
        return _T("CPenguin Object");
    }
#injected_line 40 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\copenguin.h"
    static const TCHAR* GetProgID() 
    {
        return _T("BirdsAttr.Penguin.1");
    }
#injected_line 40 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\copenguin.h"
    static const TCHAR* GetVersionIndependentProgID() 
    {
        return _T("BirdsAttr.Penguin");
    }
#injected_line 40 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\copenguin.h"
    BEGIN_COM_MAP(CPenguin)
        COM_INTERFACE_ENTRY(IPenguin)
        COM_INTERFACE_ENTRY2(IDispatch, IPenguin)
        COM_INTERFACE_ENTRY(IBird)
        COM_INTERFACE_ENTRY(IProvideClassInfo)
    END_COM_MAP()

	//--- End Injected Code For Attribute 'coclass'
};

//+++ Start Injected Code For Attribute 'coclass'
#injected_line 40 "d:\\vc++\\atlinternals-src\\chapter 04\\birdsattr\\copenguin.h"

				OBJECT_ENTRY_AUTO(__uuidof(CPenguin), CPenguin)
			
//--- End Injected Code For Attribute 'coclass'


