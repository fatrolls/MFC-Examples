///////////////////////////////////////////////////////////////////////////////
//
// clstable.cpp - Copyright 1997, Don Box
//
// This file contains the implementation of several routines for managing 
// coclass tables and implementing DllGetClassObject, DllRegisterServer, 
// DllUnregisterServer, and WinMain for out-of-process servers
//
//     ClassTableUpdateRegistry - installs/uninstalls registry entries
//     ClassTableGetClassObject - for use in DllGetClassObject
//     ClassTableRegisterClassObjects - used at start of WinMain in oop server
//     ClassTableRevokeClassObjects - used at end of WinMain in oop server
//     

#ifndef _CLSTABLE_CPP
#define _CLSTABLE_CPP

#include <windows.h>
#include "clstable.h"

#ifndef _INLINEISEQUALGUID_DEFINED
#define _INLINEISEQUALGUID_DEFINED
inline BOOL  InlineIsEqualGUID(REFGUID rguid1, REFGUID rguid2)
{
   return (
      ((PLONG) &rguid1)[0] == ((PLONG) &rguid2)[0] &&
      ((PLONG) &rguid1)[1] == ((PLONG) &rguid2)[1] &&
      ((PLONG) &rguid1)[2] == ((PLONG) &rguid2)[2] &&
      ((PLONG) &rguid1)[3] == ((PLONG) &rguid2)[3]);
}
#endif



HRESULT STDAPICALLTYPE 
ClassTableGetClassObject(COCLASS_ENTRY *pTable, 
                         REFCLSID rclsid, 
                         REFIID riid, void **ppv)
{
    HRESULT hr = CLASS_E_CLASSNOTAVAILABLE;
    *ppv = 0;
    if (pTable)
    {
        while (pTable->pclsid != &GUID_NULL)
        {
            if (InlineIsEqualGUID(*pTable->pclsid, rclsid))
            {
                if (pTable->pfnGetClassObject)
                    hr = pTable->pfnGetClassObject(riid, ppv);
                break;
            }
            pTable++;
        }
    }
    return hr;
}

HRESULT STDAPICALLTYPE 
ClassTableUpdateRegistry(HINSTANCE hInstance, 
                         COCLASS_ENTRY *pTable, 
                         REGISTRY_ENTRY *pModuleRegTable, 
                         BOOL bModuleHasTypeLib, 
                         BOOL bInstalling)
{
    HRESULT hr = S_OK;
    COCLASS_ENTRY *pHead = pTable;
    if (bInstalling)
    {
        if (pTable)
            for (;SUCCEEDED(hr) && pTable->pclsid != &GUID_NULL; pTable++)
                if (pTable->pfnUpdateRegistry)
                    hr = pTable->pfnUpdateRegistry(hInstance, bInstalling);

        if (FAILED(hr)) // unwind install
            while (--pTable >= pHead)
                if (pTable->pfnUpdateRegistry)
                    pTable->pfnUpdateRegistry(hInstance, FALSE);

        if (SUCCEEDED(hr))
            hr = RegistryTableUpdateRegistry(hInstance, pModuleRegTable, bModuleHasTypeLib, TRUE);

        if (FAILED(hr) && pTable) // unwind install
            for (pTable = pHead; pTable->pclsid != &GUID_NULL; pTable++)
                if (pTable->pfnUpdateRegistry)
                    pTable->pfnUpdateRegistry(hInstance, FALSE);
    }
    else // uninstalling
    {
        HRESULT hrtemp = S_OK;
        if (pTable)
        {
            for (;pTable->pclsid != &GUID_NULL; pTable++)
            {
                if (pTable->pfnUpdateRegistry)
                {
                    hrtemp = pTable->pfnUpdateRegistry(hInstance, bInstalling);
                    if (hrtemp != S_OK)
                        hr = hrtemp;
                }
            }
        }

        hrtemp = RegistryTableUpdateRegistry(hInstance, pModuleRegTable, bModuleHasTypeLib, FALSE);
        if (hrtemp != S_OK)
            hr = hrtemp;
    }
    return hr;
}

HRESULT STDAPICALLTYPE 
ClassTableRegisterClassObjects(COCLASS_ENTRY *pTable, 
                               DWORD dwClsCtx,
                               DWORD dwRegCls,
                               BOOL bResumeClassObjects )
{
    HRESULT hr = E_FAIL;
#ifdef _WIN32_DCOM
    dwRegCls |= REGCLS_SUSPENDED;
#else
    assert(bResumeClassObjects);
#endif
    if (pTable)
    {
        hr = S_OK;
        COCLASS_ENTRY *pHead = pTable;
        for (; SUCCEEDED(hr) && pTable->pclsid != &GUID_NULL; pTable++)
        {
            if (pTable->pfnGetClassObject)
            {
                IUnknown *pUnk = 0;
                hr = pTable->pfnGetClassObject(IID_IUnknown, (void**)&pUnk);
                if (SUCCEEDED(hr))
                {
                    hr = CoRegisterClassObject(*pTable->pclsid,
                                               pUnk,
                                               dwClsCtx,
                                               dwRegCls,
                                               &pTable->dwReg);
                    pUnk->Release();
                }
            }
        }
        
        if (SUCCEEDED(hr) && bResumeClassObjects)
            hr = CoResumeClassObjects();

        if (FAILED(hr)) // unwind if failed
            for (pTable--; pTable >= pHead; pTable--)
                if (pTable->pfnGetClassObject)
                    CoRevokeClassObject(pTable->dwReg);
        
    }
    return hr;
}

HRESULT STDAPICALLTYPE 
ClassTableRevokeClassObjects(COCLASS_ENTRY *pTable)
{
    HRESULT hr = E_FAIL;

    if (pTable)
    {
        hr = S_OK;
        for (; pTable->pclsid != &GUID_NULL; pTable++)
        {
            if (pTable->pfnGetClassObject)
            {
                HRESULT hrtemp = CoRevokeClassObject(pTable->dwReg);
                if (hrtemp != S_OK)
                    hr = hrtemp;
            }
        }
    }
    return hr;
}


#endif

