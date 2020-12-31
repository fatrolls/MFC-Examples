// CompB.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#include <comutil.h>
#include <stdio.h>
#include "objbase.h"
#include "olectl.h"

#include "CompB.h"
#include "factory.h"
#include "registry.h"

ULONG    g_LockNumber = 0;
ULONG    g_CompBNumber = 0;
HANDLE	 g_hModule;

// {16DCB981-BEEB-11d2-B362-00104B08CC22}
extern "C" const GUID CLSID_CompA = 
		{ 0x16dcb981, 0xbeeb, 0x11d2, 
		{ 0xb3, 0x62, 0x0, 0x10, 0x4b, 0x8, 0xcc, 0x22 } };

// {16DCB982-BEEB-11d2-B362-00104B08CC22}
extern "C" const GUID IID_SomeInterface = 
		{ 0x16dcb982, 0xbeeb, 0x11d2, 
		{ 0xb3, 0x62, 0x0, 0x10, 0x4b, 0x8, 0xcc, 0x22 } };

// {39C07941-BFCC-11d2-A100-00A0C9A6F472}
extern "C" const GUID CLSID_CompB = 
		{ 0x39c07941, 0xbfcc, 0x11d2, 
		{ 0xa1, 0x0, 0x0, 0xa0, 0xc9, 0xa6, 0xf4, 0x72 } };

// {39C07942-BFCC-11d2-A100-00A0C9A6F472}
extern "C" const GUID IID_OtherInterface = 
		{ 0x39c07942, 0xbfcc, 0x11d2, 
		{ 0xa1, 0x0, 0x0, 0xa0, 0xc9, 0xa6, 0xf4, 0x72 } };

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    g_hModule = hModule;
	return TRUE;
}


extern "C" HRESULT __stdcall DllGetClassObject(const CLSID& clsid, const IID& iid, void **ppv)
{
	if (clsid == CLSID_CompB) {
		
		CBFactory *pFactory = new CBFactory;
		
		if (pFactory == NULL) {
			return E_OUTOFMEMORY ;
		}
		
		HRESULT result = pFactory->QueryInterface(iid, ppv);

		return result;
	} else {
		return CLASS_E_CLASSNOTAVAILABLE;
	}
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((g_CompBNumber == 0) && (g_LockNumber == 0))
		return S_OK;
	else
		return S_FALSE;
}

//
// Server registration
//
extern "C" HRESULT __stdcall DllRegisterServer()
{
	char szModule[1024];
	DWORD dwResult = ::GetModuleFileName((HMODULE)g_hModule, szModule, 1024);
	if (dwResult == 0)
		return SELFREG_E_CLASS;
	return RegisterServer(CLSID_CompB,
	                      szModule, 
						  "CompB.Object",
						  "CompB Component",
						  NULL);
}

//
// Server unregistration
//
extern "C" HRESULT __stdcall DllUnregisterServer()
{
	return UnregisterServer(CLSID_CompB,
	                        "CompB.Object",NULL);
}

// Implemention of class CB
CB::CB ()
{
	m_Ref = 0;
	g_CompBNumber ++ ;
	m_pUnknownInner = NULL;
}

CB::~CB ( )
{
	m_Ref = 1;

	IUnknown *pUnknownOuter = this;
	pUnknownOuter->AddRef();

	if (m_pSomeInterface != NULL)
		m_pSomeInterface->Release();

	if (m_pUnknownInner != NULL) 
		m_pUnknownInner->Release();
}

HRESULT CB::Init()
{
	IUnknown *pUnknownOuter = (IUnknown *)this;
	HRESULT result = ::CoCreateInstance(CLSID_CompA, pUnknownOuter, 
						CLSCTX_INPROC_SERVER, 
						IID_IUnknown, (void **)& m_pUnknownInner) ;
	if (FAILED(result))
			return E_FAIL;
		
	result = m_pUnknownInner->QueryInterface(IID_SomeInterface, (void **)&m_pSomeInterface);
	if (FAILED(result))
	{
		m_pUnknownInner->Release();
		return E_FAIL;
	}

	pUnknownOuter->Release();
	return S_OK;
}

ULONG CB::AddRef()
{
	m_Ref ++;
	return  (ULONG) m_Ref;
}

ULONG CB::Release ()
{
	m_Ref --;
	if (m_Ref == 0 )
	{
		g_CompBNumber -- ; 
		delete this;
		return 0;
	}
	return  (ULONG) m_Ref;
}

HRESULT CB::QueryInterface(const IID& iid, void **ppv)
{
	if ( iid == IID_IUnknown )
	{
		*ppv = (IUnknown *) this ;
		((IUnknown *)(*ppv))->AddRef() ;
	} else if ( iid == IID_OtherInterface ) 
	{
		*ppv = (IOtherInterface *) this ;
		((IOtherInterface *)(*ppv))->AddRef() ;
	} else if ( iid == IID_SomeInterface ) 
	{
		return m_pUnknownInner->QueryInterface(iid, ppv) ;
	} else 
	{
		*ppv = NULL;
		return E_NOINTERFACE ;
	}
	return S_OK;
}

HRESULT CB::OtherFunction()
{
	printf("This is CB::OtherFunction!\n");
	return S_OK;
}