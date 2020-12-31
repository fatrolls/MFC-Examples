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
	                              CUnknown** ppNewComponent) ;

private:
	// Declare the delegating IUnknown.
	DECLARE_IUNKNOWN

	// Nondelegating IUnknown
	virtual HRESULT __stdcall 
		NondelegatingQueryInterface( const IID& iid, void** ppv) ;
	
	// Interface IX
	virtual HRESULT __stdcall Tick() ;
	virtual HRESULT __stdcall SetStartCount(long NewCount) ;
	virtual HRESULT __stdcall GetCurrentCount(long* pCurrentCount) ;

	// Constructor
	CA(IUnknown* pUnknownOuter) ;

	// Destructor
	~CA() ;

	// Count
	long m_count ;
};
