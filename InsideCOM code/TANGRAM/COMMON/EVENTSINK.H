#ifndef __CTangramModelEventSink_h__
#define __CTangramModelEventSink_h__
///////////////////////////////////////////////////////////
//
//
// EventSink.h	-	Header file for CTangramModelEventSink
//
//
//
#include "Event_I.h"

///////////////////////////////////////////////////////////
//
//	CTangramModelEventSink
//
class CTangramModelEventSink	:	public ITangramModelEvent
{
public:
	// IUnknown
	virtual HRESULT __stdcall QueryInterface(const IID& iid, void** ppv) ;			
	virtual ULONG   __stdcall AddRef() ;
	virtual ULONG   __stdcall Release() ;
	
   // ITangramModelEvent
   virtual HRESULT __stdcall OnModelChange() ;

	// Constructor
	CTangramModelEventSink(ITangramModelEvent* pParentToNotify) ; 

	// Destructor
	~CTangramModelEventSink() ;
	
	// Pointer to the component to notify of incomming events.
	ITangramModelEvent* m_pParentToNotify ;

	// Reference Count
	long m_cRef;	   
} ;

#endif //__CTangramModelEventSink_h__