// Created by Microsoft (R) C/C++ Compiler Version 10.00.30319.01
//
// d:\vc++\atlinternals-src\chapter 01\pisvr\attributed\pisvr\calcpi.mrg.h
// compiler-generated file created 06/19/12 at 10:20:11
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

// CalcPi.h : Declaration of the CCalcPi

#pragma once
#include "resource.h"       // main symbols


// ICalcPi
[
	object,
	uuid("6E9761C5-336F-4C41-AF16-57BBDE593FF0"),
	dual,	helpstring("ICalcPi Interface"),
	pointer_default(unique)
]
__interface ICalcPi : IDispatch
{
	[propget, id(1), helpstring("property Digits")] HRESULT Digits([out, retval] LONG* pVal);
	[propput, id(1), helpstring("property Digits")] HRESULT Digits([in] LONG newVal);
	[id(2), helpstring("method CalcPi")] HRESULT CalcPi([out,retval] BSTR* pbstrPi);
};

// _ICalcPiEvents
[
	dispinterface,
	uuid("B830F523-D87B-434F-933A-623CEF6FC4AA"),
	helpstring("_ICalcPiEvents Interface")
]
__interface _ICalcPiEvents
{
    [id(1)] void OnDigit([in] short nIndex, [in] short nDigit);
};


// IAdvertiseMyself
[
	object,
	uuid("48AC9A07-9E9E-438B-AC87-DCF0F62E729E"),
	helpstring("IAdvertiseMyself Interface"),
	pointer_default(unique)
]
__interface IAdvertiseMyself : IUnknown
{
	[helpstring("method ShowAd")] HRESULT ShowAd([in] BSTR bstrClient);
};

//+++ Start Injected Code For Attribute 'event'
#injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
#pragma comment(lib, "comsupp.lib")

//--- End Injected Code For Attribute 'event'


// CCalcPi
[
	coclass,
	threading("apartment"),
	support_error_info("ICalcPi"),
	event_source("com"),
	vi_progid("PiSvr.CalcPi"),
	progid("PiSvr.CalcPi.1"),
	version(1.0),
	uuid("E5F91723-E7AD-4596-AC90-17586D400BF7"),
	helpstring("CalcPi Class"),
	implements_category("CATID_SafeForScripting"),
	implements_category("CATID_SafeForInitializing")
]
class ATL_NO_VTABLE CCalcPi : 
	public ICalcPi,
	public IAdvertiseMyself,
	public IPersistPropertyBagImpl<CCalcPi>
//	public IDispatchImpl<ICalcPi, &__uuidof(ICalcPi), &__uuidof(PiSvr), /*wMajor =*/ 1, /*wMinor=*/ 0>

,
    /*+++ Added Baseclass */ public ISupportErrorInfo
,
    /*+++ Added Baseclass */ public IProvideClassInfo2Impl<&__uuidof(CCalcPi), &__uuidof(::_ICalcPiEvents)>
{
public:
	CCalcPi()
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

	BEGIN_PROP_MAP(CCalcPi)
		PROP_ENTRY("Digits", 1, CLSID_NULL)
	END_PROP_MAP()


	// ICalcPi
	STDMETHOD(get_Digits)(LONG* pVal);
	STDMETHOD(put_Digits)(LONG newVal);
	STDMETHOD(CalcPi)(BSTR* pbstrPi);


	// IAdvertiseMyself Methods
public:
	STDMETHOD(ShowAd)(BSTR  bstrClient)
	{
		// Add your function implementation here.
		return E_NOTIMPL;
	}
	
public:
	BOOL m_bRequiresSave;

	__event __interface _ICalcPiEvents;

private:
  long m_nDigits;

	//+++ Start Injected Code For Attribute 'event'
#injected_line 47 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
    virtual HRESULT STDMETHODCALLTYPE ICalcPi::Invoke(
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
                    hr = ((::ICalcPi*) this)->get_Digits(&i1);
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
                    hr = ((::ICalcPi*) this)->put_Digits(i1);
                    break;
                }
            }
        case 2:
            {
                if (pDispParams->cArgs != 0) {
                    return DISP_E_BADPARAMCOUNT;
                }
                BSTR i1;
                hr = ((::ICalcPi*) this)->CalcPi(&i1);
                if (pVarResult != 0) {
                    V_VT(pVarResult) = VT_BSTR;
                    V_BSTR(pVarResult) = (BSTR) i1;
                }
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
    virtual HRESULT STDMETHODCALLTYPE ICalcPi::GetIDsOfNames(
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
        static LPOLESTR names[] = { L"Digits", L"pVal", L"get_Digits", L"put_Digits", L"pbstrPi", L"CalcPi" };
        static DISPID dids[] = { 1, 0, 1, 1, 0, 2 };
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
    virtual HRESULT STDMETHODCALLTYPE ICalcPi::GetTypeInfoCount(unsigned int*  pctinfo) 
    {
        if (pctinfo == NULL) {
            return E_POINTER;
        }
        CComPtr<ITypeInfo> spTypeInfo;
        *pctinfo = 
                       (SUCCEEDED(TypeInfoHelper(__uuidof(ICalcPi), 0, &spTypeInfo))) ? 1 : 0;
        return S_OK;
    }
    virtual HRESULT STDMETHODCALLTYPE ICalcPi::GetTypeInfo(unsigned int iTInfo, LCID lcid, ITypeInfo** ppTInfo) 
    {
        if (iTInfo != 0) {
            return DISP_E_BADINDEX;
        }
        return TypeInfoHelper(__uuidof(ICalcPi), lcid, ppTInfo);
    }
#injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
    HRESULT OnDigit(short i1,short i2) 
    {
        HRESULT hrRet = S_OK;
        HRESULT hr = S_OK;
        IConnectionPointImpl<CCalcPi, &__uuidof(_ICalcPiEvents), CComDynamicUnkArray>* p = this;
        VARIANT rgvars[2];
        Lock();
        IUnknown** pp = NULL;
        __try 
        {
            pp = p->m_vec.begin();
        }
        __finally 
        {
            Unlock();
        }
        while (pp < p->m_vec.end()) {
            if (*pp != NULL) {
                IDispatch* pDispatch = (IDispatch*) *pp;
                ::VariantInit(&rgvars[1]);
                rgvars[1].vt = VT_I2;
                V_I2(&rgvars[1])= i1;
                ::VariantInit(&rgvars[0]);
                rgvars[0].vt = VT_I2;
                V_I2(&rgvars[0])= i2;
                DISPPARAMS disp = { rgvars, NULL, 2, 0 };
                VARIANT ret_val;
                hr = __ComInvokeEventHandler(pDispatch, 1, 1, &disp, &ret_val);
                if (FAILED(hr)) {
                    hrRet = hr;
                }
            }
            pp++;
        }
        return hrRet;
    }

	//--- End Injected Code For Attribute 'event'

	//+++ Start Injected Code For Attribute 'support_error_info'
#injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
    BEGIN_CONNECTION_POINT_MAP(CCalcPi)
        CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
        #injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
        CONNECTION_POINT_ENTRY(__uuidof(::_ICalcPiEvents))
        #injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
    END_CONNECTION_POINT_MAP()
#injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
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
#injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
    static RGSDWORD* GetOpcodeDWORDVals() 
    {
        static RGSDWORD rgDWORDS[] = 
            					{
            						{0, 0}
            					};
        return rgDWORDS;
    }
#injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
    static RGSBinary* GetOpcodeBinaryVals() 
    {

        static RGSBinary rgBinary[] = 
            					{
            						{0, 0}
            					};
        return rgBinary;
    }
#injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
    static RGSStrings* GetOpcodeStringVals() 
    {
        static RGSStrings rgStrings[] = 
            					{
            						{_T(""),0 }, 
            {_T("PiSvr.CalcPi.1"),0 }, 
            {_T("%FriendlyName%"),1 }, 
            {_T("CLSID"),0 }, 
            {_T("{E5F91723-E7AD-4596-AC90-17586D400BF7}"),0 }, 
            {_T("PiSvr.CalcPi"),0 }, 
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
#injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
    static HRESULT WINAPI UpdateRegistry(BOOL bRegister) 
    {
        CRegistryVirtualMachine rvm;
        HRESULT hr;
        if (FAILED(hr = rvm.AddStandardReplacements()))
            return hr;
        rvm.AddReplacement(_T("FriendlyName"), GetObjectFriendlyName());
        return rvm.VMUpdateRegistry(GetOpCodes(), GetOpcodeStringVals(), GetOpcodeDWORDVals(), GetOpcodeBinaryVals(), bRegister);
    }
#injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
    static const TCHAR* GetObjectFriendlyName() 
    {
        return _T("CCalcPi Object");
    }
#injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
    static const TCHAR* GetProgID() 
    {
        return _T("PiSvr.CalcPi.1");
    }
#injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
    static const TCHAR* GetVersionIndependentProgID() 
    {
        return _T("PiSvr.CalcPi");
    }
#injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"
    BEGIN_COM_MAP(CCalcPi)
        COM_INTERFACE_ENTRY(ICalcPi)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(IAdvertiseMyself)
        COM_INTERFACE_ENTRY(IPersistPropertyBag)
        COM_INTERFACE_ENTRY(IPersist)
        COM_INTERFACE_ENTRY(IConnectionPointContainer)
        COM_INTERFACE_ENTRY(ISupportErrorInfo)
        COM_INTERFACE_ENTRY(IProvideClassInfo2)
        COM_INTERFACE_ENTRY(IProvideClassInfo)
    END_COM_MAP()
#injected_line 106 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"

    BEGIN_CATEGORY_MAP(CCalcPi)
        IMPLEMENTED_CATEGORY(CATID_SafeForScripting)
        IMPLEMENTED_CATEGORY(CATID_SafeForInitializing)
    END_CATEGORY_MAP()
#injected_line 49 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"

    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) 
        					
    {
        static const IID* rgErrorGuids[] = 
            						{
            							&__uuidof(ICalcPi)
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
#injected_line 49 "d:\\vc++\\atlinternals-src\\chapter 01\\pisvr\\attributed\\pisvr\\calcpi.h"

				OBJECT_ENTRY_AUTO(__uuidof(CCalcPi), CCalcPi)
			
//--- End Injected Code For Attribute 'support_error_info'


