

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Jun 20 09:38:22 2012
 */
/* Compiler settings for _BirdsAttr.idl:
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

#ifndef ___BirdsAttr_h__
#define ___BirdsAttr_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPenguin_FWD_DEFINED__
#define __IPenguin_FWD_DEFINED__
typedef interface IPenguin IPenguin;
#endif 	/* __IPenguin_FWD_DEFINED__ */


#ifndef __IBird_FWD_DEFINED__
#define __IBird_FWD_DEFINED__
typedef interface IBird IBird;
#endif 	/* __IBird_FWD_DEFINED__ */


#ifndef __CPenguin_FWD_DEFINED__
#define __CPenguin_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPenguin CPenguin;
#else
typedef struct CPenguin CPenguin;
#endif /* __cplusplus */

#endif 	/* __CPenguin_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IPenguin_INTERFACE_DEFINED__
#define __IPenguin_INTERFACE_DEFINED__

/* interface IPenguin */
/* [unique][helpstring][uuid][dual][object] */ 


EXTERN_C const IID IID_IPenguin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C093AF2-1EFC-4FE9-B602-D5A23D967B77")
    IPenguin : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE StraightenTie( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPenguinVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPenguin * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPenguin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPenguin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPenguin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPenguin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPenguin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPenguin * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IPenguin * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IPenguin * This,
            /* [in] */ BSTR newVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *StraightenTie )( 
            IPenguin * This);
        
        END_INTERFACE
    } IPenguinVtbl;

    interface IPenguin
    {
        CONST_VTBL struct IPenguinVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPenguin_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPenguin_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPenguin_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPenguin_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPenguin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPenguin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPenguin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPenguin_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IPenguin_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define IPenguin_StraightenTie(This)	\
    ( (This)->lpVtbl -> StraightenTie(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPenguin_INTERFACE_DEFINED__ */


#ifndef __IBird_INTERFACE_DEFINED__
#define __IBird_INTERFACE_DEFINED__

/* interface IBird */
/* [unique][helpstring][uuid][dual][object] */ 


EXTERN_C const IID IID_IBird;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("92247816-FA98-4861-83AB-56FD45F37991")
    IBird : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Wingspan( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Wingspan( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Fly( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBirdVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBird * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBird * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBird * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBird * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBird * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBird * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBird * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Wingspan )( 
            IBird * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Wingspan )( 
            IBird * This,
            /* [in] */ LONG newVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Fly )( 
            IBird * This);
        
        END_INTERFACE
    } IBirdVtbl;

    interface IBird
    {
        CONST_VTBL struct IBirdVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBird_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBird_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBird_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBird_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBird_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBird_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBird_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IBird_get_Wingspan(This,pVal)	\
    ( (This)->lpVtbl -> get_Wingspan(This,pVal) ) 

#define IBird_put_Wingspan(This,newVal)	\
    ( (This)->lpVtbl -> put_Wingspan(This,newVal) ) 

#define IBird_Fly(This)	\
    ( (This)->lpVtbl -> Fly(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBird_INTERFACE_DEFINED__ */



#ifndef __BirdsAttr_LIBRARY_DEFINED__
#define __BirdsAttr_LIBRARY_DEFINED__

/* library BirdsAttr */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_BirdsAttr;

EXTERN_C const CLSID CLSID_CPenguin;

#ifdef __cplusplus

class DECLSPEC_UUID("F591F114-57D0-45DA-B627-5E859AB62248")
CPenguin;
#endif
#endif /* __BirdsAttr_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


