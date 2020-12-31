#include "stdafx.h"
#include "factory.h"
#include "dictionary.h"

extern ULONG    g_LockNumber;
extern ULONG    g_DictionaryNumber;
extern DWORD	dwMainThreadID;
extern "C" const GUID CLSID_Dictionary; 

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
	{
		g_LockNumber --;
		if (CanUnloadNow()) {
			::PostThreadMessage(dwMainThreadID, WM_QUIT, 0, 0) ;
		}
	}

	return NOERROR;
}

BOOL CDictionaryFactory::CanUnloadNow()
{
	if (g_LockNumber>0 || g_DictionaryNumber >0)
		return FALSE;
	else 
		return TRUE;
}

CDictionaryFactory *CDictionaryFactory::theFactory = NULL;
DWORD CDictionaryFactory::dwRegister = 0;
//
// Register factory
//
BOOL CDictionaryFactory::RegisterFactory()
{
	// Create the class factory for dictionary component.
	theFactory = new CDictionaryFactory();
	theFactory->AddRef();
	IUnknown *pUnkForFactory = (IUnknown  *)theFactory;

	// Register the class factory.
	HRESULT hr = ::CoRegisterClassObject(
		              CLSID_Dictionary,
		              pUnkForFactory,
		              CLSCTX_LOCAL_SERVER,
		              REGCLS_MULTIPLEUSE,
		              // REGCLS_MULTI_SEPARATE, //@Multi
		              &dwRegister) ;
	if (FAILED(hr))
	{
		theFactory->Release() ;
		return FALSE ;
	}
	return TRUE ;
}

//
// Unregister factories
//
void CDictionaryFactory::UnregisterFactory()
{
	if (dwRegister != 0) 
	{
		::CoRevokeClassObject(dwRegister) ;
	}

	// Release the class factory.
	if (theFactory != NULL)
		theFactory->Release();
}
