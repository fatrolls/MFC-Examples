#ifndef __CompB_FACTORY__
#define __CompB_FACTORY__

#include "Unknwn.h"

class CBFactory : public IClassFactory
{
   protected:
      ULONG           m_Ref;

   public:
      CBFactory ();
      ~CBFactory ();

      //IUnknown members
      HRESULT __stdcall QueryInterface(const IID& iid, void **ppv);
      ULONG   __stdcall AddRef();
      ULONG   __stdcall Release();

      //IClassFactory members
      HRESULT __stdcall CreateInstance(IUnknown *, const IID& iid, void **ppv);
      HRESULT __stdcall LockServer(BOOL);
};

#endif // __CompB_FACTORY__