///////////////////////////////////////////////////////
//
// impunk.h - Copyright 1997, Don Box
//
// This file contains several macros for implementing 
// QueryInterface, AddRef and Release:
//
//     IMPLEMENT_UNKNOWN(ClassName) - heap-based, non-aggregatable
//     IMPLEMENT_UNKNOWN_NO_DELETE(ClassName) - non-heap-based, non-aggregatable
//     IMPLEMENT_AGGREGATABLE_UNKNOWN(ClassName) - heap-based, aggregatable
//     
//     IMPLEMENT_COMPOSITE_UNKNOWN(OuterClassName, InnerClassName, DataMember) - MFC-style composition
// 
// The first three of these macros above expect two global functions to be defined
// somewhere in the project that [un]lock the current server:
//
//    extern void STDMETHODCALLTYPE ModuleAddRef();
//    extern void STDMETHODCALLTYPE ModuleRelease();
//
// if you do not want references to your object to keep the server alive,
// simply add the following macro before the IMPLEMENT_UNKNOWN_XXX macro:
// 
//     NO_MODULE_LOCK(ClassName)
//
// Also present in this file are macros that define a static method
// CreateInstance that is suitable for use in generic class factories:
//
//     IMPLEMENT_CREATE_INSTANCE(ClassName)
//     IMPLEMENT_CREATE_AGGREGATABLE_INSTANCE(ClassName)
//

#ifndef _IMPUNK_H
#define _IMPUNK_H

#include <assert.h>

// AUTO_LONG is just a long that constructs to zero
struct AUTO_LONG {
    LONG value;
    AUTO_LONG(void) : value(0) {}
    inline LONG *operator & (void) { return &value; }
    inline LONG operator ++(void) { return ++value; }
    inline LONG operator --(void) { return --value; }
    inline operator LONG (void) { return value; }
};

// the AddRef/Release methods defined in this file
// all call functions called ModuleAddRef and ModuleRelease
// unconditionally. If you do not want the object's 
// outstanding references to hold the object running, 
// then add the following macro to your class definition

#define NO_MODULE_LOCK(ClassName)\
inline static void STDMETHODCALLTYPE ModuleAddRef() {}\
inline static void STDMETHODCALLTYPE ModuleRelease() {}


#define IMPLEMENT_UNKNOWN(ClassName) \
AUTO_LONG m_cRef;\
STDMETHODIMP QueryInterface(REFIID riid, void **ppv) \
{\
    return InterfaceTableQueryInterface(this, GetInterfaceTable(), riid, ppv);\
}\
STDMETHODIMP_(ULONG) AddRef(void) \
{ \
    extern void STDAPICALLTYPE ModuleAddRef(void);\
    if (m_cRef == 0)\
        ModuleAddRef();\
    return InterlockedIncrement(&m_cRef); \
}\
STDMETHODIMP_(ULONG) Release(void) \
{\
    extern void STDAPICALLTYPE ModuleRelease(void);\
    ULONG res = InterlockedDecrement(&m_cRef); \
    if (res == 0) {\
        delete this;\
        ModuleRelease();\
    }\
    return res;\
}\

#define IMPLEMENT_CREATE_INSTANCE(ClassName)\
static HRESULT STDAPICALLTYPE \
CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)\
{\
    *ppv = 0;\
    if (pUnkOuter)\
        return CLASS_E_NOAGGREGATION;\
    ClassName *p = new ClassName;\
    if (!p)\
        return E_OUTOFMEMORY;\
    p->AddRef();\
    HRESULT hr = p->QueryInterface(riid, ppv);\
    p->Release();\
    return hr;\
}



#define IMPLEMENT_UNKNOWN_NODELETE(ClassName) \
STDMETHODIMP QueryInterface(REFIID riid, void **ppv) \
{\
    return InterfaceTableQueryInterface(this, GetInterfaceTable(), riid, ppv);\
}\
STDMETHODIMP_(ULONG) AddRef(void) \
{ \
    extern void STDAPICALLTYPE ModuleAddRef(void);\
    ModuleAddRef();\
    return 2; \
}\
STDMETHODIMP_(ULONG) Release(void) \
{\
    extern void STDAPICALLTYPE ModuleRelease(void);\
    ModuleRelease();\
    return 1;\
}\

inline HRESULT CreateAggregates(void) { return S_OK; };

#define IMPLEMENT_AGGREGATABLE_UNKNOWN(ClassName) \
public:\
    AUTO_LONG       m_cRef;\
    struct NonDelegatingUnknown : public IUnknown {\
        ClassName *This() { return (ClassName*)((BYTE*)this - offsetof(ClassName, m_innerUnknown)); }\
        STDMETHODIMP QueryInterface(REFIID riid, void **ppv) \
        { return This()->InternalQueryInterface(riid, ppv); }\
        STDMETHODIMP_(ULONG) AddRef(void) \
        {  return This()->InternalAddRef(); }\
        STDMETHODIMP_(ULONG) Release(void) \
        { return This()->InternalRelease(); }\
        NonDelegatingUnknown(void)\
        { This()->m_pUnkOuter = this; }\
    };\
    NonDelegatingUnknown m_innerUnknown;\
    IUnknown       *m_pUnkOuter;\
    STDMETHODIMP InternalQueryInterface(REFIID riid, void **ppv) \
    {\
        if (riid == IID_IUnknown)\
            return ((IUnknown*)(*ppv = static_cast<IUnknown*>(&m_innerUnknown)))->AddRef(), S_OK;\
        return InterfaceTableQueryInterface(this, GetInterfaceTable(), riid, ppv);\
    }\
    STDMETHODIMP_(ULONG) InternalAddRef(void) \
    { \
        extern void STDAPICALLTYPE ModuleAddRef(void);\
        if (m_cRef == 0)\
            ModuleAddRef();\
        return InterlockedIncrement(&m_cRef); \
    }\
    STDMETHODIMP_(ULONG) InternalRelease(void) \
    {\
        extern void STDAPICALLTYPE ModuleRelease(void);\
        ULONG res = InterlockedDecrement(&m_cRef); \
        if (res == 0) {\
            delete this;\
            ModuleRelease();\
        }\
        return res;\
    }\
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv) \
    { return m_pUnkOuter->QueryInterface(riid, ppv); }\
    STDMETHODIMP_(ULONG) AddRef(void) \
    {  return m_pUnkOuter->AddRef(); }\
    STDMETHODIMP_(ULONG) Release(void) \
    { return m_pUnkOuter->Release(); }\
    STDMETHODIMP ExternalQueryInterface(REFIID riid, void **ppv) \
    { return m_pUnkOuter->QueryInterface(riid, ppv); }\
    STDMETHODIMP_(ULONG) ExternalAddRef(void) \
    { return m_pUnkOuter->AddRef(); }\
    STDMETHODIMP_(ULONG) ExternalRelease(void) \
    { return m_pUnkOuter->Release(); }\
    IUnknown *GetControllingUnknown() { return m_pUnkOuter; }\
    IUnknown *GetNonDelegatingUnknown() { return &m_innerUnknown; }\
    HRESULT SetControllingUnknown(IUnknown * pUnkOuter) { \
        m_pUnkOuter = pUnkOuter ? pUnkOuter : &m_innerUnknown; \
        ++m_cRef;\
        HRESULT hr = CreateAggregates();\
        --m_cRef;\
        return hr;\
    }

#define IMPLEMENT_CREATE_AGGREGATABLE_INSTANCE(ClassName)\
static HRESULT STDAPICALLTYPE \
CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)\
{\
    *ppv = 0;\
    if (pUnkOuter && riid != IID_IUnknown)\
        return E_INVALIDARG;\
    ClassName *p = new ClassName;\
    if (!p)\
        return E_OUTOFMEMORY;\
    p->InternalAddRef();\
    HRESULT hr = p->SetControllingUnknown(pUnkOuter)\
    if (SUCCEEDED(hr))\
      hr = p->InternalQueryInterface(riid, ppv);\
    p->InternalRelease();\
    return hr;\
}



#define DECLARE_INTERNAL_EXTERNAL_NAMES(ClassName) \
public:\
    inline STDMETHODIMP InternalQueryInterface(REFIID riid, void **ppv) \
    {\
        return QueryInterface(riid, ppv); \
    }\
    inline STDMETHODIMP_(ULONG) InternalAddRef(void) \
    { \
        return AddRef(); \
    }\
    inline STDMETHODIMP_(ULONG) InternalRelease(void) \
    {\
        return Release();\
    }\
    inline STDMETHODIMP ExternalQueryInterface(REFIID riid, void **ppv) \
    { return QueryInterface(riid, ppv); }\
    inline STDMETHODIMP_(ULONG) ExternalAddRef(void) \
    { return AddRef(); }\
    inline STDMETHODIMP_(ULONG) ExternalRelease(void) \
    { return Release(); }\
    inline IUnknown *GetControllingUnknown() { return (IUnknown*)((char*)this + GetInterfaceTable()->dwData); }\
    inline IUnknown *GetNonDelegatingUnknown() { return GetControllingUnknown(); }\

#define IMPLEMENT_COMPOSITE_UNKNOWN(OuterClassName, InnerClassName, DataMemberName) \
OuterClassName *This() { return (OuterClassName*)((char*)this - offsetof(OuterClassName, DataMemberName)); }\
STDMETHODIMP QueryInterface(REFIID riid, void **ppv) \
{\
    return This()->QueryInterface(riid, ppv);\
}\
STDMETHODIMP_(ULONG) AddRef(void) \
{ \
    return This()->AddRef(); \
}\
STDMETHODIMP_(ULONG) Release(void) \
{\
    return This()->Release();\
}\

#define IMPLEMENT_TEAROFF_UNKNOWN(OuterClassName, InnerClassName) \
OuterClassName *m_pThis;\
AUTO_LONG m_cRef;\
OuterClassName *This() { return m_pThis; }\
STDMETHODIMP QueryInterface(REFIID riid, void **ppv) \
{\
    return This()->QueryInterface(riid, ppv);\
}\
STDMETHODIMP_(ULONG) AddRef(void) \
{ \
    return InterlockedIncrement(&m_cRef); \
}\
STDMETHODIMP_(ULONG) Release(void) \
{\
    ULONG res = InterlockedDecrement(&m_cRef); \
    if (res == 0) \
        delete this;\
    return res;\
}\
static HRESULT STDAPICALLTYPE Tearoff(void *pThis, DWORD dwData, REFIID riid, void **ppv)\
{\
    InnerClassName *p = new InnerClassName((OuterClassName*)pThis);\
    p->AddRef();\
    HRESULT hr = InterfaceTableQueryInterface(p, GetInterfaceTable(), riid, ppv);\
    p->Release();\
    return hr;\
}

#endif
