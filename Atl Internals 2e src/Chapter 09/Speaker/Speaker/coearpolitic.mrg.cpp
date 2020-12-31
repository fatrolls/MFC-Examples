// Created by Microsoft (R) C/C++ Compiler Version 10.00.30319.01
//
// d:\vc++\atl internals 2e src\chapter 09\speaker\speaker\coearpolitic.mrg.cpp
// compiler-generated file created 06/21/12 at 15:18:04
//
// This C++ source file is intended to be a representation of the
// source code injected by the compiler.  It may not compile or
// run exactly as the original source file.
//

// CoEarPolitic.cpp : Implementation of CEarPolitic

#include "stdafx.h"
//+++ Start Injected Code
[no_injected_text(true)];      // Suppress injected text, it has already been injected
#pragma warning(disable: 4543) // Suppress warnings about skipping injected text
#pragma warning(disable: 4199) // Suppress warnings from attribute providers

#pragma message("\n\nNOTE: This merged source file should be visually inspected for correctness.\n\n")
//--- End Injected Code


#include "CoEarPolitic.h"
#include "CoDemagogue.h"


// CEarPolitic

void __stdcall CEarPolitic::OnHearDefendantWhisper(BSTR bstrText)
{
    USES_CONVERSION;

    CComBSTR title ;
    CreateText(title, OLESTR("defendant"), OLESTR("whispering"), m_spDefendant);

    MessageBox(NULL, OLE2CT(bstrText), OLE2CT(title), MB_OK);
}

void CEarPolitic::OnHearDefendantTalk(BSTR bstrText)
{
    USES_CONVERSION;

    CComBSTR title ;
    CreateText (title, OLESTR("defendant"), OLESTR("talking"), m_spDefendant);

    MessageBox(NULL, OLE2CT(bstrText), OLE2CT(title), MB_OK);
}

void __stdcall CEarPolitic::OnHearDefendantYell(BSTR bstrText)
{
    USES_CONVERSION;

    CComBSTR title ;
    CreateText(title, OLESTR("defendant"), OLESTR("yelling"), m_spDefendant);

    MessageBox(NULL, OLE2CT(bstrText), OLE2CT(title), MB_OK);
}

void __stdcall CEarPolitic::OnHearPlaintiffWhisper(BSTR bstrText)
{
    USES_CONVERSION;

    CComBSTR title ;
    CreateText(title, OLESTR("plaintiff"), OLESTR("whispering"), m_spPlaintiff);
    
    MessageBox(NULL, OLE2CT(bstrText), OLE2CT(title), MB_OK);
}

void __stdcall CEarPolitic::OnHearPlaintiffTalk(BSTR bstrText)
{
    USES_CONVERSION;

    CComBSTR title ;
    CreateText(title, OLESTR("plaintiff"), OLESTR("talking"), m_spPlaintiff);

    MessageBox(NULL, OLE2CT(bstrText), OLE2CT(title), MB_OK);
}

void __stdcall CEarPolitic::OnHearPlaintiffYell(BSTR bstrText)
{
    USES_CONVERSION;

    CComBSTR title ;
    CreateText(title, OLESTR("plaintiff"), OLESTR("yelling"), m_spPlaintiff);

    MessageBox(NULL, OLE2CT(bstrText), OLE2CT(title), MB_OK);
}

//+++ Start Injected Code For Attribute 'hook' from CEarPolitic::ListenTo
#injected_line 99 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.cpp"
[
        coclass,
        noncreatable,
        com_interface_entry("COM_INTERFACE_ENTRY_IID(__uuidof(_ISpeakerEvents), IDispatch)")
    ]
    struct __Impl__ISpeakerEvents : IDispatch 
,
    /*+++ Added Baseclass */ public CComObjectRootEx<CComSingleThreadModel>
{
    ATL::__EventHandlerProxy* __pThis;
    ATL::__EventHandlerNodeProxy* __pThat;
    static const _GUID* Guid() 
    {
        return &__uuidof(_ISpeakerEvents);
    }
    ::HRESULT  OnWhisper(::BSTR i1) 
    {
        return __pThis->__eventHandlerProxy(__pThat->__Index(0), i1);
    }
    ::HRESULT  OnTalk(::BSTR i1) 
    {
        return __pThis->__eventHandlerProxy(__pThat->__Index(1), i1);
    }
    ::HRESULT  OnYell(::BSTR i1) 
    {
        return __pThis->__eventHandlerProxy(__pThat->__Index(2), i1);
    }
    virtual HRESULT STDMETHODCALLTYPE Invoke(
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
                hr = OnWhisper(i1);
                break;
            }
        case 2:
            {
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
                hr = OnTalk(i1);
                break;
            }
        case 3:
            {
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
                hr = OnYell(i1);
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
    virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(
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
        static LPOLESTR names[] = { L"bstrSpeech", L"OnWhisper", L"OnTalk", L"OnYell" };
        static DISPID dids[] = { 0, 1, 2, 3 };
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
    virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(unsigned int*  pctinfo) 
    {
        if (pctinfo == NULL) {
            return E_POINTER;
        }
        CComPtr<ITypeInfo> spTypeInfo;
        *pctinfo = 
                       (SUCCEEDED(TypeInfoHelper(__uuidof(_ISpeakerEvents), 0, &spTypeInfo))) ? 1 : 0;
        return S_OK;
    }
    virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(unsigned int iTInfo, LCID lcid, ITypeInfo** ppTInfo) 
    {
        if (iTInfo != 0) {
            return DISP_E_BADINDEX;
        }
        return TypeInfoHelper(__uuidof(_ISpeakerEvents), lcid, ppTInfo);
    }

	//+++ Start Injected Code For Attribute 'hook'
#injected_line 99 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.cpp"
    static HRESULT WINAPI UpdateRegistry(BOOL) 
    {
        return S_OK;
    }
#injected_line 99 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.cpp"
    static const CLSID& WINAPI GetObjectCLSID() 
    {
        return __uuidof(__Impl__ISpeakerEvents);
    }
#injected_line 99 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.cpp"
    static const TCHAR* GetObjectFriendlyName() 
    {
        return _T("__Impl__ISpeakerEvents Object");
    }
#injected_line 99 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.cpp"
    static const TCHAR* GetProgID() 
    {
        return _T("__Impl__ISpeakerEvents.__Impl__ISpeak.1");
    }
#injected_line 99 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.cpp"
    static const TCHAR* GetVersionIndependentProgID() 
    {
        return _T("__Impl__ISpeakerEvents.__Impl__ISpeak");
    }
#injected_line 99 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.cpp"
    BEGIN_COM_MAP(__Impl__ISpeakerEvents)
        COM_INTERFACE_ENTRY_IID(__uuidof(_ISpeakerEvents), IDispatch)
        COM_INTERFACE_ENTRY(IDispatch)
    END_COM_MAP()

	//--- End Injected Code For Attribute 'hook'
};

//--- End Injected Code For Attribute 'hook'


void CEarPolitic::CreateText(CComBSTR& text, LPCOLESTR strRole, LPCOLESTR strAction, LPUNKNOWN punk)
{
    text.Empty ();

    text = m_bstrName;
    text += OLESTR(" hears the ");
    text += strRole;
    text += OLESTR(" (");
    
    CComQIPtr<INamedObject> pno = punk;
    CComBSTR bstrName;
    HRESULT hr = pno->get_Name(&bstrName) ;

    text.AppendBSTR(bstrName);
    text += OLESTR(") ");
    
    text += strAction;
}

STDMETHODIMP CEarPolitic::ListenTo(SpeakerRole role, IUnknown *pSpeaker)
{
    HRESULT hr = StopListening(role, pSpeaker) ; // Validates role
    if (FAILED (hr)) return hr ;

    switch (role) 
	{
		case Defendant:
		{
			long lRet = 0;
			lRet |= __hook(&_ISpeakerEvents::OnTalk, pSpeaker, &CEarPolitic::OnHearDefendantTalk)
	//+++ Start Injected Code For Attribute 'hook' from CEarPolitic::ListenTo
                #injected_line 99 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.cpp"
    __AddHandler<__Impl__ISpeakerEvents>(this, 5, pSpeaker, 1, 3)

	//--- End Injected Code For Attribute 'hook'
;
			lRet |= __hook(&_ISpeakerEvents::OnWhisper, pSpeaker, &CEarPolitic::OnHearDefendantWhisper)
	//+++ Start Injected Code For Attribute 'hook' from CEarPolitic::ListenTo
                #injected_line 100 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.cpp"
    __AddHandler<__Impl__ISpeakerEvents>(this, 4, pSpeaker, 0, 3)

	//--- End Injected Code For Attribute 'hook'
;
			lRet |= __hook(&_ISpeakerEvents::OnYell, pSpeaker, &CEarPolitic::OnHearDefendantYell)
	//+++ Start Injected Code For Attribute 'hook' from CEarPolitic::ListenTo
                #injected_line 101 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.cpp"
    __AddHandler<__Impl__ISpeakerEvents>(this, 6, pSpeaker, 2, 3)

	//--- End Injected Code For Attribute 'hook'
;
			//lRet |= __hook(_ISpeakerEvents, pSpeaker);
			if (lRet == 0)
				m_spDefendant = pSpeaker ;
			else
				Error(OLESTR("The defendant does not support listening"), __uuidof(IListener), hr);
			break;
		}
		case Plaintiff:
		{
			long lRet = 0;
			//lRet |= __hook(&_ISpeakerEvents::OnTalk, pSpeaker, &CEarPolitic::OnHearPlaintiffTalk);
			//lRet |= __hook(&_ISpeakerEvents::OnWhisper, pSpeaker, &CEarPolitic::OnHearPlaintiffWhisper);
			//lRet |= __hook(&_ISpeakerEvents::OnYell, pSpeaker, &CEarPolitic::OnHearPlaintiffYell);
			//lRet |= __hook(_ISpeakerEvents, pSpeaker);
			if (lRet == 0)
				m_spPlaintiff = pSpeaker ;
			else
				Error(OLESTR("The Plaintiff does not support listening"), __uuidof(IListener), hr);
			break;
		}
    }



	return hr;
}

STDMETHODIMP CEarPolitic::StopListening(SpeakerRole role, IUnknown* pSpeaker)
{
    HRESULT hr = S_OK ;
    switch (role) 
	{
		case Defendant:
		{
			long lRet = 0;
			if (m_spDefendant)
			{
				//lRet |= __unhook(&_ISpeakerEvents::OnTalk, pSpeaker, &CEarPolitic::OnHearDefendantTalk);
				//lRet |= __unhook(&_ISpeakerEvents::OnWhisper, pSpeaker, &CEarPolitic::OnHearDefendantWhisper);
				//lRet |= __unhook(&_ISpeakerEvents::OnYell, pSpeaker, &CEarPolitic::OnHearDefendantYell);
				//lRet |= __unhook(_ISpeakerEvents, pSpeaker);
				hr = lRet ? E_FAIL : S_OK;
			}

			if (FAILED(hr))
				Error(OLESTR("Unexpected error trying to stop listening to the defendant"), __uuidof(IListener), hr);

			m_spDefendant = NULL;
			break;
		}
		case Plaintiff:
		{
			long lRet = 0;
			if (m_spPlaintiff)
			{
				//lRet |= __unhook(&_ISpeakerEvents::OnTalk, pSpeaker, &CEarPolitic::OnHearPlaintiffTalk);
				//lRet |= __unhook(&_ISpeakerEvents::OnWhisper, pSpeaker, &CEarPolitic::OnHearPlaintiffWhisper);
				//lRet |= __unhook(&_ISpeakerEvents::OnYell, pSpeaker, &CEarPolitic::OnHearPlaintiffYell);
				//lRet |= __unhook(_ISpeakerEvents, pSpeaker);
				hr = lRet ? E_FAIL : S_OK;
			}

			if (FAILED(hr))
				Error(OLESTR("Unexpected error trying to stop listening to the Plaintiff"), __uuidof(IListener), hr);

			m_spPlaintiff = NULL;
			break;
		}
		default:
			hr = E_INVALIDARG;
			break;
    }


    return hr;
}
