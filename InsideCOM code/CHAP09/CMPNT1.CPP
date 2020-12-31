//
// Cmpnt1.cpp - Component 1
//
#include <objbase.h>

#include "Iface.h"
#include "Util.h"
#include "CUnknown.h" // Base class for IUnknown
#include "Cmpnt1.h"

static inline void trace(char* msg)
	{Util::Trace("Component 1", msg, S_OK) ;} 
static inline void trace(char* msg, HRESULT hr)
	{Util::Trace("Component 1", msg, hr) ;}

///////////////////////////////////////////////////////////
//
// Interface IX implementation
//
void __stdcall CA::Fx()
{ 
	trace("Fx") ;
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
HRESULT __stdcall 
	CA::NondelegatingQueryInterface(const IID& iid, void** ppv)
{ 	
	if (iid == IID_IX)
	{
		return FinishQI(static_cast<IX*>(this), ppv) ;
	}
	else if (iid == IID_IY) 
	{
		trace("Return IY interface of aggregated component.") ;
		return m_pUnknownInner->QueryInterface(iid, ppv) ;
	}
	else if (iid == IID_IZ)
	{
		trace("Return IZ interface of aggregated component.") ;
		return FinishQI(m_pIZ, ppv) ;
	}
	else
	{
		return CUnknown::NondelegatingQueryInterface(iid, ppv) ;
	}
}

//
// Initialize the component and create the contained component.
//
HRESULT CA::Init()
{
	trace("Create Component 2, which is aggregated.") ;
	HRESULT hr =
		CoCreateInstance(CLSID_Component2, 
		                 GetOuterUnknown(),
		                 CLSCTX_INPROC_SERVER,
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
// FinalRelease - Called by Release before it deletes the component
//
void CA::FinalRelease()
{
	// Call base class to incremement m_cRef and prevent recursion.
	CUnknown::FinalRelease() ;

	// Counter the GetOuterUnknown()->Release in the Init method.
	GetOuterUnknown()->AddRef() ;

	// Properly release the pointer, as there might be
	// per-interface reference counts.
	m_pIZ->Release() ;	

	// Release the contained component.
	// (We can do this now since we've released the interfaces.)
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
		// Don't allow aggregation (just for the heck of it).
		return CLASS_E_NOAGGREGATION ;
	}
	
	*ppNewComponent = new CA(pUnknownOuter) ;
	return S_OK ;
}
