// CompA.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <comutil.h>
#include <stdio.h>
#include "objbase.h"
#include "olectl.h"

#include "CompA.h"
#include "factory.h"
#include "registry.h"

ULONG    g_LockNumber = 0;
ULONG    g_CompANumber = 0;
HANDLE	 g_hModule;

// {16DCB981-BEEB-11d2-B362-00104B08CC22}
extern "C" const GUID CLSID_CompA = 
		{ 0x16dcb981, 0xbeeb, 0x11d2, 
		{ 0xb3, 0x62, 0x0, 0x10, 0x4b, 0x8, 0xcc, 0x22 } };

// {16DCB982-BEEB-11d2-B362-00104B08CC22}
extern "C" const GUID IID_SomeInterface = 
		{ 0x16dcb982, 0xbeeb, 0x11d2, 
		{ 0xb3, 0x62, 0x0, 0x10, 0x4b, 0x8, 0xcc, 0x22 } };

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
	if (clsid == CLSID_CompA) {
		
		CAFactory *pFactory = new CAFactory;
		
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
	if ((g_CompANumber == 0) && (g_LockNumber == 0))
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
	return RegisterServer(CLSID_CompA,
	                      szModule, 
						  "CompA.Object",
						  "CompA Component",
						  NULL);
}


//
// Server unregistration
//
extern "C" HRESULT __stdcall DllUnregisterServer()
{
	return UnregisterServer(CLSID_CompA,
	                        "CompA.Object",NULL);
}

// Implemention of class CA
CA::CA (IUnknown *pUnknownOuter)
{
	m_Ref = 0;
	g_CompANumber ++ ;
	m_pUnknownOuter = pUnknownOuter;
}

CA::~CA()
{
}

ULONG CA::NondelegatingAddRef()
{
	m_Ref ++;
	return  (ULONG) m_Ref;
}

ULONG CA::NondelegationRelease ()
{
	m_Ref --;
	if (m_Ref == 0 )
	{
		g_CompANumber -- ; 
		delete this;
		return 0;
	}
	return  (ULONG) m_Ref;
}

HRESULT CA::NondelegationQueryInterface(const IID& iid, void **ppv)
{
	if ( iid == IID_IUnknown )
	{
		*ppv = (INondelegatingUnknown *) this ;
		((IUnknown *)(*ppv))->AddRef() ;
	} else if ( iid == IID_SomeInterface ) 
	{
		*ppv = (ISomeInterface *) this ;
		((ISomeInterface *)(*ppv))->AddRef() ;
	} 
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE ;
	}
	return S_OK;
}

ULONG CA::AddRef ()
{
	if  ( m_pUnknownOuter != NULL )
		return m_pUnknownOuter->AddRef();
	else
		return NondelegatingAddRef();
}

ULONG CA::Release ()
{
	if  ( m_pUnknownOuter != NULL )
		return m_pUnknownOuter->Release ();
	else
		return NondelegationRelease();
}

HRESULT CA::QueryInterface(const IID& iid, void **ppv)
{
	if  ( m_pUnknownOuter != NULL )
		return m_pUnknownOuter->QueryInterface(iid, ppv);
	else
		return NondelegationQueryInterface(iid, ppv);
}

HRESULT CA::SomeFunction()
{
	printf("This is CA::SomeFunction!\n");
	return S_OK;
}
