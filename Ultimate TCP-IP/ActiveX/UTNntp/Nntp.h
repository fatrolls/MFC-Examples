//=================================================================
//  class: CNntp
//  File:  Nntp.h
//
//  Implementation of CNntp class
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

#ifndef __NNTP_H_
#define __NNTP_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

#include "ut_clnt.h"	
#include "nntpc.h"	
#include "MarshalEvents.h"
#include "UTNntpCP.h"
#include "NntpLicense.h"
#include "UT_MethodQueue.h"

	// Types of methods
	typedef enum MethodTypeTag {
		METHOD_CONNECT,
		METHOD_CLOSE,
		METHOD_CHECK_CAN_POST,
		METHOD_GET_SERVER_DATE,
		METHOD_SELECT_NEWS_GROUP,
		METHOD_GET_ARTICLE,
		METHOD_POST_ARTICLE,
		METHOD_GET_ARTICLE_LIST,
		METHOD_GET_NEWS_GROUP_LIST,
        METHOD_POST_ARTICLE_FROM_FILE
		} MethodType;


/////////////////////////////////////////////////////////////////////////////
// CNntp
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE CNntp : 
	public CUT_MethodQueue<CNntp, MethodTypeTag>,

	public CUT_NNTPClient,

	public CMarshalEvents<CNntp, &DIID__INntpEvents, TRUE>,

	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CNntp, INntp, &IID_INntp, &LIBID_UTNNTPLib>,
	public CComControl<CNntp>,
	public IPersistStreamInitImpl<CNntp>,
	public IOleControlImpl<CNntp>,
	public IOleObjectImpl<CNntp>,
	public IOleInPlaceActiveObjectImpl<CNntp>,
	public IViewObjectExImpl<CNntp>,
	public IOleInPlaceObjectWindowlessImpl<CNntp>,
	public IPersistStorageImpl<CNntp>,
	public IPersistPropertyBagImpl<CNntp>,
	public ISpecifyPropertyPagesImpl<CNntp>,
	public IDataObjectImpl<CNntp>,
	public IProvideClassInfo2Impl<&CLSID_Nntp, &DIID__INntpEvents, &LIBID_UTNNTPLib>,
	public CProxy_INntpEvents< CNntp >,
	public IPropertyNotifySinkCP< CNntp >,
	public CComCoClass<CNntp, &CLSID_Nntp>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CNntp>,
	public IObjectSafetyImpl<CNntp, INTERFACESAFE_FOR_UNTRUSTED_CALLER >

{

friend	CProxy_INntpEvents< CNntp >;
friend	CUT_MethodQueue<CNntp, MethodTypeTag>;

public:
	CNntp();
	~CNntp();

DECLARE_REGISTRY_RESOURCEID(IDR_NNTP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNntp)
	COM_INTERFACE_ENTRY(INntp)
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

BEGIN_PROP_MAP(CNntp)
	PROP_ENTRY("ConnectTimeOut", DISPID_CONNECT_TIME_OUT, CLSID_NntpPropPage )
	PROP_ENTRY("ReceiveTimeOut", DISPID_RECEIVE_TIME_OUT, CLSID_NntpPropPage )
	PROP_ENTRY("BlockingMode", DISPID_BLOCKING_MODE, CLSID_NntpPropPage )
	PROP_ENTRY("HostName", DISPID_HOST_NAME, CLSID_NntpPropPage )
	PROP_ENTRY("UserName", DISPID_USER_NAME, CLSID_NntpPropPage )
	PROP_ENTRY("Password", DISPID_USER_PASSWORD, CLSID_NntpPropPage )

	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CNntp)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__INntpEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CNntp)
	CHAIN_MSG_MAP(CComControl<CNntp>)
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
	DECLARE_CLASSFACTORY2(CNntpLicense)

// INntp
public:
	STDMETHOD(PostArticleFromFile)(/*[in]*/ BSTR FileName, /*[out,retval]*/ long *Result);
	STDMETHOD(get_ServerDate)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ArticleInfo_Status)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_ArticleInfo_LineCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_ArticleInfo_ByteCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_ArticleInfo_Refer)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ArticleInfo_MsgID)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ArticleInfo_Date)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ArticleInfo_Author)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ArticleInfo_Subject)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ArticleInfo_ID)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_ArticleHeaderCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_NewArticleCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_NewsGroupCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(GetNewsGroupList)(/*[in]*/ RequestInfoType Type, /*[out, retval]*/ long *Result);
	STDMETHOD(GetArticleList)(/*[in]*/ RequestInfoType Type, /*[out, retval]*/ long *Result);
	STDMETHOD(PostArticle)(/*[in]*/ BSTR NewsGroup, /*[in]*/ BSTR From, /*[in]*/ BSTR Subject, /*[in]*/ BSTR Article, /*[out, retval]*/ long *Result);
	STDMETHOD(EnumArticleInfo)(/*[out, retval]*/ long * Result);
	STDMETHOD(ResetArticleInfoEnum)();
	STDMETHOD(GetArticle)(/*[in]*/ BSTR ArticleID, /*[in]*/ BSTR FileName, /*[out, retval]*/ long * Result);
	STDMETHOD(LoadArticleHeaderList)(/*[in]*/ BSTR FileName, /*[out, retval]*/ long * Result);
	STDMETHOD(SaveArticleHeaderList)(/*[in]*/ BSTR FileName, /*[out, retval]*/ long * Result);
	STDMETHOD(GetNewsGroupTitle)(/*[in]*/ long Index, /*[out, retval]*/ BSTR * Result);
	STDMETHOD(LoadNewsGroupList)(/*[in]*/ BSTR FileName, /*[out, retval]*/ long * Result);
	STDMETHOD(SaveNewsGroupList)(/*[in]*/ BSTR FileName, /*[out, retval]*/ long * Result);
	STDMETHOD(SelectNewsGroup)(/*[in]*/ BSTR NewsGroup, /*[out, retval]*/ long * Result);
	STDMETHOD(GetServerDate)(/*[out, retval]*/ long * Result);
	STDMETHOD(CheckCanPost)(/*[out, retval]*/ long * Result);
	STDMETHOD(Close)(/*[out, retval]*/ long * Result);
	STDMETHOD(Connect)(/*[out, retval]*/ long * Result);

	STDMETHOD(AboutBox)();
	STDMETHOD(CancelNntp)();
	STDMETHOD(GetErrorText)(/*[in]*/ long ErrorCode, /*[out, retval]*/ BSTR *ErrorText);
	STDMETHOD(get_ReceiveTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ReceiveTimeOut)(/*[in]*/ long newVal);
	STDMETHOD(get_ConnectTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ConnectTimeOut)(/*[in]*/ long newVal);
	STDMETHOD(get_BlockingMode)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_BlockingMode)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_UserPassword)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_UserPassword)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_UserName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_UserName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_HostName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_HostName)(/*[in]*/ BSTR newVal);

	STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions);
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);

	HRESULT OnDraw(ATL_DRAWINFO& di);


// INntp Private data members
protected:
	HICON				m_hNntpIcon;			// Nntp icon handle

	LONG				m_lnConnectTimeOut;		// Connection TimeOut in seconds
	LONG				m_lnReceiveTimeOut;		// Receive TimeOut in seconds
	BOOL				m_bAbortFlag;			// TRUE if we are going to abort Nntp
	BOOL				m_bBlockingMode;		// TRUE if we are working in blocking mode

	BOOL				m_bNntpThreadRunning;	// TRUE if thread running
	BOOL				m_bGoingToClose;		// TRUE if the control is going to be destroyed
	HANDLE				m_hNntpThread;

	long				m_lnCurArticleInfoIndex;// Index of current article information
	UT_ARTICLEINFO		m_CurArticleInfo;		// Current article information

	_bstr_t				m_bstrHostName;			// Host name property variable
	_bstr_t				m_bstrUserName;			// User name property variable
	_bstr_t				m_bstrUserPassword;		// User password property variable

    _bstr_t				m_bstrServerDate;		// Server date

	// Execute specified method
	virtual long	ExecuteMethod(MethodTypeTag MethodID, _variant_t *ptrVarParams, BOOL bForceNonBlocking);

	// Waits for the object to be signaled
	BOOL			WaitWithMsgLoop(HANDLE hEvent, long lTimeout);

	// Return TRUE if we are going to abort operation
	virtual BOOL	IsAborted();		

	// Article send progress function
	virtual BOOL	OnSendArticleProgress(long bytesSent,long totalBytes);

};

#endif //__NNTP_H_
