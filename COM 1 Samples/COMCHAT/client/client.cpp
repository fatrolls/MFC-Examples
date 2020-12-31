/////////////////////////////////////////////////////
//
// client.cpp
//
// Copyright 1997, Don Box/Addison Wesley
//
// This code accompanies the book "The Component
// Object Model" from Addison Wesley. Blah blah blah
//
//

#define _WIN32_WINNT 0x403
#include <windows.h>
#include <stdio.h>
#include <initguid.h>
#include <wchar.h>
#include "../include/COMChat.h"
#include "../include/COMChat_i.c"

void Error(HRESULT hr, const char *psz)
{
    printf("%s failed and returned 0x%x\n", psz, hr);
}

// utility function to print command line syntax
int Usage(void)
{
   const char *psz = 
    "usage: client.exe <action> <user> <host>\n"
    "   where:\n"
    "          action = /sessions|/chat:session|/delete:session\n"
    "          user = /user:domain\\user /password:pw |"
                "/anonymous | <nothing>\n"
    "          host = /host:hostname | <nothing>\n";
   printf(psz);
   return -1;
}

// utility function for printing a list of strings
void PrintAllStrings(IEnumString *pes)
{
    enum { CHUNKSIZE = 64 };
    OLECHAR *rgpwsz[CHUNKSIZE];
    ULONG cFetched;
    HRESULT hr;
    do
    {
        hr = pes->Next(CHUNKSIZE, rgpwsz, &cFetched);
        if (SUCCEEDED(hr))
        {
            for (ULONG i = 0; i < cFetched; i++)
                if (rgpwsz[i])
                {
                    wprintf(L"%s\n", rgpwsz[i]);
                    CoTaskMemFree(rgpwsz[i]);
                }
        }
    } while (hr == S_OK);
}

// utility function to print initial state of 
// a chat session
void PrintToDate(IChatSession *pcs)
{
    IEnumString *pes = 0;
    HRESULT hr = pcs->GetStatements(&pes);
    if (SUCCEEDED(hr))
    {
        PrintAllStrings(pes);
        pes->Release();
    }
}

// this class implements the callback interface
// that receives chat notifications. It simply 
// prints the event to the console
class EventSink : public IChatSessionEvents
{
public:
    STDMETHODIMP QueryInterface(REFIID riid, void**ppv)
    {
        if (riid == IID_IUnknown)
            *ppv = static_cast<IChatSessionEvents*>(this);
        else if (riid == IID_IChatSessionEvents)
            *ppv = static_cast<IChatSessionEvents*>(this);
        else
            return (*ppv = 0), E_NOINTERFACE;
        reinterpret_cast<IUnknown*>(*ppv)->AddRef();
        return S_OK;
    }
    STDMETHODIMP_(ULONG) AddRef(void)
    {
        return 2;
    }
    STDMETHODIMP_(ULONG) Release(void)
    {
        return 1;
    }
    STDMETHODIMP OnNewStatement(const OLECHAR *pwszUser,
                                const OLECHAR *pwszStmt)
    {
        wprintf(L"%-14s: %s\n", pwszUser, pwszStmt);
        return S_OK;
    }
    STDMETHODIMP OnNewUser(const OLECHAR *pwszUser)
    {
        wprintf(L"\n\n>>> Say Hello to %s\n\n", pwszUser);
        return S_OK;
    }
    STDMETHODIMP OnUserLeft(const OLECHAR *pwszUser)
    {
        wprintf(L"\n\n>>> Say Bye to %s\n\n", pwszUser);
        return S_OK;
    }
    
};

// type of operations this client can perform
enum ACTION
{
    ACTION_NONE,
    ACTION_CHAT,
    ACTION_DELETE_SESSION,
    ACTION_LIST_SESSION_NAMES,
};

// run chat command
void Chat(const OLECHAR *pwszSession,
          IChatSessionManager *pcsm, // manager
          COAUTHIDENTITY *pcai,      // user
          bool bAnonymous)           // anonymous
{
// create or get the named session
    IChatSession *pcs = 0;
    HRESULT hr = pcsm->FindSession(pwszSession, FALSE, 
                                   TRUE, &pcs);
    if (SUCCEEDED(hr))
    {
// adjust security blanket for session interface
        if (!bAnonymous)
            hr = CoSetProxyBlanket(pcs, RPC_C_AUTHN_WINNT, 
                                   RPC_C_AUTHZ_NONE, 0, 
                                   RPC_C_AUTHN_LEVEL_PKT, 
                                   RPC_C_IMP_LEVEL_IDENTIFY,
                                   pcai, EOAC_NONE);
// catch up on past messages
        PrintToDate(pcs);
// hook up event sink to receive new messages
        EventSink es;
        DWORD dwReg;
        hr = pcs->Advise(&es, &dwReg);
        if (SUCCEEDED(hr))
        {
// run UI loop to get statements from console and send them
            OLECHAR wszStmt[4096];
            while (_getws(wszStmt))
            {
                hr = pcs->Say(wszStmt);
                if (FAILED(hr))
                    Error(hr, "Say");
            }
// tear down connection for event sink
            pcs->Unadvise(dwReg);
        }
        else
            Error(hr, "Advise");
// release chat session
        pcs->Release();
    }
    else
        Error(hr, "FindSession");
}

// run delete command
void Delete(const OLECHAR *pwszSession,
            IChatSessionManager *pcsm)
{
    HRESULT hr = pcsm->DeleteSession(pwszSession);
    if (FAILED(hr))
        Error(hr, "DeleteSession");
}

// run list command
void List(IChatSessionManager *pcsm)
{
    IEnumString *pes = 0;
    HRESULT hr = pcsm->GetSessionNames(&pes);
    if (SUCCEEDED(hr))
    {
        printf("Active Sessions:\n");
        PrintAllStrings(pes);
        pes->Release();
    }
}

int main(int argc, char **argv)
{
// declare client control state
    bool bAnonymous = false;
    static OLECHAR wszSessionName[1024];
    static OLECHAR wszDomainName[1024];
    static OLECHAR wszUserName[1024];
    static OLECHAR wszPassword[1024];
    static OLECHAR wszHostName[1024];
    COSERVERINFO csi = { 0, wszHostName, 0, 0 };
    COSERVERINFO *pcsi = 0;
    COAUTHIDENTITY cai = {
        wszUserName,
        0,
        wszDomainName,
        0,
        wszPassword,
        0,
        SEC_WINNT_AUTH_IDENTITY_UNICODE
    };
    static COAUTHIDENTITY *pcai = 0;
    static ACTION action = ACTION_NONE;

// parse command line
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "/anonymous") == 0)
            bAnonymous = true;
        else if (strstr(argv[i], "/delete:") == argv[i])
        {
            if (action != ACTION_NONE)
                return Usage();
            action = ACTION_DELETE_SESSION;
            mbstowcs(wszSessionName, argv[i] + 8, 1024);
        }
        else if (strstr(argv[i], "/chat:") == argv[i])
        {
            if (action != ACTION_NONE)
                return Usage();
            action = ACTION_CHAT;
            mbstowcs(wszSessionName, argv[i] + 6, 1024);
        }
        else if (strcmp(argv[i], "/sessions") == 0)
        {
            if (action != ACTION_NONE)
                return Usage();
            action = ACTION_LIST_SESSION_NAMES;
        }
        else if (strstr(argv[i], "/host:") == argv[i])
        {
            if (pcsi != 0)
                return Usage();
            mbstowcs(wszHostName, argv[i] + 6, 1024);
            pcsi = &csi;
        }
        else if (strstr(argv[i], "/password:") == argv[i])
        {
            mbstowcs(wszPassword, argv[i] + 10, 1024);
            cai.PasswordLength = wcslen(wszPassword);
        }
        else if (strstr(argv[i], "/user:") == argv[i])
        {
            if (pcai != 0 || bAnonymous)
                return Usage();
            char *pszDelim = strchr(argv[i] + 7, '\\');
            if (pszDelim == 0)
                return Usage();
            *pszDelim = 0;
            pszDelim++;
            mbstowcs(wszDomainName, argv[i] + 6, 1024);
            cai.DomainLength = wcslen(wszDomainName);
            mbstowcs(wszUserName, pszDelim, 1024);
            cai.UserLength = wcslen(wszUserName);
            pcai = &cai;
        }
    }

    if (action == ACTION_NONE)
        return Usage();
    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hr))
        return hr;

// allow anonymous callbacks from chat server
    hr = CoInitializeSecurity(0, -1, 0, 0,
                              RPC_C_AUTHN_LEVEL_NONE,
                              RPC_C_IMP_LEVEL_ANONYMOUS,
                              0, EOAC_NONE, 0);
    
    if (SUCCEEDED(hr))
    {
// grab the requested session manager
        IChatSessionManager *pcsm = 0;
        hr = CoGetClassObject(CLSID_ChatSession, CLSCTX_ALL,
                              pcsi, IID_IChatSessionManager,
                              (void**)&pcsm);
        if (SUCCEEDED(hr))
        {
// apply security blanket if desired
            if (!bAnonymous)
                hr = CoSetProxyBlanket(pcsm, RPC_C_AUTHN_WINNT, 
                                       RPC_C_AUTHZ_NONE, 0, 
                                       RPC_C_AUTHN_LEVEL_PKT, 
                                       RPC_C_IMP_LEVEL_IDENTIFY,
                                       pcai, EOAC_NONE);
// dispatch request
            switch (action)
            {
            case ACTION_CHAT:
                Chat(wszSessionName, pcsm, pcai, bAnonymous);
                break;
            case ACTION_DELETE_SESSION:
                Delete(wszSessionName, pcsm);
                break;
            case ACTION_LIST_SESSION_NAMES:
                List(pcsm);
                break;
            default:
                Usage();
            }
// release session manager
            pcsm->Release();
        }
    }
    CoUninitialize();
    return hr;
}
