///////////////////////////////////////////////////////////////////////////////
//
// gencf.cpp - Copyright 1995-1997, Don Box
//
// This file contains the class definition of GenericClassFactory,
// that implements IClassFactory in terms of a function:
//    
//    HRESULT STDAPICALLTYPE CreateInstance(IUnknown*, REFIID, void**)
//

#ifndef _GENCF_CPP
#define _GENCF_CPP

#include <windows.h>
#include "gencf.h"

STDMETHODIMP 
GenericClassFactory::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown || riid == IID_IClassFactory)
        *ppv = static_cast<IClassFactory*>(this);
    else
        return (*ppv = 0), E_NOINTERFACE;
    ((IUnknown*)*ppv)->AddRef();
    return S_OK;
}

STDMETHODIMP_(ULONG)
GenericClassFactory::AddRef(void)
{
#ifndef EXESVC
    extern void STDAPICALLTYPE ModuleAddRef(void);
    ModuleAddRef();
#endif
    return 2;
}

STDMETHODIMP_(ULONG)
GenericClassFactory::Release(void)
{
#ifndef EXESVC
    extern void STDAPICALLTYPE ModuleRelease(void);
    ModuleRelease();
#endif
    return 1;
}

STDMETHODIMP 
GenericClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
    extern BOOL STDAPICALLTYPE ModuleIsStopping(void);
    LockServer(TRUE);
    *ppv = 0;
#ifdef CO_E_SERVER_IS_STOPPING
    HRESULT hr = CO_E_SERVER_IS_STOPPING;
#else
    HRESULT hr = E_FAIL;
#endif
    if (!ModuleIsStopping())
        hr = m_pfnCreateInstance(pUnkOuter, riid, ppv);
    LockServer(FALSE);
    return hr;
}

STDMETHODIMP 
GenericClassFactory::LockServer(BOOL bLock)
{
    extern void STDAPICALLTYPE ModuleAddRef(void);
    extern void STDAPICALLTYPE ModuleRelease(void);
    if (bLock)
        ModuleAddRef();
    else
        ModuleRelease();
    return S_OK;
}

#endif
