

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Wed Mar 14 15:40:43 2007
 */
/* Compiler settings for .\ChartATL.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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

#ifndef __ChartATL_h__
#define __ChartATL_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IChartCtrl_FWD_DEFINED__
#define __IChartCtrl_FWD_DEFINED__
typedef interface IChartCtrl IChartCtrl;
#endif 	/* __IChartCtrl_FWD_DEFINED__ */


#ifndef __ChartCtrl_FWD_DEFINED__
#define __ChartCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class ChartCtrl ChartCtrl;
#else
typedef struct ChartCtrl ChartCtrl;
#endif /* __cplusplus */

#endif 	/* __ChartCtrl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_ChartATL_0000 */
/* [local] */ 

typedef /* [public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_ChartATL_0000_0001
    {	L_SOLID	= 0,
	L_DASH	= 1,
	L_DOT	= 2,
	L_DASHDOT	= 3,
	L_DASHDOTDOT	= 4,
	L_EMPTY	= 5,
	L_INSIDEFRAME	= 6,
	L_USERSTYLE	= 7
    } 	PenStyle;

typedef /* [public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_ChartATL_0000_0002
    {	B_SOLID	= 0,
	B_EMPTY	= 1,
	B_HOLLOW	= 2,
	B_HATCHED	= 3,
	B_PATTERN	= 4,
	B_INDEXED	= 5,
	B_DIBPATTERN	= 6,
	B_DIBPATTERNPT	= 7,
	B_PATTERN8X8	= 8,
	B_DIBPATTERN8X8	= 9,
	B_MONOPATTERN	= 10
    } 	BrushStyle;



extern RPC_IF_HANDLE __MIDL_itf_ChartATL_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ChartATL_0000_v0_0_s_ifspec;

#ifndef __IChartCtrl_INTERFACE_DEFINED__
#define __IChartCtrl_INTERFACE_DEFINED__

/* interface IChartCtrl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IChartCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1DE9333C-3301-4EF4-8F44-01559B4195E3")
    IChartCtrl : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VerticalLineStyle( 
            /* [retval][out] */ PenStyle *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VerticalLineStyle( 
            /* [in] */ PenStyle newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VerticalLineColor( 
            /* [retval][out] */ OLE_COLOR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VerticalLineColor( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HorizontalLineColor( 
            /* [retval][out] */ OLE_COLOR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HorizontalLineColor( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ChartColor_1( 
            /* [retval][out] */ OLE_COLOR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ChartColor_1( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ChartColor_2( 
            /* [retval][out] */ OLE_COLOR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ChartColor_2( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ChartFillStyle_1( 
            /* [retval][out] */ BrushStyle *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ChartFillStyle_1( 
            /* [in] */ BrushStyle newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ChartFillStyle_2( 
            /* [retval][out] */ BrushStyle *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ChartFillStyle_2( 
            /* [in] */ BrushStyle newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateChart( 
            /* [in] */ USHORT ChartValue1,
            USHORT ChartValue2) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HorizontalLineStyle( 
            /* [retval][out] */ PenStyle *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HorizontalLineStyle( 
            /* [in] */ PenStyle newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RefreshSpeed( 
            /* [retval][out] */ USHORT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RefreshSpeed( 
            /* [in] */ USHORT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IChartCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IChartCtrl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IChartCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IChartCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IChartCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IChartCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IChartCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IChartCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IChartCtrl * This,
            /* [retval][out] */ OLE_COLOR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IChartCtrl * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VerticalLineStyle )( 
            IChartCtrl * This,
            /* [retval][out] */ PenStyle *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VerticalLineStyle )( 
            IChartCtrl * This,
            /* [in] */ PenStyle newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VerticalLineColor )( 
            IChartCtrl * This,
            /* [retval][out] */ OLE_COLOR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VerticalLineColor )( 
            IChartCtrl * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HorizontalLineColor )( 
            IChartCtrl * This,
            /* [retval][out] */ OLE_COLOR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HorizontalLineColor )( 
            IChartCtrl * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChartColor_1 )( 
            IChartCtrl * This,
            /* [retval][out] */ OLE_COLOR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ChartColor_1 )( 
            IChartCtrl * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChartColor_2 )( 
            IChartCtrl * This,
            /* [retval][out] */ OLE_COLOR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ChartColor_2 )( 
            IChartCtrl * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChartFillStyle_1 )( 
            IChartCtrl * This,
            /* [retval][out] */ BrushStyle *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ChartFillStyle_1 )( 
            IChartCtrl * This,
            /* [in] */ BrushStyle newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChartFillStyle_2 )( 
            IChartCtrl * This,
            /* [retval][out] */ BrushStyle *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ChartFillStyle_2 )( 
            IChartCtrl * This,
            /* [in] */ BrushStyle newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateChart )( 
            IChartCtrl * This,
            /* [in] */ USHORT ChartValue1,
            USHORT ChartValue2);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HorizontalLineStyle )( 
            IChartCtrl * This,
            /* [retval][out] */ PenStyle *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HorizontalLineStyle )( 
            IChartCtrl * This,
            /* [in] */ PenStyle newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RefreshSpeed )( 
            IChartCtrl * This,
            /* [retval][out] */ USHORT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RefreshSpeed )( 
            IChartCtrl * This,
            /* [in] */ USHORT newVal);
        
        END_INTERFACE
    } IChartCtrlVtbl;

    interface IChartCtrl
    {
        CONST_VTBL struct IChartCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IChartCtrl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IChartCtrl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IChartCtrl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IChartCtrl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IChartCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IChartCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IChartCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IChartCtrl_get_BackColor(This,pVal)	\
    (This)->lpVtbl -> get_BackColor(This,pVal)

#define IChartCtrl_put_BackColor(This,newVal)	\
    (This)->lpVtbl -> put_BackColor(This,newVal)

#define IChartCtrl_get_VerticalLineStyle(This,pVal)	\
    (This)->lpVtbl -> get_VerticalLineStyle(This,pVal)

#define IChartCtrl_put_VerticalLineStyle(This,newVal)	\
    (This)->lpVtbl -> put_VerticalLineStyle(This,newVal)

#define IChartCtrl_get_VerticalLineColor(This,pVal)	\
    (This)->lpVtbl -> get_VerticalLineColor(This,pVal)

#define IChartCtrl_put_VerticalLineColor(This,newVal)	\
    (This)->lpVtbl -> put_VerticalLineColor(This,newVal)

#define IChartCtrl_get_HorizontalLineColor(This,pVal)	\
    (This)->lpVtbl -> get_HorizontalLineColor(This,pVal)

#define IChartCtrl_put_HorizontalLineColor(This,newVal)	\
    (This)->lpVtbl -> put_HorizontalLineColor(This,newVal)

#define IChartCtrl_get_ChartColor_1(This,pVal)	\
    (This)->lpVtbl -> get_ChartColor_1(This,pVal)

#define IChartCtrl_put_ChartColor_1(This,newVal)	\
    (This)->lpVtbl -> put_ChartColor_1(This,newVal)

#define IChartCtrl_get_ChartColor_2(This,pVal)	\
    (This)->lpVtbl -> get_ChartColor_2(This,pVal)

#define IChartCtrl_put_ChartColor_2(This,newVal)	\
    (This)->lpVtbl -> put_ChartColor_2(This,newVal)

#define IChartCtrl_get_ChartFillStyle_1(This,pVal)	\
    (This)->lpVtbl -> get_ChartFillStyle_1(This,pVal)

#define IChartCtrl_put_ChartFillStyle_1(This,newVal)	\
    (This)->lpVtbl -> put_ChartFillStyle_1(This,newVal)

#define IChartCtrl_get_ChartFillStyle_2(This,pVal)	\
    (This)->lpVtbl -> get_ChartFillStyle_2(This,pVal)

#define IChartCtrl_put_ChartFillStyle_2(This,newVal)	\
    (This)->lpVtbl -> put_ChartFillStyle_2(This,newVal)

#define IChartCtrl_UpdateChart(This,ChartValue1,ChartValue2)	\
    (This)->lpVtbl -> UpdateChart(This,ChartValue1,ChartValue2)

#define IChartCtrl_get_HorizontalLineStyle(This,pVal)	\
    (This)->lpVtbl -> get_HorizontalLineStyle(This,pVal)

#define IChartCtrl_put_HorizontalLineStyle(This,newVal)	\
    (This)->lpVtbl -> put_HorizontalLineStyle(This,newVal)

#define IChartCtrl_get_RefreshSpeed(This,pVal)	\
    (This)->lpVtbl -> get_RefreshSpeed(This,pVal)

#define IChartCtrl_put_RefreshSpeed(This,newVal)	\
    (This)->lpVtbl -> put_RefreshSpeed(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IChartCtrl_get_BackColor_Proxy( 
    IChartCtrl * This,
    /* [retval][out] */ OLE_COLOR *pVal);


void __RPC_STUB IChartCtrl_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IChartCtrl_put_BackColor_Proxy( 
    IChartCtrl * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IChartCtrl_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IChartCtrl_get_VerticalLineStyle_Proxy( 
    IChartCtrl * This,
    /* [retval][out] */ PenStyle *pVal);


void __RPC_STUB IChartCtrl_get_VerticalLineStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IChartCtrl_put_VerticalLineStyle_Proxy( 
    IChartCtrl * This,
    /* [in] */ PenStyle newVal);


void __RPC_STUB IChartCtrl_put_VerticalLineStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IChartCtrl_get_VerticalLineColor_Proxy( 
    IChartCtrl * This,
    /* [retval][out] */ OLE_COLOR *pVal);


void __RPC_STUB IChartCtrl_get_VerticalLineColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IChartCtrl_put_VerticalLineColor_Proxy( 
    IChartCtrl * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IChartCtrl_put_VerticalLineColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IChartCtrl_get_HorizontalLineColor_Proxy( 
    IChartCtrl * This,
    /* [retval][out] */ OLE_COLOR *pVal);


void __RPC_STUB IChartCtrl_get_HorizontalLineColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IChartCtrl_put_HorizontalLineColor_Proxy( 
    IChartCtrl * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IChartCtrl_put_HorizontalLineColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IChartCtrl_get_ChartColor_1_Proxy( 
    IChartCtrl * This,
    /* [retval][out] */ OLE_COLOR *pVal);


void __RPC_STUB IChartCtrl_get_ChartColor_1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IChartCtrl_put_ChartColor_1_Proxy( 
    IChartCtrl * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IChartCtrl_put_ChartColor_1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IChartCtrl_get_ChartColor_2_Proxy( 
    IChartCtrl * This,
    /* [retval][out] */ OLE_COLOR *pVal);


void __RPC_STUB IChartCtrl_get_ChartColor_2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IChartCtrl_put_ChartColor_2_Proxy( 
    IChartCtrl * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IChartCtrl_put_ChartColor_2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IChartCtrl_get_ChartFillStyle_1_Proxy( 
    IChartCtrl * This,
    /* [retval][out] */ BrushStyle *pVal);


void __RPC_STUB IChartCtrl_get_ChartFillStyle_1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IChartCtrl_put_ChartFillStyle_1_Proxy( 
    IChartCtrl * This,
    /* [in] */ BrushStyle newVal);


void __RPC_STUB IChartCtrl_put_ChartFillStyle_1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IChartCtrl_get_ChartFillStyle_2_Proxy( 
    IChartCtrl * This,
    /* [retval][out] */ BrushStyle *pVal);


void __RPC_STUB IChartCtrl_get_ChartFillStyle_2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IChartCtrl_put_ChartFillStyle_2_Proxy( 
    IChartCtrl * This,
    /* [in] */ BrushStyle newVal);


void __RPC_STUB IChartCtrl_put_ChartFillStyle_2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IChartCtrl_UpdateChart_Proxy( 
    IChartCtrl * This,
    /* [in] */ USHORT ChartValue1,
    USHORT ChartValue2);


void __RPC_STUB IChartCtrl_UpdateChart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IChartCtrl_get_HorizontalLineStyle_Proxy( 
    IChartCtrl * This,
    /* [retval][out] */ PenStyle *pVal);


void __RPC_STUB IChartCtrl_get_HorizontalLineStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IChartCtrl_put_HorizontalLineStyle_Proxy( 
    IChartCtrl * This,
    /* [in] */ PenStyle newVal);


void __RPC_STUB IChartCtrl_put_HorizontalLineStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IChartCtrl_get_RefreshSpeed_Proxy( 
    IChartCtrl * This,
    /* [retval][out] */ USHORT *pVal);


void __RPC_STUB IChartCtrl_get_RefreshSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IChartCtrl_put_RefreshSpeed_Proxy( 
    IChartCtrl * This,
    /* [in] */ USHORT newVal);


void __RPC_STUB IChartCtrl_put_RefreshSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IChartCtrl_INTERFACE_DEFINED__ */



#ifndef __ChartATLLib_LIBRARY_DEFINED__
#define __ChartATLLib_LIBRARY_DEFINED__

/* library ChartATLLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ChartATLLib;

EXTERN_C const CLSID CLSID_ChartCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("F3758FB2-1605-4A41-BBC5-E918DB0F7E36")
ChartCtrl;
#endif
#endif /* __ChartATLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


