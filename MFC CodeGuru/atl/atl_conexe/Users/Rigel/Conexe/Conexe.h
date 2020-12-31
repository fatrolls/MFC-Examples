/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Wed Jun 10 20:47:00 1998
 */
/* Compiler settings for Conexe.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Conexe_h__
#define __Conexe_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IRandexe_FWD_DEFINED__
#define __IRandexe_FWD_DEFINED__
typedef interface IRandexe IRandexe;
#endif 	/* __IRandexe_FWD_DEFINED__ */


#ifndef __IRandexeEvent_FWD_DEFINED__
#define __IRandexeEvent_FWD_DEFINED__
typedef interface IRandexeEvent IRandexeEvent;
#endif 	/* __IRandexeEvent_FWD_DEFINED__ */


#ifndef __Randexe_FWD_DEFINED__
#define __Randexe_FWD_DEFINED__

#ifdef __cplusplus
typedef class Randexe Randexe;
#else
typedef struct Randexe Randexe;
#endif /* __cplusplus */

#endif 	/* __Randexe_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IRandexe_INTERFACE_DEFINED__
#define __IRandexe_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRandexe
 * at Wed Jun 10 20:47:00 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IRandexe;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("AB2E510F-F9F8-11D1-A7D8-0060083404B6")
    IRandexe : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Start( 
            /* [out] */ long __RPC_FAR *pnID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( 
            /* [in] */ long nID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRandexeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRandexe __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRandexe __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRandexe __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRandexe __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRandexe __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRandexe __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRandexe __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IRandexe __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pnID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IRandexe __RPC_FAR * This,
            /* [in] */ long nID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopAll )( 
            IRandexe __RPC_FAR * This);
        
        END_INTERFACE
    } IRandexeVtbl;

    interface IRandexe
    {
        CONST_VTBL struct IRandexeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRandexe_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRandexe_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRandexe_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRandexe_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRandexe_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRandexe_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRandexe_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRandexe_Start(This,pnID)	\
    (This)->lpVtbl -> Start(This,pnID)

#define IRandexe_Stop(This,nID)	\
    (This)->lpVtbl -> Stop(This,nID)

#define IRandexe_StopAll(This)	\
    (This)->lpVtbl -> StopAll(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRandexe_Start_Proxy( 
    IRandexe __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pnID);


void __RPC_STUB IRandexe_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRandexe_Stop_Proxy( 
    IRandexe __RPC_FAR * This,
    /* [in] */ long nID);


void __RPC_STUB IRandexe_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRandexe_StopAll_Proxy( 
    IRandexe __RPC_FAR * This);


void __RPC_STUB IRandexe_StopAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRandexe_INTERFACE_DEFINED__ */


#ifndef __IRandexeEvent_INTERFACE_DEFINED__
#define __IRandexeEvent_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRandexeEvent
 * at Wed Jun 10 20:47:00 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IRandexeEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("AB2E5111-F9F8-11D1-A7D8-0060083404B6")
    IRandexeEvent : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Fire( 
            /* [in] */ long nID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRandexeEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRandexeEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRandexeEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRandexeEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRandexeEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRandexeEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRandexeEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRandexeEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Fire )( 
            IRandexeEvent __RPC_FAR * This,
            /* [in] */ long nID);
        
        END_INTERFACE
    } IRandexeEventVtbl;

    interface IRandexeEvent
    {
        CONST_VTBL struct IRandexeEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRandexeEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRandexeEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRandexeEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRandexeEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRandexeEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRandexeEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRandexeEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRandexeEvent_Fire(This,nID)	\
    (This)->lpVtbl -> Fire(This,nID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRandexeEvent_Fire_Proxy( 
    IRandexeEvent __RPC_FAR * This,
    /* [in] */ long nID);


void __RPC_STUB IRandexeEvent_Fire_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRandexeEvent_INTERFACE_DEFINED__ */



#ifndef __CONEXELib_LIBRARY_DEFINED__
#define __CONEXELib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: CONEXELib
 * at Wed Jun 10 20:47:00 1998
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_CONEXELib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Randexe;

class DECLSPEC_UUID("AB2E5110-F9F8-11D1-A7D8-0060083404B6")
Randexe;
#endif
#endif /* __CONEXELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
