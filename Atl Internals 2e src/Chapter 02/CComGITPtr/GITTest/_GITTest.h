

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Jun 21 10:20:55 2012
 */
/* Compiler settings for _GITTest.idl:
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

#ifndef ___GITTest_h__
#define ___GITTest_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICalc_FWD_DEFINED__
#define __ICalc_FWD_DEFINED__
typedef interface ICalc ICalc;
#endif 	/* __ICalc_FWD_DEFINED__ */


#ifndef __CCalc_FWD_DEFINED__
#define __CCalc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCalc CCalc;
#else
typedef struct CCalc CCalc;
#endif /* __cplusplus */

#endif 	/* __CCalc_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICalc_INTERFACE_DEFINED__
#define __ICalc_INTERFACE_DEFINED__

/* interface ICalc */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICalc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("296E91A9-7F72-49FA-88F7-7B3AFEE9422D")
    ICalc : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ DOUBLE Op1,
            /* [in] */ DOUBLE Op2,
            /* [retval][out] */ DOUBLE *Result) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICalcVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICalc * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICalc * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICalc * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ICalc * This,
            /* [in] */ DOUBLE Op1,
            /* [in] */ DOUBLE Op2,
            /* [retval][out] */ DOUBLE *Result);
        
        END_INTERFACE
    } ICalcVtbl;

    interface ICalc
    {
        CONST_VTBL struct ICalcVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICalc_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICalc_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICalc_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICalc_Add(This,Op1,Op2,Result)	\
    ( (This)->lpVtbl -> Add(This,Op1,Op2,Result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICalc_INTERFACE_DEFINED__ */



#ifndef __GITTest_LIBRARY_DEFINED__
#define __GITTest_LIBRARY_DEFINED__

/* library GITTest */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_GITTest;

EXTERN_C const CLSID CLSID_CCalc;

#ifdef __cplusplus

class DECLSPEC_UUID("10AFDDFC-CBD6-4072-9065-D89D88028444")
CCalc;
#endif
#endif /* __GITTest_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


