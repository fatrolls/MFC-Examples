///////////////////////////////////////////////////
//
//  callinfo.h - Copyright 1997, Don Box
//  
//  External accessor to host info stored by channel hook
//
//


#ifndef _CALLINFO_H
#define _CALLINFO_H


#include <windows.h>
#include "hosthook.h"

class CallInfo : public ICallInfo, public IClientCallInfo
{
public:
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    STDMETHODIMP get_OriginalProcessID(long *pVal);
    STDMETHODIMP get_OriginalThreadID(long *pVal);
    STDMETHODIMP get_OriginalHostID(long *pVal);
    STDMETHODIMP get_OriginalHostName(BSTR *pVal);

    STDMETHODIMP get_DirectProcessID(long *pVal);
    STDMETHODIMP get_DirectThreadID(long *pVal);
    STDMETHODIMP get_DirectHostID(long *pVal);
    STDMETHODIMP get_DirectHostName(BSTR *pVal);

    STDMETHODIMP get_PseudoCausalityID(GUID *pguid);

    STDMETHODIMP get_TargetProcessID(long *pVal);
    STDMETHODIMP get_TargetThreadID(long *pVal);
    STDMETHODIMP get_TargetHostID(long *pVal);
    STDMETHODIMP get_TargetHostName(BSTR *pVal);
};

class CallInfoClassObject : public IClassFactory
{
public:
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv);
    STDMETHODIMP LockServer(BOOL bLock);
};

#endif
