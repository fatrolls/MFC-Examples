//
// Cmpnt3.cpp - Component 3
//
#include <objbase.h>

#include "Iface.h"
#include "Util.h"
#include "CUnknown.h"
#include "Cmpnt3.h"

static inline void trace(char* msg)
	{ Util::Trace("Component 3", msg, S_OK) ;}
static inline void trace(char* msg, HRESULT hr)
	{ Util::Trace("Component 3", msg, hr) ;}

///////////////////////////////////////////////////////////
//
// Interface IZ
//
HRESULT __stdcall CC::FzStructIn(Point3d pt)
{ 
	strstream sout ;
	sout << "FzStructIn received ("
	     << pt.x << ", "
	     << pt.y << ", "
	     << pt.z << ")."
	     << ends ;
	trace(sout.str()) ;

	m_pt = pt ;
	return S_OK ;
}

HRESULT __stdcall CC::FzStructOut(Point3d* pt)
{ 
	*pt = m_pt ;
	return S_OK ;
}

//
// Constructor
//
CC::CC(IUnknown* pUnknownOuter)
: CUnknown(pUnknownOuter)
{
	m_pt.x = -1.0 ;
	m_pt.y = -1.0 ;
	m_pt.z = -1.0 ;
}

CC::~CC() 
{
	trace("Destroy self.") ;
}

//
// NondelegatingQueryInterface implementation
//
HRESULT __stdcall CC::NondelegatingQueryInterface(const IID& iid,
                                                  void** ppv)
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
