// Created by Microsoft (R) C/C++ Compiler Version 10.00.30319.01
//
// d:\vc++\atl internals 2e src\chapter 09\speaker\speaker\coearpolitic.mrg.h
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

// CoEarPolitic.h : Declaration of the CEarPolitic

#pragma once
#include "resource.h"       // main symbols
#include "CoDemagogue.h"

// IListener
	[export]
    typedef enum SpeakerRole { Defendant, Plaintiff } SpeakerRole ;
[
	object,
	uuid("CC46569D-9123-435E-AE10-06DF0FCA6767"),
	dual,	helpstring("IListener Interface"),
	pointer_default(unique)
]
__interface IListener : IDispatch
{
	[id(1), helpstring("method ListenTo")] HRESULT ListenTo([in] SpeakerRole role, [in] IUnknown* pSpeaker);
	[id(2), helpstring("method StopListening")] HRESULT StopListening([in] SpeakerRole role, [in] IUnknown* pSpeaker);
};

//+++ Start Injected Code For Attribute 'event_receiver'
#injected_line 27 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.h"
#pragma comment(linker, "/defaultlib:user32.lib")

//--- End Injected Code For Attribute 'event_receiver'



// CEarPolitic

[
	coclass,
	event_receiver(com),
	threading("apartment"),
	support_error_info("IListener"),
	vi_progid("Speaker.EarPolitic"),
	progid("Speaker.EarPolitic.1"),
	version(1.0),
	uuid("D6C76965-DF46-45B7-A6BE-8D4A943C39A1"),
	helpstring("EarPolitic Class")
]
class ATL_NO_VTABLE CEarPolitic : 
	//public _ISpeakerEvents,
	public IDispatchImpl<IListener, &__uuidof(IListener), &CAtlModule::m_libid, LIBRARY_MAJOR, LIBRARY_MINOR>
,
    /*+++ Added Baseclass */ public ISupportErrorInfo
{
public:

	DECLARE_PROTECT_FINAL_CONSTRUCT()

// IListener
	STDMETHOD(ListenTo)(SpeakerRole role, IUnknown* pSpeaker);
	STDMETHOD(StopListening)(SpeakerRole role, IUnknown* pSpeaker);

    void __stdcall OnHearDefendantWhisper(BSTR bstrText);
    void __stdcall OnHearDefendantTalk(BSTR bstrText);
    void __stdcall OnHearDefendantYell(BSTR bstrText);
    void __stdcall OnHearPlaintiffWhisper(BSTR bstrText);
    void __stdcall OnHearPlaintiffTalk(BSTR bstrText);
    void __stdcall OnHearPlaintiffYell(BSTR bstrText);
	
// ISpeakerEvents
	HRESULT OnWhisper(BSTR bstrSpeech) { OnHearDefendantWhisper(bstrSpeech); return S_OK; }
	HRESULT OnTalk(BSTR bstrSpeech)	{ OnHearDefendantTalk(bstrSpeech); return S_OK; }
	HRESULT OnYell(BSTR bstrSpeech)	{ OnHearDefendantYell(bstrSpeech); return S_OK; }

private:
	CComBSTR            m_bstrName;
	CComPtr<IUnknown>   m_spDefendant;
	CComPtr<IUnknown>   m_spPlaintiff;

    void CreateText(CComBSTR& bstrTitle, LPCOLESTR strRole, LPCOLESTR strAction, LPUNKNOWN punk);

	//+++ Start Injected Code For Attribute 'support_error_info'
#injected_line 27 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.h"
    __EventingCriticalSectionAuto __EventingCS;
#injected_line 29 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.h"
    HRESULT __cdecl __eventHandlerProxy(int idx, ...) 
    {
        va_list parg;
        va_start(parg, idx);
        HRESULT hr = __eventHandlerVProxy(idx, parg);
        va_end(parg);
        return hr;
    }
    HRESULT __cdecl __eventHandlerVProxy(int idx, va_list parg) 
    {
        (parg);
        switch (idx) {
        case -1:
            return S_FALSE;
            break;
        case 0:
            {
                InternalFinalConstructAddRef();
                return S_OK;
                break;
            }
        case 1:
            {
                InternalFinalConstructRelease();
                return S_OK;
                break;
            }
        case 2:
            {
                ::SpeakerRole  i1 = va_arg(parg, ::SpeakerRole );
                ::IUnknown*  i2 = va_arg(parg, ::IUnknown* );
                return (HRESULT) ListenTo(i1,i2);
                break;
            }
        case 3:
            {
                ::SpeakerRole  i1 = va_arg(parg, ::SpeakerRole );
                ::IUnknown*  i2 = va_arg(parg, ::IUnknown* );
                return (HRESULT) StopListening(i1,i2);
                break;
            }
        case 4:
            {
                ::BSTR  i1 = va_arg(parg, ::BSTR );
                OnHearDefendantWhisper(i1);
                return S_OK;
                break;
            }
        case 5:
            {
                ::BSTR  i1 = va_arg(parg, ::BSTR );
                OnHearDefendantTalk(i1);
                return S_OK;
                break;
            }
        case 6:
            {
                ::BSTR  i1 = va_arg(parg, ::BSTR );
                OnHearDefendantYell(i1);
                return S_OK;
                break;
            }
        case 7:
            {
                ::BSTR  i1 = va_arg(parg, ::BSTR );
                OnHearPlaintiffWhisper(i1);
                return S_OK;
                break;
            }
        case 8:
            {
                ::BSTR  i1 = va_arg(parg, ::BSTR );
                OnHearPlaintiffTalk(i1);
                return S_OK;
                break;
            }
        case 9:
            {
                ::BSTR  i1 = va_arg(parg, ::BSTR );
                OnHearPlaintiffYell(i1);
                return S_OK;
                break;
            }
        case 10:
            {
                ::BSTR  i1 = va_arg(parg, ::BSTR );
                return (HRESULT) OnWhisper(i1);
                break;
            }
        case 11:
            {
                ::BSTR  i1 = va_arg(parg, ::BSTR );
                return (HRESULT) OnTalk(i1);
                break;
            }
        case 12:
            {
                ::BSTR  i1 = va_arg(parg, ::BSTR );
                return (HRESULT) OnYell(i1);
                break;
            }
        default:
            return E_FAIL;
            break;
        }
    }
#injected_line 29 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.h"
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
#injected_line 29 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.h"
    static RGSDWORD* GetOpcodeDWORDVals() 
    {
        static RGSDWORD rgDWORDS[] = 
            					{
            						{0, 0}
            					};
        return rgDWORDS;
    }
#injected_line 29 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.h"
    static RGSBinary* GetOpcodeBinaryVals() 
    {

        static RGSBinary rgBinary[] = 
            					{
            						{0, 0}
            					};
        return rgBinary;
    }
#injected_line 29 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.h"
    static RGSStrings* GetOpcodeStringVals() 
    {
        static RGSStrings rgStrings[] = 
            					{
            						{_T(""),0 }, 
            {_T("Speaker.EarPolitic.1"),0 }, 
            {_T("%FriendlyName%"),1 }, 
            {_T("CLSID"),0 }, 
            {_T("{D6C76965-DF46-45B7-A6BE-8D4A943C39A1}"),0 }, 
            {_T("Speaker.EarPolitic"),0 }, 
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
#injected_line 29 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.h"
    static HRESULT WINAPI UpdateRegistry(BOOL bRegister) 
    {
        CRegistryVirtualMachine rvm;
        HRESULT hr;
        if (FAILED(hr = rvm.AddStandardReplacements()))
            return hr;
        rvm.AddReplacement(_T("FriendlyName"), GetObjectFriendlyName());
        return rvm.VMUpdateRegistry(GetOpCodes(), GetOpcodeStringVals(), GetOpcodeDWORDVals(), GetOpcodeBinaryVals(), bRegister);
    }
#injected_line 29 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.h"
    static const TCHAR* GetObjectFriendlyName() 
    {
        return _T("CEarPolitic Object");
    }
#injected_line 29 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.h"
    static const TCHAR* GetProgID() 
    {
        return _T("Speaker.EarPolitic.1");
    }
#injected_line 29 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.h"
    static const TCHAR* GetVersionIndependentProgID() 
    {
        return _T("Speaker.EarPolitic");
    }
#injected_line 29 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.h"
    BEGIN_COM_MAP(CEarPolitic)
        COM_INTERFACE_ENTRY(IListener)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(IProvideClassInfo)
        COM_INTERFACE_ENTRY(ISupportErrorInfo)
    END_COM_MAP()
#injected_line 29 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.h"

    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) 
        					
    {
        static const IID* rgErrorGuids[] = 
            						{
            							&__uuidof(IListener)
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
#injected_line 29 "d:\\vc++\\atl internals 2e src\\chapter 09\\speaker\\speaker\\coearpolitic.h"

				OBJECT_ENTRY_AUTO(__uuidof(CEarPolitic), CEarPolitic)
			
//--- End Injected Code For Attribute 'support_error_info'


