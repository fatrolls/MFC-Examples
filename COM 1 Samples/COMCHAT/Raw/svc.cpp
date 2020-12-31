/////////////////////////////////////////////////////
//
// svc.cpp
//
// Copyright 1997, Don Box/Addison Wesley
//
// This code accompanies the book "The Component
// Object Model" from Addison Wesley. Blah blah blah
//
//

#define _WIN32_WINNT 0x403
#include <windows.h>
#include <olectl.h>
#include <initguid.h>
#include <iaccess.h>

#include "ChatSession.h"
#include "../include/COMChat_i.c"


#if !defined(HAVE_IID_IACCESSCONTROL)
// there is a common bug is the SDK headers and libs
// that causes IID_IAccessControl to be undefined.
// We define it here to give the GUID linkage.
DEFINE_GUID(IID_IAccessControl,0xEEDD23E0, 0x8410, 0x11CE, 
            0xA1, 0xC3, 0x08, 0x00, 0x2B, 0x2B, 0x8D, 0x8F);
#endif

// standard MTA lifetime management helpers
HANDLE g_heventDone = CreateEvent(0, TRUE, FALSE, 0);

void ModuleLock(void)
{
    CoAddRefServerProcess();
}

void ModuleUnlock(void)
{
    if (CoReleaseServerProcess() == 0)
        SetEvent(g_heventDone);
}

// standard self-registration table
const char *g_RegTable[][3] = {
{ "CLSID\\{5223A053-2441-11d1-AF4F-0060976AA886}",
  0, "ChatSession" },
{ "CLSID\\{5223A053-2441-11d1-AF4F-0060976AA886}",
  "AppId", "{5223A054-2441-11d1-AF4F-0060976AA886}"
},
{ "CLSID\\{5223A053-2441-11d1-AF4F-0060976AA886}\\LocalServer32",
  0, (const char*)-1 // rogue value indicating file name
},
{ "AppID\\{5223A054-2441-11d1-AF4F-0060976AA886}",
  0, "ChatSession Server" },
{ "AppID\\{5223A054-2441-11d1-AF4F-0060976AA886}",
  "RunAs", "Domain\\ReplaceMe"
},
{ "AppID\\{5223A054-2441-11d1-AF4F-0060976AA886}",
  "Chat Admins Group", "Domain\\ReplaceMe"
},
{ "AppID\\{5223A054-2441-11d1-AF4F-0060976AA886}",
  "Chat Users Group", "Domain\\ReplaceMe"
},
{ "AppID\\COMChat.exe",
  "AppId", "{5223A054-2441-11d1-AF4F-0060976AA886}"
},
};

// self-unregistration routine
STDAPI UnregisterServer(void) {
  HRESULT hr = S_OK;
  int nEntries = sizeof(g_RegTable)/sizeof(*g_RegTable);
  for (int i = nEntries - 1; i >= 0; i--){
    const char *pszKeyName = g_RegTable[i][0];

    long err = RegDeleteKeyA(HKEY_CLASSES_ROOT, pszKeyName);
    if (err != ERROR_SUCCESS) 
      hr = S_FALSE;
  }
  return hr;
}

// self-registration routine
STDAPI RegisterServer(HINSTANCE hInstance = 0) {
  HRESULT hr = S_OK;
// look up server's file name
  char szFileName[MAX_PATH];
  GetModuleFileNameA(hInstance, szFileName, MAX_PATH);
// register entries from table
  int nEntries = sizeof(g_RegTable)/sizeof(*g_RegTable);
  for (int i = 0; SUCCEEDED(hr) && i < nEntries; i++) {
    const char *pszKeyName   = g_RegTable[i][0];
    const char *pszValueName = g_RegTable[i][1];
    const char *pszValue     = g_RegTable[i][2];
// map rogue value to module file name
    if (pszValue == (const char*)-1)
      pszValue = szFileName;
    HKEY hkey;
// create the key
    long err = RegCreateKeyA(HKEY_CLASSES_ROOT,
                            pszKeyName, &hkey);
    if (err == ERROR_SUCCESS) {
// set the value
      err = RegSetValueExA(hkey, pszValueName, 0,
                           REG_SZ, (const BYTE*)pszValue,
                           (strlen(pszValue) + 1));
      RegCloseKey(hkey);
    }
    if (err != ERROR_SUCCESS) {
  // if cannot add key or value, back out and fail
      UnregisterServer(); 
      hr = SELFREG_E_CLASS;
    }
  }
  return hr;
}

// these point to standard access control objects
// used to protect particular methods
IAccessControl *g_pacUsers = 0;
IAccessControl *g_pacAdmins = 0;

// this routine is called at process init time
// to build access control objects and to allow
// anonymous access to server by default
HRESULT InitializeApplicationSecurity(void)
{
// load groupnames from registry
    static OLECHAR wszAdminsGroup[1024];
    static OLECHAR wszUsersGroup[1024];
    HKEY hkey;
    long err = RegOpenKeyEx(HKEY_CLASSES_ROOT,
         __TEXT("AppID\\{5223A054-2441-11d1-AF4F-0060976AA886}"),
                            0, KEY_QUERY_VALUE,
                            &hkey);
    if (err == ERROR_SUCCESS)
    {
        DWORD cb = sizeof(wszAdminsGroup);
        err = RegQueryValueExW(hkey, L"Chat Admins Group",
                              0, 0, (BYTE*)wszAdminsGroup,
                              &cb);
        cb = sizeof(wszAdminsGroup);
        if (err == ERROR_SUCCESS)
            err = RegQueryValueExW(hkey, 
                                   L"Chat Users Group",
                                   0, 0, (BYTE*)wszUsersGroup,
                                   &cb); 
        RegCloseKey(hkey);
    }
    if (err != ERROR_SUCCESS)
        return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32,
                            GetLastError());
                            
// declare vectors of user/groups for 2 access 
// control objects

    ACTRL_ACCESS_ENTRYW rgaaeUsers[] = {
      { {0, NO_MULTIPLE_TRUSTEE, TRUSTEE_IS_NAME, 
        TRUSTEE_IS_GROUP, wszUsersGroup  }, 
        ACTRL_ACCESS_ALLOWED, COM_RIGHTS_EXECUTE, 0, 
        NO_INHERITANCE, 0 },
    };
    ACTRL_ACCESS_ENTRY_LISTW aaelUsers = { 
        sizeof(rgaaeUsers)/sizeof(*rgaaeUsers), 
        rgaaeUsers
    };
    ACTRL_PROPERTY_ENTRYW apeUsers = { 0, &aaelUsers, 0 };
    ACTRL_ACCESSW aaUsers = { 1, &apeUsers };

    ACTRL_ACCESS_ENTRYW rgaaeAdmins[] = {
      { {0, NO_MULTIPLE_TRUSTEE, TRUSTEE_IS_NAME, 
        TRUSTEE_IS_GROUP, wszAdminsGroup }, 
        ACTRL_ACCESS_ALLOWED, COM_RIGHTS_EXECUTE, 0, 
        NO_INHERITANCE, 0 },
    };
    ACTRL_ACCESS_ENTRY_LISTW aaelAdmins = { 
        sizeof(rgaaeAdmins)/sizeof(*rgaaeAdmins), 
        rgaaeAdmins
    };
    ACTRL_PROPERTY_ENTRYW apeAdmins = { 0, &aaelAdmins, 0 };
    ACTRL_ACCESSW aaAdmins = { 1, &apeAdmins };

    HRESULT hr = CoInitializeSecurity(0, -1, 0, 0,
                              RPC_C_AUTHN_LEVEL_NONE,
                              RPC_C_IMP_LEVEL_ANONYMOUS,
                              0,
                              EOAC_NONE,
                              0);
    if (SUCCEEDED(hr))
    {
        hr = CoCreateInstance(CLSID_DCOMAccessControl,
                              0, CLSCTX_ALL, IID_IAccessControl,
                              (void**)&g_pacUsers);
        if (SUCCEEDED(hr))
            hr = g_pacUsers->SetAccessRights(&aaUsers);
        if (SUCCEEDED(hr))
        {
            hr = CoCreateInstance(CLSID_DCOMAccessControl,
                                  0, CLSCTX_ALL, 
                                  IID_IAccessControl,
                                  (void**)&g_pacAdmins);
            if (SUCCEEDED(hr))
                hr = g_pacAdmins->SetAccessRights(&aaAdmins);
        }
        if (FAILED(hr))
        {
            if (g_pacAdmins)
            {
                g_pacAdmins->Release();
                g_pacAdmins = 0;
            }
            if (g_pacUsers)
            {
                g_pacUsers->Release();
                g_pacUsers = 0;
            }
        }
    }
    return hr;
}

// the main thread routine that simply registers the class
// object and waits to die
int WINAPI WinMain(HINSTANCE, HINSTANCE, 
                   LPSTR szCmdParam, int)
{
    const TCHAR *pszPrompt = 
        __TEXT("Ensure that you have properly ")
        __TEXT("configured the application to ")
        __TEXT("run as a particular user and that ")
        __TEXT("you have manually changed the ")
        __TEXT("Users and Admins Group registry ")
        __TEXT("settings under this server's AppID.");

    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hr))
        return hr;

// look for self-registration flags
    if (strstr(szCmdParam, "/UnregServer") != 0
        || strstr(szCmdParam, "-UnregServer") != 0)
    {
        hr = UnregisterServer();
        CoUninitialize();
        return hr;
    }
    else if (strstr(szCmdParam, "/RegServer") != 0
             || strstr(szCmdParam, "-RegServer") != 0)
    {
        hr = RegisterServer();
        MessageBox(0, pszPrompt, __TEXT("COMChat"), 
                   MB_SETFOREGROUND);
        CoUninitialize();
        return hr;
    }
    
// set up process security
    hr = InitializeApplicationSecurity();
    if (SUCCEEDED(hr))
    {
// register class object and wait to die
        DWORD  dwReg;
        static ChatSessionClass cmc;
        hr = CoRegisterClassObject(CLSID_ChatSession, 
              static_cast<IExternalConnection*>(&cmc),
                                   CLSCTX_LOCAL_SERVER,
                  REGCLS_SUSPENDED|REGCLS_MULTIPLEUSE,
                                   &dwReg);
        if (SUCCEEDED(hr))
        {
            hr = CoResumeClassObjects();
            if (SUCCEEDED(hr))
                WaitForSingleObject(g_heventDone, INFINITE);
            CoRevokeClassObject(dwReg);
        }
        g_pacUsers->Release();
        g_pacAdmins->Release();
    }
    if (FAILED(hr))
        MessageBox(0, pszPrompt, __TEXT("Error"), 
                   MB_SETFOREGROUND);

    CoUninitialize();
    return 0;
}
