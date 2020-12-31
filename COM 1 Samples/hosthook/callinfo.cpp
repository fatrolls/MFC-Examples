///////////////////////////////////////////////////
//
//  callinfo.cpp - Copyright 1997, Don Box
//  
//  External accessor to host info stored by channel hook
//
//

#include "callinfo.h"

#include "common.h"

#include "hosthook_i.c"

// helper routine to convert IP address to a BSTR
BSTR GetNameFromIPAddress(DWORD dwIP)
{
    HOSTENT *p = gethostbyaddr((const char*)&dwIP, 4, AF_INET);
    if (p && p->h_name)
    {
        int cch = lstrlenA(p->h_name);
        BSTR bstr = SysAllocStringLen(0, cch);
        if (bstr)
            MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, p->h_name, cch + 1, bstr, cch + 1);
        return bstr;
    }
    return 0;
}

STDMETHODIMP 
CallInfo::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown)
        *ppv = static_cast<ICallInfo*>(this);
    else if (riid == IID_ICallInfo)
        *ppv = static_cast<ICallInfo*>(this);
    else if (riid == IID_IClientCallInfo)
        *ppv = static_cast<IClientCallInfo*>(this);
    else
        return (*ppv = 0), E_NOINTERFACE;
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;

}

STDMETHODIMP_(ULONG) 
CallInfo::AddRef(void)
{
    return 2;
}

STDMETHODIMP_(ULONG) 
CallInfo::Release(void)
{
    return 1;
}

STDMETHODIMP 
CallInfo::get_OriginalProcessID(long *pVal)
{
    THREAD_CONTEXT *pctx = GetCurrentThreadContext();
    NODE_INFO& rni = pctx->pCurrentCall ? pctx->pCurrentCall->niIndirect : pctx->niThis;
    *pVal = rni.pid;
    return S_OK;
}

STDMETHODIMP 
CallInfo::get_OriginalThreadID(long *pVal)
{
    THREAD_CONTEXT *pctx = GetCurrentThreadContext();
    NODE_INFO& rni = pctx->pCurrentCall ? pctx->pCurrentCall->niIndirect : pctx->niThis;
    *pVal = rni.tid;
    return S_OK;
}

STDMETHODIMP 
CallInfo::get_OriginalHostID(long *pVal)
{
    THREAD_CONTEXT *pctx = GetCurrentThreadContext();
    NODE_INFO& rni = pctx->pCurrentCall ? pctx->pCurrentCall->niIndirect : pctx->niThis;
    *pVal = rni.ip;
    return S_OK;
}

STDMETHODIMP 
CallInfo::get_OriginalHostName(BSTR *pVal)
{
    THREAD_CONTEXT *pctx = GetCurrentThreadContext();
    NODE_INFO& rni = pctx->pCurrentCall ? pctx->pCurrentCall->niIndirect : pctx->niThis;
    *pVal = GetNameFromIPAddress(rni.ip);
    return S_OK;
}

STDMETHODIMP 
CallInfo::get_DirectProcessID(long *pVal)
{
    THREAD_CONTEXT *pctx = GetCurrentThreadContext();
    NODE_INFO& rni = pctx->pCurrentCall ? pctx->pCurrentCall->niDirect : pctx->niThis;
    *pVal = rni.pid;
    return S_OK;
}

STDMETHODIMP 
CallInfo::get_DirectThreadID(long *pVal)
{
    THREAD_CONTEXT *pctx = GetCurrentThreadContext();
    NODE_INFO& rni = pctx->pCurrentCall ? pctx->pCurrentCall->niDirect : pctx->niThis;
    *pVal = rni.tid;
    return S_OK;
}

STDMETHODIMP 
CallInfo::get_DirectHostID(long *pVal)
{
    THREAD_CONTEXT *pctx = GetCurrentThreadContext();
    NODE_INFO& rni = pctx->pCurrentCall ? pctx->pCurrentCall->niDirect : pctx->niThis;
    *pVal = rni.ip;
    return S_OK;
}

STDMETHODIMP 
CallInfo::get_DirectHostName(BSTR *pVal)
{
    THREAD_CONTEXT *pctx = GetCurrentThreadContext();
    NODE_INFO& rni = pctx->pCurrentCall ? pctx->pCurrentCall->niDirect : pctx->niThis;
    *pVal = GetNameFromIPAddress(rni.ip);
    return S_OK;
}

STDMETHODIMP 
CallInfo::get_PseudoCausalityID(GUID *pguid)
{
    THREAD_CONTEXT *pctx = GetCurrentThreadContext();
    if (pctx->pCurrentCall)
        *pguid = pctx->pCurrentCall->cid;
    else
        *pguid = GUID_NULL;
    return S_OK;
}

STDMETHODIMP 
CallInfo::get_TargetProcessID(long *pVal)
{
    THREAD_CONTEXT *pctx = GetCurrentThreadContext();
    NODE_INFO& rni = pctx->niTarget;
    *pVal = rni.pid;
    rni.pid = 0;
    return S_OK;
}

STDMETHODIMP 
CallInfo::get_TargetThreadID(long *pVal)
{
    THREAD_CONTEXT *pctx = GetCurrentThreadContext();
    NODE_INFO& rni = pctx->niTarget;
    *pVal = rni.tid;
    rni.tid = 0;
    return S_OK;
}

STDMETHODIMP 
CallInfo::get_TargetHostID(long *pVal)
{
    THREAD_CONTEXT *pctx = GetCurrentThreadContext();
    NODE_INFO& rni = pctx->niTarget;
    *pVal = rni.ip;
    rni.ip = 0;
    return S_OK;
}

STDMETHODIMP 
CallInfo::get_TargetHostName(BSTR *pVal)
{
    THREAD_CONTEXT *pctx = GetCurrentThreadContext();
    NODE_INFO& rni = pctx->niTarget;
    *pVal = GetNameFromIPAddress(rni.ip);
    rni.ip = 0;
    return S_OK;
}

STDMETHODIMP 
CallInfoClassObject::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown)
        *ppv = static_cast<IUnknown*>(this);
    else if (riid == IID_IClassFactory)
        *ppv = static_cast<IClassFactory*>(this);
    else
        return (*ppv = 0), E_NOINTERFACE;
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;
}

STDMETHODIMP_(ULONG) 
CallInfoClassObject::AddRef(void)
{
    return 2;
}

STDMETHODIMP_(ULONG) 
CallInfoClassObject::Release(void)
{
    return 1;
}


STDMETHODIMP 
CallInfoClassObject::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
// we only have one CallInfo per process that satisfies all callers
    static CallInfo s_theInfo;
    if (pUnkOuter)
        return (*ppv = 0), CLASS_E_NOAGGREGATION;
    return s_theInfo.QueryInterface(riid, ppv);
}

STDMETHODIMP 
CallInfoClassObject::LockServer(BOOL bLock)
{
    return S_OK;
}
