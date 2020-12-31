////////////////////////////////////////////////////////
//
// giplip.h - Copyright 1997, Don Box
//
// IGlobalInterfaceTable Management Classes
// 
// This file provides two classes that simplify sharing interface
// pointers across intra-process apartment boundaries (such as when
// using the FreeThreadedMarshaler):
//  
//      GlobalInterfacePointer<Itf, &IID_Itf> - a wrapper around IGIT cookies
//      LocalInterfacePointer<Itf, &IID_Itf>  - wraps imported IGIT cookies
//
// Usage:
//
//   class Bar : public IBar {
//     GlobalInterfacePointer<IFoo, &IID_IFoo> m_gipFoo;
//     STDMETHODIMP put_Foo(IFoo *pFoo) {
//       if (m_gipFoo.IsOK())
//         m_gipFoo.Unglobalize();
//       return m_gipFoo.Globalize(pFoo);
//     }
//     STDMETHODIMP BarMethod(void) {
//       HRESULT hr;
//       LIP(IFoo) lipFoo(m_gipFoo, hr);
//       if (SUCCEEDED(hr)) 
//         hr = lipFoo->FooMethod();
//       return hr;
//     }
//   };
//
// define this symbol in exactly one translation unit per target (a la INITGUID)
#ifdef _INIT_GIPLIP
IGlobalInterfaceTable *g_pGIT = 0;
#endif


#ifndef _GIPLIP_H
#define _GIPLIP_H

#include <assert.h>

#ifndef __IGlobalInterfaceTable_FWD_DEFINED__
#error "You need NT4/SP3 SDK headers and libs from http:/www.microsoft.com/msdn"
#endif

// this is where the template class gets its pointer to the GIT
extern IGlobalInterfaceTable *g_pGIT;

// this is a wrapper that grabs the GIT when needed
class GIT {
public:
// initialize module-wide GIT pointer
    static HRESULT Init(void) {
        HRESULT hr = S_OK;
        if (g_pGIT == 0)
            hr = CoCreateInstance(CLSID_StdGlobalInterfaceTable, 0, CLSCTX_ALL,
                                  IID_IGlobalInterfaceTable, (void**)&g_pGIT);
        return hr;
    }

// release module-wide GIT pointer
    static void Term(void) {
        if (g_pGIT != 0)
            g_pGIT->Release();
    }

// autoinit module-wide GIT pointer
    GIT(void)  {
        HRESULT hr = Init();
        assert(SUCCEEDED(hr) && "Couldn't initialize GlobalInterfaceTable");
    }

// autoterm module-wide GIT pointer
    ~GIT(void) { Term(); }
};

// wrapper around a GIT cookie
template <class Itf, const IID* piid>
class GlobalInterfacePointer
{
// prevent missuse
    GlobalInterfacePointer(const GlobalInterfacePointer&);
    void operator =(const GlobalInterfacePointer&);

    DWORD m_dwCookie; // the GIT cookie
public:
// start as invalid cookie
    GlobalInterfacePointer(void) : m_dwCookie(0) { }
// auto-globalize local pointer
    GlobalInterfacePointer(Itf *pItf, HRESULT& hr) 
        : m_dwCookie(0) { 
        hr = Globalize(pItf); 
    }
// auto-unglobalize
    ~GlobalInterfacePointer(void) {
        if (m_dwCookie)
            Unglobalize();
    }
// register an interface pointer in GIT
    HRESULT Globalize(Itf *pItf) {
        assert(g_pGIT != 0 && "GIT::Init not called");
        assert(m_dwCookie == 0 && "Attempt to Globalize invalidCookie");
        return g_pGIT->RegisterInterfaceInGlobal(pItf, *piid, &m_dwCookie);
    }
// revoke an interface pointer in GIT
    HRESULT Unglobalize(void) {
        assert(g_pGIT != 0 && "GIT::Init not called");
        assert(m_dwCookie != 0 && "Attempt to Unglobalize invalid cookie");
        HRESULT hr = g_pGIT->RevokeInterfaceFromGlobal(m_dwCookie);
        m_dwCookie = 0;
        return hr;
    }
// get a local interface pointer from GIT
    HRESULT Localize(Itf **ppItf) const {
        assert(g_pGIT != 0 && "GIT::Init not called");
        assert(m_dwCookie != 0 && "Attempt to Localize invalid cookie");
        return g_pGIT->GetInterfaceFromGlobal(m_dwCookie, *piid,(void**)ppItf);
    }
// convenience methods
    bool IsOK(void) const {
        return m_dwCookie != 0;
    }
    DWORD GetCookie(void) const {
        return m_dwCookie;
    }

};

// convenience macro
#define GIP(Itf) GlobalInterfacePointer<Itf, &IID_##Itf>

// wrapper around locally imported pointer
template <class Itf, const IID* piid>
class LocalInterfacePointer
{
// prevent missuse
    LocalInterfacePointer(const LocalInterfacePointer&);
	LocalInterfacePointer& operator = (const LocalInterfacePointer&);

// temp imported pointer
    Itf *m_pItf;
public:
// import from GIP
    LocalInterfacePointer(const GlobalInterfacePointer<Itf, piid>& rhs, 
                          HRESULT& hr) {
        hr = rhs.Localize(&m_pItf);
    }
// import from raw cookie
    LocalInterfacePointer(DWORD dwCookie, HRESULT& hr)
    {
        assert(g_pGIT != 0 && "GIT::Init not called");
        hr = g_pGIT->GetInterfaceFromGlobal(dwCookie, *piid, (void**)&m_pItf);
    }
// release temp local pointer
    ~LocalInterfacePointer(void)
    {
        if (m_pItf)
            m_pItf->Release();
    }
// declare new Itf class with private AddRef/Release 
    class SafeItf : public Itf {
        STDMETHOD_(ULONG, AddRef)(void) = 0;
        STDMETHOD_(ULONG, Release)(void) = 0;
    };
// provide an arrow operator
    SafeItf *operator ->(void) const {
        assert(m_pItf && "Null LocalInterfacePointer Used");
        return GetInterface();
    }
// provide use of temp pointer
    SafeItf *GetInterface(void) const {
        return (SafeItf*)m_pItf;
    }
};

// convenience macro
#define LIP(Itf) LocalInterfacePointer<Itf,&IID_##Itf>

#endif

