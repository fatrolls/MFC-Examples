

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Jun 18 11:21:24 2012
 */
/* Compiler settings for PrimeSvrNoAttr.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __PrimeSvrNoAttr_h__
#define __PrimeSvrNoAttr_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPrimeNumbers_FWD_DEFINED__
#define __IPrimeNumbers_FWD_DEFINED__
typedef interface IPrimeNumbers IPrimeNumbers;
#endif 	/* __IPrimeNumbers_FWD_DEFINED__ */


#ifndef __IEnumPrimes_FWD_DEFINED__
#define __IEnumPrimes_FWD_DEFINED__
typedef interface IEnumPrimes IEnumPrimes;
#endif 	/* __IEnumPrimes_FWD_DEFINED__ */


#ifndef __PrimeNumbers_FWD_DEFINED__
#define __PrimeNumbers_FWD_DEFINED__

#ifdef __cplusplus
typedef class PrimeNumbers PrimeNumbers;
#else
typedef struct PrimeNumbers PrimeNumbers;
#endif /* __cplusplus */

#endif 	/* __PrimeNumbers_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_PrimeSvrNoAttr_0000_0000 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_PrimeSvrNoAttr_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_PrimeSvrNoAttr_0000_0000_v0_0_s_ifspec;

#ifndef __IPrimeNumbers_INTERFACE_DEFINED__
#define __IPrimeNumbers_INTERFACE_DEFINED__

/* interface IPrimeNumbers */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IPrimeNumbers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F9F30604-5F08-4184-BE87-EE5193E707B2")
    IPrimeNumbers : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CalcPrimes( 
            /* [in] */ long min,
            /* [in] */ long max) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pnCount) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long n,
            /* [retval][out] */ long *pnPrime) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Enum( 
            /* [retval][out] */ IEnumPrimes **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPrimeNumbersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPrimeNumbers * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPrimeNumbers * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPrimeNumbers * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPrimeNumbers * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPrimeNumbers * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPrimeNumbers * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPrimeNumbers * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *CalcPrimes )( 
            IPrimeNumbers * This,
            /* [in] */ long min,
            /* [in] */ long max);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPrimeNumbers * This,
            /* [retval][out] */ long *pnCount);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IPrimeNumbers * This,
            /* [in] */ long n,
            /* [retval][out] */ long *pnPrime);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enum )( 
            IPrimeNumbers * This,
            /* [retval][out] */ IEnumPrimes **ppEnum);
        
        END_INTERFACE
    } IPrimeNumbersVtbl;

    interface IPrimeNumbers
    {
        CONST_VTBL struct IPrimeNumbersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrimeNumbers_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPrimeNumbers_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPrimeNumbers_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPrimeNumbers_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPrimeNumbers_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPrimeNumbers_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPrimeNumbers_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPrimeNumbers_CalcPrimes(This,min,max)	\
    ( (This)->lpVtbl -> CalcPrimes(This,min,max) ) 

#define IPrimeNumbers_get_Count(This,pnCount)	\
    ( (This)->lpVtbl -> get_Count(This,pnCount) ) 

#define IPrimeNumbers_get_Item(This,n,pnPrime)	\
    ( (This)->lpVtbl -> get_Item(This,n,pnPrime) ) 

#define IPrimeNumbers_get_Enum(This,ppEnum)	\
    ( (This)->lpVtbl -> get_Enum(This,ppEnum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPrimeNumbers_INTERFACE_DEFINED__ */


#ifndef __IEnumPrimes_INTERFACE_DEFINED__
#define __IEnumPrimes_INTERFACE_DEFINED__

/* interface IEnumPrimes */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumPrimes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E64EDDDF-2B2C-11D2-983C-00600823CFFB")
    IEnumPrimes : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ long *rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumPrimes **ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumPrimesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumPrimes * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumPrimes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumPrimes * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumPrimes * This,
            /* [in] */ ULONG celt,
            /* [out] */ long *rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumPrimes * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumPrimes * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumPrimes * This,
            /* [out] */ IEnumPrimes **ppenum);
        
        END_INTERFACE
    } IEnumPrimesVtbl;

    interface IEnumPrimes
    {
        CONST_VTBL struct IEnumPrimesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumPrimes_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumPrimes_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumPrimes_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumPrimes_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumPrimes_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumPrimes_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumPrimes_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IEnumPrimes_RemoteNext_Proxy( 
    IEnumPrimes * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ long *rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumPrimes_RemoteNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumPrimes_INTERFACE_DEFINED__ */



#ifndef __PrimeSvrNoAttrLib_LIBRARY_DEFINED__
#define __PrimeSvrNoAttrLib_LIBRARY_DEFINED__

/* library PrimeSvrNoAttrLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PrimeSvrNoAttrLib;

EXTERN_C const CLSID CLSID_PrimeNumbers;

#ifdef __cplusplus

class DECLSPEC_UUID("687E728A-56E2-4B6F-B7DD-D066728DCCE3")
PrimeNumbers;
#endif
#endif /* __PrimeSvrNoAttrLib_LIBRARY_DEFINED__ */

/* interface __MIDL_itf_PrimeSvrNoAttr_0000_0002 */
/* [local] */ 

#ifdef __midl_proxy
static HRESULT STDMETHODCALLTYPE
IEnumPrimes_Next_Proxy(IEnumPrimes* This, ULONG celt, long* rgelt, ULONG* pceltFetched)
{
  ULONG cFetched;
  if( !pceltFetched && celt != 1 ) return E_INVALIDARG;
  return IEnumPrimes_RemoteNext_Proxy(This, celt, rgelt, pceltFetched ? pceltFetched : &cFetched);
}

static HRESULT STDMETHODCALLTYPE
IEnumPrimes_Next_Stub(IEnumPrimes* This, ULONG celt, long* rgelt, ULONG* pceltFetched)
{
  HRESULT hr = This->lpVtbl->Next(This, celt, rgelt, pceltFetched);
  if( hr == S_OK && celt == 1 ) *pceltFetched = 1;
  return hr;
}
#endif // __midl_proxy


extern RPC_IF_HANDLE __MIDL_itf_PrimeSvrNoAttr_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_PrimeSvrNoAttr_0000_0002_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* [local] */ HRESULT STDMETHODCALLTYPE IEnumPrimes_Next_Proxy( 
    IEnumPrimes * This,
    /* [in] */ ULONG celt,
    /* [out] */ long *rgelt,
    /* [out] */ ULONG *pceltFetched);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IEnumPrimes_Next_Stub( 
    IEnumPrimes * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ long *rgelt,
    /* [out] */ ULONG *pceltFetched);



/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


