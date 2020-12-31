

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Sep 23 16:33:56 2011
 */
/* Compiler settings for ReadWriteExcel.idl:
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


#ifndef __ReadWriteExcel_h_h__
#define __ReadWriteExcel_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IReadWriteExcel_FWD_DEFINED__
#define __IReadWriteExcel_FWD_DEFINED__
typedef interface IReadWriteExcel IReadWriteExcel;
#endif 	/* __IReadWriteExcel_FWD_DEFINED__ */


#ifndef __ReadWriteExcel_FWD_DEFINED__
#define __ReadWriteExcel_FWD_DEFINED__

#ifdef __cplusplus
typedef class ReadWriteExcel ReadWriteExcel;
#else
typedef struct ReadWriteExcel ReadWriteExcel;
#endif /* __cplusplus */

#endif 	/* __ReadWriteExcel_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __ReadWriteExcel_LIBRARY_DEFINED__
#define __ReadWriteExcel_LIBRARY_DEFINED__

/* library ReadWriteExcel */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ReadWriteExcel;

#ifndef __IReadWriteExcel_DISPINTERFACE_DEFINED__
#define __IReadWriteExcel_DISPINTERFACE_DEFINED__

/* dispinterface IReadWriteExcel */
/* [uuid] */ 


EXTERN_C const IID DIID_IReadWriteExcel;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("AF2A28C6-8ECD-4D30-9DAA-1A7C0EBA8D1C")
    IReadWriteExcel : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IReadWriteExcelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IReadWriteExcel * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IReadWriteExcel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IReadWriteExcel * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IReadWriteExcel * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IReadWriteExcel * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IReadWriteExcel * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IReadWriteExcel * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IReadWriteExcelVtbl;

    interface IReadWriteExcel
    {
        CONST_VTBL struct IReadWriteExcelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IReadWriteExcel_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IReadWriteExcel_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IReadWriteExcel_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IReadWriteExcel_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IReadWriteExcel_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IReadWriteExcel_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IReadWriteExcel_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IReadWriteExcel_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ReadWriteExcel;

#ifdef __cplusplus

class DECLSPEC_UUID("B2359DC3-377F-45D3-AF2A-77278B400702")
ReadWriteExcel;
#endif
#endif /* __ReadWriteExcel_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


