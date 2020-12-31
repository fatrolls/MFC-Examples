//=================================================================
//  class: CFtpServ
//  File:  FtpServ.h
//
//  Implementation of CFtpServ class
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

#ifndef __FtpServ_H_
#define __FtpServ_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

#include "FtpServLicense.h"
#include "MarshalEvents.h"
#include "ftp_s.h"
#include "UTFtpServCP.h"

class CUT_FtpThreadEx;

/////////////////////////////////////////////////////////////////////////////
// CFtpServ
class ATL_NO_VTABLE CFtpServ : 
	public CUT_FTPServer,

	public CMarshalEvents<CFtpServ, &DIID__IFtpServEvents, TRUE>,

	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CFtpServ, IFtpServ, &IID_IFtpServ, &LIBID_UTFTPSERVLib>,
	public CComControl<CFtpServ>,
	public IPersistStreamInitImpl<CFtpServ>,
	public IOleControlImpl<CFtpServ>,
	public IOleObjectImpl<CFtpServ>,
	public IOleInPlaceActiveObjectImpl<CFtpServ>,
	public IViewObjectExImpl<CFtpServ>,
	public IOleInPlaceObjectWindowlessImpl<CFtpServ>,
	public IPersistStorageImpl<CFtpServ>,
	public IPersistPropertyBagImpl<CFtpServ>,
	public ISpecifyPropertyPagesImpl<CFtpServ>,
	public IDataObjectImpl<CFtpServ>,
	public IProvideClassInfo2Impl<&CLSID_FtpServ, &DIID__IFtpServEvents, &LIBID_UTFTPSERVLib>,
	public CProxy_IFtpServEvents< CFtpServ >,
	public IPropertyNotifySinkCP< CFtpServ >,
	public CComCoClass<CFtpServ, &CLSID_FtpServ>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CFtpServ>,
	public IObjectSafetyImpl<CFtpServ, INTERFACESAFE_FOR_UNTRUSTED_CALLER >

{

friend CProxy_IFtpServEvents< CFtpServ >;
friend CUT_FtpThreadEx;

public:
	CFtpServ();
	~CFtpServ();

DECLARE_REGISTRY_RESOURCEID(IDR_FTPSERV)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFtpServ)
	COM_INTERFACE_ENTRY(IFtpServ)
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

BEGIN_PROP_MAP(CFtpServ)
	PROP_ENTRY("Path", DISPID_PATH, CLSID_FtpServPropPage )
	PROP_ENTRY("MaxConnections", DISPID_MAX_CONNECTIONS, CLSID_FtpServPropPage )
	PROP_ENTRY("Port", DISPID_PORT, CLSID_FtpServPropPage )
	PROP_ENTRY("WelcomeMsg", DISPID_WELCOME_MSG, CLSID_FtpServPropPage )
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CFtpServ)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IFtpServEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CFtpServ)
	CHAIN_MSG_MAP(CComControl<CFtpServ>)
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
	DECLARE_CLASSFACTORY2(CFtpServLicense)

// IFtpServ
public:
	STDMETHOD(get_MaxTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_MaxTimeOut)(/*[in]*/ long newVal);
	STDMETHOD(GetCommandName)(/*[in]*/ FtpCommand CommandID, /*[out, retval]*/ BSTR *Name);
	STDMETHOD(get_WelcomeMsg)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_WelcomeMsg)(/*[in]*/ BSTR newVal);
	STDMETHOD(Stop)();
	STDMETHOD(get_Port)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Port)(/*[in]*/ long newVal);
	STDMETHOD(get_MaxConnections)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_MaxConnections)(/*[in]*/ long newVal);
	STDMETHOD(get_Connections)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Path)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Path)(/*[in]*/ BSTR newVal);
	STDMETHOD(Start)(/*[out, retval]*/ long *Result);
	STDMETHOD(AboutBox)();
	STDMETHOD(GetErrorText)(/*[in]*/ long ErrorCode, /*[out, retval]*/ BSTR *ErrorText);

	STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions);
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);


	HRESULT OnDraw(ATL_DRAWINFO& di);

// IFtpServ protected data members
protected:
	HICON				m_hFtpServIcon;			// Http server icon handle
	long				m_lFtpServPort;			// Http server listening port number
	BOOL				m_bGoingToClose;		// TRUE if we are going to destroy the control

	LPSTR				m_lpszWelcomeMsg;		// FTP server welcome message

	CComCriticalSection	m_EventLock;			// Event critical section object

	// Returns a pointer to an instance
	// of a class derived from CUT_WSThread
    CUT_WSThread	*CreateInstance();

	// This virtual function is called each time we have any
	// status information to display.
	virtual int		OnStatus(LPCSTR StatusText);

    // This virtual function is called each time the server 
    // accepting new connection.
    virtual long    OnCanAccept(LPCSTR address);

};

//=================================================================
//  class: CUT_FtpThread
//=================================================================

class CUT_FtpThreadEx : public CUT_FTPThread {

friend CFtpServ;

protected:

    // Over ride this to handle the max connection reached
    virtual void	OnMaxConnect();    
    
    // Over ride this to handle each client connection separatly
	virtual void	OnConnect();       

    // Override this function to implement your own server login message
    virtual void	OnWelcome();  
    
    // Override this function to implement your own password checking routines
    virtual int     OnCheckPassword(LPSTR user,LPSTR pass);  

    // Inform us of the client attepting to connects IP address
    virtual int     OnConnectNotify(LPCSTR ipAddress);             
    
    // Inform us when the client is disconnecting
    virtual void    OnDisconnect();                             

    // Override this function to enforce level of access on
    // each command for each client, or to provide alternate processing.
    virtual int     OnCommandStart(CommandID command,LPCSTR data); 

    // Inform us when the command has been processed 
    virtual void    OnCommandFinished(CommandID	command,LPCSTR data,int success); 
};

#endif //__FtpServ_H_
