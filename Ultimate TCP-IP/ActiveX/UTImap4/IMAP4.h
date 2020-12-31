//=================================================================
//  class: CIMAP4
//  File:  IMAP4.h
//
//  Implementation of CIMAP4 class
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

#ifndef __IMAP4_H_
#define __IMAP4_H_

#include "IMAP4License.h"
#include "MarshalEvents.h"
#include "UT_MethodQueue.h"

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "UTImap4CP.h"
#include "imap4_c.h"

	// Types of methods
	typedef enum MethodTypeTag {
		METHOD_CONNECT,
		METHOD_CLOSE,
        METHOD_NOOP,
        METHOD_MAIL_BOX_SELECT,
        METHOD_MAIL_BOX_EXAMINE,
        METHOD_MAIL_BOX_CREATE,
        METHOD_MAIL_BOX_DELETE,
        METHOD_MAIL_BOX_SUBSCRIBE,
        METHOD_MAIL_BOX_UNSUBSCRIBE,
        METHOD_MAIL_BOX_RENAME,
        METHOD_MAIL_BOX_LIST,
        METHOD_MAIL_BOX_LSUB,
        METHOD_MAIL_BOX_APPEND,
        METHOD_MAIL_BOX_CHECK,
        METHOD_MAIL_BOX_CLOSE,
        METHOD_MAIL_BOX_STATUS,
        METHOD_MESSAGE_EXPUNGE,
        METHOD_MESSAGE_SEARCH,
        METHOD_MESSAGE_COPY,
        METHOD_MESSAGE_FETCH,
        METHOD_MESSAGE_STORE
		} MethodType;

/////////////////////////////////////////////////////////////////////////////
// CIMAP4
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE CIMAP4 : 
	public CUT_MethodQueue<CIMAP4, MethodTypeTag>,
    public CMarshalEvents<CIMAP4, &DIID__IIMAP4Events, TRUE>,

	public CUT_IMAP4Client,

	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CIMAP4, IIMAP4, &IID_IIMAP4, &LIBID_UTIMAP4Lib>,
	public CComControl<CIMAP4>,
	public IPersistStreamInitImpl<CIMAP4>,
	public IOleControlImpl<CIMAP4>,
	public IOleObjectImpl<CIMAP4>,
	public IOleInPlaceActiveObjectImpl<CIMAP4>,
	public IViewObjectExImpl<CIMAP4>,
	public IOleInPlaceObjectWindowlessImpl<CIMAP4>,
	public IPersistStorageImpl<CIMAP4>,
	public IPersistPropertyBagImpl<CIMAP4>,
	public ISpecifyPropertyPagesImpl<CIMAP4>,
	public IDataObjectImpl<CIMAP4>,
	public IProvideClassInfo2Impl<&CLSID_IMAP4, &DIID__IIMAP4Events, &LIBID_UTIMAP4Lib>,
	public CProxy_IIMAP4Events< CIMAP4 >,
	public IPropertyNotifySinkCP< CIMAP4 >,
	public CComCoClass<CIMAP4, &CLSID_IMAP4>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CIMAP4>,
	public IObjectSafetyImpl<CIMAP4, INTERFACESAFE_FOR_UNTRUSTED_CALLER >
{

friend CProxy_IIMAP4Events< CIMAP4 >;
friend	CUT_MethodQueue<CIMAP4, MethodTypeTag>;

public:
	CIMAP4();
    ~CIMAP4();

DECLARE_REGISTRY_RESOURCEID(IDR_IMAP4)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CIMAP4)
	COM_INTERFACE_ENTRY(IIMAP4)
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

BEGIN_PROP_MAP(CIMAP4)
	PROP_ENTRY("ConnectTimeOut", DISPID_CONNECT_TIME_OUT, CLSID_IMAP4PropPage )
	PROP_ENTRY("ReceiveTimeOut", DISPID_RECEIVE_TIME_OUT, CLSID_IMAP4PropPage )
    PROP_ENTRY("NewMailCheckInterval", DISPID_NEW_MAIL_CHECK_INER, CLSID_IMAP4PropPage )
	PROP_ENTRY("BlockingMode", DISPID_BLOCKING_MODE, CLSID_IMAP4PropPage )
	PROP_ENTRY("HostName", DISPID_HOST_NAME, CLSID_IMAP4PropPage )
	PROP_ENTRY("UserName", DISPID_USER_NAME, CLSID_IMAP4PropPage )
	PROP_ENTRY("Password", DISPID_USER_PASSWORD, CLSID_IMAP4PropPage )
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CIMAP4)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IIMAP4Events)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CIMAP4)
	CHAIN_MSG_MAP(CComControl<CIMAP4>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, VARIANT_BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, VARIANT_BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, VARIANT_BOOL& bHandled);


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IClassFactory2
	DECLARE_CLASSFACTORY2(CIMAP4License)

// IIMAP4
public:
	STDMETHOD(GetStatusResultUIVV)(/*[out, retval]*/ long *UIVV);
	STDMETHOD(GetStatusResultNextUID)(/*[out, retval]*/ long *UID);
	STDMETHOD(GetStatusResultMsgUnseen)(/*[out, retval]*/ long *UnseenNumber);
	STDMETHOD(GetStatusResultMsgRecent)(/*[out, retval]*/ long *RecentNumber);
	STDMETHOD(GetStatusResultMsgNumber)(/*[out, retval]*/ long *Number);
	STDMETHOD(GetStatusResultName)(/*[out, retval]*/ BSTR *Name);
	STDMETHOD(MailBoxStatus)(/*[in]*/ BSTR MailBoxName, /*[in]*/ BSTR StatusName, /*[out, retval]*/ long *Result);
	STDMETHOD(FlagsToString)(/*[in]*/ long Flags, /*[out, retval]*/ BSTR *Result);
	STDMETHOD(MessageStore)(/*[in]*/ BSTR MessageSet, /*[in]*/ IMAP4StoreType Type, /*[in]*/ BSTR Flags, /*[in,defaultvalue(FALSE)]*/ VARIANT_BOOL UseUID,  /*[out, retval]*/ long *Result);
	STDMETHOD(SetCurrentMessage)(/*[in]*/ long Index, /*[out, retval]*/ long *Result);
	STDMETHOD(GetMessageListSize)(/*[out, retval]*/ long *Size);
	STDMETHOD(MessageFetch)(/*[in]*/ BSTR MessageSet, /*[in]*/ IMAP4FetchItem Item, /*[in, defaultvalue(FALSE)]*/ VARIANT_BOOL SetSeenFlag, /*[in, defaultvalue(FALSE)]*/ VARIANT_BOOL UseUID, /*[out, retval]*/ long *Result);
	STDMETHOD(MessageCopy)(/*[in]*/ BSTR MessageSet, /*[in]*/ BSTR DestMailBoxName, /*[in, defaulvalue(FALSE)]*/ VARIANT_BOOL UseUID, /*[out, retval]*/ long *Result);
	STDMETHOD(GetSearchResultItem)(/*[in]*/ long Index, /*[out, retval]*/ long *MessageID);
	STDMETHOD(GetSearchResultSize)(/*[out, retval]*/ long *Result);
	STDMETHOD(MessageSearch)(/*[in]*/ BSTR SearchString, /*[in, defaultvalue(FALSE)]*/ VARIANT_BOOL UseUID, /*[out, retval]*/ long *Result);
	STDMETHOD(MessageExpunge)(/*[out, retval]*/ long *Result);
	STDMETHOD(MailBoxClose)(/*[out, retval]*/ long *Result);
	STDMETHOD(MailBoxCheck)(/*[out, retval]*/ long *Result);
	STDMETHOD(MailBoxAppend)(/*[in]*/ BSTR MailBoxName, /*[in]*/ BSTR FileName, /*[in, defaultvalue("")]*/ BSTR Flags, /*[in, defaultvalue("")]*/ BSTR DateTime, /*[out, retval]*/ long *Result);
	STDMETHOD(GetMailBoxListAttrib)(/*[in]*/ long Index, /*[out, retval]*/ long *Attrib);
	STDMETHOD(GetMailBoxListDelimiter)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *Delimiter);
	STDMETHOD(GetMailBoxListName)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *Name);
	STDMETHOD(GetMailBoxListSize)(/*[out, retval]*/ long *Result);
	STDMETHOD(MailBoxLSub)(/*[in]*/ BSTR Reference, /*[in]*/ BSTR MailBoxName, /*[out, retval]*/ long *Result);
	STDMETHOD(MailBoxList)(/*[in]*/ BSTR Reference, /*[in]*/ BSTR MailBoxName, /*[out, retval]*/ long *Result);
	STDMETHOD(MailBoxRename)(/*[in]*/ BSTR MailBoxName, /*[in]*/ BSTR MailBoxNewName, /*[out, retval]*/ long *Result);
	STDMETHOD(MailBoxUnSubscribe)(/*[in]*/ BSTR MailBoxName, /*[out, retval]*/ long *Result);
	STDMETHOD(MailBoxSubscribe)(/*[in]*/ BSTR MailBoxName, /*[out, retval]*/ long *Result);
	STDMETHOD(MailBoxDelete)(/*[in]*/ BSTR MailBoxName, /*[out, retval]*/ long *Result);
	STDMETHOD(MailBoxCreate)(/*[in]*/ BSTR MailBoxName, /*[out, retval]*/ long *Result);
	STDMETHOD(MailBoxExamine)(/*[in]*/ BSTR MailBoxName, /*[out, retval]*/ long *Result);
	STDMETHOD(MailBoxSelect)(/*[in]*/ BSTR MailBoxName, /*[out, retval]*/ long *Result);
	STDMETHOD(Noop)(/*[out, retval]*/ long *Result);
	STDMETHOD(GetMsgUID)(/*[out, retval]*/ long *Result);
	STDMETHOD(GetMsgDate)(/*[out, retval]*/ BSTR *Result);
	STDMETHOD(GetMsgSystemFlags)(/*[out, retval]*/ long *Result);
	STDMETHOD(GetMsgFlags)(/*[out, retval]*/ BSTR *Result);
	STDMETHOD(GetMsgSize)(/*[out, retval]*/ long *Result);
	STDMETHOD(GetMsgSequenceNumber)(/*[out, retval]*/ long *Result);
	STDMETHOD(get_ClientState)(/*[out, retval]*/ IMAP4ClientState *pVal);
	STDMETHOD(get_Capability)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(GetMsgHeaderFieldName)(/*[in]*/ MsgHeaderFields Type, /*[out,retval]*/ BSTR *Name);
	STDMETHOD(GetMsgHeader)(/*[in]*/ MsgHeaderFields Type, /*[out, retval]*/ BSTR *Header);
	STDMETHOD(DecodeMsgAttach)(/*[in]*/ long AttachIndex, /*[in]*/ BSTR DestFileName, /*[out, retval]*/ long *Result);
	STDMETHOD(GetAttachName)(/*[in]*/ long AttachIndex, /*[out, retval]*/ BSTR *Name);
	STDMETHOD(GetAttachType)(/*[in]*/ long AttachIndex, /*[out, retval]*/ BSTR *Type);
	STDMETHOD(GetDecodedMsgBody)(/*[out, retval]*/ BSTR *MsgBody);
	STDMETHOD(GetAttachNumber)(/*[out, retval]*/ long *AttachNumber);
	STDMETHOD(get_MailBoxMsgUnseen)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_MailBoxUID)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_MailBoxPermFlags)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_MailBoxPermSystemFlags)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_MailBoxFlags)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_MailBoxSystemFlags)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_MailBoxMsgRecent)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_MailBoxMsgNumber)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_MailBoxWriteAccess)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_NewMailCheckInterval)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_NewMailCheckInterval)(/*[in]*/ long newVal);
   	STDMETHOD(Close)(/*[out, retval]*/ long *Result);
	STDMETHOD(Connect)(/*[out, retval]*/ long *Result);
	STDMETHOD(AboutBox)();
	STDMETHOD(Cancel)();
	STDMETHOD(GetErrorText)(/*[in]*/ long ErrorCode, /*[out, retval]*/ BSTR *ErrorText);
	STDMETHOD(get_ConnectTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ConnectTimeOut)(/*[in]*/ long newVal);
	STDMETHOD(get_ReceiveTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ReceiveTimeOut)(/*[in]*/ long newVal);
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
// IIMAP4 Private data members
private:
	CUT_Msg				*m_CurMessage;			// Current decoding message
    CUT_MsgData         *m_CurMessageData;      // Current IMAP4 message data 
    UT_StatusData       *m_CurStatusData;       // Last status result

	HICON				m_hIMAP4Icon;			// IMAP4 icon handle
	VARIANT_BOOL		m_bAbortFlag;			// TRUE if we are going to abort IMAP4
	VARIANT_BOOL			m_bBlockingMode;		// TRUE if we are working in blocking mode

	_bstr_t				m_bstrHostName;	        // IMAP4 host name property variable
    _bstr_t				m_bstrUserName;			// User name property variable
	_bstr_t				m_bstrUserPassword;		// User password property variable

	BOOL				m_bGoingToClose;		// TRUE if the control is going to be destroyed

public:
	STDMETHOD(GetLastCommandResponseText)(/*[out, retval]*/ BSTR *Text);
	// Execute specified method
	virtual long		ExecuteMethod(MethodTypeTag MethodID, _variant_t *ptrVarParams, BOOL bForceNonBlocking);

	// Waits for the object to be signaled
	BOOL		        WaitWithMsgLoop(HANDLE hEvent, long lTimeout);

    virtual	BOOL        NewMailThreadStarted();

    virtual	void        NewMailThreadTerminated();

    virtual	void        OnAlertMessage(LPCSTR lpszAlertMsg);

	virtual	void        OnExpunge(long nMsgNumber);

	virtual	void        OnFetch();
	
	virtual	void        OnExists(long nMsgNumber);
	
	virtual	void        OnRecent(long nMsgNumber);
};

#endif //__IMAP4_H_
