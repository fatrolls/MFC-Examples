////////////////////////////////////////////////////////
//
// CCOW.h - Copyright 1997, Don Box 
//
// A ClassObjectWrapper that that forwards activation
// requests to an STA.
//

#ifndef _CCOW_H
#define _CCOW_H


#include <windows.h>
#include <assert.h>

class CClassObjectWrapper : public IClassFactory,
                            public IMarshal
{
    LONG m_cRef;
    CLSID m_clsid;
    DWORD m_dwReg;
    friend class CSurrogate;
public:
    CClassObjectWrapper(REFCLSID rclsid);
    virtual ~CClassObjectWrapper(void);
    
// IUnknown methods
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);
    
// IClassFactory methods
    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv);
    STDMETHODIMP LockServer(BOOL fLock);
    
// IMarshal methods
    STDMETHODIMP GetUnmarshalClass(REFIID riid, void *pv, DWORD dwDstCtx,
                                   void *pvDstCtx, DWORD flags, CLSID *pCid);
    STDMETHODIMP GetMarshalSizeMax(REFIID riid, void *pv, DWORD dwDstCtx,
                                    void *pvDstCtx, DWORD flags, DWORD *pSize);
    STDMETHODIMP MarshalInterface(IStream *pStm, REFIID riid, void *pv,
                                  DWORD dwDstCtx, void *pvDstCtx, DWORD flags);
    STDMETHODIMP UnmarshalInterface(IStream *pStm, REFIID riid, void **ppv);
    STDMETHODIMP ReleaseMarshalData(IStream *pStm);
    STDMETHODIMP DisconnectObject(DWORD dwReserved);
};

#endif
