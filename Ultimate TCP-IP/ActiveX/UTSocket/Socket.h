//=================================================================
//  class: CSocket
//  File:  Socket.h
//
//  Implementation of CSocket class
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

#ifndef __SOCKET_H_
#define __SOCKET_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "ut_clnt.h"	
#include "UTSocketCP.h"
#include "MarshalEvents.h"
#include "SocketLicense.h"
#include "UT_MethodQueue.h"

	// Types of methods
	typedef enum MethodTypeTag {
		METHOD_CONNECT,
		METHOD_CONNECT_BOUND,
		METHOD_CREATE_UDP_SOCKET,
		METHOD_WAIT_FOR_ACCEPT,
		METHOD_SEND,
		METHOD_SEND_FILE,
		METHOD_SEND_TO,
        METHOD_SEND_AS_LINE,
		METHOD_WAIT_FOR_SEND,
		METHOD_RECEIVE,
        METHOD_RECEIVE_FROM,
		METHOD_RECEIVE_LINE,
		METHOD_RECEIVE_TO_FILE,
		METHOD_CLOSE_CONNECTION,
		METHOD_RESET,
		METHOD_ACCEPT_CONNECTION
		} MethodType;


/////////////////////////////////////////////////////////////////////////////
// CSocket
class ATL_NO_VTABLE CSocket : 
	public CUT_MethodQueue<CSocket, MethodTypeTag>,
	public CMarshalEvents<CSocket, &DIID__ISocketEvents, TRUE>,

	public CUT_WSClient,

	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CSocket, ISocket, &IID_ISocket, &LIBID_UTSOCKETLib>,
	public CComControl<CSocket>,
	public IPersistStreamInitImpl<CSocket>,
	public IOleControlImpl<CSocket>,
	public IOleObjectImpl<CSocket>,
	public IOleInPlaceActiveObjectImpl<CSocket>,
	public IViewObjectExImpl<CSocket>,
	public IOleInPlaceObjectWindowlessImpl<CSocket>,
	public IPersistStorageImpl<CSocket>,
	public IPersistPropertyBagImpl<CSocket>,
	public ISpecifyPropertyPagesImpl<CSocket>,
	public IDataObjectImpl<CSocket>,
	public IProvideClassInfo2Impl<&CLSID_Socket, &DIID__ISocketEvents, &LIBID_UTSOCKETLib>,
	public CProxy_ISocketEvents< CSocket >,
	public IPropertyNotifySinkCP< CSocket >,
	public CComCoClass<CSocket, &CLSID_Socket>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CSocket>,
	public IObjectSafetyImpl<CSocket, INTERFACESAFE_FOR_UNTRUSTED_CALLER >

{
friend	CProxy_ISocketEvents< CSocket >;
friend	CUT_MethodQueue<CSocket, MethodTypeTag>;

public:
	CSocket();
	~CSocket();

DECLARE_REGISTRY_RESOURCEID(IDR_SOCKET)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSocket)
	COM_INTERFACE_ENTRY(ISocket)
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

BEGIN_PROP_MAP(CSocket)
	PROP_ENTRY("ConnectTimeOut", DISPID_CONNECT_TIME_OUT, CLSID_SocketPropPage )
	PROP_ENTRY("ReceiveTimeOut", DISPID_RECEIVE_TIME_OUT, CLSID_SocketPropPage )
	PROP_ENTRY("BlockingMode", DISPID_BLOCKING_MODE, CLSID_SocketPropPage )
	PROP_ENTRY("SocketType", DISPID_SOCKET_TYPE, CLSID_SocketPropPage )
	PROP_ENTRY("SocketProtocol", DISPID_SOCKET_PROTOCOL, CLSID_SocketPropPage )
	PROP_ENTRY("SocketFamily", DISPID_SOCKET_FAMILY, CLSID_SocketPropPage )
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CSocket)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__ISocketEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CSocket)
	CHAIN_MSG_MAP(CComControl<CSocket>)
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
	DECLARE_CLASSFACTORY2(CSocketLicense)


// ISocket
public:
    STDMETHOD(get_LastAcceptSocketError)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_LastSocketError)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_AcceptPort)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_LocalPort)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_RemotePort)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_SocketHandle)(/*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_RemoteHostIPAddress)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_IsConnected)(/*[out, retval]*/ VARIANT_BOOL *pVal);
    STDMETHOD(SendAsLine)(/*[in]*/ BSTR Line, /*[in,defvalue(0)]*/ long MaxLineLength, /*[out,retval]*/ long *Result);
	STDMETHOD(ReceiveFrom)(/*[in]*/ long MaxSize, /*[out, retval]*/ long *Result);
	STDMETHOD(get_LastReceivedData)(/*[out, retval]*/ VARIANT *pVal);
    STDMETHOD(get_LastReceivedLine)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(IsIPAddress)(/*[in]*/ BSTR Address, /*[out, retval]*/ BOOL *Result);
	STDMETHOD(GetSocketOption)(/*[in]*/ long OptionType, /*[out, retval]*/ long *OptionData);
	STDMETHOD(SetSocketOption)(/*[in]*/ long OptionType, /*[in]*/ long OptionData, /*[out, retval]*/ long *Result);
	STDMETHOD(ReceiveToFile)(/*[in]*/ BSTR FileName, /*[in]*/ FileWriteType Type, /*[out, retval]*/ long *Result);
	STDMETHOD(ReceiveLine)(/*[out, retval]*/ long *Result);
	STDMETHOD(Receive)(/*[in]*/ long MaxSize, /*[out, retval]*/ long *Result);
	STDMETHOD(WaitForSend)(/*[in]*/ long Seconds, /*[in, defaultvalue(0)]*/ long MilliSeconds, /*[out, retval]*/ long *Result);
	STDMETHOD(SendTo)(/*[in]*/ VARIANT Data, BSTR Address, long Port, /*[out, retval]*/ long *Result);
	STDMETHOD(SendFile)(/*[in]*/ BSTR FileName, /*[out, retval]*/ long *Result);
	STDMETHOD(Send)(/*[in]*/ VARIANT Data, /*[out, retval]*/ long *Result);
	STDMETHOD(WaitForAccept)(/*[in]*/ long Seconds, /*[out, retval]*/ long *Result);
	STDMETHOD(Listen)(/*[in]*/ long Port, /*[in,defaultvalue("")]*/ BSTR Address, /*[in,defaultvalue(1)]*/ long QueueSize, /*[out, retval]*/ long *Result);
	STDMETHOD(CreateUDPSocket)(/*[in]*/ long LocalPort, /*[in]*/ long RemotePort, /*[in]*/ BSTR RemoteAddress, /*[in, defaultvalue("")]*/ BSTR LocalAddress, /*[out, retval]*/ long * Result);
	STDMETHOD(ConnectBound)(/*[in]*/ long LocalPort, /*[in]*/ long RemotePort, /*[in]*/ BSTR LocalAddress, /*[in]*/ BSTR RemoteAddress, /*[out, retval]*/ long * Result);
	STDMETHOD(Connect)(/*[in]*/ BSTR Address, /*[in]*/ long Port, /*[out, retval]*/ long * Result);
	STDMETHOD(GetHostAddress)(VARIANT_BOOL UseCurrentConnectAddr, /*[out, retval]*/ BSTR *Address);
	STDMETHOD(GetNameFromAddress)(/*[in]*/ BSTR Address, /*[out, retval]*/ BSTR *Name);
	STDMETHOD(GetAddressFromName)(/*[in]*/ BSTR Name, /*[out, retval]*/ BSTR *Address);
	STDMETHOD(IsDataWaiting)(/*[out, retval]*/ BOOL *Result);
	STDMETHOD(get_MaxSend)(/*[out, retval]*/ long *pVal);
    STDMETHOD(put_MaxSend)(/*[in]*/ long newVal);
	STDMETHOD(get_MaxReceive)(/*[out, retval]*/ long *pVal);
    STDMETHOD(put_MaxReceive)(/*[in]*/ long newVal);
	STDMETHOD(AcceptConnection)(/*[out, retval]*/ long *Result);
	STDMETHOD(Reset)(/*[out, retval]*/ long *Result);
	STDMETHOD(CloseConnection)(/*[out, retval]*/ long *Result);
	STDMETHOD(get_Protocol)(/*[out, retval]*/ SocketProtocol *pVal);
	STDMETHOD(put_Protocol)(/*[in]*/ SocketProtocol newVal);
	STDMETHOD(get_Family)(/*[out, retval]*/ SocketFamily *pVal);
	STDMETHOD(put_Family)(/*[in]*/ SocketFamily newVal);
	STDMETHOD(get_Type)(/*[out, retval]*/ SocketType *pVal);
	STDMETHOD(put_Type)(/*[in]*/ SocketType newVal);
	STDMETHOD(get_SendTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_SendTimeOut)(/*[in]*/ long newVal);
	STDMETHOD(AboutBox)();
	STDMETHOD(CancelTransfer)();
	STDMETHOD(GetErrorText)(/*[in]*/ long ErrorCode, /*[out, retval]*/ BSTR *ErrorText);
	STDMETHOD(get_ConnectTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ConnectTimeOut)(/*[in]*/ long newVal);
	STDMETHOD(get_ReceiveTimeOut)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ReceiveTimeOut)(/*[in]*/ long newVal);
	STDMETHOD(get_BlockingMode)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_BlockingMode)(/*[in]*/ VARIANT_BOOL newVal);

	STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions);
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);

	HRESULT OnDraw(ATL_DRAWINFO& di);

// ISocket Private data members
private:
	HICON				m_hSocketIcon;			// Socket icon handle
	BOOL				m_bAbortFlag;			// TRUE if we are going to abort Socket
	BOOL				m_bGoingToClose;		// TRUE if the control is going to be destroyed
	BOOL				m_bBlockingMode;		// TRUE if we are working in blocking mode
    long				m_nConnectTimeout;      // Connect time out
	long				m_nSendTimeout;			// Send time out 
	long				m_nReceiveTimeout;		// Receive time out 
	long				m_nPort;				// port number
    SAFEARRAY           *m_arrayLastLine;       // Last received data
    _bstr_t             m_bstrLastReceived;     // Last received line

    void                SetSafeArrayData(SAFEARRAY **ppsa, LPCSTR buffer, int size);

public:

    // Execute specified method
	virtual long		ExecuteMethod(MethodTypeTag MethodID, _variant_t *ptrVarParams, BOOL bForceNonBlocking);

	// Waits for the object to be signaled
	BOOL				WaitWithMsgLoop(HANDLE hEvent, long lTimeout);

	// Return TRUE if we are going to abort operation
	virtual BOOL		IsAborted();
    
    // Monitor progress and/or cancel the receive 
    virtual BOOL		ReceiveFileStatus(long bytesReceived);

    // Monitor progress and/or cancel the send
    virtual BOOL		SendFileStatus(long bytesSent);


};

#endif //__SOCKET_H_
