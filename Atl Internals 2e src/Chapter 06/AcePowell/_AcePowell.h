

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Jun 21 14:52:35 2012
 */
/* Compiler settings for _AcePowell.idl:
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

#ifndef ___AcePowell_h__
#define ___AcePowell_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICowboy_FWD_DEFINED__
#define __ICowboy_FWD_DEFINED__
typedef interface ICowboy ICowboy;
#endif 	/* __ICowboy_FWD_DEFINED__ */


#ifndef __IArtist_FWD_DEFINED__
#define __IArtist_FWD_DEFINED__
typedef interface IArtist IArtist;
#endif 	/* __IArtist_FWD_DEFINED__ */


#ifndef __CAcePowell_FWD_DEFINED__
#define __CAcePowell_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAcePowell CAcePowell;
#else
typedef struct CAcePowell CAcePowell;
#endif /* __cplusplus */

#endif 	/* __CAcePowell_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICowboy_INTERFACE_DEFINED__
#define __ICowboy_INTERFACE_DEFINED__

/* interface ICowboy */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICowboy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("251DF313-37DE-445C-8115-AFC550B812AA")
    ICowboy : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Draw( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICowboyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICowboy * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICowboy * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICowboy * This);
        
        HRESULT ( STDMETHODCALLTYPE *Draw )( 
            ICowboy * This);
        
        END_INTERFACE
    } ICowboyVtbl;

    interface ICowboy
    {
        CONST_VTBL struct ICowboyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICowboy_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICowboy_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICowboy_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICowboy_Draw(This)	\
    ( (This)->lpVtbl -> Draw(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICowboy_INTERFACE_DEFINED__ */


#ifndef __IArtist_INTERFACE_DEFINED__
#define __IArtist_INTERFACE_DEFINED__

/* interface IArtist */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IArtist;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C78F9C90-F937-4CD5-B737-B9AE2B1BC42D")
    IArtist : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Draw( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IArtistVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IArtist * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IArtist * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IArtist * This);
        
        HRESULT ( STDMETHODCALLTYPE *Draw )( 
            IArtist * This);
        
        END_INTERFACE
    } IArtistVtbl;

    interface IArtist
    {
        CONST_VTBL struct IArtistVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IArtist_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IArtist_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IArtist_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IArtist_Draw(This)	\
    ( (This)->lpVtbl -> Draw(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IArtist_INTERFACE_DEFINED__ */



#ifndef __AcePowell_LIBRARY_DEFINED__
#define __AcePowell_LIBRARY_DEFINED__

/* library AcePowell */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_AcePowell;

EXTERN_C const CLSID CLSID_CAcePowell;

#ifdef __cplusplus

class DECLSPEC_UUID("17287156-31BC-4C50-8FFD-40DE67B02BA2")
CAcePowell;
#endif
#endif /* __AcePowell_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


