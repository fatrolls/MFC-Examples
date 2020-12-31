#include "stdafx.h"
#include "factory.h"
#include "CompA.h"

extern ULONG    g_LockNumber;
extern ULONG    g_CompANumber;

CAFactory::CAFactory()
{
	m_Ref = 0;
}

CAFactory::~CAFactory()
{
}

HRESULT  CAFactory::QueryInterface(const IID& iid, void **ppv)
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

ULONG	  CAFactory::AddRef()
{
	m_Ref ++;
	return  (ULONG) m_Ref;
}

ULONG	  CAFactory::Release()
{
	m_Ref --;
	if (m_Ref == 0 ) {
		delete this;
		return 0;
	}
	return  (ULONG) m_Ref;
}

HRESULT CAFactory::CreateInstance(IUnknown *pUnknownOuter, 
							   const IID& iid, void **ppv)
{
	HRESULT hr;
	//  iid must be IID_IUnknown for aggregating 
	if ( ( pUnknownOuter != NULL ) && ( iid != IID_IUnknown ) )
	{
		return CLASS_E_NOAGGREGATION;
	}

   	*ppv=NULL;
	hr=E_OUTOFMEMORY;

	//Create the object passing function to notify on destruction.
	CA *pObj=new CA (pUnknownOuter);
	if (NULL==pObj)
		return hr;   
   
	//Obtain the first interface pointer (which does an AddRef)
	hr = pObj->NondelegationQueryInterface(iid, ppv);
    if (hr != S_OK) {
 		//Kill the object if initial creation or FInit failed.
		g_CompANumber --; // Reference count g_CompANumber be added in constructor
		delete pObj;
	}
   
	return hr;   
}

HRESULT CAFactory::LockServer(BOOL bLock)
{
   if (bLock)
      g_LockNumber ++;
   else
   {
      g_LockNumber --;
   }

   return NOERROR;
}