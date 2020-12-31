/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Fri Jun 27 14:23:49 1997
 */
/* Compiler settings for MeowMoniker.idl:
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

#ifndef __MeowMoniker_h__
#define __MeowMoniker_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __DIFeline_FWD_DEFINED__
#define __DIFeline_FWD_DEFINED__
typedef interface DIFeline DIFeline;
#endif 	/* __DIFeline_FWD_DEFINED__ */


#ifndef __CoMeowMoniker_FWD_DEFINED__
#define __CoMeowMoniker_FWD_DEFINED__

#ifdef __cplusplus
typedef class CoMeowMoniker CoMeowMoniker;
#else
typedef struct CoMeowMoniker CoMeowMoniker;
#endif /* __cplusplus */

#endif 	/* __CoMeowMoniker_FWD_DEFINED__ */


#ifndef __CoFeline_FWD_DEFINED__
#define __CoFeline_FWD_DEFINED__

#ifdef __cplusplus
typedef class CoFeline CoFeline;
#else
typedef struct CoFeline CoFeline;
#endif /* __cplusplus */

#endif 	/* __CoFeline_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_MeowMoniker_0000
 * at Fri Jun 27 14:23:49 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


STDAPI CreateMeowMoniker(IUnknown* punk, REFIID riid, DWORD dwDestContext, DWORD mshlflags, IMoniker** ppmk);
typedef HRESULT (WINAPI *PFNCREATEMEOWMONIKER)(IUnknown* punk, REFIID riid, DWORD dwDestContext, DWORD mshlflags, IMoniker** ppmk);


extern RPC_IF_HANDLE __MIDL_itf_MeowMoniker_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MeowMoniker_0000_v0_0_s_ifspec;

#ifndef __DIFeline_INTERFACE_DEFINED__
#define __DIFeline_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: DIFeline
 * at Fri Jun 27 14:23:49 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_DIFeline;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("CB18CB8E-C7CC-11D0-9A44-00008600A105")
    DIFeline : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDisplayName( 
            /* [in] */ IDispatch __RPC_FAR *pdisp,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ParseDisplayName( 
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DIFelineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DIFeline __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DIFeline __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DIFeline __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DIFeline __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DIFeline __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DIFeline __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DIFeline __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDisplayName )( 
            DIFeline __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pdisp,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ParseDisplayName )( 
            DIFeline __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdisp);
        
        END_INTERFACE
    } DIFelineVtbl;

    interface DIFeline
    {
        CONST_VTBL struct DIFelineVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DIFeline_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DIFeline_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DIFeline_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DIFeline_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DIFeline_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DIFeline_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DIFeline_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define DIFeline_GetDisplayName(This,pdisp,pbstrName)	\
    (This)->lpVtbl -> GetDisplayName(This,pdisp,pbstrName)

#define DIFeline_ParseDisplayName(This,bstrName,ppdisp)	\
    (This)->lpVtbl -> ParseDisplayName(This,bstrName,ppdisp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DIFeline_GetDisplayName_Proxy( 
    DIFeline __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pdisp,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB DIFeline_GetDisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DIFeline_ParseDisplayName_Proxy( 
    DIFeline __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdisp);


void __RPC_STUB DIFeline_ParseDisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DIFeline_INTERFACE_DEFINED__ */



#ifndef __MEOWMONIKERLib_LIBRARY_DEFINED__
#define __MEOWMONIKERLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: MEOWMONIKERLib
 * at Fri Jun 27 14:23:49 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_MEOWMONIKERLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CoMeowMoniker;

class DECLSPEC_UUID("E900C00E-BD9D-11D0-9A44-00008600A105")
CoMeowMoniker;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CoFeline;

class DECLSPEC_UUID("CB18CB8F-C7CC-11D0-9A44-00008600A105")
CoFeline;
#endif
#endif /* __MEOWMONIKERLib_LIBRARY_DEFINED__ */

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
