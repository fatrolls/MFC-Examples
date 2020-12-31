//=================================================================
//  class: CMailServ
//  File:  MailServ.h
//
//  Implementation of CMailServ class
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


#ifndef __MAILSERV_H_
#define __MAILSERV_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

#include "UTMailServCP.h"
#include "MailServLicense.h"
#include "MarshalEvents.h"
#include "UT_MailServer.h"
#include "pop3_s.h"
#include "smtp_s.h"

class MailServerEx;
class POP3ServerEx;
class SMTPServerEx;
class SMTPOutEx;


/////////////////////////////////////////////////////////////////////////////
// CMailServ
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE CMailServ : 
	public CUT_MailServer,

	public CMarshalEvents<CMailServ, &DIID__IMailServEvents, TRUE>,

	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CMailServ, IMailServ, &IID_IMailServ, &LIBID_UTMAILSERVLib>,
	public CComControl<CMailServ>,
	public IPersistStreamInitImpl<CMailServ>,
	public IOleControlImpl<CMailServ>,
	public IOleObjectImpl<CMailServ>,
	public IOleInPlaceActiveObjectImpl<CMailServ>,
	public IViewObjectExImpl<CMailServ>,
	public IOleInPlaceObjectWindowlessImpl<CMailServ>,
	public IPersistStorageImpl<CMailServ>,
	public IPersistPropertyBagImpl<CMailServ>,
	public ISpecifyPropertyPagesImpl<CMailServ>,
	public IDataObjectImpl<CMailServ>,
	public IProvideClassInfo2Impl<&CLSID_MailServ, &DIID__IMailServEvents, &LIBID_UTMAILSERVLib>,
	public CProxy_IMailServEvents< CMailServ >,
	public IPropertyNotifySinkCP< CMailServ >,
	public CComCoClass<CMailServ, &CLSID_MailServ>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CMailServ>,
	public IObjectSafetyImpl<CMailServ, INTERFACESAFE_FOR_UNTRUSTED_CALLER >

{

friend CProxy_IMailServEvents< CMailServ >;

public:
	CMailServ();
	~CMailServ();

DECLARE_REGISTRY_RESOURCEID(IDR_MAILSERV)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMailServ)
	COM_INTERFACE_ENTRY(IMailServ)
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

BEGIN_PROP_MAP(CMailServ)
	PROP_ENTRY("RootKey", DISPID_REGISTRY_ROOT_KEY, CLSID_MailServPropPage )
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CMailServ)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IMailServEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CMailServ)
	CHAIN_MSG_MAP(CComControl<CMailServ>)
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
	DECLARE_CLASSFACTORY2(CMailServLicense)


// IMailServ
public:
	STDMETHOD(User_Modify)(/*[in]*/ BSTR Name, /*[in]*/ BSTR NewName, /*[in]*/ BSTR NewPassword, /*[in]*/ BSTR NewAddresses, /*[out, retval]*/ long *Result);
	STDMETHOD(get_RegistryRootKey)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_RegistryRootKey)(/*[in]*/ BSTR newVal);
	STDMETHOD(LocalName_Delete)(/*[in]*/ long Index, /*[out, retval]*/ long *Result);
	STDMETHOD(LocalName_Add)(/*[in]*/ BSTR LocalName, /*[out, retval]*/ long *Result);
	STDMETHOD(LocalName_Get)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *LocalName);
	STDMETHOD(LocalName_GetCount)(/*[out, retval]*/ long *LocalNamesCount);
	STDMETHOD(DNS_Delete)(/*[in]*/ long Index, /*[out, retval]*/ long *Result);
	STDMETHOD(DNS_Add)(/*[in]*/ BSTR DNSName, /*[out, retval]*/ long *Result);
	STDMETHOD(DNS_Get)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *DNSName);
	STDMETHOD(DNS_GetCount)(/*[out, retval]*/ long *DNSCount);
	STDMETHOD(User_GetName)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *Name);
	STDMETHOD(User_GetPassword)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *Password);
	STDMETHOD(User_GetAddress)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *MailAddresses);
	STDMETHOD(User_GetCount)(/*[out, retval]*/ long *UserCount);
	STDMETHOD(User_Delete)(/*[in]*/ BSTR Name, /*[out, retval]*/ long * Result);
	STDMETHOD(User_Add)(/*[in]*/ BSTR Name, /*[in]*/ BSTR Password, /*[in]*/ BSTR MailAddresses, /*[out, retval]*/ long * Result);

	STDMETHOD(Start)(/*[out, retval]*/ long *Result);
	STDMETHOD(AboutBox)();
	STDMETHOD(GetErrorText)(/*[in]*/ long ErrorCode, /*[out, retval]*/ BSTR *ErrorText);

	STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions);
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);


	HRESULT OnDraw(ATL_DRAWINFO& di);

// IMailServ protected data members
protected:
	POP3ServerEx		*m_ptrPOP3Server;			// Pointer to the POP3 server class
	SMTPServerEx		*m_ptrSMTPServer;			// Pointer to the SMTP server class
	SMTPOutEx			*m_ptrSMTPOut;				// Pointer to the SMTP Out class

	HICON				m_hMailServIcon;			// Mail server icon handle
	long				m_lMailServerPort;			// Mail server listening port number
	BOOL				m_bGoingToClose;			// TRUE if we are going to destroy the control

	CComCriticalSection	m_EventLock;				// Event critical section object

	// Returns a pointer to an instance
	// of a class derived from CUT_WSThread
    CUT_WSThread	*CreateInstance();

	// On display status
	virtual int		OnStatus(LPCSTR StatusText);

    // This virtual function is called each time the server 
    // accepting new connection.
    virtual long    OnCanAccept(LPCSTR address);

};

/////////////////////////////////////////////////////////////////////////////
// POP3ServerEx
/////////////////////////////////////////////////////////////////////////////
class POP3ServerEx : public CUT_POP3Server {
public:
	POP3ServerEx(CUT_MailServer &ptrMailServer) : CUT_POP3Server(ptrMailServer) {}

protected:
	// Create class instance callback, this is where a C_WSTHREAD clss is created
    virtual CUT_WSThread	*CreateInstance();

};

/////////////////////////////////////////////////////////////////////////////
// POP3ThreadEx
/////////////////////////////////////////////////////////////////////////////
class POP3ThreadEx : public CUT_POP3Thread {
	// This function is called whenever a new connection is made
    // and the max. number of connections has already been reached
    virtual void	OnMaxConnect();

	// This function is called whenever a new connection is made
    virtual void	OnConnect();
};

/////////////////////////////////////////////////////////////////////////////
// SMTPServerEx
/////////////////////////////////////////////////////////////////////////////
class SMTPServerEx : public CUT_SMTPServer {
public:
	SMTPServerEx(CUT_MailServer &ptrMailServer) : CUT_SMTPServer(ptrMailServer) {}

protected:
	// Create class instance callback, this is where a C_WSTHREAD clss is created
    virtual CUT_WSThread	*CreateInstance();

};

/////////////////////////////////////////////////////////////////////////////
// SMTPThreadEx
/////////////////////////////////////////////////////////////////////////////
class SMTPThreadEx : public CUT_SMTPThread {
	// This function is called whenever a new connection is made
    // and the max. number of connections has already been reached
    virtual void	OnMaxConnect();

	// This function is called whenever a new connection is made
    virtual void	OnConnect();
};

/////////////////////////////////////////////////////////////////////////////
// SMTPOutEx
/////////////////////////////////////////////////////////////////////////////
class SMTPOutEx : public CUT_SMTPOut {
public:
	SMTPOutEx(CUT_MailServer &ptrMailServer) : CUT_SMTPOut(ptrMailServer) {}

protected:
	// Send mail. 
	virtual void		SendMail(CUT_SMTPOutInfo	*info);

};

#endif //__MAILSERV_H_
