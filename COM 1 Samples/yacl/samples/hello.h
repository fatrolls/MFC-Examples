/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Mon Mar 31 02:21:48 1997
 */
/* Compiler settings for hello.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __hello_h__
#define __hello_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IHello_FWD_DEFINED__
#define __IHello_FWD_DEFINED__
typedef interface IHello IHello;
#endif 	/* __IHello_FWD_DEFINED__ */


#ifndef __IAnimal_FWD_DEFINED__
#define __IAnimal_FWD_DEFINED__
typedef interface IAnimal IAnimal;
#endif 	/* __IAnimal_FWD_DEFINED__ */


#ifndef __IDog_FWD_DEFINED__
#define __IDog_FWD_DEFINED__
typedef interface IDog IDog;
#endif 	/* __IDog_FWD_DEFINED__ */


#ifndef __ICat_FWD_DEFINED__
#define __ICat_FWD_DEFINED__
typedef interface ICat ICat;
#endif 	/* __ICat_FWD_DEFINED__ */


#ifndef __IPug_FWD_DEFINED__
#define __IPug_FWD_DEFINED__
typedef interface IPug IPug;
#endif 	/* __IPug_FWD_DEFINED__ */


#ifndef __IOldPug_FWD_DEFINED__
#define __IOldPug_FWD_DEFINED__
typedef interface IOldPug IOldPug;
#endif 	/* __IOldPug_FWD_DEFINED__ */


#ifndef __Hello_FWD_DEFINED__
#define __Hello_FWD_DEFINED__

#ifdef __cplusplus
typedef class Hello Hello;
#else
typedef struct Hello Hello;
#endif /* __cplusplus */

#endif 	/* __Hello_FWD_DEFINED__ */


#ifndef __Goodbye_FWD_DEFINED__
#define __Goodbye_FWD_DEFINED__

#ifdef __cplusplus
typedef class Goodbye Goodbye;
#else
typedef struct Goodbye Goodbye;
#endif /* __cplusplus */

#endif 	/* __Goodbye_FWD_DEFINED__ */


#ifndef __SoLong_FWD_DEFINED__
#define __SoLong_FWD_DEFINED__

#ifdef __cplusplus
typedef class SoLong SoLong;
#else
typedef struct SoLong SoLong;
#endif /* __cplusplus */

#endif 	/* __SoLong_FWD_DEFINED__ */


#ifndef __OldPugCat_FWD_DEFINED__
#define __OldPugCat_FWD_DEFINED__

#ifdef __cplusplus
typedef class OldPugCat OldPugCat;
#else
typedef struct OldPugCat OldPugCat;
#endif /* __cplusplus */

#endif 	/* __OldPugCat_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __HelloLib_LIBRARY_DEFINED__
#define __HelloLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: HelloLib
 * at Mon Mar 31 02:21:48 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_HelloLib;

#ifndef __IHello_INTERFACE_DEFINED__
#define __IHello_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IHello
 * at Mon Mar 31 02:21:48 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][oleautomation][object] */ 



EXTERN_C const IID IID_IHello;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("DABA24E1-A38F-11d0-8C2F-0080C73925BA")
    IHello : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE HelloWorld( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHelloVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHello __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHello __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHello __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HelloWorld )( 
            IHello __RPC_FAR * This);
        
        END_INTERFACE
    } IHelloVtbl;

    interface IHello
    {
        CONST_VTBL struct IHelloVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHello_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHello_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHello_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHello_HelloWorld(This)	\
    (This)->lpVtbl -> HelloWorld(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHello_HelloWorld_Proxy( 
    IHello __RPC_FAR * This);


void __RPC_STUB IHello_HelloWorld_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHello_INTERFACE_DEFINED__ */


#ifndef __IAnimal_INTERFACE_DEFINED__
#define __IAnimal_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAnimal
 * at Mon Mar 31 02:21:48 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][oleautomation][object] */ 



EXTERN_C const IID IID_IAnimal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("DABA24E2-A38F-11d0-8C2F-0080C73925BA")
    IAnimal : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Eat( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAnimalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAnimal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAnimal __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAnimal __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Eat )( 
            IAnimal __RPC_FAR * This);
        
        END_INTERFACE
    } IAnimalVtbl;

    interface IAnimal
    {
        CONST_VTBL struct IAnimalVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAnimal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAnimal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAnimal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAnimal_Eat(This)	\
    (This)->lpVtbl -> Eat(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAnimal_Eat_Proxy( 
    IAnimal __RPC_FAR * This);


void __RPC_STUB IAnimal_Eat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAnimal_INTERFACE_DEFINED__ */


#ifndef __IDog_INTERFACE_DEFINED__
#define __IDog_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDog
 * at Mon Mar 31 02:21:48 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][oleautomation][object] */ 



EXTERN_C const IID IID_IDog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("DABA24E3-A38F-11d0-8C2F-0080C73925BA")
    IDog : public IAnimal
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Bark( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDog __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDog __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDog __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Eat )( 
            IDog __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Bark )( 
            IDog __RPC_FAR * This);
        
        END_INTERFACE
    } IDogVtbl;

    interface IDog
    {
        CONST_VTBL struct IDogVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDog_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDog_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDog_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDog_Eat(This)	\
    (This)->lpVtbl -> Eat(This)


#define IDog_Bark(This)	\
    (This)->lpVtbl -> Bark(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDog_Bark_Proxy( 
    IDog __RPC_FAR * This);


void __RPC_STUB IDog_Bark_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDog_INTERFACE_DEFINED__ */


#ifndef __ICat_INTERFACE_DEFINED__
#define __ICat_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICat
 * at Mon Mar 31 02:21:48 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][oleautomation][object] */ 



EXTERN_C const IID IID_ICat;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("DABA24E4-A38F-11d0-8C2F-0080C73925BA")
    ICat : public IAnimal
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IgnoreMaster( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICatVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICat __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICat __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICat __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Eat )( 
            ICat __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IgnoreMaster )( 
            ICat __RPC_FAR * This);
        
        END_INTERFACE
    } ICatVtbl;

    interface ICat
    {
        CONST_VTBL struct ICatVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICat_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICat_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICat_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICat_Eat(This)	\
    (This)->lpVtbl -> Eat(This)


#define ICat_IgnoreMaster(This)	\
    (This)->lpVtbl -> IgnoreMaster(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICat_IgnoreMaster_Proxy( 
    ICat __RPC_FAR * This);


void __RPC_STUB ICat_IgnoreMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICat_INTERFACE_DEFINED__ */


#ifndef __IPug_INTERFACE_DEFINED__
#define __IPug_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPug
 * at Mon Mar 31 02:21:48 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][oleautomation][object] */ 



EXTERN_C const IID IID_IPug;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("DABA24E5-A38F-11d0-8C2F-0080C73925BA")
    IPug : public IDog
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Snore( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPugVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPug __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPug __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPug __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Eat )( 
            IPug __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Bark )( 
            IPug __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Snore )( 
            IPug __RPC_FAR * This);
        
        END_INTERFACE
    } IPugVtbl;

    interface IPug
    {
        CONST_VTBL struct IPugVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPug_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPug_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPug_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPug_Eat(This)	\
    (This)->lpVtbl -> Eat(This)


#define IPug_Bark(This)	\
    (This)->lpVtbl -> Bark(This)


#define IPug_Snore(This)	\
    (This)->lpVtbl -> Snore(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPug_Snore_Proxy( 
    IPug __RPC_FAR * This);


void __RPC_STUB IPug_Snore_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPug_INTERFACE_DEFINED__ */


#ifndef __IOldPug_INTERFACE_DEFINED__
#define __IOldPug_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IOldPug
 * at Mon Mar 31 02:21:48 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][oleautomation][object] */ 



EXTERN_C const IID IID_IOldPug;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("DABA24E6-A38F-11d0-8C2F-0080C73925BA")
    IOldPug : public IPug
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SnoreLoudly( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOldPugVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IOldPug __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IOldPug __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IOldPug __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Eat )( 
            IOldPug __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Bark )( 
            IOldPug __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Snore )( 
            IOldPug __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SnoreLoudly )( 
            IOldPug __RPC_FAR * This);
        
        END_INTERFACE
    } IOldPugVtbl;

    interface IOldPug
    {
        CONST_VTBL struct IOldPugVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOldPug_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IOldPug_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IOldPug_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IOldPug_Eat(This)	\
    (This)->lpVtbl -> Eat(This)


#define IOldPug_Bark(This)	\
    (This)->lpVtbl -> Bark(This)


#define IOldPug_Snore(This)	\
    (This)->lpVtbl -> Snore(This)


#define IOldPug_SnoreLoudly(This)	\
    (This)->lpVtbl -> SnoreLoudly(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IOldPug_SnoreLoudly_Proxy( 
    IOldPug __RPC_FAR * This);


void __RPC_STUB IOldPug_SnoreLoudly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOldPug_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Hello;

class DECLSPEC_UUID("DABA24E7-A38F-11d0-8C2F-0080C73925BA")
Hello;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Goodbye;

class DECLSPEC_UUID("DABA24E9-A38F-11d0-8C2F-0080C73925BA")
Goodbye;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_SoLong;

class DECLSPEC_UUID("DABA24EA-A38F-11d0-8C2F-0080C73925BA")
SoLong;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_OldPugCat;

class DECLSPEC_UUID("DABA24E8-A38F-11d0-8C2F-0080C73925BA")
OldPugCat;
#endif
#endif /* __HelloLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
