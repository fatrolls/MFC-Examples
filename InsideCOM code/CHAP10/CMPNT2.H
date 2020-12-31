//
// Cmpnt2.cpp - Component 2
//
#include "iface.h"
#include "CUnknown.h"

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

	// IUnknown
	virtual HRESULT __stdcall 
		NondelegatingQueryInterface( const IID& iid, void** ppv) ;
	
	// Interface IY
	virtual HRESULT __stdcall FyCount(long* sizeArray) ;
	virtual HRESULT __stdcall FyArrayIn(long sizeIn, long arrayIn[]) ;
	virtual HRESULT __stdcall FyArrayOut(long* psizeInOut,
	                                     long arrayOut[]) ;

	// Initialization
 	virtual HRESULT Init() ;

	// Notify derived classes that we are releasing.
	virtual void FinalRelease() ;

	// Constructor
	CB(IUnknown* pUnknownOuter) ;

	// Destructor
	~CB() ;

	 // Pointer to inner object being aggregated
	IUnknown* m_pUnknownInner;

	// Pointer to IZ interface supported by inner component
	IZ* m_pIZ ;

	// Pointer to array
	long* m_array ;

	// Size of array
	long m_sizeArray ;
};
