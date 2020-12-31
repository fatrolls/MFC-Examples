//=================================================================
//  class: CHttp
//  File:  Http.h
//
//  Implementation of CHttp class
//
//=================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
//=================================================================

#ifndef __HTTP_H_
#define __HTTP_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

#include "ut_clnt.h"	
#include "http_c.h"	
#include "MarshalEvents.h"
#include "HttpLicense.h"
#include "UTHttpCP.h"
#include "UT_MethodQueue.h"

	// Types of commands
	typedef enum MethodTypeTag {
		METHOD_GET,				// GET command
		METHOD_HEAD,			// HEAD command
		METHOD_PUT,				// PUT command
		METHOD_DEL_FILE,		// Delete File command
		METHOD_OTHER			// Other command
		} MethodType;

/////////////////////////////////////////////////////////////////////////////
// CHttp
class ATL_NO_VTABLE CHttp : 
	public CUT_MethodQueue<CHttp, MethodTypeTag>,

	public CUT_HTTPClient,

	public CMarshalEvents<CHttp, &DIID__IHttpEvents, TRUE>,

	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CHttp, IHttp, &IID_IHttp, &LIBID_UTHTTPLib>,
	public CComControl<CHttp>,
	public IPersistStreamInitImpl<CHttp>,
	public IOleControlImpl<CHttp>,
	public IOleObjectImpl<CHttp>,
	public IOleInPlaceActiveObjectImpl<CHttp>,
	public IViewObjectExImpl<CHttp>,
	public IOleInPlaceObjectWindowlessImpl<CHttp>,
	public IPersistStorageImpl<CHttp>,
	public IPersistPropertyBagImpl<CHttp>,
	public ISpecifyPropertyPagesImpl<CHttp>,
	public IDataObjectImpl<CHttp>,
	public IProvideClassInfo2Impl<&CLSID_Http, &DIID__IHttpEvents, &LIBID_UTHTTPLib>,
	public CProxy_IHttpEvents< CHttp >,
	public IPropertyNotifySinkCP< CHttp >,
	public CComCoClass<CHttp, &CLSID_Http>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CHttp>,
	public IObjectSafetyImpl<CHttp, INTERFACESAFE_FOR_UNTRUSTED_CALLER >

{

friend	CProxy_IHttpEvents< CHttp >;
friend	CUT_MethodQueue<CHttp, MethodTypeTag>;

public:
	CHttp();
	~CHttp();

DECLARE_REGISTRY_RESOURCEID(IDR_HTTP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHttp)
	COM_INTERFACE_ENTRY(IHttp)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IPersistPropertyBag)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IObjectSafety) 
END_COM_MAP()

BEGIN_PROP_MAP(CHttp)
	PROP_ENTRY("ConnectTimeOut", DISPID_CONNECT_TIME_OUT, CLSID_HttpPropPage )
	PROP_ENTRY("MaxLinesToStore", DISPID_MAX_LINES_TO_STORE, CLSID_HttpPropPage )
	PROP_ENTRY("BlockingMode", DISPID_BLOCKING_MODE, CLSID_HttpPropPage )
	PROP_ENTRY("ProxyServer", DISPID_PROXY_SERVER, CLSID_HttpPropPage )
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CHttp)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IHttpEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CHttp)
	CHAIN_MSG_MAP(CComControl<CHttp>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IClassFactory2
	DECLARE_CLASSFACTORY2(CHttpLicense)

// IHttp
public:
	STDMETHOD(DeleteFile)(/*[in]*/ BSTR URL, /*[out, retval]*/ long *Result);
	STDMETHOD(PUT)(/*[in]*/ BSTR URL, /*[in]*/ BSTR FileName, /*[out, retval]*/ long * Result);
	STDMETHOD(get_ProxyServer)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ProxyServer)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_MaxLinesToStore)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_MaxLinesToStore)(/*[in]*/ long newVal);
	STDMETHOD(get_ContentType)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ModifiedDate)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_LinkTagCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_HeaderLineCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_BodyLineCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(SaveToFile)(/*[in]*/ BSTR FileName, /*[out, retval]*/ long * Result);
	STDMETHOD(GetLinkTag)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *Result);
	STDMETHOD(GetHeaderLine)(/*[in]*/ long Index, /*[out, retval]*/ BSTR * Result);
	STDMETHOD(GetBodyLine)(/*[in]*/ long Index, /*[out, retval]*/ BSTR * Result);
	STDMETHOD(ClearReceivedData)();
	STDMETHOD(ClearSendHeaderTags)();
	STDMETHOD(AddSendHeaderTag)(/*[in]*/ BSTR Tag, /*[out, retval]*/ long * Result);
	STDMETHOD(CommandLine)(/*[in]*/ BSTR Command, /*[in]*/ BSTR URL, /*[in, defaultvalue("")]*/ BSTR Data, /*[out, retval]*/ long * Result);
	STDMETHOD(HEAD)(/*[in]*/ BSTR URL, /*[out, retval]*/ long * Result);
	STDMETHOD(GET)(/*[in]*/ BSTR URL, /*[in, defaultvalue("")]*/ BSTR FileName, /*[out, retval]*/ long * Result);

	STDMETHOD(CancelHttp)();
	STDMETHOD(AboutBox)();
	STDMETHOD(GetErrorText)(/*[in]*/ long ErrorCode, /*[out, retval]*/ BSTR *ErrorText);
	STDMETHOD(get_ConnectTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ConnectTimeOut)(/*[in]*/ long newVal);
	STDMETHOD(get_BlockingMode)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_BlockingMode)(/*[in]*/ VARIANT_BOOL newVal);

	STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions);
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);

	HRESULT OnDraw(ATL_DRAWINFO& di);

// IHttp Private data members
private:
	HICON				m_hHttpIcon;			// Http icon handle

	LONG				m_lnConnectTimeOut;		// Connection TimeOut in seconds
	BOOL				m_bAbortFlag;			// TRUE if we are going to abort Http
	BOOL				m_bBlockingMode;		// TRUE if we are working in blocking mode

	BOOL				m_bGoingToClose;		// TRUE if the control is going to be destroyed

	// Execute specified method
	virtual long		ExecuteMethod(MethodTypeTag MethodID, _variant_t *ptrVarParams, BOOL bForceNonBlocking);

	// Waits for the object to be signaled
	BOOL			WaitWithMsgLoop(HANDLE hEvent, long lTimeout);

	// Return TRUE if we are going to abort operation
	virtual BOOL	IsAborted();		


};

#endif //__HTTP_H_
