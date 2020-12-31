

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Jun 26 14:29:37 2012
 */
/* Compiler settings for SourceComp.odl:
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


#ifndef __SourceComp_h_h__
#define __SourceComp_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISourceObj_FWD_DEFINED__
#define __ISourceObj_FWD_DEFINED__
typedef interface ISourceObj ISourceObj;
#endif 	/* __ISourceObj_FWD_DEFINED__ */


#ifndef __IEventSet_FWD_DEFINED__
#define __IEventSet_FWD_DEFINED__
typedef interface IEventSet IEventSet;
#endif 	/* __IEventSet_FWD_DEFINED__ */


#ifndef __SourceObj_FWD_DEFINED__
#define __SourceObj_FWD_DEFINED__

#ifdef __cplusplus
typedef class SourceObj SourceObj;
#else
typedef struct SourceObj SourceObj;
#endif /* __cplusplus */

#endif 	/* __SourceObj_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __SourceComp_LIBRARY_DEFINED__
#define __SourceComp_LIBRARY_DEFINED__

/* library SourceComp */
/* [version][uuid] */ 


DEFINE_GUID(LIBID_SourceComp,0xB77C2977,0x56DD,0x11CF,0xB3,0x55,0x00,0x10,0x4B,0x08,0xCC,0x22);

#ifndef __ISourceObj_DISPINTERFACE_DEFINED__
#define __ISourceObj_DISPINTERFACE_DEFINED__

/* dispinterface ISourceObj */
/* [uuid] */ 


DEFINE_GUID(DIID_ISourceObj,0xB77C2984,0x56DD,0x11CF,0xB3,0x55,0x00,0x10,0x4B,0x08,0xCC,0x22);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B77C2984-56DD-11CF-B355-00104B08CC22")
    ISourceObj : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ISourceObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISourceObj * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISourceObj * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISourceObj * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISourceObj * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISourceObj * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISourceObj * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISourceObj * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ISourceObjVtbl;

    interface ISourceObj
    {
        CONST_VTBL struct ISourceObjVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISourceObj_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISourceObj_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISourceObj_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISourceObj_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISourceObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISourceObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISourceObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ISourceObj_DISPINTERFACE_DEFINED__ */


#ifndef __IEventSet_DISPINTERFACE_DEFINED__
#define __IEventSet_DISPINTERFACE_DEFINED__

/* dispinterface IEventSet */
/* [uuid] */ 


DEFINE_GUID(DIID_IEventSet,0xB77C2985,0x56DD,0x11CF,0xB3,0x55,0x00,0x10,0x4B,0x08,0xCC,0x22);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B77C2985-56DD-11CF-B355-00104B08CC22")
    IEventSet : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IEventSetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEventSet * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEventSet * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEventSet * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IEventSet * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IEventSet * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IEventSet * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IEventSet * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IEventSetVtbl;

    interface IEventSet
    {
        CONST_VTBL struct IEventSetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEventSet_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEventSet_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEventSet_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEventSet_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IEventSet_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IEventSet_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IEventSet_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IEventSet_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_SourceObj,0xB77C2986,0x56DD,0x11CF,0xB3,0x55,0x00,0x10,0x4B,0x08,0xCC,0x22);

#ifdef __cplusplus

class DECLSPEC_UUID("B77C2986-56DD-11CF-B355-00104B08CC22")
SourceObj;
#endif
#endif /* __SourceComp_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


