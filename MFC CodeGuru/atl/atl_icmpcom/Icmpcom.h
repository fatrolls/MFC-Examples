/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Sat Jun 20 18:49:21 1998
 */
/* Compiler settings for Icmpcom.idl:
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

#ifndef __Icmpcom_h__
#define __Icmpcom_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICMPCom_FWD_DEFINED__
#define __ICMPCom_FWD_DEFINED__
typedef interface ICMPCom ICMPCom;
#endif 	/* __ICMPCom_FWD_DEFINED__ */


#ifndef __DICMPComEvent_FWD_DEFINED__
#define __DICMPComEvent_FWD_DEFINED__
typedef interface DICMPComEvent DICMPComEvent;
#endif 	/* __DICMPComEvent_FWD_DEFINED__ */


#ifndef __CICMPCom_FWD_DEFINED__
#define __CICMPCom_FWD_DEFINED__

#ifdef __cplusplus
typedef class CICMPCom CICMPCom;
#else
typedef struct CICMPCom CICMPCom;
#endif /* __cplusplus */

#endif 	/* __CICMPCom_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ICMPCom_INTERFACE_DEFINED__
#define __ICMPCom_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICMPCom
 * at Sat Jun 20 18:49:21 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICMPCom;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BFD09810-E756-11D1-83E6-00A0244DBC26")
    ICMPCom : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartICMP( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopICMP( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPingVariables( 
            BSTR hostname,
            BOOL opttrcrt,
            BOOL optresolve,
            BOOL optnofrag,
            BOOL optruntointerupt,
            INT optttl,
            INT optpacketlen,
            INT optnumpackets,
            INT optrroutenum,
            INT opttimestamp,
            INT opttos,
            INT opttimeout) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RunPing( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopPing( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICMPComVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICMPCom __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICMPCom __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICMPCom __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICMPCom __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICMPCom __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICMPCom __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICMPCom __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartICMP )( 
            ICMPCom __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopICMP )( 
            ICMPCom __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPingVariables )( 
            ICMPCom __RPC_FAR * This,
            BSTR hostname,
            BOOL opttrcrt,
            BOOL optresolve,
            BOOL optnofrag,
            BOOL optruntointerupt,
            INT optttl,
            INT optpacketlen,
            INT optnumpackets,
            INT optrroutenum,
            INT opttimestamp,
            INT opttos,
            INT opttimeout);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RunPing )( 
            ICMPCom __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopPing )( 
            ICMPCom __RPC_FAR * This);
        
        END_INTERFACE
    } ICMPComVtbl;

    interface ICMPCom
    {
        CONST_VTBL struct ICMPComVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICMPCom_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICMPCom_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICMPCom_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICMPCom_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICMPCom_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICMPCom_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICMPCom_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICMPCom_StartICMP(This)	\
    (This)->lpVtbl -> StartICMP(This)

#define ICMPCom_StopICMP(This)	\
    (This)->lpVtbl -> StopICMP(This)

#define ICMPCom_SetPingVariables(This,hostname,opttrcrt,optresolve,optnofrag,optruntointerupt,optttl,optpacketlen,optnumpackets,optrroutenum,opttimestamp,opttos,opttimeout)	\
    (This)->lpVtbl -> SetPingVariables(This,hostname,opttrcrt,optresolve,optnofrag,optruntointerupt,optttl,optpacketlen,optnumpackets,optrroutenum,opttimestamp,opttos,opttimeout)

#define ICMPCom_RunPing(This)	\
    (This)->lpVtbl -> RunPing(This)

#define ICMPCom_StopPing(This)	\
    (This)->lpVtbl -> StopPing(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICMPCom_StartICMP_Proxy( 
    ICMPCom __RPC_FAR * This);


void __RPC_STUB ICMPCom_StartICMP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICMPCom_StopICMP_Proxy( 
    ICMPCom __RPC_FAR * This);


void __RPC_STUB ICMPCom_StopICMP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICMPCom_SetPingVariables_Proxy( 
    ICMPCom __RPC_FAR * This,
    BSTR hostname,
    BOOL opttrcrt,
    BOOL optresolve,
    BOOL optnofrag,
    BOOL optruntointerupt,
    INT optttl,
    INT optpacketlen,
    INT optnumpackets,
    INT optrroutenum,
    INT opttimestamp,
    INT opttos,
    INT opttimeout);


void __RPC_STUB ICMPCom_SetPingVariables_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICMPCom_RunPing_Proxy( 
    ICMPCom __RPC_FAR * This);


void __RPC_STUB ICMPCom_RunPing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICMPCom_StopPing_Proxy( 
    ICMPCom __RPC_FAR * This);


void __RPC_STUB ICMPCom_StopPing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICMPCom_INTERFACE_DEFINED__ */



#ifndef __ICMPCOMLib_LIBRARY_DEFINED__
#define __ICMPCOMLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: ICMPCOMLib
 * at Sat Jun 20 18:49:21 1998
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_ICMPCOMLib;

#ifndef __DICMPComEvent_DISPINTERFACE_DEFINED__
#define __DICMPComEvent_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: DICMPComEvent
 * at Sat Jun 20 18:49:21 1998
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][nonextensible][uuid] */ 



EXTERN_C const IID DIID_DICMPComEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface DECLSPEC_UUID("7699DC01-F7E5-11d1-841B-00A0244DBC26")
    DICMPComEvent : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct DICMPComEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DICMPComEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DICMPComEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DICMPComEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DICMPComEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DICMPComEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DICMPComEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DICMPComEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } DICMPComEventVtbl;

    interface DICMPComEvent
    {
        CONST_VTBL struct DICMPComEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DICMPComEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DICMPComEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DICMPComEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DICMPComEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DICMPComEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DICMPComEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DICMPComEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __DICMPComEvent_DISPINTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CICMPCom;

class DECLSPEC_UUID("BFD09811-E756-11D1-83E6-00A0244DBC26")
CICMPCom;
#endif
#endif /* __ICMPCOMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
