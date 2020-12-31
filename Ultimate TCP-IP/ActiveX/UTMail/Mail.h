//=================================================================
//  class: CMail
//  File:  Mail.h
//
//  Implementation of CMail class
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

#ifndef __MAIL_H_
#define __MAIL_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

#include "ut_clnt.h"	
#include "MarshalEvents.h"
#include "MailLicense.h"
#include "UTMailCP.h"
#include "MailClient.h"
#include "UT_MethodQueue.h"

	// Types of methods
	typedef enum MethodTypeTag {
		METHOD_SMTP_CONNECT,
		METHOD_SMTP_CLOSE,
		METHOD_SEND_MAIL,
        METHOD_SEND_MAIL_FROM_FILE,
		METHOD_POP3_CONNECT,
		METHOD_POP3_CLOSE,
		METHOD_GET_MSG_NUMBER,
		METHOD_GET_MSG_SIZE,
		METHOD_SAVE_MSG,
		METHOD_DELETE_MSG,
		METHOD_RESET_DELETE,
		METHOD_OPEN_MSG,
		METHOD_CLOSE_MSG,
		METHOD_READ_MSG_LINE,
		METHOD_OPEN_TOP,
		METHOD_CLOSE_TOP,
		METHOD_READ_TOP_LINE

		} MethodType;

/////////////////////////////////////////////////////////////////////////////
// CMail
/////////////////////////////////////////////////////////////////////////////

class ATL_NO_VTABLE CMail : 
	public CUT_MethodQueue<CMail, MethodTypeTag>,
	public CMarshalEvents<CMail, &DIID__IMailEvents, TRUE>,

	public CUT_POP3MailClient,
	public CUT_SMTPMailClient,

	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CMail, IMail, &IID_IMail, &LIBID_UTMAILLib>,
	public CComControl<CMail>,
	public IPersistStreamInitImpl<CMail>,
	public IOleControlImpl<CMail>,
	public IOleObjectImpl<CMail>,
	public IOleInPlaceActiveObjectImpl<CMail>,
	public IViewObjectExImpl<CMail>,
	public IOleInPlaceObjectWindowlessImpl<CMail>,
	public IPersistStorageImpl<CMail>,
	public IPersistPropertyBagImpl<CMail>,
	public ISpecifyPropertyPagesImpl<CMail>,
	public IDataObjectImpl<CMail>,
	public IProvideClassInfo2Impl<&CLSID_Mail, &DIID__IMailEvents, &LIBID_UTMAILLib>,
	public CProxy_IMailEvents< CMail >,
	public IPropertyNotifySinkCP< CMail >,
	public CComCoClass<CMail, &CLSID_Mail>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CMail>,
	public IObjectSafetyImpl<CMail, INTERFACESAFE_FOR_UNTRUSTED_CALLER >

{

friend	CProxy_IMailEvents< CMail >;
friend	CUT_MethodQueue<CMail, MethodTypeTag>;

public:
	CMail();
	~CMail();

DECLARE_REGISTRY_RESOURCEID(IDR_MAIL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMail)
	COM_INTERFACE_ENTRY(IMail)
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

BEGIN_PROP_MAP(CMail)
	PROP_ENTRY("ConnectTimeOut", DISPID_CONNECT_TIME_OUT, CLSID_MailPropPage )
	PROP_ENTRY("ReceiveTimeOut", DISPID_RECEIVE_TIME_OUT, CLSID_MailPropPage )
#ifndef _BLOCKING_MODE_ONLY
	PROP_ENTRY("BlockingMode", DISPID_BLOCKING_MODE, CLSID_MailPropPage )
#endif
	PROP_ENTRY("MailHostName", DISPID_MAIL_HOST_NAME, CLSID_MailPropPage )
	PROP_ENTRY("POP3HostName", DISPID_POP3_HOST_NAME, CLSID_MailPropPage )
	PROP_ENTRY("UserName", DISPID_USER_NAME, CLSID_MailPropPage )
	PROP_ENTRY("Password", DISPID_USER_PASSWORD, CLSID_MailPropPage )
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CMail)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IMailEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CMail)
	CHAIN_MSG_MAP(CComControl<CMail>)
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
	DECLARE_CLASSFACTORY2(CMailLicense)


// IMail
public:
	STDMETHOD(ReadTopLine)(/*[out, retval]*/ long *Result);
	STDMETHOD(CloseTop)(/*[out, retval]*/ long *Result);
	STDMETHOD(OpenTop)(/*[in]*/ long MsgIndex, /*[in] */long MsgLines, /*[out, retval]*/ long *Result);
	STDMETHOD(ReadMsgLine)(/*[out, retval]*/ long *Result);
	STDMETHOD(CloseMsg)(/*[out, retval]*/ long *Result);
	STDMETHOD(OpenMsg)(/*[in]*/ long MsgIndex, /*[out, retval]*/ long *Result);
	STDMETHOD(ResetDelete)(/*[out, retval]*/ long *Result);
	STDMETHOD(DeleteMsg)(/*[in]*/ long MsgIndex, /*[out, retval]*/ long *Result);
	STDMETHOD(SaveMsg)(/*[in]*/ long MsgIndex, /*[in]*/ BSTR FileName, /*[out, retval]*/ long *Result);
	STDMETHOD(GetMsgSize)(/*[in]*/ long MsgIndex, /*[out, retval]*/ long *Result);
	STDMETHOD(GetMsgNumber)(/*[out, retval]*/ long *Result);
	STDMETHOD(POP3Close)(/*[out, retval]*/ long *Result);
	STDMETHOD(POP3Connect)(/*[out, retval]*/ long *Result);
	STDMETHOD(SendMail)(/*[in]*/ BSTR To, /*[in]*/ BSTR From, /*[in]*/ BSTR Subject, /*[in]*/ BSTR Message, /*[in, defaultvalue("")]*/ BSTR Cc, /*[in, defaultvalue("")]*/ BSTR Bcc, /*[in, defaultvalue("")]*/ BSTR Attach,  /*[out, retval]*/ long * Result);
	STDMETHOD(SMTPClose)(/*[out, retval]*/ long * Result);
	STDMETHOD(SMTPConnect)(/*[out, retval]*/ long * Result);
	STDMETHOD(AboutBox)();
#ifndef _BLOCKING_MODE_ONLY
	STDMETHOD(CancelMail)();
#endif // _BLOCKING_MODE_ONLY
	STDMETHOD(GetErrorText)(/*[in]*/ long ErrorCode, /*[out, retval]*/ BSTR *ErrorText);
	STDMETHOD(get_ConnectTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ConnectTimeOut)(/*[in]*/ long newVal);
	STDMETHOD(get_ReceiveTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ReceiveTimeOut)(/*[in]*/ long newVal);
#ifndef _BLOCKING_MODE_ONLY
	STDMETHOD(get_BlockingMode)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_BlockingMode)(/*[in]*/ VARIANT_BOOL newVal);
#endif // _BLOCKING_MODE_ONLY
	STDMETHOD(get_UserPassword)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_UserPassword)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_UserName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_UserName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_MailHostName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_MailHostName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_POP3HostName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_POP3HostName)(/*[in]*/ BSTR newVal);

	STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions);
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);

	HRESULT OnDraw(ATL_DRAWINFO& di);

// IMail Private data members
private:
	HICON				m_hMailIcon;			// Mail icon handle
	BOOL				m_bAbortFlag;			// TRUE if we are going to abort Mail
	BOOL				m_bBlockingMode;		// TRUE if we are working in blocking mode

	_bstr_t				m_bstrMailHostName;		// Mail host name property variable
    _bstr_t             m_bstrLocalHostName;    // Local host name property variable
	_bstr_t				m_bstrPOP3HostName;		// Pop3 host name property variable
	_bstr_t				m_bstrUserName;			// User name property variable
	_bstr_t				m_bstrUserPassword;		// User password property variable

    int                 m_nMsgNumber;           // Number of messages
    long                m_lMsgSize;             // Message size
    _bstr_t             m_bstrLineRead;         // Last linr read from message

	BOOL				m_bGoingToClose;		// TRUE if the control is going to be destroyed

public:
	STDMETHOD(SendMailFromFile)(/*[in]*/ BSTR FileName, /*[out,retval]*/ long *Result);
	STDMETHOD(get_LineRead)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_MsgSize)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_MsgNumber)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_LocalHostName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_LocalHostName)(/*[in]*/ BSTR newVal);
	// Execute specified method
	virtual long		ExecuteMethod(MethodTypeTag MethodID, _variant_t *ptrVarParams, BOOL bForceNonBlocking);

	// Waits for the object to be signaled
	BOOL				WaitWithMsgLoop(HANDLE hEvent, long lTimeout);

    // Delegated function to be invoked to inform us of the message send progress
    virtual BOOL		OnSendMailProgress(long bytesSent,long totalBytes); 

	// Virtual function to be overridden to report the save message progress
    virtual BOOL		OnSaveMsg(long bytesRetrieved);

};

#endif //__MAIL_H_
