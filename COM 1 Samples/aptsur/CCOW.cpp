////////////////////////////////////////////////////////
//
// CCOW.cpp - Copyright 1997, Don Box 
//
// A ClassObjectWrapper that that forwards activation
// requests to an STA.
//


#include "CCOW.h"
#include "CSurrogate.h"

// this class is needed to trigger FreeSurrogate requests
struct CDummyUnknown : public IUnknown {
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv) {
        if (riid == IID_IUnknown)
            return ((IUnknown*)(*ppv = (IUnknown*)this))->AddRef(), S_OK;
        else
            return (*ppv = 0), E_NOINTERFACE;
    }

    STDMETHODIMP_(ULONG) AddRef(void)
    {  return 2; }

    STDMETHODIMP_(ULONG) Release(void)
    {  return 1; }
};

        
CClassObjectWrapper::CClassObjectWrapper(REFCLSID rclsid)
:   m_cRef(0)
{
    m_clsid = rclsid;
}

CClassObjectWrapper::~CClassObjectWrapper(void) { }

// IUnknown methods
STDMETHODIMP 
CClassObjectWrapper::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown || riid == IID_IClassFactory)
        *ppv = (IClassFactory*)this;
    else if (riid == IID_IMarshal)
        *ppv = (IMarshal*)this;
    else 
        return (*ppv = 0), E_NOINTERFACE;
    ((IUnknown*)*ppv)->AddRef();
    return S_OK;
}

STDMETHODIMP_(ULONG) 
CClassObjectWrapper::AddRef(void)
{
    return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) 
CClassObjectWrapper::Release(void)
{
    ULONG result = InterlockedDecrement(&m_cRef);
    if (result == 0)
        delete this;
    return result;
}

// IClassFactory methods
STDMETHODIMP 
CClassObjectWrapper::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
// forward the call to the "real" inproc factory 
    HRESULT hr = CSurrogate::GetSurrogate()->GetNextApartment(m_clsid)->RequestNewObject(m_clsid,riid,ppv);
    if (FAILED(hr)) 
    {
// we need to trigger a FreeSurrogate by creating and 
// destroying a stub (if we are 1st CCI, we will leak otherwise)
        CDummyUnknown dummy;
        hr = CoLockObjectExternal(&dummy, TRUE, TRUE);
        assert(hr);
        hr = CoLockObjectExternal(&dummy, FALSE, TRUE);
        assert(hr);
    }
    return hr;
}


STDMETHODIMP 
CClassObjectWrapper::LockServer(BOOL fLock)
{
    return S_OK;
}


// IMarshal methods
STDMETHODIMP 
CClassObjectWrapper::GetUnmarshalClass(REFIID riid, void *pv, DWORD dwDstCtx,
                                     void *pvDstCtx, DWORD flags, CLSID *pCid)
{
    *pCid = CLSID_StdMarshal; // we hardwire the standard marshaler here
    return S_OK;
}

STDMETHODIMP 
CClassObjectWrapper::GetMarshalSizeMax(REFIID riid, void *pv, DWORD dwDstCtx,
                                     void *pvDstCtx, DWORD flags, DWORD *pSize)
{
// because we use the standard marshaler, we will never be asked to size a ptr.
    return E_UNEXPECTED;                                         
}

STDMETHODIMP 
CClassObjectWrapper::MarshalInterface(IStream *pStm, REFIID riid, void *pv,
                                   DWORD dwDstCtx, void *pvDstCtx, DWORD flags)
{
// this is called when the SCM needs a pointer to the inproc class object
// we need to return the inproc pointer marshaled into pStm
    IUnknown *pUnk = 0;
    HRESULT hr = CSurrogate::GetSurrogate()->GetNextApartment(m_clsid)->RequestNewObject(m_clsid, riid, (void**)&pUnk);
    if (SUCCEEDED(hr))
    {
        hr = CoMarshalInterface(pStm,riid,pUnk,dwDstCtx,pvDstCtx,flags);
        pUnk->Release();
    }
    if (FAILED(hr))
    {
// we need to trigger a FreeSurrogate by creating and 
// destroying a stub (if we are 1st CGCO, we will leak otherwise)
        CDummyUnknown dummy;
        hr = CoLockObjectExternal(&dummy, TRUE, TRUE);
        assert(hr);
        hr = CoLockObjectExternal(&dummy, FALSE, TRUE);
        assert(hr);
    }
    return hr;                                         
}

STDMETHODIMP 
CClassObjectWrapper::UnmarshalInterface(IStream *pStm,REFIID riid,void **ppv)
{
    return E_UNEXPECTED;
}

STDMETHODIMP 
CClassObjectWrapper::ReleaseMarshalData(IStream *pStm)
{
    return CoReleaseMarshalData(pStm);                                         
}


STDMETHODIMP 
CClassObjectWrapper::DisconnectObject(DWORD dwReserved)
{
    return S_OK;
}

