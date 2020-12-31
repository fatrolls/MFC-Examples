//
// Cmpnt3.cpp - Component 3
//
#include <objbase.h>

#include "Iface.h"
#include "Util.h"
#include "CUnknown.h" // Base class for IUnknown
#include "Cmpnt3.h"

static inline void trace(char* msg)
	{Util::Trace("Component 3", msg, S_OK) ;} 
static inline void trace(char* msg, HRESULT hr)
	{Util::Trace("Component 3", msg, hr) ;}

///////////////////////////////////////////////////////////
//
// Interface IZ implementation
//
void __stdcall CC::Fz() 
{ 
	trace("Fz") ;
}

//
// Constructor
//
CC::CC(IUnknown* pUnknownOuter)
: CUnknown(pUnknownOuter)
{
	// Empty
}

//
// Destructor
//
CC::~CC() 
{
	trace("Destroy self.") ;
}

//
// NondelegatingQueryInterface implementation
//
HRESULT __stdcall
	CC::NondelegatingQueryInterface(const IID& iid, void** ppv)
{ 	
	if (iid == IID_IZ)
	{
		return FinishQI(static_cast<IZ*>(this), ppv) ;
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
HRESULT CC::CreateInstance(IUnknown* pUnknownOuter,
                           CUnknown** ppNewComponent)
{
	*ppNewComponent = new CC(pUnknownOuter) ;
	return S_OK ;
}
