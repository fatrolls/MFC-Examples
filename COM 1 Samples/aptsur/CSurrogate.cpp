////////////////////////////////////////////////////////
//
// CSurrogate.cpp - Copyright 1997, Don Box 
//
// An implementation of ISurrogate that that forwards 
// activation requests to one of N STAs.
//


#include "CCOW.h"
#include "CSurrogate.h"

CSurrogate *CSurrogate::s_pSurrogate = 0;

static HRESULT GUIDFromStringA(char *szGUID, GUID *pguid)
{
    OLECHAR wszGUID[39];
    mbstowcs(wszGUID, szGUID, 39);
    wszGUID[38] = 0;  
    return CLSIDFromString(wszGUID, pguid);
}

CSurrogate *CSurrogate::GetSurrogate(void)
{
    return s_pSurrogate;
}

HRESULT
CSurrogate::ParseCommandLine(LPSTR szCmdParam,
                             CLSID *pclsidInitial,
                             GUID  *pappid)
{
    enum { SURROGATE_SUFFIX = 38 + 1 + 10 };
    LPSTR szSuffix = szCmdParam + lstrlenA(szCmdParam) - SURROGATE_SUFFIX;
    HRESULT hr = GUIDFromStringA(szSuffix, pclsidInitial);
    if (SUCCEEDED(hr))
    {
        char sz[128];
        lstrcpyA(sz, "CLSID\\");
        memcpy(sz + 6, szSuffix, 38);
        sz[44] = 0;

        HKEY hkey = 0;
        LONG err = RegOpenKeyExA(HKEY_CLASSES_ROOT, sz, 0, 
                                 KEY_READ, &hkey);
        if (err == ERROR_SUCCESS)
        {
            DWORD cb = sizeof(sz);
            err = RegQueryValueEx(hkey, "AppID", 0, 0, (BYTE*)sz, &cb);
            if (err == ERROR_SUCCESS)
                hr = GUIDFromStringA(sz, pappid);
            else
                hr = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, err);

            RegCloseKey(hkey);
        }
        else
            hr = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, err);
    }
    return hr;
}


CSurrogate::CSurrogate(int nSTAThreads)
:   m_nMaxThreads(nSTAThreads),
    m_iNextThread(0),
    m_dwThreadId(GetCurrentThreadId())
{
    assert(s_pSurrogate == 0); // singleton
    s_pSurrogate = this;
    if (m_nMaxThreads < 1)
        m_nMaxThreads = 1;
    m_prgSTAs = new CSingleThreadedApartment[m_nMaxThreads];
    
}

CSurrogate::~CSurrogate(void)
{
    delete[] m_prgSTAs;
}

CSingleThreadedApartment *
CSurrogate::GetNextApartment(REFCLSID rclsid)
{
    LONG i = InterlockedIncrement(&m_iNextThread);
    return m_prgSTAs + (i % m_nMaxThreads);
}


// IUnknown methods
STDMETHODIMP 
CSurrogate::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown || riid == IID_ISurrogate)
        *ppv = (ISurrogate*)this;
    else 
        return (*ppv = 0), E_NOINTERFACE;
    ((IUnknown*)*ppv)->AddRef();
    return S_OK;
}

STDMETHODIMP_(ULONG) 
CSurrogate::AddRef(void)
{
    return 2;
}

STDMETHODIMP_(ULONG) 
CSurrogate::Release(void)
{
    return 1;
}

// ISurrogate methods
STDMETHODIMP 
CSurrogate::LoadDllServer(REFCLSID rclsid)
{
// create a wrapper class object
    CClassObjectWrapper *pcf = new CClassObjectWrapper(rclsid);
    if (!pcf)
        return E_OUTOFMEMORY;
// register the wrapper with COM using REGCLS_SURROGATE
    DWORD dwReg;
    pcf->AddRef();
    HRESULT hr = CoRegisterClassObject(rclsid, (IClassFactory*)pcf,
                                       CLSCTX_LOCAL_SERVER, REGCLS_SURROGATE,
                                       &dwReg);
    pcf->Release();
// keep track of class object to revoke later on
    if (SUCCEEDED(hr))
        m_rgdwReg.push_back(dwReg);
    return hr;
}

STDMETHODIMP 
CSurrogate::FreeSurrogate()
{
// tear down all connections with COM
    for (int i = 0; i < m_rgdwReg.size(); i++)
        CoRevokeClassObject(m_rgdwReg[i]);

// tear down all apartments
    {
    for (int i = 0; i < m_nMaxThreads; i++)
        m_prgSTAs[i].RequestShutdown(30000);
    }
// terminate main thread
    PostThreadMessage(m_dwThreadId, WM_QUIT, 0, 0);
    return S_OK;
}
        
