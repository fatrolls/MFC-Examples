//
// Cmpnt.cpp - Component
//
#include <objbase.h>

#include "Iface.h"

#include "Util.h"
#include "CUnknown.h" // Base class for IUnknown
#include "Cmpnt.h"
#include "Lock.h"

static inline void trace(char* msg)
	{ Util::Trace("Component", msg, S_OK) ;} 
static inline void trace(char* msg, HRESULT hr)
	{ Util::Trace("Component", msg, hr) ;}


///////////////////////////////////////////////////////////
//
// Interface IX - Implementation
//
HRESULT __stdcall CA::Tick(int delta) 
{ 
	CSimpleLock Lock(m_hCountMutex) ;

	m_count += delta  ;
	return S_OK ;
}

HRESULT __stdcall CA::SetStartCount(long NewCount) 
{ 
	CSimpleLock Lock(m_hCountMutex) ;

	m_count = NewCount ;
	return S_OK ;
}

HRESULT __stdcall CA::GetCurrentCount(long* pCurrentCount) 
{ 	
	*pCurrentCount = m_count ;
	return S_OK ;
}

HRESULT __stdcall CA::Left()
{
	CSimpleLock Lock(m_hHandMutex) ;

	m_bRightHand = FALSE ;
	return S_OK ;
}

HRESULT __stdcall CA::Right()
{
	CSimpleLock Lock(m_hHandMutex) ;

	m_bRightHand = TRUE ;
	return S_OK ;
}

HRESULT __stdcall CA::InRightHand(BOOL* pbool)
{
	*pbool = m_bRightHand ;
	return S_OK ;
}


//
// Constructor
//
CA::CA(IUnknown* pUnknownOuter)
: CUnknown(pUnknownOuter)
{
	m_count = 0 ;
	m_bRightHand = TRUE ;
	m_hCountMutex = NULL ;
	m_hHandMutex = NULL ;
	m_pIUnknownFreeThreadedMarshaler = NULL ;
}

//
// Destructor
//
CA::~CA()
{
	trace("Destroy self.") ;
}

//
// NondelegatingQueryInterface Implementation
//
HRESULT __stdcall CA::NondelegatingQueryInterface(const IID& iid,
                                                  void** ppv)
{ 	
	if (iid == IID_IX)
	{
		return FinishQI(static_cast<IX*>(this), ppv) ;
	}
	else if (iid == IID_IMarshal)
	{
		return m_pIUnknownFreeThreadedMarshaler->QueryInterface(iid,
		                                                        ppv) ;
	}
	else
	{
		return CUnknown::NondelegatingQueryInterface(iid, ppv) ;
	}
}

///////////////////////////////////////////////////////////
//
// Creation function used by CFactory
//
HRESULT CA::CreateInstance(IUnknown* pUnknownOuter,
                           CUnknown** ppNewComponent ) 
{
   if (pUnknownOuter != NULL)
   {
      // Don't allow aggregation (just for the heck of it).
      return CLASS_E_NOAGGREGATION ;
   }
	
   *ppNewComponent = new CA(pUnknownOuter) ;
   return S_OK ;
}


///////////////////////////////////////////////////////////
//
// Initialize the component by creating the contained component
//
HRESULT CA::Init()
{
	HRESULT hr = CUnknown::Init() ;
	if (FAILED(hr))
	{
		return hr ;
	}

	// Create a mutex to protect the count.
	m_hCountMutex = CreateMutex(0, FALSE, 0) ;
	if (m_hCountMutex == NULL)
	{
		return E_FAIL ;
	}

	// Create a mutex to protect the hand.
	m_hHandMutex = CreateMutex(0, FALSE, 0) ;
	if (m_hHandMutex == NULL)
	{
		return E_FAIL ;
	}

	// Aggregate the free-threaded marshaler.
	hr = ::CoCreateFreeThreadedMarshaler(
	        GetOuterUnknown(),
	        &m_pIUnknownFreeThreadedMarshaler) ;
	if (FAILED(hr))
	{
		return E_FAIL ;
	}
	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// Release the aggregated component.
//
void CA::FinalRelease()
{
	// Call base class to incremement m_cRef to prevent recusion.
	CUnknown::FinalRelease() ;

	if (m_pIUnknownFreeThreadedMarshaler != NULL)
	{
		m_pIUnknownFreeThreadedMarshaler->Release() ;
	}
}
