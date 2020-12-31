#include "stdafx.h"
#include "factory.h"
#include "dictcomp.h"

extern ULONG    g_LockNumber;
extern ULONG    g_DictionaryNumber;

CDictionaryFactory::CDictionaryFactory()
{
	m_Ref = 0;
}

CDictionaryFactory::~CDictionaryFactory()
{
}

HRESULT  CDictionaryFactory::QueryInterface(const IID& iid, void **ppv)
{
	if ( iid == IID_IUnknown )
	{
		*ppv = (IUnknown *) this ;
				((IUnknown *)(*ppv))->AddRef() ;
	} else if ( iid == IID_IClassFactory) 
	{
		*ppv = (IClassFactory *) this ;
				((IClassFactory *)(*ppv))->AddRef() ;
	} 
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE ;
	}
	return S_OK;
}

ULONG	  CDictionaryFactory::AddRef()
{
	m_Ref ++;
	return  (ULONG) m_Ref;
}

ULONG	  CDictionaryFactory::Release()
{
	m_Ref --;
	if (m_Ref == 0 ) {
		delete this;
		return 0;
	}
	return  (ULONG) m_Ref;
}

HRESULT CDictionaryFactory::CreateInstance(IUnknown *pUnknownOuter, 
										   const IID& iid, void **ppv)
{
   CDictionary * pObj;   
   HRESULT hr;
   
   *ppv=NULL;
   hr=E_OUTOFMEMORY;
   if (NULL != pUnknownOuter)
	   return CLASS_E_NOAGGREGATION;
   
   //Create the object passing function to notify on destruction.
   pObj=new CDictionary();
   if (NULL==pObj)
      return hr;   
   
   //Obtain the first interface pointer (which does an AddRef)
   hr=pObj->QueryInterface(iid, ppv);

   if (hr != S_OK) {
	   //Kill the object if initial creation or FInit failed.
      g_DictionaryNumber --; // Reference count g_cDictionary be added in constructor
	  delete pObj;
   }
   
   return hr;   
}

HRESULT CDictionaryFactory::LockServer(BOOL bLock)
{
   if (bLock)
      g_LockNumber ++;
   else
      g_LockNumber --;

   return NOERROR;
}