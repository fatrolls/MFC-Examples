

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Jun 21 14:50:56 2012
 */
/* Compiler settings for _Architect.idl:
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

#ifndef ___Architect_h__
#define ___Architect_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IArchitect_FWD_DEFINED__
#define __IArchitect_FWD_DEFINED__
typedef interface IArchitect IArchitect;
#endif 	/* __IArchitect_FWD_DEFINED__ */


#ifndef __CArchitect_FWD_DEFINED__
#define __CArchitect_FWD_DEFINED__

#ifdef __cplusplus
typedef class CArchitect CArchitect;
#else
typedef struct CArchitect CArchitect;
#endif /* __cplusplus */

#endif 	/* __CArchitect_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IArchitect_INTERFACE_DEFINED__
#define __IArchitect_INTERFACE_DEFINED__

/* interface IArchitect */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IArchitect;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("09016650-D78A-41AC-81DB-078E670A131F")
    IArchitect : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Draw( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IArchitectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IArchitect * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IArchitect * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IArchitect * This);
        
        HRESULT ( STDMETHODCALLTYPE *Draw )( 
            IArchitect * This);
        
        END_INTERFACE
    } IArchitectVtbl;

    interface IArchitect
    {
        CONST_VTBL struct IArchitectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IArchitect_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IArchitect_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IArchitect_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IArchitect_Draw(This)	\
    ( (This)->lpVtbl -> Draw(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IArchitect_INTERFACE_DEFINED__ */



#ifndef __Architect_LIBRARY_DEFINED__
#define __Architect_LIBRARY_DEFINED__

/* library Architect */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_Architect;

EXTERN_C const CLSID CLSID_CArchitect;

#ifdef __cplusplus

class DECLSPEC_UUID("3F6FAEE0-E243-466E-93A3-4F5C2C388A73")
CArchitect;
#endif
#endif /* __Architect_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


