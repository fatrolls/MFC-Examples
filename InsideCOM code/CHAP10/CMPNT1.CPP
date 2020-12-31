//
// Cmpnt1.cpp - Component 1
//
#include <objbase.h>

#include "Iface.h"
#include "Util.h"
#include "CUnknown.h" // Base class for IUnknown
#include "Cmpnt1.h"

static inline void trace(char* msg)
	{ Util::Trace("Component 1", msg, S_OK) ;}
static inline void trace(char* msg, HRESULT hr)
	{ Util::Trace("Component 1", msg, hr) ;}

///////////////////////////////////////////////////////////
//
// Interface IX
//
HRESULT __stdcall CA::FxStringIn(wchar_t* szIn)
{ 
	// Display the incoming string.
	ostrstream sout ;
	sout << "FxStringIn received a string:  "
	     << szIn
	     << ends ;
	trace(sout.str()) ;
	return S_OK ;
}

HRESULT __stdcall CA::FxStringOut(wchar_t** pszOut)
{
	const wchar_t wsz[] = L"[String from FxStringOut]" ;
	const int iLength = (wcslen(wsz)+1)*sizeof(wchar_t) ;

	// Allocate an outgoing string.

	wchar_t* pBuf = static_cast<wchar_t*>(::CoTaskMemAlloc(iLength)) ;
	if (pBuf == NULL)
	{
		return E_OUTOFMEMORY ;
	}
	
	// Copy string to output buffer.
	wcscpy(pBuf, wsz) ;

	*pszOut = pBuf ;
	return S_OK ;
}

//
// Constructor
//
CA::CA(IUnknown* pUnknownOuter)
: CUnknown(pUnknownOuter),
  m_pUnknownInner(NULL),
  m_pIZ(NULL)
{
	// Empty
}

//
// Destructor
//
CA::~CA()
{
	trace("Destroy self.") ;
}

//
// NondelegatingQueryInterface implementation
//
HRESULT __stdcall CA::NondelegatingQueryInterface(const IID& iid,
                                                  void** ppv)
{ 	
	if (iid == IID_IX)
	{
		return FinishQI((IX*)this, ppv) ;
	}
	else if (iid == IID_IY)
	{
		trace("Return IY interface of aggregated component.") ;
		return m_pUnknownInner->QueryInterface(iid, ppv) ;
	}
	else if (iid == IID_IZ)
	{
		("Return IZ interface of aggregated component.") ;
		return FinishQI(m_pIZ, ppv) ;
	}
	else if (iid == IID_IMarshal)
	{
		trace("The COM Library asked for IMarshal.") ;
		// We don't implement IMarshal.
		return CUnknown::NondelegatingQueryInterface(iid, ppv) ;
	}
	else
	{
		return CUnknown::NondelegatingQueryInterface(iid, ppv) ;
	}
}


//
// Initialize the component by creating the contained component.
//
HRESULT CA::Init()
{
	trace("Create Component 2, which is aggregated.") ;
	HRESULT hr = CoCreateInstance(CLSID_Component2, 
	                              GetOuterUnknown(), 
	                              CLSCTX_INPROC_SERVER,
	                              //CLSCTX_ALL, //@Multi
	                              IID_IUnknown,
	                              (void**)&m_pUnknownInner) ;
	if (FAILED(hr))
	{
		trace("Could not create inner component.", hr) ;
		return E_FAIL ;
	}

	trace("Get pointer to interface IZ to cache.") ;
	hr = m_pUnknownInner->QueryInterface(IID_IZ, (void**)&m_pIZ) ;
	if (FAILED(hr))
	{
		trace("Inner component does not support IZ.", hr) ;
		m_pUnknownInner->Release() ;
		m_pUnknownInner = NULL ;
		return E_FAIL ;
	}

	// Decrement the reference count caused by the QI call.
	trace("Got IZ interface pointer. Release reference.") ;
	GetOuterUnknown()->Release() ;
	return S_OK ;
}

//
// FinalRelease - called by Release before it deletes the component
//
void CA::FinalRelease()
{
	// Call base class to incremement m_cRef to prevent recusion.
	CUnknown::FinalRelease() ;

	// Counter the GetOuterUnknown()->Release in the Init method.
	GetOuterUnknown()->AddRef() ;	

	// Properly release the pointer; there may be per-interface
	// reference counts.
	m_pIZ->Release() ;

	// Release the aggregated component.
	if (m_pUnknownInner != NULL)
	{
		m_pUnknownInner->Release() ;
	}
}



///////////////////////////////////////////////////////////
//
// Creation function used by CFactory
//
HRESULT CA::CreateInstance(IUnknown* pUnknownOuter,
                           CUnknown** ppNewComponent)
{
	if (pUnknownOuter != NULL)
	{
		// Don't allow aggregation. Just for the heck of it.
		return CLASS_E_NOAGGREGATION ;
	}
	
	*ppNewComponent = new CA(pUnknownOuter) ;
	return S_OK ;
}
