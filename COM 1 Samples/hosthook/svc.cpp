///////////////////////////////////////////////////
//
//  svc.h - Copyright 1997, Don Box
//  
//  Standard four entry points for hook DLL
//
//


#include "callinfo.h"
#include "common.h"

// this is to allow no CRT for tiny dlls
#ifndef _DEBUG
int    __cdecl atexit(void (__cdecl *)(void))
{
    return 0;
}
#endif

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
    static CallInfoClassObject s_callInfoClass;
    if (rclsid == CLSID_CallInfo)
        return s_callInfoClass.QueryInterface(riid, ppv);
    else
        return (*ppv = 0), CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllCanUnloadNow(void)
{
    return S_FALSE;
}


const TCHAR g_szCLSID[] = __TEXT("CLSID\\{F23ADD52-4992-11d1-991C-006097585A3C}");
const TCHAR g_szIPS32[] = __TEXT("CLSID\\{F23ADD52-4992-11d1-991C-006097585A3C}\\InprocServer32");

    
STDAPI DllUnregisterServer(void)
{
    HRESULT hr = UnRegisterTypeLib(LIBID_CallInfoLib, 1, 0, 0, SYS_WIN32);

    BOOL bSuccess = SUCCEEDED(hr);
    LONG err = RegDeleteKey(HKEY_CLASSES_ROOT, g_szIPS32);
    if (err != ERROR_SUCCESS)
        bSuccess = FALSE;
    
    err = RegDeleteKey(HKEY_CLASSES_ROOT, g_szCLSID);
    if (err != ERROR_SUCCESS)
        bSuccess = FALSE;

    return bSuccess ? S_OK : S_FALSE;
}


STDAPI DllRegisterServer(void)
{
    TCHAR szFileName[MAX_PATH];
    OLECHAR wszFileName[MAX_PATH];
    GetModuleFileName(g_hInstance, szFileName, MAX_PATH);
#ifdef UNICODE
    lstrcpy(wszFileName, szFileName);
#else
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szFileName, lstrlen(szFileName) + 1, wszFileName, MAX_PATH);
#endif
    BOOL bSuccess = TRUE;
    LONG err = RegSetValue(HKEY_CLASSES_ROOT, g_szCLSID, REG_SZ, __TEXT("CallInfo"), 9);
    if (err != ERROR_SUCCESS)
        return HRESULT_FROM_WIN32(err);

    HKEY hkey;
    err = RegCreateKey(HKEY_CLASSES_ROOT, g_szIPS32, &hkey);
    if (err == ERROR_SUCCESS)
    {
        err = RegSetValueEx(hkey, 0,0, REG_SZ, 
                        (const BYTE*)szFileName, (lstrlen(szFileName) + 1) * sizeof(TCHAR));
        if (err == ERROR_SUCCESS)
            err = RegSetValueEx(hkey, __TEXT("ThreadingModel"), 0, REG_SZ, 
                        (const BYTE*)__TEXT("Both"), (5) * sizeof(TCHAR));
        if (err != ERROR_SUCCESS)
        {
            bSuccess = FALSE;
            return DllUnregisterServer(), E_FAIL;
        }
        RegCloseKey(hkey);
    }

    if (!bSuccess)
        return bSuccess ? S_OK : E_FAIL;

    ITypeLib *ptl = 0;
    HRESULT hr = LoadTypeLib(wszFileName, &ptl);
    if (SUCCEEDED(hr))
    {
        hr = RegisterTypeLib(ptl, wszFileName, 0);
        ptl->Release();
    }
    return hr;

}
