#ifndef __CompA_H__
#define __CompA_H__

#ifndef __ISomeInterface_H__
#include "SomeIFace.h"
#endif

class INondelegatingUnknown
{
public:
	virtual HRESULT  __stdcall  NondelegationQueryInterface(const IID& iid, void **ppv) = 0 ;
	virtual ULONG	 __stdcall  NondelegatingAddRef() = 0; 
	virtual ULONG	 __stdcall  NondelegationRelease() = 0;
};

class CA : public ISomeInterface, public INondelegatingUnknown
{
protected:
     ULONG           m_Ref;

public:
     CA(IUnknown *pUnknownOuter);
     ~CA();

public :
	// Delegating IUnknown
	virtual HRESULT	  __stdcall  QueryInterface(const IID& iid, void **ppv) ;
	virtual ULONG	  __stdcall  AddRef() ; 
	virtual ULONG	  __stdcall  Release() ;

	// Nondelegating IUnknown
	virtual HRESULT   __stdcall  NondelegationQueryInterface(const IID& iid, void **ppv);
	virtual ULONG	  __stdcall  NondelegatingAddRef();
	virtual ULONG	  __stdcall  NondelegationRelease();

	virtual HRESULT __stdcall SomeFunction( ) ;

	private :
		IUnknown  *m_pUnknownOuter;  // pointer to outer IUnknown
};

#endif __CompA_H__