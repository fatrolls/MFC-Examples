///////////////////////////////////////////////////////////////////////////////
//
// gencf.h - Copyright 1995-1997, Don Box
//
// This file contains the class definition of GenericClassFactory,
// that implements IClassFactory in terms of a function:
//    
//    HRESULT STDAPICALLTYPE CreateInstance(IUnknown*, REFIID, void**)
//
// There is also a macro that defines a static routine, GetClassObject
// that returns a GenericClassFactory as a singleton:
//
//    IMPLEMENT_GENERIC_CLASS_FACTORY(ClassName)
//
// Usage:
/*
class Hello : public IHello
{
  IMPLEMENT_UNKNOWN(Hello)
  IMPLEMENT_CREATE_INSTANCE(Hello)
  IMPLEMENT_GENERIC_CLASS_FACTORY(Hello)
};
*/

#ifndef _GENCF_H
#define _GENCF_H


typedef HRESULT (STDAPICALLTYPE *CREATE_INSTANCE_PROC)(IUnknown *pUnkOuter, REFIID riid, void **ppv);

class GenericClassFactory : public IClassFactory
{
    CREATE_INSTANCE_PROC    m_pfnCreateInstance;
public:
    GenericClassFactory(CREATE_INSTANCE_PROC pfnCreateInstance);

    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv);
    STDMETHODIMP LockServer(BOOL bLock);
};

inline 
GenericClassFactory::GenericClassFactory(CREATE_INSTANCE_PROC pfnCreateInstance)
    : m_pfnCreateInstance(pfnCreateInstance)
{
}


#define IMPLEMENT_GENERIC_CLASS_FACTORY(ClassName)\
static HRESULT STDAPICALLTYPE \
GetClassObject(REFIID riid, void **ppv)\
{\
    static GenericClassFactory cf(CreateInstance);\
    return cf.QueryInterface(riid, ppv);\
}


#endif

