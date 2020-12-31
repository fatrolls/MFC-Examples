//
// Cmpnt.cpp - Component
//
#include <objbase.h>

#include "Iface.h"

#include "Util.h"
#include "CUnknown.h" // Base class for IUnknown
#include "Cmpnt.h"


static inline void trace(char* msg)
	{ Util::Trace("Component", msg, S_OK) ;} 
static inline void trace(char* msg, HRESULT hr)
	{ Util::Trace("Component", msg, hr) ;}


///////////////////////////////////////////////////////////
//
// Interface IX - Implementation
//
HRESULT __stdcall CA::Tick() 
{ 
	m_count++ ;
	return S_OK ;
}

HRESULT __stdcall CA::SetStartCount(long NewCount) 
{ 
	m_count = NewCount ;
	return S_OK ;
}

HRESULT __stdcall CA::GetCurrentCount(long* pCurrentCount) 
{ 	
	*pCurrentCount = m_count ;
	return S_OK ;
}

//
// Constructor
//
CA::CA(IUnknown* pUnknownOuter)
: CUnknown(pUnknownOuter)
{
	m_count = 0 ;
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
		return FinishQI(static_cast<IX*>(this), ppv) ;
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
