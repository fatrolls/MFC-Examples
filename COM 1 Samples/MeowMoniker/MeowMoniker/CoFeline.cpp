// CoFeline.cpp : Implementation of CoFeline

#include "stdafx.h"
#include "..\yacl\include\hrx.h"
#include "..\yacl\include\smartif.h"
#include "MeowMoniker.h"
#include "CoFeline.h"

#define BAD_POINTER_RETURN(p) if( !p ) return E_POINTER
#define BAD_POINTER_RETURN_OR_ZERO(p) if( !p ) return E_POINTER; else *p = 0

/////////////////////////////////////////////////////////////////////////////
// CoFeline

STDMETHODIMP CoFeline::GetDisplayName(
    IDispatch*  pdisp,
    BSTR*       pbstrName)
{
    BAD_POINTER_RETURN_OR_ZERO(pbstrName);
    BAD_POINTER_RETURN(pdisp);

    COM_TRY
    {
        HRX hrx;

        SI(IMoniker)    pmk;
        hrx = CreateMeowMoniker(pdisp,
                                IID_IDispatch,
                                MSHCTX_DIFFERENTMACHINE,
                                MSHLFLAGS_NORMAL,
                                pmk.RelItfRef());

        SI(IBindCtx)    pbc;
        hrx = CreateBindCtx(0, pbc.RelItfRef());

        wchar_t*    pwszDisplayName;
        hrx = pmk->GetDisplayName(pbc.Itf(), 0, &pwszDisplayName);

        *pbstrName = SysAllocString(pwszDisplayName);
        CoTaskMemFree(pwszDisplayName);
        if( !pbstrName ) hrx = E_OUTOFMEMORY;
    }
    COM_CATCH
}

STDMETHODIMP CoFeline::ParseDisplayName(
    BSTR        bstrName,
    IDispatch** ppdisp)
{
    BAD_POINTER_RETURN_OR_ZERO(ppdisp);
    BAD_POINTER_RETURN(bstrName);

    COM_TRY
    {
        HRX hrx;

        SI(IBindCtx)    pbc;
        hrx = CreateBindCtx(0, pbc.RelItfRef());

        SI(IMoniker)    pmk;
        ULONG           cchEaten;
        hrx = MkParseDisplayName(pbc.Itf(),
                                 bstrName,
                                 &cchEaten,
                                 pmk.RelItfRef());
        hrx = pmk->BindToObject(pbc.Itf(),
                                0,
                                IID_IDispatch,
                                (void**)ppdisp);
    }
    COM_CATCH
}
