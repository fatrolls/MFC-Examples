///////////////////////////////////////////////////////////////////////////////
//
// itftable.cpp - Copyright 1995-1997, Don Box
//
// This file contains a datatype, INTERFACE_ENTRY that can be used to build
// tables that map IIDs onto vptrs. 
//
// This file contains the prototype for a routine that implements
// QueryInterface based on an interface table.
//
//     InterfaceTableQueryInterface - finds and AddRef's vptr on an object
//     

#include <windows.h>
#include "inttable.h"

#ifndef _INLINEISEQUALGUID_DEFINED
#define _INLINEISEQUALGUID_DEFINED
inline BOOL  InlineIsEqualGUID(REFGUID rguid1, REFGUID rguid2)
{
   return (
      ((PLONG) &rguid1)[0] == ((PLONG) &rguid2)[0] &&
      ((PLONG) &rguid1)[1] == ((PLONG) &rguid2)[1] &&
      ((PLONG) &rguid1)[2] == ((PLONG) &rguid2)[2] &&
      ((PLONG) &rguid1)[3] == ((PLONG) &rguid2)[3]);
}
#endif


// the routine that implements QueryInterface basd on the table
EXTERN_C HRESULT STDAPICALLTYPE InterfaceTableQueryInterface(void *pThis, const INTERFACE_ENTRY *pTable, REFIID riid, void **ppv)
{
    if (InlineIsEqualGUID(riid, IID_IUnknown))
    {
        ((IUnknown*)(*ppv = (char*)pThis + pTable->dwData))->AddRef();
        return S_OK;
    }
    else
    {
        HRESULT hr = E_NOINTERFACE;
        while (pTable->pfnFinder)
        {
            if (!pTable->pIID || InlineIsEqualGUID(riid, *pTable->pIID))
            {
                if (pTable->pfnFinder == ENTRY_IS_OFFSET)
                {
                    ((IUnknown*)(*ppv = (char*)pThis + pTable->dwData))->AddRef();
                    hr = S_OK;
                    break;
                }
                else
                {
                    hr = pTable->pfnFinder(pThis, pTable->dwData, riid, ppv);
                    if (hr == S_OK)
                        break;
                }
            }
            pTable++;
        }
        if (hr != S_OK)
            *ppv = 0;
        return hr;
    }
}
