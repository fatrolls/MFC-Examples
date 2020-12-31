/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Thu Feb 26 00:40:25 1998
 */
/* Compiler settings for KbdMac.idl:
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

#ifndef __KbdMac_h__
#define __KbdMac_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IKMAddIn_FWD_DEFINED__
#define __IKMAddIn_FWD_DEFINED__
typedef interface IKMAddIn IKMAddIn;
#endif 	/* __IKMAddIn_FWD_DEFINED__ */


#ifndef __KMAddIn_FWD_DEFINED__
#define __KMAddIn_FWD_DEFINED__

#ifdef __cplusplus
typedef class KMAddIn KMAddIn;
#else
typedef struct KMAddIn KMAddIn;
#endif /* __cplusplus */

#endif 	/* __KMAddIn_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IKMAddIn_INTERFACE_DEFINED__
#define __IKMAddIn_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IKMAddIn
 * at Thu Feb 26 00:40:25 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IKMAddIn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("CF6847F2-AE24-11D1-AE27-00A0C91BA903")
    IKMAddIn : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE KMPlay( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE KMStop( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE KMRecord( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IKMAddInVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IKMAddIn __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IKMAddIn __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IKMAddIn __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IKMAddIn __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IKMAddIn __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IKMAddIn __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IKMAddIn __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *KMPlay )( 
            IKMAddIn __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *KMStop )( 
            IKMAddIn __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *KMRecord )( 
            IKMAddIn __RPC_FAR * This);
        
        END_INTERFACE
    } IKMAddInVtbl;

    interface IKMAddIn
    {
        CONST_VTBL struct IKMAddInVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IKMAddIn_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IKMAddIn_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IKMAddIn_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IKMAddIn_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IKMAddIn_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IKMAddIn_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IKMAddIn_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IKMAddIn_KMPlay(This)	\
    (This)->lpVtbl -> KMPlay(This)

#define IKMAddIn_KMStop(This)	\
    (This)->lpVtbl -> KMStop(This)

#define IKMAddIn_KMRecord(This)	\
    (This)->lpVtbl -> KMRecord(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IKMAddIn_KMPlay_Proxy( 
    IKMAddIn __RPC_FAR * This);


void __RPC_STUB IKMAddIn_KMPlay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IKMAddIn_KMStop_Proxy( 
    IKMAddIn __RPC_FAR * This);


void __RPC_STUB IKMAddIn_KMStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IKMAddIn_KMRecord_Proxy( 
    IKMAddIn __RPC_FAR * This);


void __RPC_STUB IKMAddIn_KMRecord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IKMAddIn_INTERFACE_DEFINED__ */



#ifndef __KBDMACLib_LIBRARY_DEFINED__
#define __KBDMACLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: KBDMACLib
 * at Thu Feb 26 00:40:25 1998
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_KBDMACLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_KMAddIn;

class DECLSPEC_UUID("CF6847F3-AE24-11D1-AE27-00A0C91BA903")
KMAddIn;
#endif
#endif /* __KBDMACLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
