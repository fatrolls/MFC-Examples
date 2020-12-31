//
// Cmpnt.cpp - Component
//
#include "Iface.h"
#include "CUnknown.h" // Base class for IUnknown

///////////////////////////////////////////////////////////
//
// Component A
//
class CA : public CUnknown,
           public IX
{
public:	
	// Creation
	static HRESULT CreateInstance(IUnknown* pUnknownOuter,
	                              CUnknown** ppNewComponent ) ;

private:
	// Declare the delegating IUnknown.
	DECLARE_IUNKNOWN

	// Nondelegating IUnknown
	virtual HRESULT __stdcall 
		NondelegatingQueryInterface( const IID& iid, void** ppv) ;
	
	// Interface IX
	virtual HRESULT __stdcall Tick(int delta) ;
	virtual HRESULT __stdcall SetStartCount(long NewCount) ;
	virtual HRESULT __stdcall GetCurrentCount(long* pCurrentCount) ;
	virtual HRESULT __stdcall Left() ;
	virtual HRESULT __stdcall Right() ;
	virtual HRESULT __stdcall InRightHand(BOOL* pbool) ;

   // Constructor
   CA(IUnknown* pUnknownOuter) ;

	// Destructor
	~CA() ;

	// Create aggregates.
	virtual HRESULT Init() ;

	// Release aggregates.
	virtual void FinalRelease() ;

	// Count
	long m_count ;

	// Current hand
	BOOL m_bRightHand ;

	// Mutex to protect count
	HANDLE m_hCountMutex ;

	// Mutex to protect hand
	HANDLE m_hHandMutex ;

	// Handle to the free threaded marshaller
	IUnknown* m_pIUnknownFreeThreadedMarshaler ;
} ;
