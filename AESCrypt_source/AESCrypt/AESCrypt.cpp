/*
 *  AESCrypt.cpp
 *
 *  Copyright (C) 2006, 2007, 2008, 2013
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 *  This module contains the main entry points for the DLL that are
 *  called by the Windows shell (Explorer) and by the AESCrypt32.exe
 *  program.
 *
 */


#include "stdafx.h"
#include "resource.h"
#include "AESCrypt.h"
#include "AESCryptWorkerThreads.h"

class AESCryptModule : public CAtlDllModuleT< AESCryptModule >
{
    public:
        DECLARE_LIBID(LIBID_AESCryptLib)
        DECLARE_REGISTRY_APPID_RESOURCEID(
                        IDR_AESCRYPT,
                        "{BACE464C-A450-46A7-BC98-F441BCE45CE9}")
};

// Create an ATL module instance
AESCryptModule _AtlModule;

// AES Crypt Worker Threads class
AESCryptWorkerThreads AES_Crypt_Worker_Threads;

#ifdef _MANAGED
#pragma managed(push, off)
#endif

// DLL Entry Point
extern "C" BOOL WINAPI DllMain( HINSTANCE hInstance,
                                DWORD dwReason,
                                LPVOID lpReserved)
{
    return _AtlModule.DllMain(dwReason, lpReserved); 
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
    if (AES_Crypt_Worker_Threads.IsBusy())
    {
        return S_FALSE;
    }
    else
    {
        return _AtlModule.DllCanUnloadNow();
    }
}

// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(   REFCLSID rclsid,
                            REFIID riid,
                            LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
    // If we're on NT, add ourselves to the list of approved shell extensions.
    if ((GetVersion() & 0x80000000UL) == 0)
    {
        CRegKey reg;
        LONG    lRet;

        lRet = reg.Open(HKEY_LOCAL_MACHINE,
                        _T("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"),
                        KEY_SET_VALUE);

        if (lRet != ERROR_SUCCESS)
        {
            return E_ACCESSDENIED;
        }

        lRet = reg.SetStringValue(
                        _T("{35872D53-3BD4-45FA-8DB5-FFC47D4235E7}"),
                        _T("AESCrypt"));

        if (lRet != ERROR_SUCCESS)
        {
            return HRESULT_FROM_WIN32(lRet);
        }
    }

    HRESULT hr = _AtlModule.DllRegisterServer(FALSE);
    return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
    // If we're on NT, remove ourselves from the list of approved shell extensions.
    if ((GetVersion() & 0x80000000UL) == 0)
    {
        CRegKey reg;
        LONG    lRet;

        lRet = reg.Open(HKEY_LOCAL_MACHINE,
                        _T("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"),
                        KEY_SET_VALUE);

        if (lRet == ERROR_SUCCESS)
        {
            lRet = reg.DeleteValue(_T("{35872D53-3BD4-45FA-8DB5-FFC47D4235E7}") );
        }
    }

    HRESULT hr = _AtlModule.DllUnregisterServer(FALSE);
    return hr;
}

__declspec(dllexport) void __cdecl ProcessFiles(StringList *file_list,
                                                bool encrypt)
{
   AES_Crypt_Worker_Threads.ProcessFiles(file_list, encrypt);
}

__declspec(dllexport) bool __cdecl AESLibBusy()
{
   return AES_Crypt_Worker_Threads.IsBusy();
}
