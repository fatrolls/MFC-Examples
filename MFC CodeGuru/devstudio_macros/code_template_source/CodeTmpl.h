/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Tue Mar 24 01:45:09 1998
 */
/* Compiler settings for CodeTmpl.idl:
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

#ifndef __CodeTmpl_h__
#define __CodeTmpl_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICTAddIn_FWD_DEFINED__
#define __ICTAddIn_FWD_DEFINED__
typedef interface ICTAddIn ICTAddIn;
#endif 	/* __ICTAddIn_FWD_DEFINED__ */


#ifndef __CTAddIn_FWD_DEFINED__
#define __CTAddIn_FWD_DEFINED__

#ifdef __cplusplus
typedef class CTAddIn CTAddIn;
#else
typedef struct CTAddIn CTAddIn;
#endif /* __cplusplus */

#endif 	/* __CTAddIn_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ICTAddIn_INTERFACE_DEFINED__
#define __ICTAddIn_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICTAddIn
 * at Tue Mar 24 01:45:09 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICTAddIn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("9EDADF6F-C069-11D1-A446-0000E8D2CD0A")
    ICTAddIn : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CTInsCodeTmpl( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICTAddInVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICTAddIn __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICTAddIn __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICTAddIn __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICTAddIn __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICTAddIn __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICTAddIn __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICTAddIn __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CTInsCodeTmpl )( 
            ICTAddIn __RPC_FAR * This);
        
        END_INTERFACE
    } ICTAddInVtbl;

    interface ICTAddIn
    {
        CONST_VTBL struct ICTAddInVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICTAddIn_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICTAddIn_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICTAddIn_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICTAddIn_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICTAddIn_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICTAddIn_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICTAddIn_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICTAddIn_CTInsCodeTmpl(This)	\
    (This)->lpVtbl -> CTInsCodeTmpl(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICTAddIn_CTInsCodeTmpl_Proxy( 
    ICTAddIn __RPC_FAR * This);


void __RPC_STUB ICTAddIn_CTInsCodeTmpl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICTAddIn_INTERFACE_DEFINED__ */



#ifndef __CODETMPLLib_LIBRARY_DEFINED__
#define __CODETMPLLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: CODETMPLLib
 * at Tue Mar 24 01:45:09 1998
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_CODETMPLLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CTAddIn;

class DECLSPEC_UUID("9EDADF70-C069-11D1-A446-0000E8D2CD0A")
CTAddIn;
#endif
#endif /* __CODETMPLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
