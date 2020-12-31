

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Jun 26 14:29:27 2012
 */
/* Compiler settings for TextComp.odl:
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


#ifndef __TextComp_h_h__
#define __TextComp_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITextObject_FWD_DEFINED__
#define __ITextObject_FWD_DEFINED__
typedef interface ITextObject ITextObject;
#endif 	/* __ITextObject_FWD_DEFINED__ */


#ifndef __Object_FWD_DEFINED__
#define __Object_FWD_DEFINED__

#ifdef __cplusplus
typedef class Object Object;
#else
typedef struct Object Object;
#endif /* __cplusplus */

#endif 	/* __Object_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __TextComp_LIBRARY_DEFINED__
#define __TextComp_LIBRARY_DEFINED__

/* library TextComp */
/* [version][uuid] */ 


DEFINE_GUID(LIBID_TextComp,0x4F168D44,0xC210,0x11D2,0x9E,0x60,0x00,0x10,0x4B,0x08,0xCC,0x22);

#ifndef __ITextObject_DISPINTERFACE_DEFINED__
#define __ITextObject_DISPINTERFACE_DEFINED__

/* dispinterface ITextObject */
/* [uuid] */ 


DEFINE_GUID(DIID_ITextObject,0x4F168D56,0xC210,0x11D2,0x9E,0x60,0x00,0x10,0x4B,0x08,0xCC,0x22);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4F168D56-C210-11D2-9E60-00104B08CC22")
    ITextObject : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ITextObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITextObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITextObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITextObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITextObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITextObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITextObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITextObject * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ITextObjectVtbl;

    interface ITextObject
    {
        CONST_VTBL struct ITextObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITextObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITextObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITextObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITextObject_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITextObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITextObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITextObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ITextObject_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Object,0x4F168D57,0xC210,0x11D2,0x9E,0x60,0x00,0x10,0x4B,0x08,0xCC,0x22);

#ifdef __cplusplus

class DECLSPEC_UUID("4F168D57-C210-11D2-9E60-00104B08CC22")
Object;
#endif
#endif /* __TextComp_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


