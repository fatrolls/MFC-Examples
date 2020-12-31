// Created by Microsoft (R) C/C++ Compiler Version 10.00.30319.01
//
// d:\vc++\atl internals 2e src\chapter 09\speaker\speaker\codemagogue.mrg.h
// compiler-generated file created 06/21/12 at 15:18:03
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
	const int DISPID_VOLUME         = 1;
	[idl_quote("const int DISPID_VOLUME         = 1;")];
	const int DISPID_SPEECH         = 2;
	[idl_quote("const int DISPID_SPEECH         = 2;")];
	const int DISPID_SPEAK          = 3;
	[idl_quote("const int DISPID_SPEAK          = 3;")];
[
	object,
	uuid("4C5AC360-51D5-4DA2-84F2-992D8584B807"),
	dual,	helpstring("ISpeaker Interface"),
	pointer_default(unique)
]
__interface ISpeaker : IDispatch
{
	[propget, id(DISPID_VOLUME), helpstring("property Volume")] HRESULT Volume([out, retval] LONG* pVal);
	[propput, id(DISPID_VOLUME), helpstring("property Volume")] HRESULT Volume([in] LONG newVal);
	[propget, id(DISPID_SPEECH), helpstring("property Speech")] HRESULT Speech([out, retval] BSTR* pVal);
	[propput, id(DISPID_SPEECH), helpstring("property Speech")] HRESULT Speech([in] BSTR newVal);
	[id(DISPID_SPEAK), helpstring("method Speak")] HRESULT Speak(void);
};

// INamedObject
	const int DISPID_NAME           = 1;
	[idl_quote("const int DISPID_NAME           = 1;")];
[
	object,
	uuid(450D6780-FC73-11d1-8CC3-00A0C9C8E50D),
	dual,
	helpstring("INamedObject Interface"),
	pointer_default(unique)
]
__interface INamedObject : IDispatch
{
	[propget, id(DISPID_NAME), helpstring("property Name")] HRESULT Name([out, retval] BSTR *pVal);
	[propput, id(DISPID_NAME), helpstring("property Name")] HRESULT Name([in] BSTR newVal);
};

// _IDemagogueEvents
	const int DISPID_ONWHISPER      = 1;
	[idl_quote("const int DISPID_ONWHISPER      = 1;")];
	const int DISPID_ONTALK         = 2;
	[idl_quote("const int DISPID_ONTALK         = 2;")];
	const int DISPID_ONYELL         = 3;
	[idl_quote("const int DISPID_ONYELL         = 3;")];
[
	dispinterface,
	uuid("EF75866F-28FA-4411-8A7D-AE7B65BB7F95"),
	helpstring("_ISpeakerEvents Interface")
]
__interface _ISpeakerEvents
{	
	[id(DISPID_ONWHISPER), helpstring("method OnWhisper")] HRESULT OnWhisper(BSTR bstrSpeech);
	[id(DISPID_ONTALK), helpstring("method OnTalk")]    HRESULT OnTalk(BSTR bstrSpeech);
	[id(DISPID_ONYELL), helpstring("method OnYell")]    HRESULT OnYell(BSTR bstrSpeech);
};

//+++ Start Injected Code For Attribute 'event'
#injected_line 84 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
#pragma comment(lib, "comsupp.lib")

//--- End Injected Code For Attribute 'event'


// CDemagogue

[
	coclass,
	event_source(com),
	threading("apartment"),
	support_error_info("ISpeaker"),
	vi_progid("Speaker.Demagogue"),
	progid("Speaker.Demagogue.1"),
	version(1.0),
	uuid("798AC41B-03D6-45A7-8311-8056A7EF0CFD"),
	helpstring("Demagogue Class"),
	default(INamedObject, _ISpeakerEvents)
]
class ATL_NO_VTABLE CDemagogue : 
	public ISpeaker,
	public INamedObject
,
    /*+++ Added Baseclass */ public ISupportErrorInfo
,
    /*+++ Added Baseclass */ public IProvideClassInfo2Impl<&__uuidof(CDemagogue), &__uuidof(::_ISpeakerEvents)>
{
public:

	__event __interface _ISpeakerEvents;

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	
// INamedObject
	STDMETHOD(get_Name)(BSTR * pVal)
	{
		if (pVal == NULL) return E_POINTER;
		
        *pVal = m_bstrName.Copy ();
		return S_OK;
	}
	STDMETHOD(put_Name)(BSTR pVal)
	{
		m_bstrName = pVal;
        return S_OK;
	}

	STDMETHOD(get_Volume)(LONG* pVal);
	STDMETHOD(put_Volume)(LONG newVal);
	STDMETHOD(get_Speech)(BSTR* pVal);
	STDMETHOD(put_Speech)(BSTR newVal);
	STDMETHOD(Speak)(void);
	
private:
	CComBSTR m_bstrName;
    long     m_nVolume;
	CComBSTR m_bstrSpeech;

	//+++ Start Injected Code For Attribute 'event'
#injected_line 67 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
    virtual HRESULT STDMETHODCALLTYPE ISpeaker::Invoke(
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
                    hr = ((::ISpeaker*) this)->get_Volume(&i1);
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
                    hr = ((::ISpeaker*) this)->put_Volume(i1);
                    break;
                }
            }
        case 2:
            {
                if (wFlags & 2) {
                    if (pDispParams->cArgs != 0) {
                        return DISP_E_BADPARAMCOUNT;
                    }
                    BSTR i1;
                    hr = ((::ISpeaker*) this)->get_Speech(&i1);
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
                    hr = ((::ISpeaker*) this)->put_Speech(i1);
                    break;
                }
            }
        case 3:
            {
                if (pDispParams->cArgs != 0) {
                    return DISP_E_BADPARAMCOUNT;
                }
                hr = ((::ISpeaker*) this)->Speak();
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
    virtual HRESULT STDMETHODCALLTYPE ISpeaker::GetIDsOfNames(
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
        static LPOLESTR names[] = { L"Volume", L"pVal", L"get_Volume", L"put_Volume", L"Speech", L"get_Speech", L"put_Speech", L"Speak" };
        static DISPID dids[] = { 1, 0, 1, 1, 2, 2, 2, 3 };
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
    virtual HRESULT STDMETHODCALLTYPE ISpeaker::GetTypeInfoCount(unsigned int*  pctinfo) 
    {
        if (pctinfo == NULL) {
            return E_POINTER;
        }
        CComPtr<ITypeInfo> spTypeInfo;
        *pctinfo = 
                       (SUCCEEDED(TypeInfoHelper(__uuidof(ISpeaker), 0, &spTypeInfo))) ? 1 : 0;
        return S_OK;
    }
    virtual HRESULT STDMETHODCALLTYPE ISpeaker::GetTypeInfo(unsigned int iTInfo, LCID lcid, ITypeInfo** ppTInfo) 
    {
        if (iTInfo != 0) {
            return DISP_E_BADINDEX;
        }
        return TypeInfoHelper(__uuidof(ISpeaker), lcid, ppTInfo);
    }
#injected_line 67 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
    virtual HRESULT STDMETHODCALLTYPE INamedObject::Invoke(
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
                    hr = ((::INamedObject*) this)->get_Name(&i1);
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
                    hr = ((::INamedObject*) this)->put_Name(i1);
                    break;
                }
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
    virtual HRESULT STDMETHODCALLTYPE INamedObject::GetIDsOfNames(
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
        static LPOLESTR names[] = { L"Name", L"pVal", L"get_Name", L"put_Name" };
        static DISPID dids[] = { 1, 0, 1, 1 };
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
    virtual HRESULT STDMETHODCALLTYPE INamedObject::GetTypeInfoCount(unsigned int*  pctinfo) 
    {
        if (pctinfo == NULL) {
            return E_POINTER;
        }
        CComPtr<ITypeInfo> spTypeInfo;
        *pctinfo = 
                       (SUCCEEDED(TypeInfoHelper(__uuidof(INamedObject), 0, &spTypeInfo))) ? 1 : 0;
        return S_OK;
    }
    virtual HRESULT STDMETHODCALLTYPE INamedObject::GetTypeInfo(unsigned int iTInfo, LCID lcid, ITypeInfo** ppTInfo) 
    {
        if (iTInfo != 0) {
            return DISP_E_BADINDEX;
        }
        return TypeInfoHelper(__uuidof(INamedObject), lcid, ppTInfo);
    }
#injected_line 84 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
    HRESULT OnWhisper(::BSTR i1) 
    {
        HRESULT hrRet = S_OK;
        HRESULT hr = S_OK;
        IConnectionPointImpl<CDemagogue, &__uuidof(_ISpeakerEvents), CComDynamicUnkArray>* p = this;
        VARIANT rgvars[1];
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
                ::VariantInit(&rgvars[0]);
                rgvars[0].vt = VT_BSTR;
                V_BSTR(&rgvars[0])= (BSTR) i1;
                DISPPARAMS disp = { rgvars, NULL, 1, 0 };
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
    HRESULT OnTalk(::BSTR i1) 
    {
        HRESULT hrRet = S_OK;
        HRESULT hr = S_OK;
        IConnectionPointImpl<CDemagogue, &__uuidof(_ISpeakerEvents), CComDynamicUnkArray>* p = this;
        VARIANT rgvars[1];
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
                ::VariantInit(&rgvars[0]);
                rgvars[0].vt = VT_BSTR;
                V_BSTR(&rgvars[0])= (BSTR) i1;
                DISPPARAMS disp = { rgvars, NULL, 1, 0 };
                VARIANT ret_val;
                hr = __ComInvokeEventHandler(pDispatch, 2, 1, &disp, &ret_val);
                if (FAILED(hr)) {
                    hrRet = hr;
                }
            }
            pp++;
        }
        return hrRet;
    }
    HRESULT OnYell(::BSTR i1) 
    {
        HRESULT hrRet = S_OK;
        HRESULT hr = S_OK;
        IConnectionPointImpl<CDemagogue, &__uuidof(_ISpeakerEvents), CComDynamicUnkArray>* p = this;
        VARIANT rgvars[1];
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
                ::VariantInit(&rgvars[0]);
                rgvars[0].vt = VT_BSTR;
                V_BSTR(&rgvars[0])= (BSTR) i1;
                DISPPARAMS disp = { rgvars, NULL, 1, 0 };
                VARIANT ret_val;
                hr = __ComInvokeEventHandler(pDispatch, 3, 1, &disp, &ret_val);
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
#injected_line 84 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
    BEGIN_CONNECTION_POINT_MAP(CDemagogue)
        CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
        #injected_line 84 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
        CONNECTION_POINT_ENTRY(__uuidof(::_ISpeakerEvents))
        #injected_line 84 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
    END_CONNECTION_POINT_MAP()
#injected_line 84 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
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
#injected_line 84 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
    static RGSDWORD* GetOpcodeDWORDVals() 
    {
        static RGSDWORD rgDWORDS[] = 
            					{
            						{0, 0}
            					};
        return rgDWORDS;
    }
#injected_line 84 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
    static RGSBinary* GetOpcodeBinaryVals() 
    {

        static RGSBinary rgBinary[] = 
            					{
            						{0, 0}
            					};
        return rgBinary;
    }
#injected_line 84 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
    static RGSStrings* GetOpcodeStringVals() 
    {
        static RGSStrings rgStrings[] = 
            					{
            						{_T(""),0 }, 
            {_T("Speaker.Demagogue.1"),0 }, 
            {_T("%FriendlyName%"),1 }, 
            {_T("CLSID"),0 }, 
            {_T("{798AC41B-03D6-45A7-8311-8056A7EF0CFD}"),0 }, 
            {_T("Speaker.Demagogue"),0 }, 
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
#injected_line 84 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
    static HRESULT WINAPI UpdateRegistry(BOOL bRegister) 
    {
        CRegistryVirtualMachine rvm;
        HRESULT hr;
        if (FAILED(hr = rvm.AddStandardReplacements()))
            return hr;
        rvm.AddReplacement(_T("FriendlyName"), GetObjectFriendlyName());
        return rvm.VMUpdateRegistry(GetOpCodes(), GetOpcodeStringVals(), GetOpcodeDWORDVals(), GetOpcodeBinaryVals(), bRegister);
    }
#injected_line 84 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
    static const TCHAR* GetObjectFriendlyName() 
    {
        return _T("CDemagogue Object");
    }
#injected_line 84 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
    static const TCHAR* GetProgID() 
    {
        return _T("Speaker.Demagogue.1");
    }
#injected_line 84 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
    static const TCHAR* GetVersionIndependentProgID() 
    {
        return _T("Speaker.Demagogue");
    }
#injected_line 84 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"
    BEGIN_COM_MAP(CDemagogue)
        COM_INTERFACE_ENTRY(ISpeaker)
        COM_INTERFACE_ENTRY2(IDispatch, ISpeaker)
        COM_INTERFACE_ENTRY(INamedObject)
        COM_INTERFACE_ENTRY(IConnectionPointContainer)
        COM_INTERFACE_ENTRY(ISupportErrorInfo)
        COM_INTERFACE_ENTRY(IProvideClassInfo2)
        COM_INTERFACE_ENTRY(IProvideClassInfo)
    END_COM_MAP()
#injected_line 70 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"

    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) 
        					
    {
        static const IID* rgErrorGuids[] = 
            						{
            							&__uuidof(ISpeaker)
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
#injected_line 70 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\codemagogue.h"

				OBJECT_ENTRY_AUTO(__uuidof(CDemagogue), CDemagogue)
			
//--- End Injected Code For Attribute 'support_error_info'


