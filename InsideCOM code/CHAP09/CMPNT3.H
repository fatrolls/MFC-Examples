//
// Cmpnt3.h - Component 3
//
#include "Iface.h"
#include "CUnknown.h" // Base class for IUnknown

///////////////////////////////////////////////////////////
//
// Component C
//
class CC : public CUnknown,
           public IZ
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

	// Interface IZ
	virtual void __stdcall Fz() ;

	// Constructor
	CC(IUnknown* pUnknownOuter) ;

	// Destructor
	~CC() ;
} ;
