/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Feb 01 14:11:56 2000
 */
/* Compiler settings for D:\mario\ATLNewGrid2\ATLNewGrid.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __ATLNewGrid_h__
#define __ATLNewGrid_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IGridCell_FWD_DEFINED__
#define __IGridCell_FWD_DEFINED__
typedef interface IGridCell IGridCell;
#endif 	/* __IGridCell_FWD_DEFINED__ */


#ifndef __IGrid_FWD_DEFINED__
#define __IGrid_FWD_DEFINED__
typedef interface IGrid IGrid;
#endif 	/* __IGrid_FWD_DEFINED__ */


#ifndef ___IGridEvents_FWD_DEFINED__
#define ___IGridEvents_FWD_DEFINED__
typedef interface _IGridEvents _IGridEvents;
#endif 	/* ___IGridEvents_FWD_DEFINED__ */


#ifndef __Grid_FWD_DEFINED__
#define __Grid_FWD_DEFINED__

#ifdef __cplusplus
typedef class Grid Grid;
#else
typedef struct Grid Grid;
#endif /* __cplusplus */

#endif 	/* __Grid_FWD_DEFINED__ */


#ifndef __GridCell_FWD_DEFINED__
#define __GridCell_FWD_DEFINED__

#ifdef __cplusplus
typedef class GridCell GridCell;
#else
typedef struct GridCell GridCell;
#endif /* __cplusplus */

#endif 	/* __GridCell_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __ATLNEWGRIDLib_LIBRARY_DEFINED__
#define __ATLNEWGRIDLib_LIBRARY_DEFINED__

/* library ATLNEWGRIDLib */
/* [helpstring][version][uuid] */ 

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_ATLNewGrid_0000_0001
    {	GVL_NONE	= 0,
	GVL_HORZ	= 1,
	GVL_VERT	= 2,
	GVL_BOTH	= 3
    }	grGridLines;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_ATLNewGrid_0000_0002
    {	grPictOrientationLeft	= 0,
	grPictOrientationCenter	= 1,
	grPictOrientationRight	= 2
    }	grPictOrientation;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_ATLNewGrid_0000_0003
    {	grOrizAlignLeft	= 0,
	grOrizAlignRight	= 1,
	grOrizAlignCenter	= 2
    }	grOrizontalAlignment;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_ATLNewGrid_0000_0004
    {	grVertAlignBottom	= 0,
	grVertAlignTop	= 1,
	grVertAlignCenter	= 2
    }	grVerticalAlignment;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_ATLNewGrid_0000_0005
    {	grBreakingTWNormal	= 0,
	grBreakingTWWordBreak	= 1,
	grBreakingTWEndEllipsis	= 2
    }	grBreakingTextWords;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_ATLNewGrid_0000_0006
    {	grTextSingleLine	= 0,
	grTextNoLimit	= 1
    }	grTextLine;


EXTERN_C const IID LIBID_ATLNEWGRIDLib;

#ifndef __IGridCell_INTERFACE_DEFINED__
#define __IGridCell_INTERFACE_DEFINED__

/* interface IGridCell */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGridCell;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("67C165D4-BE9B-11D3-9942-006097FEBF00")
    IGridCell : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PictureOrientation( 
            /* [retval][out] */ grPictOrientation __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_PictureOrientation( 
            /* [in] */ grPictOrientation newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Text( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Font( 
            /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Font( 
            /* [in] */ IFontDisp __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HorizontalAlignment( 
            /* [retval][out] */ grOrizontalAlignment __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HorizontalAlignment( 
            /* [in] */ grOrizontalAlignment newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VerticalAlignment( 
            /* [retval][out] */ grVerticalAlignment __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VerticalAlignment( 
            /* [in] */ grVerticalAlignment newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BreakingTextWords( 
            /* [retval][out] */ grBreakingTextWords __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BreakingTextWords( 
            /* [in] */ grBreakingTextWords newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Picture( 
            /* [retval][out] */ IPictureDisp __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Picture( 
            /* [in] */ IPictureDisp __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGridCellVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGridCell __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGridCell __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGridCell __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PictureOrientation )( 
            IGridCell __RPC_FAR * This,
            /* [retval][out] */ grPictOrientation __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PictureOrientation )( 
            IGridCell __RPC_FAR * This,
            /* [in] */ grPictOrientation newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Text )( 
            IGridCell __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Text )( 
            IGridCell __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Font )( 
            IGridCell __RPC_FAR * This,
            /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Font )( 
            IGridCell __RPC_FAR * This,
            /* [in] */ IFontDisp __RPC_FAR *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HorizontalAlignment )( 
            IGridCell __RPC_FAR * This,
            /* [retval][out] */ grOrizontalAlignment __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HorizontalAlignment )( 
            IGridCell __RPC_FAR * This,
            /* [in] */ grOrizontalAlignment newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VerticalAlignment )( 
            IGridCell __RPC_FAR * This,
            /* [retval][out] */ grVerticalAlignment __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VerticalAlignment )( 
            IGridCell __RPC_FAR * This,
            /* [in] */ grVerticalAlignment newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BreakingTextWords )( 
            IGridCell __RPC_FAR * This,
            /* [retval][out] */ grBreakingTextWords __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BreakingTextWords )( 
            IGridCell __RPC_FAR * This,
            /* [in] */ grBreakingTextWords newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Picture )( 
            IGridCell __RPC_FAR * This,
            /* [retval][out] */ IPictureDisp __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Picture )( 
            IGridCell __RPC_FAR * This,
            /* [in] */ IPictureDisp __RPC_FAR *newVal);
        
        END_INTERFACE
    } IGridCellVtbl;

    interface IGridCell
    {
        CONST_VTBL struct IGridCellVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGridCell_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGridCell_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGridCell_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGridCell_get_PictureOrientation(This,pVal)	\
    (This)->lpVtbl -> get_PictureOrientation(This,pVal)

#define IGridCell_put_PictureOrientation(This,newVal)	\
    (This)->lpVtbl -> put_PictureOrientation(This,newVal)

#define IGridCell_get_Text(This,pVal)	\
    (This)->lpVtbl -> get_Text(This,pVal)

#define IGridCell_put_Text(This,newVal)	\
    (This)->lpVtbl -> put_Text(This,newVal)

#define IGridCell_get_Font(This,pVal)	\
    (This)->lpVtbl -> get_Font(This,pVal)

#define IGridCell_put_Font(This,newVal)	\
    (This)->lpVtbl -> put_Font(This,newVal)

#define IGridCell_get_HorizontalAlignment(This,pVal)	\
    (This)->lpVtbl -> get_HorizontalAlignment(This,pVal)

#define IGridCell_put_HorizontalAlignment(This,newVal)	\
    (This)->lpVtbl -> put_HorizontalAlignment(This,newVal)

#define IGridCell_get_VerticalAlignment(This,pVal)	\
    (This)->lpVtbl -> get_VerticalAlignment(This,pVal)

#define IGridCell_put_VerticalAlignment(This,newVal)	\
    (This)->lpVtbl -> put_VerticalAlignment(This,newVal)

#define IGridCell_get_BreakingTextWords(This,pVal)	\
    (This)->lpVtbl -> get_BreakingTextWords(This,pVal)

#define IGridCell_put_BreakingTextWords(This,newVal)	\
    (This)->lpVtbl -> put_BreakingTextWords(This,newVal)

#define IGridCell_get_Picture(This,pVal)	\
    (This)->lpVtbl -> get_Picture(This,pVal)

#define IGridCell_put_Picture(This,newVal)	\
    (This)->lpVtbl -> put_Picture(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IGridCell_get_PictureOrientation_Proxy( 
    IGridCell __RPC_FAR * This,
    /* [retval][out] */ grPictOrientation __RPC_FAR *pVal);


void __RPC_STUB IGridCell_get_PictureOrientation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IGridCell_put_PictureOrientation_Proxy( 
    IGridCell __RPC_FAR * This,
    /* [in] */ grPictOrientation newVal);


void __RPC_STUB IGridCell_put_PictureOrientation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IGridCell_get_Text_Proxy( 
    IGridCell __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IGridCell_get_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IGridCell_put_Text_Proxy( 
    IGridCell __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IGridCell_put_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IGridCell_get_Font_Proxy( 
    IGridCell __RPC_FAR * This,
    /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IGridCell_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IGridCell_put_Font_Proxy( 
    IGridCell __RPC_FAR * This,
    /* [in] */ IFontDisp __RPC_FAR *newVal);


void __RPC_STUB IGridCell_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IGridCell_get_HorizontalAlignment_Proxy( 
    IGridCell __RPC_FAR * This,
    /* [retval][out] */ grOrizontalAlignment __RPC_FAR *pVal);


void __RPC_STUB IGridCell_get_HorizontalAlignment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IGridCell_put_HorizontalAlignment_Proxy( 
    IGridCell __RPC_FAR * This,
    /* [in] */ grOrizontalAlignment newVal);


void __RPC_STUB IGridCell_put_HorizontalAlignment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IGridCell_get_VerticalAlignment_Proxy( 
    IGridCell __RPC_FAR * This,
    /* [retval][out] */ grVerticalAlignment __RPC_FAR *pVal);


void __RPC_STUB IGridCell_get_VerticalAlignment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IGridCell_put_VerticalAlignment_Proxy( 
    IGridCell __RPC_FAR * This,
    /* [in] */ grVerticalAlignment newVal);


void __RPC_STUB IGridCell_put_VerticalAlignment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IGridCell_get_BreakingTextWords_Proxy( 
    IGridCell __RPC_FAR * This,
    /* [retval][out] */ grBreakingTextWords __RPC_FAR *pVal);


void __RPC_STUB IGridCell_get_BreakingTextWords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IGridCell_put_BreakingTextWords_Proxy( 
    IGridCell __RPC_FAR * This,
    /* [in] */ grBreakingTextWords newVal);


void __RPC_STUB IGridCell_put_BreakingTextWords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IGridCell_get_Picture_Proxy( 
    IGridCell __RPC_FAR * This,
    /* [retval][out] */ IPictureDisp __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IGridCell_get_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IGridCell_put_Picture_Proxy( 
    IGridCell __RPC_FAR * This,
    /* [in] */ IPictureDisp __RPC_FAR *newVal);


void __RPC_STUB IGridCell_put_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGridCell_INTERFACE_DEFINED__ */


#ifndef __IGrid_INTERFACE_DEFINED__
#define __IGrid_INTERFACE_DEFINED__

/* interface IGrid */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IGrid;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3B1CCC50-58C4-11D3-B221-006097FEBF00")
    IGrid : public IDispatch
    {
    public:
        virtual /* [id][requestedit][bindable][propputref] */ HRESULT STDMETHODCALLTYPE putref_Font( 
            /* [in] */ IFontDisp __RPC_FAR *pFont) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Font( 
            /* [in] */ IFontDisp __RPC_FAR *pFont) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Font( 
            /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *ppFont) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Image( 
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Image( 
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Text( 
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InsertRow( 
            /* [in] */ int Row,
            /* [in] */ BSTR caption) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RowCount( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RowCount( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ColumnCount( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ColumnCount( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RowHeight( 
            /* [in] */ int nRow,
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RowHeight( 
            /* [in] */ int nRow,
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ColumnWidth( 
            /* [in] */ int Col,
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ColumnWidth( 
            /* [in] */ int Col,
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CellFont( 
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CellFont( 
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [in] */ IFontDisp __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AutoSize( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ColumnResizing( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ColumnResizing( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RowResizing( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RowResizing( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GridLines( 
            /* [retval][out] */ grGridLines __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_GridLines( 
            /* [in] */ grGridLines newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Editable( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Editable( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FixedRows( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FixedRows( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FixedCols( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FixedCols( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AutosizeColumn( 
            /* [in] */ int col) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AutosizeRow( 
            /* [in] */ int row) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CellEnabled( 
            /* [in] */ int row,
            /* [in] */ int col,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CellEnabled( 
            /* [in] */ int row,
            /* [in] */ int col,
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AllowSelection( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AllowSelection( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ListMode( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ListMode( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentRow( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentRow( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentCol( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentCol( 
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteRow( 
            /* [in] */ int row) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HeaderSort( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HeaderSort( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SingleRowSelection( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SingleRowSelection( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteColumn( 
            /* [in] */ int col) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FixedBackColor( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FixedBackColor( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TextColor( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TextColor( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TextBackColor( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TextBackColor( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Color( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Color( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FixedTextColor( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FixedTextColor( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CellFgColor( 
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CellFgColor( 
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CellBgColor( 
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CellBgColor( 
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SimpleConf( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Cell( 
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [retval][out] */ IGridCell __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Cell( 
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [in] */ IGridCell __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ToolTip( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ToolTip( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectAllCells( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeepTab( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KeepTab( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGridVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGrid __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGrid __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGrid __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IGrid __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IGrid __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IGrid __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IGrid __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][requestedit][bindable][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_Font )( 
            IGrid __RPC_FAR * This,
            /* [in] */ IFontDisp __RPC_FAR *pFont);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Font )( 
            IGrid __RPC_FAR * This,
            /* [in] */ IFontDisp __RPC_FAR *pFont);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Font )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *ppFont);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BackColor )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BackColor )( 
            IGrid __RPC_FAR * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Image )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Image )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Text )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Text )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InsertRow )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Row,
            /* [in] */ BSTR caption);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RowCount )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RowCount )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColumnCount )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ColumnCount )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RowHeight )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int nRow,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RowHeight )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int nRow,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColumnWidth )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Col,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ColumnWidth )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Col,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CellFont )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CellFont )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [in] */ IFontDisp __RPC_FAR *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AutoSize )( 
            IGrid __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColumnResizing )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ColumnResizing )( 
            IGrid __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RowResizing )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RowResizing )( 
            IGrid __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GridLines )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ grGridLines __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GridLines )( 
            IGrid __RPC_FAR * This,
            /* [in] */ grGridLines newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Editable )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Editable )( 
            IGrid __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FixedRows )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FixedRows )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FixedCols )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FixedCols )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AutosizeColumn )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int col);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AutosizeRow )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int row);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CellEnabled )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CellEnabled )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AllowSelection )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AllowSelection )( 
            IGrid __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ListMode )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ListMode )( 
            IGrid __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentRow )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CurrentRow )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentCol )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CurrentCol )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteRow )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int row);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HeaderSort )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HeaderSort )( 
            IGrid __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SingleRowSelection )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SingleRowSelection )( 
            IGrid __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteColumn )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int col);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FixedBackColor )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FixedBackColor )( 
            IGrid __RPC_FAR * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TextColor )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TextColor )( 
            IGrid __RPC_FAR * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TextBackColor )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TextBackColor )( 
            IGrid __RPC_FAR * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Color )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Color )( 
            IGrid __RPC_FAR * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FixedTextColor )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FixedTextColor )( 
            IGrid __RPC_FAR * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CellFgColor )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CellFgColor )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CellBgColor )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CellBgColor )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SimpleConf )( 
            IGrid __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cell )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [retval][out] */ IGridCell __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Cell )( 
            IGrid __RPC_FAR * This,
            /* [in] */ int Row,
            /* [in] */ int Col,
            /* [in] */ IGridCell __RPC_FAR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ToolTip )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ToolTip )( 
            IGrid __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IGrid __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SelectAllCells )( 
            IGrid __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeepTab )( 
            IGrid __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeepTab )( 
            IGrid __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IGridVtbl;

    interface IGrid
    {
        CONST_VTBL struct IGridVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGrid_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGrid_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGrid_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGrid_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IGrid_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IGrid_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IGrid_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IGrid_putref_Font(This,pFont)	\
    (This)->lpVtbl -> putref_Font(This,pFont)

#define IGrid_put_Font(This,pFont)	\
    (This)->lpVtbl -> put_Font(This,pFont)

#define IGrid_get_Font(This,ppFont)	\
    (This)->lpVtbl -> get_Font(This,ppFont)

#define IGrid_get_BackColor(This,pVal)	\
    (This)->lpVtbl -> get_BackColor(This,pVal)

#define IGrid_put_BackColor(This,newVal)	\
    (This)->lpVtbl -> put_BackColor(This,newVal)

#define IGrid_get_Image(This,Row,Col,pVal)	\
    (This)->lpVtbl -> get_Image(This,Row,Col,pVal)

#define IGrid_put_Image(This,Row,Col,newVal)	\
    (This)->lpVtbl -> put_Image(This,Row,Col,newVal)

#define IGrid_get_Text(This,Row,Col,pVal)	\
    (This)->lpVtbl -> get_Text(This,Row,Col,pVal)

#define IGrid_put_Text(This,Row,Col,newVal)	\
    (This)->lpVtbl -> put_Text(This,Row,Col,newVal)

#define IGrid_InsertRow(This,Row,caption)	\
    (This)->lpVtbl -> InsertRow(This,Row,caption)

#define IGrid_get_RowCount(This,pVal)	\
    (This)->lpVtbl -> get_RowCount(This,pVal)

#define IGrid_put_RowCount(This,newVal)	\
    (This)->lpVtbl -> put_RowCount(This,newVal)

#define IGrid_get_ColumnCount(This,pVal)	\
    (This)->lpVtbl -> get_ColumnCount(This,pVal)

#define IGrid_put_ColumnCount(This,newVal)	\
    (This)->lpVtbl -> put_ColumnCount(This,newVal)

#define IGrid_get_RowHeight(This,nRow,pVal)	\
    (This)->lpVtbl -> get_RowHeight(This,nRow,pVal)

#define IGrid_put_RowHeight(This,nRow,newVal)	\
    (This)->lpVtbl -> put_RowHeight(This,nRow,newVal)

#define IGrid_get_ColumnWidth(This,Col,pVal)	\
    (This)->lpVtbl -> get_ColumnWidth(This,Col,pVal)

#define IGrid_put_ColumnWidth(This,Col,newVal)	\
    (This)->lpVtbl -> put_ColumnWidth(This,Col,newVal)

#define IGrid_get_CellFont(This,Row,Col,pVal)	\
    (This)->lpVtbl -> get_CellFont(This,Row,Col,pVal)

#define IGrid_put_CellFont(This,Row,Col,newVal)	\
    (This)->lpVtbl -> put_CellFont(This,Row,Col,newVal)

#define IGrid_AutoSize(This)	\
    (This)->lpVtbl -> AutoSize(This)

#define IGrid_get_ColumnResizing(This,pVal)	\
    (This)->lpVtbl -> get_ColumnResizing(This,pVal)

#define IGrid_put_ColumnResizing(This,newVal)	\
    (This)->lpVtbl -> put_ColumnResizing(This,newVal)

#define IGrid_get_RowResizing(This,pVal)	\
    (This)->lpVtbl -> get_RowResizing(This,pVal)

#define IGrid_put_RowResizing(This,newVal)	\
    (This)->lpVtbl -> put_RowResizing(This,newVal)

#define IGrid_get_GridLines(This,pVal)	\
    (This)->lpVtbl -> get_GridLines(This,pVal)

#define IGrid_put_GridLines(This,newVal)	\
    (This)->lpVtbl -> put_GridLines(This,newVal)

#define IGrid_get_Editable(This,pVal)	\
    (This)->lpVtbl -> get_Editable(This,pVal)

#define IGrid_put_Editable(This,newVal)	\
    (This)->lpVtbl -> put_Editable(This,newVal)

#define IGrid_get_FixedRows(This,pVal)	\
    (This)->lpVtbl -> get_FixedRows(This,pVal)

#define IGrid_put_FixedRows(This,newVal)	\
    (This)->lpVtbl -> put_FixedRows(This,newVal)

#define IGrid_get_FixedCols(This,pVal)	\
    (This)->lpVtbl -> get_FixedCols(This,pVal)

#define IGrid_put_FixedCols(This,newVal)	\
    (This)->lpVtbl -> put_FixedCols(This,newVal)

#define IGrid_AutosizeColumn(This,col)	\
    (This)->lpVtbl -> AutosizeColumn(This,col)

#define IGrid_AutosizeRow(This,row)	\
    (This)->lpVtbl -> AutosizeRow(This,row)

#define IGrid_get_CellEnabled(This,row,col,pVal)	\
    (This)->lpVtbl -> get_CellEnabled(This,row,col,pVal)

#define IGrid_put_CellEnabled(This,row,col,newVal)	\
    (This)->lpVtbl -> put_CellEnabled(This,row,col,newVal)

#define IGrid_get_AllowSelection(This,pVal)	\
    (This)->lpVtbl -> get_AllowSelection(This,pVal)

#define IGrid_put_AllowSelection(This,newVal)	\
    (This)->lpVtbl -> put_AllowSelection(This,newVal)

#define IGrid_get_ListMode(This,pVal)	\
    (This)->lpVtbl -> get_ListMode(This,pVal)

#define IGrid_put_ListMode(This,newVal)	\
    (This)->lpVtbl -> put_ListMode(This,newVal)

#define IGrid_get_CurrentRow(This,pVal)	\
    (This)->lpVtbl -> get_CurrentRow(This,pVal)

#define IGrid_put_CurrentRow(This,newVal)	\
    (This)->lpVtbl -> put_CurrentRow(This,newVal)

#define IGrid_get_CurrentCol(This,pVal)	\
    (This)->lpVtbl -> get_CurrentCol(This,pVal)

#define IGrid_put_CurrentCol(This,newVal)	\
    (This)->lpVtbl -> put_CurrentCol(This,newVal)

#define IGrid_DeleteRow(This,row)	\
    (This)->lpVtbl -> DeleteRow(This,row)

#define IGrid_get_HeaderSort(This,pVal)	\
    (This)->lpVtbl -> get_HeaderSort(This,pVal)

#define IGrid_put_HeaderSort(This,newVal)	\
    (This)->lpVtbl -> put_HeaderSort(This,newVal)

#define IGrid_get_SingleRowSelection(This,pVal)	\
    (This)->lpVtbl -> get_SingleRowSelection(This,pVal)

#define IGrid_put_SingleRowSelection(This,newVal)	\
    (This)->lpVtbl -> put_SingleRowSelection(This,newVal)

#define IGrid_DeleteColumn(This,col)	\
    (This)->lpVtbl -> DeleteColumn(This,col)

#define IGrid_get_FixedBackColor(This,pVal)	\
    (This)->lpVtbl -> get_FixedBackColor(This,pVal)

#define IGrid_put_FixedBackColor(This,newVal)	\
    (This)->lpVtbl -> put_FixedBackColor(This,newVal)

#define IGrid_get_TextColor(This,pVal)	\
    (This)->lpVtbl -> get_TextColor(This,pVal)

#define IGrid_put_TextColor(This,newVal)	\
    (This)->lpVtbl -> put_TextColor(This,newVal)

#define IGrid_get_TextBackColor(This,pVal)	\
    (This)->lpVtbl -> get_TextBackColor(This,pVal)

#define IGrid_put_TextBackColor(This,newVal)	\
    (This)->lpVtbl -> put_TextBackColor(This,newVal)

#define IGrid_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IGrid_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)

#define IGrid_get_FixedTextColor(This,pVal)	\
    (This)->lpVtbl -> get_FixedTextColor(This,pVal)

#define IGrid_put_FixedTextColor(This,newVal)	\
    (This)->lpVtbl -> put_FixedTextColor(This,newVal)

#define IGrid_get_CellFgColor(This,Row,Col,pVal)	\
    (This)->lpVtbl -> get_CellFgColor(This,Row,Col,pVal)

#define IGrid_put_CellFgColor(This,Row,Col,newVal)	\
    (This)->lpVtbl -> put_CellFgColor(This,Row,Col,newVal)

#define IGrid_get_CellBgColor(This,Row,Col,pVal)	\
    (This)->lpVtbl -> get_CellBgColor(This,Row,Col,pVal)

#define IGrid_put_CellBgColor(This,Row,Col,newVal)	\
    (This)->lpVtbl -> put_CellBgColor(This,Row,Col,newVal)

#define IGrid_SimpleConf(This)	\
    (This)->lpVtbl -> SimpleConf(This)

#define IGrid_get_Cell(This,Row,Col,pVal)	\
    (This)->lpVtbl -> get_Cell(This,Row,Col,pVal)

#define IGrid_put_Cell(This,Row,Col,newVal)	\
    (This)->lpVtbl -> put_Cell(This,Row,Col,newVal)

#define IGrid_get_ToolTip(This,pVal)	\
    (This)->lpVtbl -> get_ToolTip(This,pVal)

#define IGrid_put_ToolTip(This,newVal)	\
    (This)->lpVtbl -> put_ToolTip(This,newVal)

#define IGrid_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IGrid_SelectAllCells(This)	\
    (This)->lpVtbl -> SelectAllCells(This)

#define IGrid_get_KeepTab(This,pVal)	\
    (This)->lpVtbl -> get_KeepTab(This,pVal)

#define IGrid_put_KeepTab(This,newVal)	\
    (This)->lpVtbl -> put_KeepTab(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][requestedit][bindable][propputref] */ HRESULT STDMETHODCALLTYPE IGrid_putref_Font_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ IFontDisp __RPC_FAR *pFont);


void __RPC_STUB IGrid_putref_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_Font_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ IFontDisp __RPC_FAR *pFont);


void __RPC_STUB IGrid_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_Font_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *ppFont);


void __RPC_STUB IGrid_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_BackColor_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_BackColor_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IGrid_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_Image_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Row,
    /* [in] */ int Col,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_Image_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Row,
    /* [in] */ int Col,
    /* [in] */ short newVal);


void __RPC_STUB IGrid_put_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_Text_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Row,
    /* [in] */ int Col,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_Text_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Row,
    /* [in] */ int Col,
    /* [in] */ BSTR newVal);


void __RPC_STUB IGrid_put_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGrid_InsertRow_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Row,
    /* [in] */ BSTR caption);


void __RPC_STUB IGrid_InsertRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_RowCount_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_RowCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_RowCount_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IGrid_put_RowCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_ColumnCount_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_ColumnCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_ColumnCount_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IGrid_put_ColumnCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_RowHeight_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int nRow,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_RowHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_RowHeight_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int nRow,
    /* [in] */ int newVal);


void __RPC_STUB IGrid_put_RowHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_ColumnWidth_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Col,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_ColumnWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_ColumnWidth_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Col,
    /* [in] */ int newVal);


void __RPC_STUB IGrid_put_ColumnWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_CellFont_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Row,
    /* [in] */ int Col,
    /* [retval][out] */ IFontDisp __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IGrid_get_CellFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_CellFont_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Row,
    /* [in] */ int Col,
    /* [in] */ IFontDisp __RPC_FAR *newVal);


void __RPC_STUB IGrid_put_CellFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGrid_AutoSize_Proxy( 
    IGrid __RPC_FAR * This);


void __RPC_STUB IGrid_AutoSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_ColumnResizing_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_ColumnResizing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_ColumnResizing_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IGrid_put_ColumnResizing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_RowResizing_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_RowResizing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_RowResizing_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IGrid_put_RowResizing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_GridLines_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ grGridLines __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_GridLines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_GridLines_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ grGridLines newVal);


void __RPC_STUB IGrid_put_GridLines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_Editable_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_Editable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_Editable_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IGrid_put_Editable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_FixedRows_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_FixedRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_FixedRows_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IGrid_put_FixedRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_FixedCols_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_FixedCols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_FixedCols_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IGrid_put_FixedCols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGrid_AutosizeColumn_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int col);


void __RPC_STUB IGrid_AutosizeColumn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGrid_AutosizeRow_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int row);


void __RPC_STUB IGrid_AutosizeRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_CellEnabled_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int row,
    /* [in] */ int col,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_CellEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_CellEnabled_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int row,
    /* [in] */ int col,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IGrid_put_CellEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_AllowSelection_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_AllowSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_AllowSelection_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IGrid_put_AllowSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_ListMode_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_ListMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_ListMode_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IGrid_put_ListMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_CurrentRow_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_CurrentRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_CurrentRow_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IGrid_put_CurrentRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_CurrentCol_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_CurrentCol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_CurrentCol_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int newVal);


void __RPC_STUB IGrid_put_CurrentCol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGrid_DeleteRow_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int row);


void __RPC_STUB IGrid_DeleteRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_HeaderSort_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_HeaderSort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_HeaderSort_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IGrid_put_HeaderSort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_SingleRowSelection_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_SingleRowSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_SingleRowSelection_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IGrid_put_SingleRowSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGrid_DeleteColumn_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int col);


void __RPC_STUB IGrid_DeleteColumn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_FixedBackColor_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_FixedBackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_FixedBackColor_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IGrid_put_FixedBackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_TextColor_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_TextColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_TextColor_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IGrid_put_TextColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_TextBackColor_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_TextBackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_TextBackColor_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IGrid_put_TextBackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_Color_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_Color_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IGrid_put_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_FixedTextColor_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_FixedTextColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_FixedTextColor_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IGrid_put_FixedTextColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_CellFgColor_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Row,
    /* [in] */ int Col,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_CellFgColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_CellFgColor_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Row,
    /* [in] */ int Col,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IGrid_put_CellFgColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_CellBgColor_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Row,
    /* [in] */ int Col,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_CellBgColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_CellBgColor_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Row,
    /* [in] */ int Col,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IGrid_put_CellBgColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGrid_SimpleConf_Proxy( 
    IGrid __RPC_FAR * This);


void __RPC_STUB IGrid_SimpleConf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_Cell_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Row,
    /* [in] */ int Col,
    /* [retval][out] */ IGridCell __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IGrid_get_Cell_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_Cell_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ int Row,
    /* [in] */ int Col,
    /* [in] */ IGridCell __RPC_FAR *newVal);


void __RPC_STUB IGrid_put_Cell_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_ToolTip_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_ToolTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_ToolTip_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IGrid_put_ToolTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGrid_Refresh_Proxy( 
    IGrid __RPC_FAR * This);


void __RPC_STUB IGrid_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGrid_SelectAllCells_Proxy( 
    IGrid __RPC_FAR * This);


void __RPC_STUB IGrid_SelectAllCells_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGrid_get_KeepTab_Proxy( 
    IGrid __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IGrid_get_KeepTab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IGrid_put_KeepTab_Proxy( 
    IGrid __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IGrid_put_KeepTab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGrid_INTERFACE_DEFINED__ */


#ifndef ___IGridEvents_DISPINTERFACE_DEFINED__
#define ___IGridEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IGridEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IGridEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("466C80A1-58C4-11D3-B221-006097FEBF00")
    _IGridEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IGridEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IGridEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IGridEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IGridEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IGridEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IGridEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IGridEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IGridEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IGridEventsVtbl;

    interface _IGridEvents
    {
        CONST_VTBL struct _IGridEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IGridEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IGridEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IGridEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IGridEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IGridEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IGridEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IGridEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IGridEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Grid;

#ifdef __cplusplus

class DECLSPEC_UUID("466C80A0-58C4-11D3-B221-006097FEBF00")
Grid;
#endif

EXTERN_C const CLSID CLSID_GridCell;

#ifdef __cplusplus

class DECLSPEC_UUID("67C165D5-BE9B-11D3-9942-006097FEBF00")
GridCell;
#endif
#endif /* __ATLNEWGRIDLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
