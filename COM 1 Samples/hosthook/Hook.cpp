///////////////////////////////////////////////////
//
//  Hook.cpp - Copyright 1997, Don Box
//  
//  A host info channel hook
//
//

#include "hook.h"
#include <initguid.h>
#include "common.h"

#include <assert.h>


static NODE_INFO g_niThis;
DWORD g_dwTLSIndex;
HANDLE g_hheap;
HINSTANCE g_hInstance;

BOOL WINAPI DllMain(HINSTANCE h, DWORD dwReason, void *pv) {
// declare one process-wide channel hook instance
    static HostHook s_theHook;
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        {
// turn on sockets if not already enabled in this process
            WSADATA wsad;
            WSAStartup(MAKEWORD(1,1), &wsad);
// acquire a TLS slot
            if ((g_dwTLSIndex = TlsAlloc()) == 0xFFFFFFFF)
                return FALSE;
// register the process-wide channel hook
            HRESULT hr = CoRegisterChannelHook(EXTENTID_HostHook, &s_theHook);
            if (FAILED(hr))
                return FALSE;
// initialize various globals including getting the current IP address
            g_hInstance = h;
            g_hheap = HeapCreate(0, 1, 0);
            g_niThis.pid = GetCurrentProcessId();
            char szHostName[1024];
            int res = gethostname(szHostName, 1024);
            if (res == 0) {
                HOSTENT *p = gethostbyname(szHostName);
                if (p)
                    memcpy(&g_niThis.ip, p->h_addr, 4);
            }
        }
        break;
    case DLL_THREAD_DETACH:
        {
// clean up any thread/call context acquired for this thread
            THREAD_CONTEXT *p = (THREAD_CONTEXT *)TlsGetValue(g_dwTLSIndex);
            if (p)
            {
                CALL_CONTEXT *pc = p->pCurrentCall;
                while (pc)
                {
                    p->pCurrentCall = p->pCurrentCall->pNext;
                    HeapFree(g_hheap, 0, pc);
                    pc = p->pCurrentCall;
                }
                HeapFree(g_hheap, 0, p);
            }
        }
        break;
    case DLL_PROCESS_DETACH:
// release TLS slot and deallocate all memory
        if (g_dwTLSIndex != 0xFFFFFFFF)
            TlsFree(g_dwTLSIndex);
        HeapDestroy(g_hheap);
        break;
    }
    return TRUE;
}

// Helper routine to grab onto the current THREAD_CONTEXT
THREAD_CONTEXT *GetCurrentThreadContext(void)
{
// grab the pointer
    void *pv = TlsGetValue(g_dwTLSIndex);

// if this is the first time through, alloc and init
    if (pv == 0) 
    {
        pv = HeapAlloc(g_hheap, 0, sizeof(THREAD_CONTEXT));
        assert(pv);
        TlsSetValue(g_dwTLSIndex, pv);
        THREAD_CONTEXT& tc = *((THREAD_CONTEXT*)pv);
        tc.pCurrentCall = 0;
        tc.niThis = g_niThis;
        tc.niThis.tid = GetCurrentThreadId();
        tc.niTarget = tc.niThis;
    }
    return (THREAD_CONTEXT*)pv;
}

// Helper routine to push a new call context onto the current stack
// based (potentially) on a new incoming call
CALL_CONTEXT *PushCallContext(void *pvORPCTHIS)
{
// get TLS slot for this thread
    THREAD_CONTEXT *pThreadContext = GetCurrentThreadContext();
    assert(pThreadContext);

// allocate a new call context for this call    
    CALL_CONTEXT *pNewCallContext = (CALL_CONTEXT*)HeapAlloc(g_hheap, 0, sizeof(CALL_CONTEXT));
    assert(pNewCallContext);

// initialize new call context
    if (pvORPCTHIS)
    {
        memcpy(static_cast<HOOK_THIS*>(pNewCallContext), pvORPCTHIS, sizeof(HOOK_THIS));
    }
    else if (pThreadContext->pCurrentCall)
    {
        *pNewCallContext = *pThreadContext->pCurrentCall;
        pNewCallContext->niDirect = pThreadContext->niThis;
    }
    else
    {
        CoCreateGuid(&pNewCallContext->cid);
        pNewCallContext->niDirect = pNewCallContext->niIndirect = pThreadContext->niThis;
    }

// push context onto stack
    pNewCallContext->pNext = pThreadContext->pCurrentCall;
    pThreadContext->pCurrentCall = pNewCallContext;
    return pNewCallContext;
}

// Helper routine to pop current call context from the thread stack
void PopCallContext(void *pvORPCTHAT)
{
    THREAD_CONTEXT *pThreadContext = GetCurrentThreadContext();
    assert(pThreadContext);
    HOOK_THAT *pht = pThreadContext;

    if (pvORPCTHAT)
        *pht = *(HOOK_THAT*)pvORPCTHAT;
    else
        pThreadContext->niTarget = pThreadContext->niThis;
    
// pop the current call context
    if (pThreadContext->pCurrentCall)
    {
        CALL_CONTEXT *pctx = pThreadContext->pCurrentCall;
        pThreadContext->pCurrentCall = pThreadContext->pCurrentCall->pNext;
        HeapFree(g_hheap, 0, pctx);
    }
}

STDMETHODIMP 
HostHook::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown)
        *ppv = static_cast<IUnknown*>(this);
    else if (riid == IID_IUnknown)
        *ppv = static_cast<IChannelHook*>(this);
    else
        return (*ppv = 0), E_NOINTERFACE;
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;
}

STDMETHODIMP_(ULONG) 
HostHook::AddRef(void)
{
    return 2;
}

STDMETHODIMP_(ULONG) 
HostHook::Release(void)
{
    return 1;
}


// called in client prior to making a call
STDMETHODIMP_(void) 
HostHook::ClientGetSize(REFGUID uExtent, REFIID riid, ULONG *pDataSize)
{
    assert(uExtent == EXTENTID_HostHook);
    *pDataSize = sizeof(HOOK_THIS);
}

// called in client prior to making a call
STDMETHODIMP_(void) 
HostHook::ClientFillBuffer(REFGUID uExtent, REFIID riid, ULONG *pDataSize, void *pDataBuffer)
{
    assert(uExtent == EXTENTID_HostHook);
    CALL_CONTEXT *pContext = PushCallContext(0);
    HOOK_THIS *pORPCTHIS = (HOOK_THIS *)pDataBuffer;

    *pORPCTHIS = *pContext;

    *pDataSize = sizeof(HOOK_THIS);
}

// called in client just after a call completes
STDMETHODIMP_(void) 
HostHook::ClientNotify(REFGUID uExtent, REFIID riid, ULONG cbDataSize, void *pDataBuffer, DWORD lDataRep, HRESULT hrFault)
{
    assert(uExtent == EXTENTID_HostHook);
    assert(lDataRep == NDR_LOCAL_DATA_REPRESENTATION);
    PopCallContext(pDataBuffer);
}

// called in server just prior to invoking a call
STDMETHODIMP_(void) 
HostHook::ServerNotify(REFGUID uExtent, REFIID riid, ULONG cbDataSize, void *pDataBuffer, DWORD lDataRep)
{
    assert(uExtent == EXTENTID_HostHook);
    assert(lDataRep == NDR_LOCAL_DATA_REPRESENTATION);
    PushCallContext(pDataBuffer);
}

// called in server just after invoking a call
STDMETHODIMP_(void) 
HostHook::ServerGetSize(REFGUID uExtent, REFIID riid, HRESULT hrFault, ULONG *pDataSize)
{
    *pDataSize = sizeof(HOOK_THAT);
}

// called in server just after invoking a call
STDMETHODIMP_(void) 
HostHook::ServerFillBuffer(REFGUID uExtent, REFIID riid, ULONG *pDataSize, void *pDataBuffer, HRESULT hrFault)
{
    assert(uExtent == EXTENTID_HostHook);
    THREAD_CONTEXT *pThreadContext = GetCurrentThreadContext();
    HOOK_THAT *pORPCTHAT = (HOOK_THAT *)pDataBuffer;

    pORPCTHAT->niTarget = pThreadContext->niThis;
    
    *pDataSize = sizeof(HOOK_THAT);
    PopCallContext(0);
}
