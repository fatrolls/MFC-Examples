//
// Cmpnt2.cpp - Component 2
//   Note the changes in the class factory marked with @N.
//
#include <iostream.h>
#include <objbase.h>

#include "Iface.h"
#include "Registry.h"

void trace(const char* msg) { cout << "Component 2:\t" << msg << endl ;}

///////////////////////////////////////////////////////////
//
// Global variables
//

// Static variables
static HMODULE g_hModule = NULL ;   // DLL module handle
static long g_cComponents = 0 ;     // Count of active components
static long g_cServerLocks = 0 ;    // Count of locks

// Friendly name of component
const char g_szFriendlyName[]
	= "Inside COM, Chapter 8 Example 2, Component 2" ;

// Version-independent ProgID
const char g_szVerIndProgID[] = "InsideCOM.Chap08.Ex2.Cmpnt2" ;

// ProgID
const char g_szProgID[] = "InsideCOM.Chap08.Ex2.Cmpnt2.1" ;

///////////////////////////////////////////////////////////
//
// Nondelegating IUnknown interface  @N
//
struct INondelegatingUnknown
{
	virtual HRESULT __stdcall
		NondelegatingQueryInterface(const IID&, void**) = 0 ;
	virtual ULONG __stdcall NondelegatingAddRef() = 0 ;
	virtual ULONG __stdcall NondelegatingRelease() = 0 ;
} ;

///////////////////////////////////////////////////////////
//
// Component 
//
class CB : public IY,
           public INondelegatingUnknown
{
public:
	// Delegating IUnknown
	virtual HRESULT __stdcall
		QueryInterface(const IID& iid, void** ppv)
	{
		trace("Delegate QueryInterface.") ;
		return m_pUnknownOuter->QueryInterface(iid, ppv) ; 
	}

	virtual ULONG __stdcall AddRef() 
	{
		trace("Delegate AddRef.") ;
		return m_pUnknownOuter->AddRef() ; 
	}

	virtual ULONG __stdcall Release() 
	{
		trace("Delegate Release.") ;
		return m_pUnknownOuter->Release() ; 
	}

	// Nondelegating IUnknown
	virtual HRESULT __stdcall
		NondelegatingQueryInterface(const IID& iid, void** ppv) ;
	virtual ULONG   __stdcall NondelegatingAddRef() ;
	virtual ULONG   __stdcall NondelegatingRelease() ;

	// Interface IY
	virtual void __stdcall Fy() { cout << "Fy" << endl ;}

	// Constructor
	CB(IUnknown* m_pUnknownOuter) ;

	// Destructor
	~CB() ;

private:
	long m_cRef ;
	
	IUnknown* m_pUnknownOuter ;
} ;

//
// IUnknown implementation
//
HRESULT __stdcall CB::NondelegatingQueryInterface(const IID& iid,
                                                  void** ppv)
{ 	
	if (iid == IID_IUnknown)
	{
		// !!! CAST IS VERY IMPORTANT !!!
		*ppv = static_cast<INondelegatingUnknown*>(this) ;  // @N
	}
	else if (iid == IID_IY)
	{
		*ppv = static_cast<IY*>(this) ;
	}
	else
	{
		*ppv = NULL ;
		return E_NOINTERFACE ;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef() ;
	return S_OK ;
}

ULONG __stdcall CB::NondelegatingAddRef()
{
	return ::InterlockedIncrement(&m_cRef) ;
}

ULONG __stdcall CB::NondelegatingRelease() 
{
	if (::InterlockedDecrement(&m_cRef) == 0)
	{
		delete this ;
		return 0 ;
	}
	return m_cRef ;
}

//
// Constructor
//
CB::CB(IUnknown* pUnknownOuter) 
: m_cRef(1)
{ 
	::InterlockedIncrement(&g_cComponents) ; 

	if (pUnknownOuter == NULL)
	{
		trace("Not aggregating; delegate to nondelegating IUnknown.") ;
		m_pUnknownOuter = reinterpret_cast<IUnknown*>
		                  (static_cast<INondelegatingUnknown*>
		                  (this)) ;
	}
	else
	{
		trace("Aggregating; delegate to outer IUnknown.") ;
		m_pUnknownOuter = pUnknownOuter ;
	}
}

//
// Destructor
//
CB::~CB() 
{ 
	::InterlockedDecrement(&g_cComponents) ; 
	trace("Destroy self.") ;
}

///////////////////////////////////////////////////////////
//
// Class factory
//
class CFactory : public IClassFactory
{
public:
	// IUnknown
	virtual HRESULT __stdcall QueryInterface(const IID& iid, void** ppv) ;
	virtual ULONG   __stdcall AddRef() ;
	virtual ULONG   __stdcall Release() ;

	// Interface IClassFactory
	virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter,
	                                         const IID& iid,
	                                         void** ppv) ;
	virtual HRESULT __stdcall LockServer(BOOL bLock) ; 

	// Constructor
	CFactory() : m_cRef(1) {}

	// Destructor
	~CFactory() {}
	
private:
	long m_cRef ;
} ;

//
// Class factory IUnknown implementation
//
HRESULT __stdcall CFactory::QueryInterface(const IID& iid, void** ppv)
{ 	
	if ((iid == IID_IUnknown) || (iid == IID_IClassFactory))
	{
		*ppv = static_cast<IClassFactory*>(this) ; 
	}
	else
	{
		*ppv = NULL ;
		return E_NOINTERFACE ;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef() ;
	return S_OK ;
}

ULONG __stdcall CFactory::AddRef()
{
	return ::InterlockedIncrement(&m_cRef) ;
}

ULONG __stdcall CFactory::Release() 
{
	if (::InterlockedDecrement(&m_cRef) == 0)
	{
		delete this ;
		return 0 ;
	}
	return m_cRef ;
}

//
// IClassFactory implementation
//
HRESULT __stdcall CFactory::CreateInstance(IUnknown* pUnknownOuter,
	                                   const IID& iid,
	                                   void** ppv)
{
	// Aggregate only if the requested iid is IID_IUnknown.
	if ((pUnknownOuter != NULL) && (iid != IID_IUnknown)) //@N
	{
		return CLASS_E_NOAGGREGATION ;
	}
	
	// Create component.
	CB* pB = new CB(pUnknownOuter) ; // @N
	if (pB == NULL)
	{
		return E_OUTOFMEMORY ;
	}
	
	// Get the requested interface.
	HRESULT hr = pB->NondelegatingQueryInterface(iid, ppv) ; //@N
	pB->NondelegatingRelease() ; 
	return hr ;   
}

// LockServer
HRESULT __stdcall CFactory::LockServer(BOOL bLock) 
{
	if (bLock) 
	{
		::InterlockedIncrement(&g_cServerLocks) ; 
	}
	else
	{
		::InterlockedDecrement(&g_cServerLocks) ;
	}
	return S_OK ;
}


///////////////////////////////////////////////////////////
//
// Exported functions
//

STDAPI DllCanUnloadNow()
{
	if ((g_cComponents == 0) && (g_cServerLocks == 0))
	{
		return S_OK ;
	}
	else
	{
		return S_FALSE ;
	}
}

//
// Get class factory.
//
STDAPI DllGetClassObject(const CLSID& clsid,
                         const IID& iid,
                         void** ppv) 
{
	// Can we create this component?
	if (clsid != CLSID_Component2)
	{
		return CLASS_E_CLASSNOTAVAILABLE ;
	}

	// Create class factory.
	CFactory* pFactory = new CFactory ; // No Addref in constructor
	if (pFactory == NULL)
	{
		return E_OUTOFMEMORY ;
	}

	// Get requested interface.
	HRESULT hr = pFactory->QueryInterface(iid, ppv) ;
	pFactory->Release() ;

	return hr ;	   
}

//
// Server registration
//
STDAPI DllRegisterServer()
{
	return RegisterServer(g_hModule,
	                      CLSID_Component2, 
	                      g_szFriendlyName,
	                      g_szVerIndProgID,
	                      g_szProgID) ;
}


STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_Component2,
	                        g_szVerIndProgID,
	                        g_szProgID) ;
}

///////////////////////////////////////////////////////////
//
// DLL module information
//
BOOL APIENTRY DllMain(HANDLE hModule,
                      DWORD dwReason,
                      void* lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		g_hModule = hModule ;
	}
	return TRUE ;
}
