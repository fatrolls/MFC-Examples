/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Feb 10 15:19:36 1999
 */
/* Compiler settings for dictionary.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __dictionary_h__
#define __dictionary_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDictionary_FWD_DEFINED__
#define __IDictionary_FWD_DEFINED__
typedef interface IDictionary IDictionary;
#endif 	/* __IDictionary_FWD_DEFINED__ */


#ifndef __ISpellCheck_FWD_DEFINED__
#define __ISpellCheck_FWD_DEFINED__
typedef interface ISpellCheck ISpellCheck;
#endif 	/* __ISpellCheck_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDictionary_INTERFACE_DEFINED__
#define __IDictionary_INTERFACE_DEFINED__

/* interface IDictionary */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IDictionary;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("54BF6568-1007-11D1-B0AA-444553540000")
    IDictionary : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LoadLibrary( 
            /* [string][in] */ WCHAR __RPC_FAR *pFilename) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InsertWord( 
            /* [string][in] */ WCHAR __RPC_FAR *pWord,
            /* [string][in] */ WCHAR __RPC_FAR *pWordUsingOtherLang) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteWord( 
            /* [string][in] */ WCHAR __RPC_FAR *pWord) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LookupWord( 
            /* [string][in] */ WCHAR __RPC_FAR *pWord,
            /* [out] */ WCHAR __RPC_FAR pWordOut[ 32 ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RestoreLibrary( 
            /* [string][in] */ WCHAR __RPC_FAR *pFilename) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FreeLibrary( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDictionaryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDictionary __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDictionary __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDictionary __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IDictionary __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadLibrary )( 
            IDictionary __RPC_FAR * This,
            /* [string][in] */ WCHAR __RPC_FAR *pFilename);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InsertWord )( 
            IDictionary __RPC_FAR * This,
            /* [string][in] */ WCHAR __RPC_FAR *pWord,
            /* [string][in] */ WCHAR __RPC_FAR *pWordUsingOtherLang);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteWord )( 
            IDictionary __RPC_FAR * This,
            /* [string][in] */ WCHAR __RPC_FAR *pWord);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LookupWord )( 
            IDictionary __RPC_FAR * This,
            /* [string][in] */ WCHAR __RPC_FAR *pWord,
            /* [out] */ WCHAR __RPC_FAR pWordOut[ 32 ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestoreLibrary )( 
            IDictionary __RPC_FAR * This,
            /* [string][in] */ WCHAR __RPC_FAR *pFilename);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreeLibrary )( 
            IDictionary __RPC_FAR * This);
        
        END_INTERFACE
    } IDictionaryVtbl;

    interface IDictionary
    {
        CONST_VTBL struct IDictionaryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDictionary_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDictionary_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDictionary_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDictionary_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IDictionary_LoadLibrary(This,pFilename)	\
    (This)->lpVtbl -> LoadLibrary(This,pFilename)

#define IDictionary_InsertWord(This,pWord,pWordUsingOtherLang)	\
    (This)->lpVtbl -> InsertWord(This,pWord,pWordUsingOtherLang)

#define IDictionary_DeleteWord(This,pWord)	\
    (This)->lpVtbl -> DeleteWord(This,pWord)

#define IDictionary_LookupWord(This,pWord,pWordOut)	\
    (This)->lpVtbl -> LookupWord(This,pWord,pWordOut)

#define IDictionary_RestoreLibrary(This,pFilename)	\
    (This)->lpVtbl -> RestoreLibrary(This,pFilename)

#define IDictionary_FreeLibrary(This)	\
    (This)->lpVtbl -> FreeLibrary(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDictionary_Initialize_Proxy( 
    IDictionary __RPC_FAR * This);


void __RPC_STUB IDictionary_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDictionary_LoadLibrary_Proxy( 
    IDictionary __RPC_FAR * This,
    /* [string][in] */ WCHAR __RPC_FAR *pFilename);


void __RPC_STUB IDictionary_LoadLibrary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDictionary_InsertWord_Proxy( 
    IDictionary __RPC_FAR * This,
    /* [string][in] */ WCHAR __RPC_FAR *pWord,
    /* [string][in] */ WCHAR __RPC_FAR *pWordUsingOtherLang);


void __RPC_STUB IDictionary_InsertWord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDictionary_DeleteWord_Proxy( 
    IDictionary __RPC_FAR * This,
    /* [string][in] */ WCHAR __RPC_FAR *pWord);


void __RPC_STUB IDictionary_DeleteWord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDictionary_LookupWord_Proxy( 
    IDictionary __RPC_FAR * This,
    /* [string][in] */ WCHAR __RPC_FAR *pWord,
    /* [out] */ WCHAR __RPC_FAR pWordOut[ 32 ]);


void __RPC_STUB IDictionary_LookupWord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDictionary_RestoreLibrary_Proxy( 
    IDictionary __RPC_FAR * This,
    /* [string][in] */ WCHAR __RPC_FAR *pFilename);


void __RPC_STUB IDictionary_RestoreLibrary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDictionary_FreeLibrary_Proxy( 
    IDictionary __RPC_FAR * This);


void __RPC_STUB IDictionary_FreeLibrary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDictionary_INTERFACE_DEFINED__ */


#ifndef __ISpellCheck_INTERFACE_DEFINED__
#define __ISpellCheck_INTERFACE_DEFINED__

/* interface ISpellCheck */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ISpellCheck;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("54BF6569-1007-11D1-B0AA-444553540000")
    ISpellCheck : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CheckWord( 
            /* [string][in] */ WCHAR __RPC_FAR *pWord,
            /* [out] */ WCHAR __RPC_FAR pWordOut[ 32 ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpellCheckVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISpellCheck __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISpellCheck __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISpellCheck __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckWord )( 
            ISpellCheck __RPC_FAR * This,
            /* [string][in] */ WCHAR __RPC_FAR *pWord,
            /* [out] */ WCHAR __RPC_FAR pWordOut[ 32 ]);
        
        END_INTERFACE
    } ISpellCheckVtbl;

    interface ISpellCheck
    {
        CONST_VTBL struct ISpellCheckVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpellCheck_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpellCheck_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpellCheck_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpellCheck_CheckWord(This,pWord,pWordOut)	\
    (This)->lpVtbl -> CheckWord(This,pWord,pWordOut)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISpellCheck_CheckWord_Proxy( 
    ISpellCheck __RPC_FAR * This,
    /* [string][in] */ WCHAR __RPC_FAR *pWord,
    /* [out] */ WCHAR __RPC_FAR pWordOut[ 32 ]);


void __RPC_STUB ISpellCheck_CheckWord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpellCheck_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
