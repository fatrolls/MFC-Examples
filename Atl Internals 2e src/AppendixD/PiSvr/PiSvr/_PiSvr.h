

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Jun 19 10:42:16 2012
 */
/* Compiler settings for _PiSvr.idl:
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

#ifndef ___PiSvr_h__
#define ___PiSvr_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICalcPi_FWD_DEFINED__
#define __ICalcPi_FWD_DEFINED__
typedef interface ICalcPi ICalcPi;
#endif 	/* __ICalcPi_FWD_DEFINED__ */


#ifndef ___ICalcPiEvents_FWD_DEFINED__
#define ___ICalcPiEvents_FWD_DEFINED__
typedef interface _ICalcPiEvents _ICalcPiEvents;
#endif 	/* ___ICalcPiEvents_FWD_DEFINED__ */


#ifndef __CCalcPi_FWD_DEFINED__
#define __CCalcPi_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCalcPi CCalcPi;
#else
typedef struct CCalcPi CCalcPi;
#endif /* __cplusplus */

#endif 	/* __CCalcPi_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICalcPi_INTERFACE_DEFINED__
#define __ICalcPi_INTERFACE_DEFINED__

/* interface ICalcPi */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICalcPi;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8E3ABD67-5075-4C38-BA00-8289E336E7F9")
    ICalcPi : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Digits( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Digits( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CalcPi( 
            /* [retval][out] */ BSTR *pbstrPi) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICalcPiVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICalcPi * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICalcPi * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICalcPi * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICalcPi * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICalcPi * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICalcPi * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICalcPi * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Digits )( 
            ICalcPi * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Digits )( 
            ICalcPi * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CalcPi )( 
            ICalcPi * This,
            /* [retval][out] */ BSTR *pbstrPi);
        
        END_INTERFACE
    } ICalcPiVtbl;

    interface ICalcPi
    {
        CONST_VTBL struct ICalcPiVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICalcPi_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICalcPi_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICalcPi_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICalcPi_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICalcPi_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICalcPi_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICalcPi_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICalcPi_get_Digits(This,pVal)	\
    ( (This)->lpVtbl -> get_Digits(This,pVal) ) 

#define ICalcPi_put_Digits(This,newVal)	\
    ( (This)->lpVtbl -> put_Digits(This,newVal) ) 

#define ICalcPi_CalcPi(This,pbstrPi)	\
    ( (This)->lpVtbl -> CalcPi(This,pbstrPi) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICalcPi_INTERFACE_DEFINED__ */



#ifndef __PiSvr_LIBRARY_DEFINED__
#define __PiSvr_LIBRARY_DEFINED__

/* library PiSvr */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_PiSvr;

#ifndef ___ICalcPiEvents_DISPINTERFACE_DEFINED__
#define ___ICalcPiEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ICalcPiEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ICalcPiEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("9822AB1A-8031-4914-BD73-3459A91B98A9")
    _ICalcPiEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ICalcPiEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ICalcPiEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ICalcPiEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ICalcPiEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ICalcPiEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ICalcPiEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ICalcPiEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ICalcPiEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ICalcPiEventsVtbl;

    interface _ICalcPiEvents
    {
        CONST_VTBL struct _ICalcPiEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ICalcPiEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ICalcPiEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ICalcPiEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ICalcPiEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _ICalcPiEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _ICalcPiEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _ICalcPiEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ICalcPiEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CCalcPi;

#ifdef __cplusplus

class DECLSPEC_UUID("A892A09D-98C9-4AD4-98C5-769F7743F204")
CCalcPi;
#endif
#endif /* __PiSvr_LIBRARY_DEFINED__ */

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


