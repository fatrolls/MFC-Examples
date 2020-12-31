//
// Cmpnt1.cpp - Component 1
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

	// IUnknown
	virtual HRESULT __stdcall 
		NondelegatingQueryInterface( const IID& iid, void** ppv) ;			
	
	// Interface IX
	virtual HRESULT __stdcall FxStringIn(wchar_t* szIn) ; 
	virtual HRESULT __stdcall FxStringOut(wchar_t** pszOut) ;

	// Initialization
 	virtual HRESULT Init() ;

	// Notify derived classes that we are releasing.
	virtual void FinalRelease() ;

	// Constructor
	CA(IUnknown* pUnknownOuter) ;

	// Destructor
	~CA() ;

	 // Pointer to inner object being aggregated.
	IUnknown* m_pUnknownInner;

	// Pointer to IZ interface supported by inner component.
	IZ* m_pIZ ;
} ;
