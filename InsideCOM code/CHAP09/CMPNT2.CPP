//
// Cmpnt2.cpp - Component 2
//
#include <objbase.h>

#include "Iface.h"
#include "Util.h"
#include "CUnknown.h" // Base class for IUnknown
#include "Cmpnt2.h"

static inline void trace(char* msg)
	{Util::Trace("Component 2", msg, S_OK) ;} 
static inline void trace(char* msg, HRESULT hr)
	{Util::Trace("Component 2", msg, hr) ;}

///////////////////////////////////////////////////////////
//
// Interface IY implementation
//
void __stdcall CB::Fy()
{ 
	trace("Fy") ;
}

//
// Constructor
//
CB::CB(IUnknown* pUnknownOuter)
: CUnknown(pUnknownOuter),
  m_pUnknownInner(NULL),
  m_pIZ(NULL)
{
	// Empty
}

//
// Destructor
//
CB::~CB()
{
	trace("Destroy self.") ;
}

//
// NondelegatingQueryInterface implementation
//
HRESULT __stdcall 
	CB::NondelegatingQueryInterface(const IID& iid, void** ppv)
{ 	
	if (iid == IID_IY)
	{
		return FinishQI(static_cast<IY*>(this), ppv) ;
	}
	else if (iid == IID_IZ)
	{
		return m_pUnknownInner->QueryInterface(iid, ppv) ;
	}
	else
	{
		return CUnknown::NondelegatingQueryInterface(iid, ppv) ;
	}
}


//
// Initialize the component and create the contained component.
//
HRESULT CB::Init()
{
	trace("Create Component 3, which is aggregated.") ;
	HRESULT hr =
		CoCreateInstance(CLSID_Component3,
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
void CB::FinalRelease()
{
	// Call base class to incremement m_cRef and prevent recursion.
	CUnknown::FinalRelease() ;

	// Counter the GetOuterUnknown()->Release in the Init method.
	GetOuterUnknown()->AddRef() ;

	// Properly release the pointer, as there might be
	// per-interface reference counts.
	m_pIZ->Release();

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
HRESULT CB::CreateInstance(IUnknown* pUnknownOuter,
                           CUnknown** ppNewComponent) 
{
	*ppNewComponent = new CB(pUnknownOuter) ;
	return S_OK ;
}
