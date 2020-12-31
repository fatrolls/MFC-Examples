// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
#define $$FILE_NAME_SYMBOL$$_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
$$IF(CTreeView || CListView)
#include <afxcview.h>
$$ENDIF //CTreeView || CListView
$$IF(PROJTYPE_DLL)

#ifndef _AFX_NO_OLE_SUPPORT
$$ENDIF //PROJTYPE_DLL
$$IF(CONTAINER || MINI_SERVER || FULL_SERVER || CONTAINER_SERVER || PROJTYPE_DLL)
#include <afxole.h>         // MFC OLE classes
$$IF(CONTAINER || CONTAINER_SERVER || PROJTYPE_DLL)
#include <afxodlgs.h>       // MFC OLE dialog classes
$$ENDIF
$$ENDIF
$$IF(AUTOMATION || PROJTYPE_DLL || OLECTL)
#include <afxdisp.h>        // MFC OLE automation classes
$$ENDIF
$$IF(ACTIVE_DOC_SERVER)
#include <afxdocob.h>
$$ENDIF
$$IF(PROJTYPE_DLL)
#endif // _AFX_NO_OLE_SUPPORT

$$ENDIF //PROJTYPE_DLL
$$// Include database headers.  For a DLL or app which just includes database
$$//  headers (no database view), conditionally include DAO and ODBC.
$$//  If an actual view is used, always & only include the corresponding header.
$$// First, actual view is used:
$$IF(CRecordView)
#include <afxdb.h>			// MFC ODBC database classes
$$ELIF(CDaoRecordView)
#include <afxdao.h>			// MFC DAO database classes
$$ELIF(DB || PROJTYPE_DLL)
$$// Here, minimal DB support is requested, or we're a DLL.  No view is chosen.

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

$$ENDIF // database/DLL options
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

$$IF(SOCKETS)
#include <afxsock.h>		// MFC socket extensions
$$ENDIF //SOCKETS
$$IF(CRichEditView)
#include <afxrich.h>		// MFC rich edit classes
$$ENDIF //CRichEditView
$$IF(PROJTYPE_DLG)
$$IF(AUTOMATION)

$$IF(VERBOSE)
// This macro is the same as IMPLEMENT_OLECREATE, except it passes TRUE
//  for the bMultiInstance parameter to the COleObjectFactory constructor.
//  We want a separate instance of this application to be launched for
//  each OLE automation proxy object requested by automation controllers.
$$ENDIF //VERBOSE
#ifndef IMPLEMENT_OLECREATE2
#define IMPLEMENT_OLECREATE2(class_name, external_name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
	AFX_DATADEF COleObjectFactory class_name::factory(class_name::guid, \
		RUNTIME_CLASS(class_name), TRUE, _T(external_name)); \
	const AFX_DATADEF GUID class_name::guid = \
		{ l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } };
#endif // IMPLEMENT_OLECREATE2
$$ENDIF //AUTOMATION
$$ENDIF //PROJTYPE_DLG

//{{AFX_INSERT_LOCATION}}
// $$INSERT_LOCATION_COMMENT$$

#endif // !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
