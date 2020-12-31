///////////////////////////////////////////////////////////
//
// EventSink.cpp - Implementation for CCTangramModelEventSink 
// 
// Defines the connection point object used by CTangramModel.
//
//
#include "Windows.h"
#include "EventSink.h"
#include "Assert.h"

///////////////////////////////////////////////////////////
//
// Constructor
//
CTangramModelEventSink::CTangramModelEventSink(ITangramModelEvent* pParentToNotify)
: m_cRef(1) 
{
	assert(pParentToNotify != NULL) ;

	// We are controlled by the ConnectionPoint, so leave the parent alone.
	m_pParentToNotify = pParentToNotify ;
}

///////////////////////////////////////////////////////////
//
// Destructor
CTangramModelEventSink::~CTangramModelEventSink()
{
}

///////////////////////////////////////////////////////////
//
//					ITangramModelEvent
//
///////////////////////////////////////////////////////////
//
// OnModelChange
//
HRESULT __stdcall CTangramModelEventSink::OnModelChange()
{
	assert(m_pParentToNotify != NULL) ;

	// Call the ITangramModelEvent interface in the parent object.
	return m_pParentToNotify->OnModelChange() ;
}

///////////////////////////////////////////////////////////
//
//			Interface IUnknown Methods
//
///////////////////////////////////////////////////////////
//
// QueryInterface
//
HRESULT __stdcall 
CTangramModelEventSink::QueryInterface(const IID& iid, void** ppv)
{
	if ((iid == IID_IUnknown) ||(iid == IID_ITangramModelEvent))
	{
		*ppv = static_cast<ITangramModelEvent*>(this) ; 
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	(reinterpret_cast<IUnknown*>(*ppv))->AddRef() ;
	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// AddRef
//
ULONG __stdcall 
CTangramModelEventSink::AddRef() 
{
	return InterlockedIncrement(&m_cRef) ;
}

///////////////////////////////////////////////////////////
//
// Release
//
ULONG __stdcall 
CTangramModelEventSink::Release() 
{
   if (InterlockedDecrement(&m_cRef) == 0)
	{
		delete this ;
      return 0 ;
	}
	return m_cRef;
}
