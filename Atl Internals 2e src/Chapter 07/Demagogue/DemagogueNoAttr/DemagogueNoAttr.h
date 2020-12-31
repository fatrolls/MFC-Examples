

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Jun 21 14:50:07 2012
 */
/* Compiler settings for DemagogueNoAttr.idl:
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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DemagogueNoAttr_h__
#define __DemagogueNoAttr_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDemagogue_FWD_DEFINED__
#define __IDemagogue_FWD_DEFINED__
typedef interface IDemagogue IDemagogue;
#endif 	/* __IDemagogue_FWD_DEFINED__ */


#ifndef __Demagogue_FWD_DEFINED__
#define __Demagogue_FWD_DEFINED__

#ifdef __cplusplus
typedef class Demagogue Demagogue;
#else
typedef struct Demagogue Demagogue;
#endif /* __cplusplus */

#endif 	/* __Demagogue_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IDemagogue_INTERFACE_DEFINED__
#define __IDemagogue_INTERFACE_DEFINED__

/* interface IDemagogue */
/* [unique][helpstring][nonextensible][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDemagogue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("780AB26F-32EA-4E2D-B54B-E025ABDF7CDF")
    IDemagogue : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Volume( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Volume( 
            /* [in] */ DOUBLE newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDemagogueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDemagogue * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDemagogue * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDemagogue * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Volume )( 
            IDemagogue * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Volume )( 
            IDemagogue * This,
            /* [in] */ DOUBLE newVal);
        
        END_INTERFACE
    } IDemagogueVtbl;

    interface IDemagogue
    {
        CONST_VTBL struct IDemagogueVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDemagogue_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDemagogue_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDemagogue_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDemagogue_get_Volume(This,pVal)	\
    ( (This)->lpVtbl -> get_Volume(This,pVal) ) 

#define IDemagogue_put_Volume(This,newVal)	\
    ( (This)->lpVtbl -> put_Volume(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDemagogue_INTERFACE_DEFINED__ */



#ifndef __DemagogueNoAttrLib_LIBRARY_DEFINED__
#define __DemagogueNoAttrLib_LIBRARY_DEFINED__

/* library DemagogueNoAttrLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DemagogueNoAttrLib;

EXTERN_C const CLSID CLSID_Demagogue;

#ifdef __cplusplus

class DECLSPEC_UUID("F0861CE5-B86C-4214-997B-3E9AF6020316")
Demagogue;
#endif
#endif /* __DemagogueNoAttrLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


