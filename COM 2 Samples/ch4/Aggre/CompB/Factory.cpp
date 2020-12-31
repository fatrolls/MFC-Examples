#include "stdafx.h"
#include "factory.h"
#include "CompB.h"

extern ULONG    g_LockNumber;
extern ULONG    g_CompBNumber;

CBFactory::CBFactory()
{
	m_Ref = 0;
}

CBFactory::~CBFactory()
{
}

HRESULT  CBFactory::QueryInterface(const IID& iid, void **ppv)
{
	if ( iid == IID_IUnknown )
	{
		*ppv = (IUnknown *) this ;
		((IUnknown *)(*ppv))->AddRef();
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

ULONG	  CBFactory::AddRef()
{
	m_Ref ++;
	return  (ULONG) m_Ref;
}

ULONG	  CBFactory::Release()
{
	m_Ref --;
	if (m_Ref == 0 ) {
		delete this;
		return 0;
	}
	return  (ULONG) m_Ref;
}

HRESULT CBFactory::CreateInstance(IUnknown *pUnknownOuter, 
							   const IID& iid, void **ppv)
{
	CB  *pObj;   
	HRESULT hr;
   
	*ppv=NULL;
	hr=E_OUTOFMEMORY;

	if (NULL != pUnknownOuter)
	return CLASS_E_NOAGGREGATION;
   
	//Create the object passing function to notify on destruction.
	pObj=new CB ();
	if (NULL==pObj)
		return hr;   
   
	pObj->AddRef();  // The Reference count of pObj is 1
	hr = pObj->Init();
	if (FAILED(hr) ) {
		g_CompBNumber --; // Reference count g_CompBNumber be added in constructor
		delete pObj;
		return E_FAIL;
	}
   
	//Obtain the first interface pointer (which does an AddRef)
	hr=pObj->QueryInterface(iid, ppv);

	pObj->Release();	// The Reference count of pObj is 1
	
	return hr;
}

HRESULT CBFactory::LockServer(BOOL bLock)
{
   if (bLock)
      g_LockNumber ++;
   else
      g_LockNumber --;

   return NOERROR;
}
