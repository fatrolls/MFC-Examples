//
// Cmpnt3.cpp - Component 3
//
#include "Iface.h"
#include "CUnknown.h"

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
		NondelegatingQueryInterface(const IID& iid, void** ppv) ;

	// Interface IZ
	virtual HRESULT __stdcall FzStructIn(Point3d pt) ;
	virtual HRESULT __stdcall FzStructOut(Point3d* pt) ;

	// Constructor
	CC(IUnknown* pUnknownOuter) ;

	// Destruction
	~CC() ;

	// Member variables
	Point3d m_pt ;
} ;
