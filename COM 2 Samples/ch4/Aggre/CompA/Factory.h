#ifndef __CompA_FACTORY__
#define __CompA_FACTORY__

#include "Unknwn.h"

class CAFactory : public IClassFactory
{
   protected:
      ULONG           m_Ref;

   public:
      CAFactory ();
      ~CAFactory ();

      //IUnknown members
      HRESULT __stdcall QueryInterface(const IID& iid, void **ppv);
      ULONG   __stdcall AddRef();
      ULONG   __stdcall Release();

      //IClassFactory members
      HRESULT __stdcall CreateInstance(IUnknown *, const IID& iid, void **ppv);
      HRESULT __stdcall LockServer(BOOL);
};

#endif // __CompA_FACTORY__