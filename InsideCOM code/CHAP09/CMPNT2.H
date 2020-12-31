//
// Cmpnt2.h - Component 2
//
#include "Iface.h"
#include "CUnknown.h" // Base class for IUnknown

///////////////////////////////////////////////////////////
//
// Component B
//
class CB : public CUnknown,
           public IY
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
		NondelegatingQueryInterface(const IID& iid, void** ppv) ;

	// Interface IY
	virtual void __stdcall Fy() ;

	// Initialization
	virtual HRESULT Init() ;

	// Cleanup
	virtual void FinalRelease() ;

	// Constructor
	CB(IUnknown* pUnknownOuter) ;

	// Destructor
	~CB() ;

	// Pointer to inner object being aggregated
	IUnknown* m_pUnknownInner ;

	// Pointer to IZ interface supported by inner component
	IZ* m_pIZ ;
} ;
