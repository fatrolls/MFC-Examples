/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.76 */
/* at Sun Jun 01 23:10:55 1997
 */
/* Compiler settings for RectPoint.idl:
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

#ifndef __RectPoint_h__
#define __RectPoint_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPoint_FWD_DEFINED__
#define __IPoint_FWD_DEFINED__
typedef interface IPoint IPoint;
#endif 	/* __IPoint_FWD_DEFINED__ */


#ifndef __IRect_FWD_DEFINED__
#define __IRect_FWD_DEFINED__
typedef interface IRect IRect;
#endif 	/* __IRect_FWD_DEFINED__ */


#ifndef __Point_FWD_DEFINED__
#define __Point_FWD_DEFINED__

#ifdef __cplusplus
typedef class Point Point;
#else
typedef struct Point Point;
#endif /* __cplusplus */

#endif 	/* __Point_FWD_DEFINED__ */


#ifndef __Rect_FWD_DEFINED__
#define __Rect_FWD_DEFINED__

#ifdef __cplusplus
typedef class Rect Rect;
#else
typedef struct Rect Rect;
#endif /* __cplusplus */

#endif 	/* __Rect_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IPoint_INTERFACE_DEFINED__
#define __IPoint_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPoint
 * at Sun Jun 01 23:10:55 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][oleautomation][uuid][object] */ 



EXTERN_C const IID IID_IPoint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("CCA7F35D-DAF3-11D0-8C53-0080C73925BA")
    IPoint : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCoords( 
            /* [out] */ long __RPC_FAR *px,
            /* [out] */ long __RPC_FAR *py) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCoords( 
            /* [in] */ long x,
            /* [in] */ long y) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPoint __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPoint __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPoint __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCoords )( 
            IPoint __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *px,
            /* [out] */ long __RPC_FAR *py);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCoords )( 
            IPoint __RPC_FAR * This,
            /* [in] */ long x,
            /* [in] */ long y);
        
        END_INTERFACE
    } IPointVtbl;

    interface IPoint
    {
        CONST_VTBL struct IPointVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoint_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPoint_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPoint_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPoint_GetCoords(This,px,py)	\
    (This)->lpVtbl -> GetCoords(This,px,py)

#define IPoint_SetCoords(This,x,y)	\
    (This)->lpVtbl -> SetCoords(This,x,y)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPoint_GetCoords_Proxy( 
    IPoint __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *px,
    /* [out] */ long __RPC_FAR *py);


void __RPC_STUB IPoint_GetCoords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPoint_SetCoords_Proxy( 
    IPoint __RPC_FAR * This,
    /* [in] */ long x,
    /* [in] */ long y);


void __RPC_STUB IPoint_SetCoords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPoint_INTERFACE_DEFINED__ */


#ifndef __IRect_INTERFACE_DEFINED__
#define __IRect_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRect
 * at Sun Jun 01 23:10:55 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][oleautomation][uuid][object] */ 



EXTERN_C const IID IID_IRect;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("CCA7F35F-DAF3-11D0-8C53-0080C73925BA")
    IRect : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCoords( 
            /* [in] */ long left,
            /* [in] */ long top,
            /* [in] */ long right,
            /* [in] */ long bottom) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Volume( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRect __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRect __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRect __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCoords )( 
            IRect __RPC_FAR * This,
            /* [in] */ long left,
            /* [in] */ long top,
            /* [in] */ long right,
            /* [in] */ long bottom);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Volume )( 
            IRect __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } IRectVtbl;

    interface IRect
    {
        CONST_VTBL struct IRectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRect_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRect_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRect_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRect_SetCoords(This,left,top,right,bottom)	\
    (This)->lpVtbl -> SetCoords(This,left,top,right,bottom)

#define IRect_get_Volume(This,pVal)	\
    (This)->lpVtbl -> get_Volume(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRect_SetCoords_Proxy( 
    IRect __RPC_FAR * This,
    /* [in] */ long left,
    /* [in] */ long top,
    /* [in] */ long right,
    /* [in] */ long bottom);


void __RPC_STUB IRect_SetCoords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IRect_get_Volume_Proxy( 
    IRect __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IRect_get_Volume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRect_INTERFACE_DEFINED__ */



#ifndef __RECTPOINTLib_LIBRARY_DEFINED__
#define __RECTPOINTLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: RECTPOINTLib
 * at Sun Jun 01 23:10:55 1997
 * using MIDL 3.01.76
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_RECTPOINTLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Point;

class DECLSPEC_UUID("CCA7F35E-DAF3-11D0-8C53-0080C73925BA")
Point;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Rect;

class DECLSPEC_UUID("CCA7F360-DAF3-11D0-8C53-0080C73925BA")
Rect;
#endif
#endif /* __RECTPOINTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
