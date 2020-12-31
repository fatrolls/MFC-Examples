/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Tue Oct 21 21:50:50 1997
 */
/* Compiler settings for .\HostHook.idl:
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

#ifndef __HostHook_h__
#define __HostHook_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICallInfo_FWD_DEFINED__
#define __ICallInfo_FWD_DEFINED__
typedef interface ICallInfo ICallInfo;
#endif 	/* __ICallInfo_FWD_DEFINED__ */


#ifndef __IClientCallInfo_FWD_DEFINED__
#define __IClientCallInfo_FWD_DEFINED__
typedef interface IClientCallInfo IClientCallInfo;
#endif 	/* __IClientCallInfo_FWD_DEFINED__ */


#ifndef __CallInfo_FWD_DEFINED__
#define __CallInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class CallInfo CallInfo;
#else
typedef struct CallInfo CallInfo;
#endif /* __cplusplus */

#endif 	/* __CallInfo_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ICallInfo_INTERFACE_DEFINED__
#define __ICallInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICallInfo
 * at Tue Oct 21 21:50:50 1997
 * using MIDL 3.01.75
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_ICallInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F23ADD50-4992-11d1-991C-006097585A3C")
    ICallInfo : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_OriginalProcessID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_OriginalThreadID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_OriginalHostID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_OriginalHostName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DirectProcessID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DirectThreadID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DirectHostID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DirectHostName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_PseudoCausalityID( 
            /* [retval][out] */ GUID __RPC_FAR *pguid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICallInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICallInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICallInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICallInfo __RPC_FAR * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OriginalProcessID )( 
            ICallInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OriginalThreadID )( 
            ICallInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OriginalHostID )( 
            ICallInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OriginalHostName )( 
            ICallInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DirectProcessID )( 
            ICallInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DirectThreadID )( 
            ICallInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DirectHostID )( 
            ICallInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DirectHostName )( 
            ICallInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PseudoCausalityID )( 
            ICallInfo __RPC_FAR * This,
            /* [retval][out] */ GUID __RPC_FAR *pguid);
        
        END_INTERFACE
    } ICallInfoVtbl;

    interface ICallInfo
    {
        CONST_VTBL struct ICallInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICallInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICallInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICallInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICallInfo_get_OriginalProcessID(This,pVal)	\
    (This)->lpVtbl -> get_OriginalProcessID(This,pVal)

#define ICallInfo_get_OriginalThreadID(This,pVal)	\
    (This)->lpVtbl -> get_OriginalThreadID(This,pVal)

#define ICallInfo_get_OriginalHostID(This,pVal)	\
    (This)->lpVtbl -> get_OriginalHostID(This,pVal)

#define ICallInfo_get_OriginalHostName(This,pVal)	\
    (This)->lpVtbl -> get_OriginalHostName(This,pVal)

#define ICallInfo_get_DirectProcessID(This,pVal)	\
    (This)->lpVtbl -> get_DirectProcessID(This,pVal)

#define ICallInfo_get_DirectThreadID(This,pVal)	\
    (This)->lpVtbl -> get_DirectThreadID(This,pVal)

#define ICallInfo_get_DirectHostID(This,pVal)	\
    (This)->lpVtbl -> get_DirectHostID(This,pVal)

#define ICallInfo_get_DirectHostName(This,pVal)	\
    (This)->lpVtbl -> get_DirectHostName(This,pVal)

#define ICallInfo_get_PseudoCausalityID(This,pguid)	\
    (This)->lpVtbl -> get_PseudoCausalityID(This,pguid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE ICallInfo_get_OriginalProcessID_Proxy( 
    ICallInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ICallInfo_get_OriginalProcessID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICallInfo_get_OriginalThreadID_Proxy( 
    ICallInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ICallInfo_get_OriginalThreadID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICallInfo_get_OriginalHostID_Proxy( 
    ICallInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ICallInfo_get_OriginalHostID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICallInfo_get_OriginalHostName_Proxy( 
    ICallInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ICallInfo_get_OriginalHostName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICallInfo_get_DirectProcessID_Proxy( 
    ICallInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ICallInfo_get_DirectProcessID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICallInfo_get_DirectThreadID_Proxy( 
    ICallInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ICallInfo_get_DirectThreadID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICallInfo_get_DirectHostID_Proxy( 
    ICallInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ICallInfo_get_DirectHostID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICallInfo_get_DirectHostName_Proxy( 
    ICallInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ICallInfo_get_DirectHostName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICallInfo_get_PseudoCausalityID_Proxy( 
    ICallInfo __RPC_FAR * This,
    /* [retval][out] */ GUID __RPC_FAR *pguid);


void __RPC_STUB ICallInfo_get_PseudoCausalityID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICallInfo_INTERFACE_DEFINED__ */


#ifndef __IClientCallInfo_INTERFACE_DEFINED__
#define __IClientCallInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IClientCallInfo
 * at Tue Oct 21 21:50:50 1997
 * using MIDL 3.01.75
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IClientCallInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F23ADD54-4992-11d1-991C-006097585A3C")
    IClientCallInfo : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_TargetProcessID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_TargetThreadID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_TargetHostID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_TargetHostName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IClientCallInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IClientCallInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IClientCallInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IClientCallInfo __RPC_FAR * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TargetProcessID )( 
            IClientCallInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TargetThreadID )( 
            IClientCallInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TargetHostID )( 
            IClientCallInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TargetHostName )( 
            IClientCallInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } IClientCallInfoVtbl;

    interface IClientCallInfo
    {
        CONST_VTBL struct IClientCallInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IClientCallInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IClientCallInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IClientCallInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IClientCallInfo_get_TargetProcessID(This,pVal)	\
    (This)->lpVtbl -> get_TargetProcessID(This,pVal)

#define IClientCallInfo_get_TargetThreadID(This,pVal)	\
    (This)->lpVtbl -> get_TargetThreadID(This,pVal)

#define IClientCallInfo_get_TargetHostID(This,pVal)	\
    (This)->lpVtbl -> get_TargetHostID(This,pVal)

#define IClientCallInfo_get_TargetHostName(This,pVal)	\
    (This)->lpVtbl -> get_TargetHostName(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IClientCallInfo_get_TargetProcessID_Proxy( 
    IClientCallInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IClientCallInfo_get_TargetProcessID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IClientCallInfo_get_TargetThreadID_Proxy( 
    IClientCallInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IClientCallInfo_get_TargetThreadID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IClientCallInfo_get_TargetHostID_Proxy( 
    IClientCallInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IClientCallInfo_get_TargetHostID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IClientCallInfo_get_TargetHostName_Proxy( 
    IClientCallInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IClientCallInfo_get_TargetHostName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IClientCallInfo_INTERFACE_DEFINED__ */



#ifndef __CallInfoLib_LIBRARY_DEFINED__
#define __CallInfoLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: CallInfoLib
 * at Tue Oct 21 21:50:50 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][lcid][version][uuid] */ 



EXTERN_C const IID LIBID_CallInfoLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CallInfo;

class DECLSPEC_UUID("F23ADD52-4992-11d1-991C-006097585A3C")
CallInfo;
#endif
#endif /* __CallInfoLib_LIBRARY_DEFINED__ */

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
