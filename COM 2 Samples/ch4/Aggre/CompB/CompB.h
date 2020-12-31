#ifndef __CompB_H__
#define __CompB_H__

#ifndef __ISomeInterface_H__
#include "SomeIFace.h"
#endif

#ifndef __IOtherInterface_H__
#include "OtherIFace.h"
#endif

class CB : public IOtherInterface
{
protected:
     ULONG           m_Ref;

public:
     CB();
     ~CB();

     //IUnknown members
     HRESULT __stdcall  QueryInterface(const IID& iid, void **ppv);
     ULONG	 __stdcall  AddRef();
     ULONG   __stdcall  Release();

	//IOtherInterface members
	HRESULT __stdcall OtherFunction( ) ;

    HRESULT Init();

	private :
		IUnknown  *m_pUnknownInner;  // pointer to A's IUnknown
		ISomeInterface *m_pSomeInterface;

};

#endif // __CompB_H__