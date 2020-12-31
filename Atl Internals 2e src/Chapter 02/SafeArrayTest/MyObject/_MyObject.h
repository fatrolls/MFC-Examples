

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Jun 21 10:24:31 2012
 */
/* Compiler settings for _MyObject.idl:
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

#ifndef ___MyObject_h__
#define ___MyObject_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITestObject_FWD_DEFINED__
#define __ITestObject_FWD_DEFINED__
typedef interface ITestObject ITestObject;
#endif 	/* __ITestObject_FWD_DEFINED__ */


#ifndef __CTestObject_FWD_DEFINED__
#define __CTestObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CTestObject CTestObject;
#else
typedef struct CTestObject CTestObject;
#endif /* __cplusplus */

#endif 	/* __CTestObject_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ITestObject_INTERFACE_DEFINED__
#define __ITestObject_INTERFACE_DEFINED__

/* interface ITestObject */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITestObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5D8C02D0-11EC-47C2-8468-BD1909A1627A")
    ITestObject : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetArray( 
            /* [retval][out] */ SAFEARRAY * *myArray) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITestObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITestObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITestObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITestObject * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetArray )( 
            ITestObject * This,
            /* [retval][out] */ SAFEARRAY * *myArray);
        
        END_INTERFACE
    } ITestObjectVtbl;

    interface ITestObject
    {
        CONST_VTBL struct ITestObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITestObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITestObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITestObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITestObject_GetArray(This,myArray)	\
    ( (This)->lpVtbl -> GetArray(This,myArray) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITestObject_INTERFACE_DEFINED__ */



#ifndef __MyObject_LIBRARY_DEFINED__
#define __MyObject_LIBRARY_DEFINED__

/* library MyObject */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_MyObject;

EXTERN_C const CLSID CLSID_CTestObject;

#ifdef __cplusplus

class DECLSPEC_UUID("2B70187A-8E12-4DDC-BE8D-1A5A151D698F")
CTestObject;
#endif
#endif /* __MyObject_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


