#ifndef __DICTIONARY_FACTORY__
#define __DICTIONARY_FACTORY__

#include "Unknwn.h"

class CDictionaryFactory : public IClassFactory
{
   protected:
      ULONG           m_Ref;

   public:
      CDictionaryFactory ();
      ~CDictionaryFactory ();

      //IUnknown members
      HRESULT __stdcall QueryInterface(const IID& iid, void **ppv);
      ULONG __stdcall AddRef();
      ULONG __stdcall Release();

      //IClassFactory members
      HRESULT __stdcall CreateInstance(IUnknown *, const IID& iid, void **ppv);
      HRESULT __stdcall LockServer(BOOL);
};

#endif // __DICTIONARY_FACTORY__