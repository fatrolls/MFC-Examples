

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Jun 18 11:03:13 2012
 */
/* Compiler settings for BullsEyeControl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


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

#ifndef __BullsEyeControl_h__
#define __BullsEyeControl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBullsEye_FWD_DEFINED__
#define __IBullsEye_FWD_DEFINED__
typedef interface IBullsEye IBullsEye;
#endif 	/* __IBullsEye_FWD_DEFINED__ */


#ifndef ___IBullsEyeEvents_FWD_DEFINED__
#define ___IBullsEyeEvents_FWD_DEFINED__
typedef interface _IBullsEyeEvents _IBullsEyeEvents;
#endif 	/* ___IBullsEyeEvents_FWD_DEFINED__ */


#ifndef __BullsEye_FWD_DEFINED__
#define __BullsEye_FWD_DEFINED__

#ifdef __cplusplus
typedef class BullsEye BullsEye;
#else
typedef struct BullsEye BullsEye;
#endif /* __cplusplus */

#endif 	/* __BullsEye_FWD_DEFINED__ */


#ifndef __BullsEyePropPage_FWD_DEFINED__
#define __BullsEyePropPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class BullsEyePropPage BullsEyePropPage;
#else
typedef struct BullsEyePropPage BullsEyePropPage;
#endif /* __cplusplus */

#endif 	/* __BullsEyePropPage_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "CategorizeProperties.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IBullsEye_INTERFACE_DEFINED__
#define __IBullsEye_INTERFACE_DEFINED__

/* interface IBullsEye */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 

#define	DISPID_ALTERNATECOLOR	( 1 )

#define	DISPID_BEEP	( 2 )

#define	DISPID_CENTERCOLOR	( 3 )

#define	DISPID_RINGCOUNT	( 4 )

#define	DISPID_RINGVALUE	( 5 )

#define	DISPID_APPLICATION	( 6 )

#define	DISPID_PARENT	( 7 )


EXTERN_C const IID IID_IBullsEye;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B4FBD008-B03D-4F48-9C5B-4A981EB6A515")
    IBullsEye : public IDispatch
    {
    public:
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_BackStyle( 
            /* [in] */ long style) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_BackStyle( 
            /* [retval][out] */ long *pstyle) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_ForeColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_ForeColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AboutBox( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DoClick( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_AlternateColor( 
            /* [retval][out] */ OLE_COLOR *pVal) = 0;
        
        virtual /* [helpstring][id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_AlternateColor( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Beep( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Beep( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_CenterColor( 
            /* [retval][out] */ OLE_COLOR *pVal) = 0;
        
        virtual /* [helpstring][id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_CenterColor( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_RingCount( 
            /* [retval][out] */ SHORT *pVal) = 0;
        
        virtual /* [helpstring][id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_RingCount( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_RingValue( 
            /* [in] */ SHORT sRingNumber,
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_RingValue( 
            /* [in] */ SHORT sRingNumber,
            /* [in] */ LONG newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBullsEyeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBullsEye * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBullsEye * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBullsEye * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBullsEye * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBullsEye * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBullsEye * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBullsEye * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IBullsEye * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IBullsEye * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackStyle )( 
            IBullsEye * This,
            /* [in] */ long style);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackStyle )( 
            IBullsEye * This,
            /* [retval][out] */ long *pstyle);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ForeColor )( 
            IBullsEye * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForeColor )( 
            IBullsEye * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IBullsEye * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IBullsEye * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AboutBox )( 
            IBullsEye * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DoClick )( 
            IBullsEye * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IBullsEye * This);
        
        /* [helpstring][id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            IBullsEye * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AlternateColor )( 
            IBullsEye * This,
            /* [retval][out] */ OLE_COLOR *pVal);
        
        /* [helpstring][id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AlternateColor )( 
            IBullsEye * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beep )( 
            IBullsEye * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Beep )( 
            IBullsEye * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CenterColor )( 
            IBullsEye * This,
            /* [retval][out] */ OLE_COLOR *pVal);
        
        /* [helpstring][id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CenterColor )( 
            IBullsEye * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            IBullsEye * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RingCount )( 
            IBullsEye * This,
            /* [retval][out] */ SHORT *pVal);
        
        /* [helpstring][id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RingCount )( 
            IBullsEye * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RingValue )( 
            IBullsEye * This,
            /* [in] */ SHORT sRingNumber,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RingValue )( 
            IBullsEye * This,
            /* [in] */ SHORT sRingNumber,
            /* [in] */ LONG newVal);
        
        END_INTERFACE
    } IBullsEyeVtbl;

    interface IBullsEye
    {
        CONST_VTBL struct IBullsEyeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBullsEye_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBullsEye_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBullsEye_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBullsEye_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBullsEye_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBullsEye_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBullsEye_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IBullsEye_put_BackColor(This,clr)	\
    ( (This)->lpVtbl -> put_BackColor(This,clr) ) 

#define IBullsEye_get_BackColor(This,pclr)	\
    ( (This)->lpVtbl -> get_BackColor(This,pclr) ) 

#define IBullsEye_put_BackStyle(This,style)	\
    ( (This)->lpVtbl -> put_BackStyle(This,style) ) 

#define IBullsEye_get_BackStyle(This,pstyle)	\
    ( (This)->lpVtbl -> get_BackStyle(This,pstyle) ) 

#define IBullsEye_put_ForeColor(This,clr)	\
    ( (This)->lpVtbl -> put_ForeColor(This,clr) ) 

#define IBullsEye_get_ForeColor(This,pclr)	\
    ( (This)->lpVtbl -> get_ForeColor(This,pclr) ) 

#define IBullsEye_put_Enabled(This,vbool)	\
    ( (This)->lpVtbl -> put_Enabled(This,vbool) ) 

#define IBullsEye_get_Enabled(This,pbool)	\
    ( (This)->lpVtbl -> get_Enabled(This,pbool) ) 

#define IBullsEye_AboutBox(This)	\
    ( (This)->lpVtbl -> AboutBox(This) ) 

#define IBullsEye_DoClick(This)	\
    ( (This)->lpVtbl -> DoClick(This) ) 

#define IBullsEye_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IBullsEye_get_Application(This,pVal)	\
    ( (This)->lpVtbl -> get_Application(This,pVal) ) 

#define IBullsEye_get_AlternateColor(This,pVal)	\
    ( (This)->lpVtbl -> get_AlternateColor(This,pVal) ) 

#define IBullsEye_put_AlternateColor(This,newVal)	\
    ( (This)->lpVtbl -> put_AlternateColor(This,newVal) ) 

#define IBullsEye_get_Beep(This,pVal)	\
    ( (This)->lpVtbl -> get_Beep(This,pVal) ) 

#define IBullsEye_put_Beep(This,newVal)	\
    ( (This)->lpVtbl -> put_Beep(This,newVal) ) 

#define IBullsEye_get_CenterColor(This,pVal)	\
    ( (This)->lpVtbl -> get_CenterColor(This,pVal) ) 

#define IBullsEye_put_CenterColor(This,newVal)	\
    ( (This)->lpVtbl -> put_CenterColor(This,newVal) ) 

#define IBullsEye_get_Parent(This,pVal)	\
    ( (This)->lpVtbl -> get_Parent(This,pVal) ) 

#define IBullsEye_get_RingCount(This,pVal)	\
    ( (This)->lpVtbl -> get_RingCount(This,pVal) ) 

#define IBullsEye_put_RingCount(This,newVal)	\
    ( (This)->lpVtbl -> put_RingCount(This,newVal) ) 

#define IBullsEye_get_RingValue(This,sRingNumber,pVal)	\
    ( (This)->lpVtbl -> get_RingValue(This,sRingNumber,pVal) ) 

#define IBullsEye_put_RingValue(This,sRingNumber,newVal)	\
    ( (This)->lpVtbl -> put_RingValue(This,sRingNumber,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBullsEye_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_BullsEyeControl_0000_0001 */
/* [local] */ 

#define	DISPID_ONRINGHIT	( 1 )

#define	DISPID_ONSCORECHANGED	( 2 )



extern RPC_IF_HANDLE __MIDL_itf_BullsEyeControl_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_BullsEyeControl_0000_0001_v0_0_s_ifspec;


#ifndef __BullsEyeControlLib_LIBRARY_DEFINED__
#define __BullsEyeControlLib_LIBRARY_DEFINED__

/* library BullsEyeControlLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_BullsEyeControlLib;

#ifndef ___IBullsEyeEvents_DISPINTERFACE_DEFINED__
#define ___IBullsEyeEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IBullsEyeEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IBullsEyeEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("58D6D8CB-765D-4C59-A41F-BBA8C40F7A14")
    _IBullsEyeEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IBullsEyeEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IBullsEyeEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IBullsEyeEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IBullsEyeEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IBullsEyeEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IBullsEyeEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IBullsEyeEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IBullsEyeEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IBullsEyeEventsVtbl;

    interface _IBullsEyeEvents
    {
        CONST_VTBL struct _IBullsEyeEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IBullsEyeEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IBullsEyeEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IBullsEyeEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IBullsEyeEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IBullsEyeEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IBullsEyeEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IBullsEyeEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IBullsEyeEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_BullsEye;

#ifdef __cplusplus

class DECLSPEC_UUID("E9312AF5-1C11-4BA4-A0C6-CB660E949B78")
BullsEye;
#endif

EXTERN_C const CLSID CLSID_BullsEyePropPage;

#ifdef __cplusplus

class DECLSPEC_UUID("47446235-8500-43a2-92A7-F0686FDAA69C")
BullsEyePropPage;
#endif
#endif /* __BullsEyeControlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


