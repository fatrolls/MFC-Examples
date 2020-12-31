///////////////////////////////////////////////////////////////////////////////
//
// regtable.cpp - Copyright 1996-1997, Don Box
//
// This file contains the implementation of a routine that adds/removes
// the table's registry entries and optionally registers a type library.
//
//     RegistryTableUpdateRegistry - adds/removes registry entries for table
//     

#ifndef _REGTABLE_CPP
#define _REGTABLE_CPP

#include <windows.h>
#include <olectl.h> 
#include "regtable.h"

LONG RegDeleteAllKeys(HKEY hkeyRoot, const char *pszKeyName)
{
    LONG err = ERROR_BADKEY;
    if (pszKeyName && lstrlenA(pszKeyName))
    {
        HKEY    hkey;
        err = RegOpenKeyExA(hkeyRoot, pszKeyName, 0, 
                           KEY_ENUMERATE_SUB_KEYS | DELETE, &hkey );
        if(err == ERROR_SUCCESS)
        {
            while (err == ERROR_SUCCESS )
            {
                enum { MAX_KEY_LEN = 1024 };
                char szSubKey[MAX_KEY_LEN]; 
                DWORD   dwSubKeyLength = MAX_KEY_LEN;
                err = RegEnumKeyExA(hkey, 0, szSubKey,
                                    &dwSubKeyLength, 0, 0, 0, 0);
                
                if(err == ERROR_NO_MORE_ITEMS)
                {
                    err = RegDeleteKeyA(hkeyRoot, pszKeyName);
                    break;
                }
                else if (err == ERROR_SUCCESS)
                    err = RegDeleteAllKeys(hkey, szSubKey);
            }
            RegCloseKey(hkey);
            // Do not save return code because error
            // has already occurred
        }
    }
    return err;
}


// the routine that inserts/deletes Registry keys based on the table
EXTERN_C HRESULT STDAPICALLTYPE 
RegistryTableUpdateRegistry(HINSTANCE hInstance, 
                            REGISTRY_ENTRY *pEntries, 
                            BOOL bRegisterModuleAsTypeLib, 
                            BOOL bInstalling)
{
    HRESULT hr = S_OK;
    if (bInstalling)
    {
        char szModuleName[MAX_PATH];
        GetModuleFileNameA(hInstance, szModuleName, MAX_PATH);
        if (bRegisterModuleAsTypeLib)
        {
            ITypeLib *pTypeLib = 0;
            OLECHAR szTypeLibName[MAX_PATH];
#ifdef OLE2ANSI
            strcpy(szTypeLibName, szModuleName);
#else
            mbstowcs(szTypeLibName, szModuleName, MAX_PATH);
#endif
            hr = LoadTypeLib(szTypeLibName, &pTypeLib);
            if (SUCCEEDED(hr)) 
            {
                hr = RegisterTypeLib(pTypeLib, szTypeLibName, 0);
                pTypeLib->Release();
            }
        }
        if (FAILED(hr))
            hr = SELFREG_E_TYPELIB;
        else if (pEntries)
        {
            REGISTRY_ENTRY *pHead = pEntries;
            char szKey[4096];
            HKEY hkeyRoot = 0;
        
            while (pEntries->fFlags != -1)
            {
                char szFullKey[4096];
                const char *pszValue = (pEntries->pszValue != REG_MODULE_NAME) ? pEntries->pszValue : szModuleName;
                if (pEntries->hkeyRoot)
                {
                    hkeyRoot = pEntries->hkeyRoot;
                    lstrcpyA(szKey, pEntries->pszKey);
                    lstrcpyA(szFullKey, pEntries->pszKey);
                }
                else
                {
                    lstrcpyA(szFullKey, szKey);
                    lstrcatA(szFullKey, "\\");
                    lstrcatA(szFullKey, pEntries->pszKey);
                }
                if (hkeyRoot == 0)
                {
                    RegistryTableUpdateRegistry(hInstance, 
                                                pHead, 
                                                bRegisterModuleAsTypeLib, 
                                                FALSE);
                    return SELFREG_E_CLASS;

                }
                HKEY hkey; DWORD dw;
                if (pEntries->fFlags & (REGFLAG_DELETE_BEFORE_REGISTERING|REGFLAG_DELETE_WHEN_REGISTERING))
                {
                    LONG err = RegDeleteAllKeys(hkeyRoot, szFullKey);
                    if (err != ERROR_SUCCESS && err != ERROR_FILE_NOT_FOUND) 
                    {
                        RegistryTableUpdateRegistry(hInstance, 
                                                    pHead, 
                                                    bRegisterModuleAsTypeLib, 
                                                    FALSE);
                        return SELFREG_E_CLASS;
                    }
                }
                if (!(pEntries->fFlags & REGFLAG_DELETE_WHEN_REGISTERING))
                {
                    LONG err = RegCreateKeyExA(hkeyRoot, szFullKey,
                                               0, 0, REG_OPTION_NON_VOLATILE,
                                               KEY_WRITE, 0, &hkey, &dw);
                    if (err == ERROR_SUCCESS)
                    {
                        if (pszValue)
                            err = RegSetValueExA(hkey, pEntries->pszValueName, 0, REG_SZ, (const BYTE *)pszValue, lstrlenA(pszValue) + 1);
                        RegCloseKey(hkey);
                        if (hkeyRoot == 0)
                        {
                            RegistryTableUpdateRegistry(hInstance, 
                                                        pHead, 
                                                        bRegisterModuleAsTypeLib, 
                                                        FALSE);
                            return SELFREG_E_CLASS;

                        }
                    }
                    else
                    {
                        RegistryTableUpdateRegistry(hInstance, 
                                                    pHead, 
                                                    bRegisterModuleAsTypeLib, 
                                                    FALSE);
                        return SELFREG_E_CLASS;

                    }
                }
                pEntries++;
            }
        }
    }
    else
    {
        if (bRegisterModuleAsTypeLib)
        {
            char szModuleName[MAX_PATH];
            GetModuleFileNameA(hInstance, szModuleName, MAX_PATH);
            ITypeLib *pTypeLib = 0;
            OLECHAR szTypeLibName[MAX_PATH];
#ifdef OLE2ANSI
            strcpy(szTypeLibName, szModuleName);
#else
            mbstowcs(szTypeLibName, szModuleName, MAX_PATH);
#endif
            hr = LoadTypeLib(szTypeLibName, &pTypeLib);
            if (SUCCEEDED(hr)) 
            {
                TLIBATTR *ptla = 0;
                hr = pTypeLib->GetLibAttr(&ptla);
                if (SUCCEEDED(hr))
                {
                    hr = UnRegisterTypeLib(ptla->guid, ptla->wMajorVerNum, ptla->wMinorVerNum, ptla->lcid, ptla->syskind);
                    pTypeLib->ReleaseTLibAttr(ptla);
                }
                pTypeLib->Release();
            }
        }
        if (FAILED(hr))
            hr = SELFREG_E_TYPELIB;
        else if (pEntries)
        {
            char szKey[4096];
            HKEY hkeyRoot = 0;
        
            while (pEntries->fFlags != -1)
            {
                char szFullKey[4096];
                if (pEntries->hkeyRoot)
                {
                    hkeyRoot = pEntries->hkeyRoot;
                    lstrcpyA(szKey, pEntries->pszKey);
                    lstrcpyA(szFullKey, pEntries->pszKey);
                }
                else
                {
                    lstrcpyA(szFullKey, szKey);
                    lstrcatA(szFullKey, "\\");
                    lstrcatA(szFullKey, pEntries->pszKey);
                }
                if ((hkeyRoot != 0) 
                    && !(pEntries->fFlags & REGFLAG_NEVER_DELETE)
                    && !(pEntries->fFlags & REGFLAG_DELETE_WHEN_REGISTERING))
                {
                    LONG err = RegDeleteAllKeys(hkeyRoot, szFullKey);
                    if (err != ERROR_SUCCESS && err != ERROR_FILE_NOT_FOUND)
                        hr = SELFREG_E_CLASS;
                    
                }
                pEntries++;
            }
        }
    }
    return hr;
}



#endif
