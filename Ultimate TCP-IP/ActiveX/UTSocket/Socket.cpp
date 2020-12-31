//=================================================================
//  class: CSocket
//  File:  Socket.cpp
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


#include "stdafx.h"
#include "UTSocket.h"
#include "Socket.h"

#include <process.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include "ut_clnt.h"
#include "AboutDlg.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

/////////////////////////////////////////////////////////////////////////////
// CSocket
/////////////////////////////////////////////////////////////////////////////

/***************************************************
CSocket
	Standart constructor. 
Params
    none
Return
	none
****************************************************/
CSocket::CSocket() : CUT_MethodQueue<CSocket, MethodTypeTag>(this),
		m_nConnectTimeout(5),			// Initialize connect timeout
		m_nSendTimeout(30),				// Initialize send timeout
		m_nReceiveTimeout(30),			// Initialize receive timeout
		m_bBlockingMode(FALSE),			// Set non blocking mode as default
		m_bGoingToClose(FALSE),			// Initialize closing flag with FALSE
		m_bAbortFlag(FALSE),  			// Clear abort flag
        m_bstrLastReceived(L""),        // Initialize last received line
        m_arrayLastLine(NULL)           // Initialize last received data
{
	// Load Socket Icon
	m_hSocketIcon = LoadIcon(_Module.m_hInst, MAKEINTRESOURCE(IDI_ICON_SOCKET));	

	// Initiate default control size 32 x 32 pixels
    SIZE	sz = { 32, 32 };
    AtlPixelToHiMetric (&sz, &m_sizeExtent);		// convert pixels to himetric
    m_sizeNatural	= m_sizeExtent;					// store natural extent

	// Disable resizing of the control
	m_bAutoSize		= TRUE;				
}

/***************************************************
~CSocket
	Destructor.
Params
    none
Return
	none
****************************************************/
CSocket::~CSocket()
{
	// Set flags to terminate all running threads
	m_bGoingToClose	= TRUE;
	m_bAbortFlag	= TRUE;

	// If thread is running - will wait till it exits
	// or will time-out. 
	if(m_hMethodThread != NULL) {
		// Resume working thread
		ResumeThread(m_hMethodThread);	

		// Wait for thread termination
		WaitWithMsgLoop(m_hMethodThread, max(120000, m_nConnectTimeout *1000));

	//	Sleep(1000);
		}

	// Destroy Socket icon handle
	if(m_hSocketIcon) {
		DestroyIcon( m_hSocketIcon );							
		m_hSocketIcon = NULL;
		}

    // Destroy safe array
    if(m_arrayLastLine != NULL) 
        SafeArrayDestroy(m_arrayLastLine);

}

/***************************************************
InterfaceSupportsErrorInfo
	Checks if specified interface supports error
	information.
Params
    riid	- inteface id
Return
	S_OK	- support error info
	S_FALSE - don't support error info
****************************************************/
STDMETHODIMP CSocket::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISocket,
	};
	for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

/***************************************************
OnDraw
	Draw the icon
Params
    di	- A reference to the ATL_DRAWINFO structure
Return
	S_OK	- success
****************************************************/
HRESULT CSocket::OnDraw(ATL_DRAWINFO& di)
{
	// Fill background & draw a boreder
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	// Draw Socket Icon
	if(m_hSocketIcon)
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hSocketIcon);	
 		
	return S_OK;
}


////////////////////////////////////////////////////
//	ISocket interface properties Set/Get functions
////////////////////////////////////////////////////

/***************************************************
get_ConnectTimeOut
	Get connect time-out value
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CSocket::get_ConnectTimeOut(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = m_nConnectTimeout;
	return S_OK;
}

/***************************************************
put_ConnectTimeOut
	Set connect time-out value
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CSocket::put_ConnectTimeOut(long newVal)
{
	if(newVal == m_nConnectTimeout)	return S_OK;

	if(FireOnRequestEdit(DISPID_CONNECT_TIME_OUT) == S_FALSE)
		return S_FALSE;

	if(newVal >= 0) {
		m_nConnectTimeout = newVal;
		m_bRequiresSave = TRUE;

		FireOnChanged(DISPID_CONNECT_TIME_OUT);

		SendOnDataChange(NULL);
		}
	else 
		return AtlReportError(CLSID_Socket,"Invalid Connect Time Out value", IID_ISocket, E_FAIL);


	return S_OK;
}

/***************************************************
get_ReceiveTimeOut
	Get receive time-out value
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CSocket::get_ReceiveTimeOut(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = m_nReceiveTimeout;
	return S_OK;
}

/***************************************************
put_ReceiveTimeOut
	Set receive time-out value
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CSocket::put_ReceiveTimeOut(long newVal)
{
	if(newVal == m_nReceiveTimeout)	return S_OK;

	if(FireOnRequestEdit(DISPID_RECEIVE_TIME_OUT) == S_FALSE)
		return S_FALSE;

	if(newVal >= 0) {
		m_nReceiveTimeout = newVal;
		CUT_WSClient::SetReceiveTimeOut(m_nReceiveTimeout*1000);
		
		m_bRequiresSave = TRUE;

		FireOnChanged(DISPID_RECEIVE_TIME_OUT);

		SendOnDataChange(NULL);
		}
	else 
		return AtlReportError(CLSID_Socket,"Invalid Receive Time Out value", IID_ISocket,E_FAIL);

	return S_OK;
}

/***************************************************
get_BlockingMode
	Get blocking mode value
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CSocket::get_BlockingMode(VARIANT_BOOL *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = m_bBlockingMode;
	return S_OK;
}

/***************************************************
put_BlockingMode
	Set blocking mode value
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CSocket::put_BlockingMode(VARIANT_BOOL newVal)
{
	if(newVal == m_bBlockingMode)	return S_OK;

	if(FireOnRequestEdit(DISPID_BLOCKING_MODE) == S_FALSE)
		return S_FALSE;

	m_bBlockingMode = newVal;

	m_bRequiresSave = TRUE;
	FireOnChanged(DISPID_BLOCKING_MODE);
	SendOnDataChange(NULL);

	return S_OK;
}

/***************************************************
get_SendTimeOut
	Get send time-out value
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CSocket::get_SendTimeOut(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = m_nSendTimeout;
	return S_OK;
}

/***************************************************
put_SendTimeOut
	Set send time-out value
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CSocket::put_SendTimeOut(long newVal)
{
	if(newVal == m_nSendTimeout)	return S_OK;

	if(FireOnRequestEdit(DISPID_SEND_TIME_OUT) == S_FALSE)
		return S_FALSE;

	if(newVal >= 0) {
		m_nSendTimeout = newVal;
		CUT_WSClient::SetSendTimeOut(m_nSendTimeout*1000);
		
		m_bRequiresSave = TRUE;

		FireOnChanged(DISPID_SEND_TIME_OUT);

		SendOnDataChange(NULL);
		}
	else 
		return AtlReportError(CLSID_Socket,"Invalid Send Time Out value", IID_ISocket,E_FAIL);

	return S_OK;
}

/***************************************************
get_Type
	Get socket type
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CSocket::get_Type(SocketType *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = (SocketType)m_nSockType;
	return S_OK;
}

/***************************************************
put_Type
	Set socket type
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CSocket::put_Type(SocketType newVal)
{
	if(newVal == (SocketType)m_nSockType)	return S_OK;

	if(FireOnRequestEdit(DISPID_SOCKET_TYPE) == S_FALSE)
		return S_FALSE;

	m_nSockType = newVal;
	
	m_bRequiresSave = TRUE;

	FireOnChanged(DISPID_SOCKET_TYPE);

	SendOnDataChange(NULL);

	return S_OK;
}

/***************************************************
get_Family
	Get socket family
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CSocket::get_Family(SocketFamily *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = (SocketFamily)m_nFamily;
	return S_OK;
}

/***************************************************
put_Family
	Set socket family
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CSocket::put_Family(SocketFamily newVal)
{
	if(newVal == (SocketFamily)m_nFamily)	return S_OK;

	if(FireOnRequestEdit(DISPID_SOCKET_FAMILY) == S_FALSE)
		return S_FALSE;

	m_nFamily = newVal;
	
	m_bRequiresSave = TRUE;

	FireOnChanged(DISPID_SOCKET_FAMILY);

	SendOnDataChange(NULL);

	return S_OK;
}

/***************************************************
get_Protocol
	Get socket protocol
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CSocket::get_Protocol(SocketProtocol *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = (SocketProtocol)m_nProtocol;
	return S_OK;
}

/***************************************************
put_Protocol
	Set socket protocol
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CSocket::put_Protocol(SocketProtocol newVal)
{
	if(newVal == (SocketProtocol)m_nProtocol)	return S_OK;

	if(FireOnRequestEdit(DISPID_SOCKET_PROTOCOL) == S_FALSE)
		return S_FALSE;

	m_nProtocol = newVal;
	
	m_bRequiresSave = TRUE;

	FireOnChanged(DISPID_SOCKET_PROTOCOL);

	SendOnDataChange(NULL);

	return S_OK;
}


/***************************************************
get_MaxReceive
	Returns the maximum number of bytes that can
    be received at once.
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CSocket::get_MaxReceive(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = CUT_WSClient::GetMaxReceive();
	return S_OK;
}

/***************************************************
put_MaxReceive
	Sets the maximum number of bytes that can
    be received at once.
Params
    newVal	- new value of the property
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CSocket::put_MaxReceive(long newVal)
{
	CUT_WSClient::SetMaxReceive(newVal);
	return S_OK;
}

/***************************************************
get_MaxSend
	Returns the maximum number of bytes that can be
    sent at once. By sending full packets total 
    throughput is increased.
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CSocket::get_MaxSend(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = CUT_WSClient::GetMaxSend();
	return S_OK;
}

/***************************************************
put_MaxSend
	Sets the maximum number of bytes that can be
    sent at once. By sending full packets total 
    throughput is increased.
Params
    newVal	- new value of the property
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CSocket::put_MaxSend(long newVal)
{
	CUT_WSClient::SetMaxSend(newVal);
	return S_OK;
}

/***************************************************
get_LastReceivedLine
	Returns last received data. Call ReceiveLine method
    prior to this call
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CSocket::get_LastReceivedLine(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

 	if(!SysReAllocString(pVal, m_bstrLastReceived))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_LastReceivedData
	Returns last received data. Call Receive or ReceiveFrom
    methods prior to this call
Params
    pVariant	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CSocket::get_LastReceivedData(VARIANT *pVariant)
{
	if(pVariant == NULL)	return E_POINTER;

    VariantInit(pVariant);
    pVariant->vt = VT_ARRAY | VT_UI1;
    pVariant->parray = m_arrayLastLine;
	return S_OK;
}

/***************************************************
get_IsConnected
	Gets the connected state
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CSocket::get_IsConnected(VARIANT_BOOL *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = CUT_WSClient::IsConnected();
    return S_OK;
}

/***************************************************
get_RemoteHostIPAddress
	Gets the connected remote host IP address
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CSocket::get_RemoteHostIPAddress(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

 	if(!SysReAllocString(pVal, _bstr_t(m_szAddress)))
 		return E_OUTOFMEMORY;

    return S_OK;
}

/***************************************************
get_SocketHandle
	Gets socket handle
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CSocket::get_SocketHandle(LONG *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = (long) m_socket;
    return S_OK;
}

/***************************************************
get_RemotePort
	Gets remote port
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CSocket::get_RemotePort(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

    *pVal = (long) CUT_WSClient::GetRemotePort();
    return S_OK;
}

/***************************************************
get_LocalPort
	Gets local port
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CSocket::get_LocalPort(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = (long) CUT_WSClient::GetLocalPort();
    return S_OK;
}

/***************************************************
get_AcceptPort
	Gets accept port
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CSocket::get_AcceptPort(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = (long) CUT_WSClient::GetAcceptPort();
    return S_OK;
}

/***************************************************
get_LastSocketError
	Gets socket error string
Params
    pVal    - pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CSocket::get_LastSocketError(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

 	if(!SysReAllocString(pVal, _bstr_t(CUT_ERR::GetSocketError(&m_socket))))
 		return E_OUTOFMEMORY;

    return S_OK;
}

/***************************************************
get_LastAcceptSocketError
	Gets accept socket error string
Params
    pVal    - pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CSocket::get_LastAcceptSocketError(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

 	if(!SysReAllocString(pVal, _bstr_t(CUT_ERR::GetSocketError(&m_serverSocket))))
 		return E_OUTOFMEMORY;

	return S_OK;
}

////////////////////////////////////////////////////
//	ISocket interface methods
////////////////////////////////////////////////////

/***************************************************
IsIPAddress
	Checks to see if the given string has a vaild
    IP address format. Note: it does not check the
    IP value itself only the format.
Params
    Address		- address to check
	Result		- pointer to the variable receiving the result
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CSocket::IsIPAddress(BSTR Address, BOOL *Result)
{
	*Result = CUT_WSClient::IsIPAddress((LPCTSTR)_bstr_t(Address));
	return S_OK;
}

/***************************************************
CancelTransfer
	Cancel current Socket transfer operations
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CSocket::CancelTransfer()
{
	m_bAbortFlag = TRUE;
	return S_OK;
}

/***************************************************
AboutBox
	Display about box
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CSocket::AboutBox()
{
	CAboutDlg	dlg;

	dlg.DoModal();
	return S_OK;
}

/***************************************************
GetErrorText
	Returns a string representation of numeric error code.
Params
	ErrorCode	- number of error code
	ErrorText	- pointer to the error text varaible
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CSocket::GetErrorText(long ErrorCode, BSTR *ErrorText)
{
 	HRESULT		hResult			= S_OK;
 	CComBSTR	bstrErrorMsg	= CUT_ERR::GetErrorString(ErrorCode);
 
 	if(!SysReAllocString(ErrorText, bstrErrorMsg))
 		hResult = E_OUTOFMEMORY;
 
 	return hResult;
}

/***************************************************
GetAddressFromName
	Returns the address associated with the given name
Params
	Name	- name to lookup
	Address - pointer to the variable receiving the address
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CSocket::GetAddressFromName(BSTR Name, BSTR *Address)
{
	char	buffer[WSC_BUFFER_SIZE + 1] = "";

	if(CUT_WSClient::GetAddressFromName(_bstr_t(Name), buffer, WSC_BUFFER_SIZE) != UTE_SUCCESS)
		buffer[0] = 0;

 	if(!SysReAllocString(Address, _bstr_t(buffer)))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
GetNameFromAddress
	Returns the name associated with the given address
Params
	Address	- address to lookup
	Name	- pointer to the variable receiving the name
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CSocket::GetNameFromAddress(BSTR Address, BSTR *Name)
{
	char	buffer[WSC_BUFFER_SIZE + 1] = "";

	if(CUT_WSClient::GetNameFromAddress(_bstr_t(Address), buffer, WSC_BUFFER_SIZE) != UTE_SUCCESS)
		buffer[0] = 0;

 	if(!SysReAllocString(Name, _bstr_t(buffer)))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
GetHostAddress
	Returns the address of the local machine.
    It is possible for this function to fail
    since it is not guaranteed to be available
    in a winsock implementation 
Params
	Address - pointer to the variable receiving the address
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CSocket::GetHostAddress(VARIANT_BOOL UseCurrentConnectAddr, BSTR *Address)
{
	char	buffer[WSC_BUFFER_SIZE + 1] = "";

	if(CUT_WSClient::GetHostAddress(buffer, WSC_BUFFER_SIZE, (BOOL)UseCurrentConnectAddr) != UTE_SUCCESS)
		buffer[0] = 0;

 	if(!SysReAllocString(Address, _bstr_t(buffer)))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
SetSocketOption
	Sets the current value for the socket option 
    associated with the client socket
Params
	Address - pointer to the variable receiving the address
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CSocket::SetSocketOption(long OptionType, long OptionData, long *Result)
{
	int	Data = (long)OptionData;
	*Result = CUT_WSClient::SetSocketOption(OptionType, &Data);

	return S_OK;
}

/***************************************************
GetSocketOption
	Retrieves the current value for the socket option 
    associated with the client socket
Params
	Address - pointer to the variable receiving the address
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CSocket::GetSocketOption(long OptionType, long *OptionData)
{
	if(OptionData == NULL)	return E_POINTER;

	int	Data = 0;
	CUT_WSClient::GetSocketOption(OptionType, &Data);
	*OptionData = (long)Data;

	return S_OK;
}

/***************************************************
IsDataWaiting
	Returns if data is immediately available for receiving.
Params
	Result - pointer to the variable receiving the result
Return
	S_OK			- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CSocket::IsDataWaiting(BOOL *Result)
{
	if(Result == NULL)	return E_POINTER;

	*Result = CUT_WSClient::IsDataWaiting();
	return S_OK;
}

/***************************************************
Connect
	Connects to a specified port
Params
	Address	- address to connect to (ex."204.64.75.73")
	Result	- pointer to the variable receiving the result
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CSocket::Connect(BSTR Address, long Port, long *Result)
{
	AddMethod(METHOD_CONNECT, Result, _VP((long)Port), _VP(Address), _VP((long)m_nConnectTimeout), _VP((long)m_nFamily), _VP((long)m_nSockType), NULL);
	return S_OK;
}

/***************************************************
ConnectBound
	Connects to a specified port from a specified port
Params
    LocalPort		- local port to connect the socket to
    RemotePort		- remote port to connect the socket to
    LocalAddress	- local address to connect to
    RemoteAddress	- remote address to connect to
	Result			- pointer to the variable receiving the result
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CSocket::ConnectBound(long LocalPort, long RemotePort, BSTR LocalAddress, BSTR RemoteAddress, long *Result)
{
	AddMethod(METHOD_CONNECT_BOUND, Result, _VP(LocalPort), _VP(RemotePort), _VP(LocalAddress), _VP(RemoteAddress), _VP((long)m_nFamily), _VP((long)m_nSockType), NULL);
	return S_OK;
}

/***************************************************
CreateUDPSocket
	Creates a socket for UDP use.  The socket is 
    setup and bound to the given ports, but 
    no connection is made
Params
    LocalPort		- local port to bind socket to
    RemotePort		- port to use when SendTo and 
					  ReceiveFrom are used
    RemoteAddress	- addresess to use when using
                      SendTo and ReceiveFrom
	[LocalAddress]	- local address to bind the socket to
	Result			- pointer to the variable receiving the result
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CSocket::CreateUDPSocket(long LocalPort, long RemotePort, BSTR RemoteAddress, BSTR LocalAddress, long *Result)
{
	AddMethod(METHOD_CREATE_UDP_SOCKET, Result, _VP(LocalPort), _VP(RemotePort), _VP(RemoteAddress), _VP(LocalAddress), NULL);
	return S_OK;
}

/***************************************************
Listen
	Creates a socket and binds it to the given port
    and address. Then puts the socket in a listening state
Params
    Port		- port to listen on
    Address		- address to listen on
	QueSize		- que size for incomming connections
	Result		- pointer to the variable receiving the result
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CSocket::Listen(long Port, BSTR Address, long QueueSize, long *Result)
{
	unsigned long	nAddress; 
	_bstr_t			bstrAddress = Address; 

	if(bstrAddress.length() > 0)
		nAddress = inet_addr(bstrAddress);
	else
		nAddress = htonl(INADDR_ANY);	

	*Result = CUT_WSClient::WaitForConnect(	(unsigned short)Port,
											(int)QueueSize,
											(short)m_nFamily, 
											nAddress);
	return S_OK;
}

/***************************************************
WaitForAccept
	Waits up til the specified time to see if there
    is an incomming connection waiting with a read set. If this 
    function returns UTE_SUCCESS then call 
    AcceptConnection to connect.
Params
    Seconds	- the max. number of seconds to wait
	Result	- pointer to the variable receiving the result
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CSocket::WaitForAccept(long Seconds, long *Result)
{
	AddMethod(METHOD_WAIT_FOR_ACCEPT, Result, _VP(Seconds), NULL);
	return S_OK;
}

/***************************************************
Send
	Sends the given data to the client.
Params
    Data	- data to send
	Result	- pointer to the variable receiving the result
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CSocket::Send(VARIANT Data, long *Result)
{
	AddMethod(METHOD_SEND, Result, _VP(Data), NULL);
	return S_OK;
}

/***************************************************
SendAsLine
	Sends the given data to the client.
Params
    Line	- data to send
    MaxLineLength
	Result	- pointer to the variable receiving the result
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CSocket::SendAsLine(BSTR Line, long MaxLineLength, long *Result)
{
	AddMethod(METHOD_SEND_AS_LINE, Result, _VP(Line), _VP(MaxLineLength), NULL);
	return S_OK;
}


/***************************************************
SendFile
	Sends the specified file accross the connection
Params
    FileName	- file to send
	Result		- pointer to the variable receiving the result
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CSocket::SendFile(BSTR FileName, long *Result)
{
	AddMethod(METHOD_SEND_FILE, Result, _VP(FileName), NULL);
	return S_OK;
}

/***************************************************
SendTo
	Sends the specified data accross the UDP
    connection (See CreateUDPSocket)
Params
    Data	- data to send
	Result	- pointer to the variable receiving the result
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CSocket::SendTo(VARIANT Data, BSTR Address, long Port, long *Result)
{
	AddMethod(METHOD_SEND_TO, Result, _VP(Data), _VP(Address), _VP(Port), NULL);
	return S_OK;
}

/***************************************************
WaitForSend
	Waits up til the specified time to see if the
    connection is ready to send data if it is then
    it will return UTE_SUCCESS
Params
    Seconds			- max. seconds to wait
    MilliSeconds	- max. milli seconds to wait
	Result			- pointer to the variable receiving the result
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CSocket::WaitForSend(long Seconds, long MilliSeconds, long *Result)
{
	AddMethod(METHOD_WAIT_FOR_SEND, Result, _VP(Seconds), _VP(MilliSeconds), NULL);
	return S_OK;
}

/***************************************************
Receive
	Receives data from the remote connection
Params
    MaxSize	- maximum size of data to receive
	Result	- pointer to the variable receiving the result
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CSocket::Receive(long MaxSize, long *Result)
{
    if(m_arrayLastLine != NULL) {
        SafeArrayDestroy(m_arrayLastLine);
        m_arrayLastLine = NULL;
        }
	AddMethod(METHOD_RECEIVE, Result, _VP(MaxSize), NULL);
	return S_OK;
}

/***************************************************
ReceiveFrom
	Receives data from the UDP 
Params
    MaxSize	- maximum size of data to receive
	Result	- pointer to the variable receiving the result
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CSocket::ReceiveFrom(long MaxSize, long *Result)
{
    if(m_arrayLastLine != NULL) {
        SafeArrayDestroy(m_arrayLastLine);
        m_arrayLastLine = NULL;
        }

	AddMethod(METHOD_RECEIVE_FROM, Result, _VP(MaxSize), NULL);
	return S_OK;
}

/***************************************************
ReceiveLine
	Receives a line of data. This function will receive data
    until the maxDataLen is reached or a '\r\n' is encountered.
Params
	Result	- pointer to the variable receiving the result
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CSocket::ReceiveLine(long *Result)
{
    m_bstrLastReceived = L"";
	AddMethod(METHOD_RECEIVE_LINE, Result, NULL);
	return S_OK;
}

/***************************************************
ReceiveToFile
	Receives data from the current connection directly
    to a file.
Params
    FileName	- name of file to copy received data into
    Type		- FileTruncate/FileAdd
	Result		- pointer to the variable receiving the result
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CSocket::ReceiveToFile(BSTR FileName, FileWriteType Type, long *Result)
{
	AddMethod(METHOD_RECEIVE_TO_FILE, Result, _VP(FileName), _VP((long)Type), NULL);
	return S_OK;
}
		
/***************************************************
CloseConnection
	Call this function to close any used and/or
    open port. 
Params
	Result		- pointer to the variable receiving the result
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CSocket::CloseConnection(long *Result)
{
	AddMethod(METHOD_CLOSE_CONNECTION, Result, NULL);
	return S_OK;
}

/***************************************************
Reset
	Shuts down and restarts the winsock DLL
Params
	Result		- pointer to the variable receiving the result
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CSocket::Reset(long *Result)
{
	AddMethod(METHOD_RESET, Result, NULL);
	return S_OK;
}

/***************************************************
AcceptConnection
	This function is used to accept a connection
    once a socket is set up for listening see:
    Listen
    To see if a connection is waiting call:
    WaitForAccept
Params
	Result		- pointer to the variable receiving the result
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CSocket::AcceptConnection(long *Result)
{
	AddMethod(METHOD_ACCEPT_CONNECTION, Result, NULL);
	return S_OK;
}

/***************************************************
IsAborted
    This virtual function is called during time consuming
	operations to check if we want to abort operatin
Params
    none
Return
    TRUE	- abort operation
	FALSE	- continue
****************************************************/
BOOL CSocket::IsAborted() {
	return m_bAbortFlag;
}

/***************************************************
ReceiveFileStatus
    This virtual function is called during a 
    ReceiveToFile function.
Params
    bytesReceived - number of bytes received so far
Return
    TRUE - allow the receive to continue
    FALSE - abort the receive
****************************************************/
BOOL CSocket::ReceiveFileStatus(long bytesReceived){
	m_bUseMarshaling = !m_bBlockingMode; 
	Fire_OnReceiveFileProgress(bytesReceived);
    return !IsAborted();
}
/***************************************************
SendFileStatus
    This virtual function is called during a 
    SendFile function.
Params
    bytesSent - number of bytes sent so far
Return
    TRUE - allow the send to continue
    FALSE - abort the send
****************************************************/
BOOL CSocket::SendFileStatus(long bytesSent){
	m_bUseMarshaling = !m_bBlockingMode; 
	Fire_OnSendFileProgress(bytesSent);
    return !IsAborted();
}

/***************************************************
GetInterfaceSafetyOptions
	Gets inteface safety options
Params
	riid				- interface ID
	pdwSupportedOptions	- supported options
	pdwEnabledOptions	- enabled options
Return
	S_OK			- success
	E_NOINTERFACE	- no such interface
	E_FAIL			- failed
****************************************************/
STDMETHODIMP CSocket::GetInterfaceSafetyOptions(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
{

	ATLTRACE(_T("CObjectSafetyImpl::GetInterfaceSafetyOptions\n"));

	if (!pdwSupportedOptions || !pdwEnabledOptions)
		return E_FAIL;

	LPUNKNOWN pUnk;
	if (_InternalQueryInterface (riid, (void**)&pUnk) == E_NOINTERFACE) {
		// Our object doesn't even support this interface.
		return E_NOINTERFACE;
		}
	else {
		// Cleanup after ourselves.
		pUnk->Release();
		pUnk = NULL;
		}

	if (riid == IID_IDispatch) {
		// IDispatch is an interface used for scripting. If your
		// control supports other IDispatch or Dual interfaces, you
		// may decide to add them here as well. Client wants to know
		// if object is safe for scripting. Only indicate safe for
		// scripting when the interface is safe.
		*pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER;
		*pdwEnabledOptions = m_dwCurrentSafety & INTERFACESAFE_FOR_UNTRUSTED_CALLER;
		return S_OK;
		}
	else if ((riid == IID_IPersistStreamInit) || (riid == IID_IPersistStorage) || (riid == IID_IPersistPropertyBag)) {
		// IID_IPersistStreamInit and IID_IPersistStorage are
		// interfaces used for Initialization. If your control
		// supports other Persistence interfaces, you may decide to
		// add them here as well. Client wants to know if object is
		// safe for initializing. Only indicate safe for initializing
		// when the interface is safe.
		*pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA;
		*pdwEnabledOptions = m_dwCurrentSafety & INTERFACESAFE_FOR_UNTRUSTED_DATA;
		return S_OK;
		}
	else {
		// We are saying that no other interfaces in this control are
		// safe for initializing or scripting.
		*pdwSupportedOptions = 0;
		*pdwEnabledOptions = 0;
		return E_FAIL;
		}
   }


/***************************************************
SetInterfaceSafetyOptions
	Sets inteface safety options
Params
	riid				- interface ID
	dwOptionSetMask		- options mask
	pdwEnabledOptions	- enabled options
Return
	S_OK			- success
	E_NOINTERFACE	- no such interface
	E_FAIL			- failed
****************************************************/
STDMETHODIMP CSocket::SetInterfaceSafetyOptions(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
{

	ATLTRACE(_T("CObjectSafetyImpl::SetInterfaceSafetyOptions\n"));

	if (!dwOptionSetMask && !dwEnabledOptions) return E_FAIL;
   
	LPUNKNOWN pUnk;
	if (_InternalQueryInterface (riid, (void**)&pUnk) == E_NOINTERFACE) {
		// Our object doesn't even support this interface.
		return E_NOINTERFACE;
		}
	else {
		// Cleanup after ourselves.
		pUnk->Release();
		pUnk = NULL;
		}

	// Store our current safety level to return in
	// GetInterfaceSafetyOptions
	m_dwCurrentSafety |= dwEnabledOptions & dwOptionSetMask;
	if ((riid == IID_IDispatch) && (m_dwCurrentSafety & INTERFACESAFE_FOR_UNTRUSTED_CALLER)) {
		// Client wants us to disable any functionality that would
		// make the control unsafe for scripting. The same applies to
		// any other IDispatch or Dual interfaces your control may
		// support. Because our control is safe for scripting by
		// default we just return S_OK.
		return S_OK;
		}
	else if (((riid == IID_IPersistStreamInit) || (riid == IID_IPersistStorage) || (riid == IID_IPersistPropertyBag)) &&
             (m_dwCurrentSafety & INTERFACESAFE_FOR_UNTRUSTED_DATA)) {
		// Client wants us to make the control safe for initializing
		// from persistent data. For these interfaces, this control
		// is safe so we return S_OK. For Any interfaces that are not
		// safe, we would return E_FAIL.
		return S_OK;
		}
	else {
		// This control doesn't allow Initialization or Scripting
		// from any other interfaces so return E_FAIL.
		return E_FAIL;
		}
}

/***************************************************
WaitWithMsgLoop
    Waits for the object to be signaled, meanwhile 
	dispatching window messages as needed. Analog of
	AtlWaitWithMessageLoop() but supports timeouts.
Params
    hEvent	- event to wait
	lTimeot	- timeout
Return
	TRUE	- signaled
	FALSE	- timeout
****************************************************/
BOOL CSocket::WaitWithMsgLoop(HANDLE hEvent, long lTimeout)
{
	struct _timeb	tstruct;
	DWORD			dwStartTime, dwCurTime;
	DWORD			dwRet;
	MSG				msg;
    
	if (hEvent == NULL)
		return TRUE;

	// Get current time
	_ftime( &tstruct );
	dwStartTime  =	tstruct.millitm + (DWORD)(tstruct.time * 1000);

	while(1)
	{
		// Wait for our event or any message 
		dwRet = MsgWaitForMultipleObjects(1, &hEvent, FALSE, lTimeout, QS_ALLINPUT);

		if (dwRet == WAIT_OBJECT_0)
			return TRUE;    // The event was signaled

		if (dwRet != WAIT_OBJECT_0 + 1)
		{
			// 
			dwRet = MsgWaitForMultipleObjects(1, &hEvent, FALSE, INFINITE, QS_ALLINPUT);
			break;          // Something else happened (timeout)
		}

		// There is one or more window message available. Dispatch them
		while(PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE))
		{
			// Each time subtract from timeout value
			_ftime( &tstruct );
			dwCurTime  = tstruct.millitm + (DWORD)(tstruct.time * 1000);
			lTimeout -= (dwStartTime-dwCurTime);

			// Timed out
			if(lTimeout < 0)
				return FALSE;

			// Translate messages
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (WaitForSingleObject(hEvent, 0) == WAIT_OBJECT_0)
				return TRUE; // Event is now signaled.
		}
	}
	return FALSE;
}

/***************************************************
ExecuteMethod
	Executes method of specified type and then fire
	event if nesessary.
Params
    type	- type of method
Return
	UTE_SUCCESS	- success
	UTE_ERROR	- error
****************************************************/
long CSocket::ExecuteMethod(MethodTypeTag MethodID, _variant_t *ptrVarParams, BOOL bForceNonBlocking)
{
	LONG	lRetCode;

	switch(MethodID) {
		case(METHOD_CONNECT):
			lRetCode = CUT_WSClient::Connect(	(long)ptrVarParams[0], 
												(LPCTSTR)_bstr_t(ptrVarParams[1]), 
												(long)ptrVarParams[2],
												(long)ptrVarParams[3],
												(long)ptrVarParams[4]);
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnConnect(lRetCode);
				}
			break;
		case(METHOD_CONNECT_BOUND):
			lRetCode = CUT_WSClient::ConnectBound(	(long)ptrVarParams[0],
													(long)ptrVarParams[1],
													(LPTSTR)_bstr_t(ptrVarParams[2]), 
													_bstr_t(ptrVarParams[3]), 
													(long)ptrVarParams[4],
													(long)ptrVarParams[5]);
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnConnectBound(lRetCode);
				}
			break;
		case(METHOD_CREATE_UDP_SOCKET):
			lRetCode = CUT_WSClient::CreateUDPSocket(	(long)ptrVarParams[0],
														(long)ptrVarParams[1],
														(LPTSTR)_bstr_t(ptrVarParams[2]), 
														_bstr_t(ptrVarParams[3]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnCreateUDPSocket(lRetCode);
				}
			break;
		case(METHOD_WAIT_FOR_ACCEPT):
			lRetCode = CUT_WSClient::WaitForAccept((long)ptrVarParams[0]);
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnWaitForAccept(lRetCode);
				}
			break;

        case(METHOD_SEND_AS_LINE):
            {
			_bstr_t	Data	= ptrVarParams[0];
			int		nDataLength	= Data.length();
            int     nLineLength = (int)(long)ptrVarParams[1];

            if(nLineLength <= 0)
                lRetCode = CUT_WSClient::Send((char*)Data, nDataLength);
            else
                lRetCode = CUT_WSClient::SendAsLine((char*)Data, nDataLength, nLineLength);
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnSendAsLine(lRetCode);
				}
			break;
			}

		case(METHOD_SEND):
            {
            lRetCode = UTE_ERROR;

            // If the paramater passed by reference
            if(ptrVarParams[0].vt == (VT_VARIANT | VT_BYREF)) {
                ptrVarParams[0].Attach(*ptrVarParams[0].pvarVal);
                }

            SAFEARRAY *psa = ptrVarParams[0].parray;
            if(psa != NULL && ptrVarParams[0].vt & VT_ARRAY) {
                long    lLBound = 0, lUBound = 0;
                char    *lpszBuffer;

                SafeArrayGetUBound(psa, 1, &lUBound);
                SafeArrayGetLBound(psa, 1, &lLBound);
                lpszBuffer = new char [lUBound - lLBound + 2];

				long l;
                for( l=lLBound; l<=lUBound; l++) {
                    VARIANT rgvar;
                    if(ptrVarParams[0].vt & VT_VARIANT) {
                        SafeArrayGetElement(psa, &l, &rgvar);
                        lpszBuffer[l-lLBound] = rgvar.bVal;
                        }
                    else 
                        SafeArrayGetElement(psa, &l, (unsigned char *)&lpszBuffer[l-lLBound]);
                    
                    }
                lpszBuffer[l-lLBound] = NULL;


                lRetCode = CUT_WSClient::Send(lpszBuffer, lUBound - lLBound + 1);
                delete [] lpszBuffer;
                }
			
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnSend(lRetCode);
				}
			break;
            }
		case(METHOD_SEND_FILE):
			lRetCode = CUT_WSClient::SendFile(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnSendFile(lRetCode);
				}
			break;
		case(METHOD_SEND_TO):
			{
            int     nBytesSend = 0;
            long    lPort = ptrVarParams[2];

            // Set new remote port
            if(lPort >= 0)
                CUT_WSClient::m_nRemotePort = (unsigned int) lPort;

            lRetCode = UTE_ERROR;
            SAFEARRAY *psa = ptrVarParams[0].parray;
            if(psa != NULL) {
                long    lLBound = 0, lUBound = 0;
                char    *lpszBuffer;
                _bstr_t bstrAddress = ptrVarParams[1];

                // Copy the address parameter
                if(bstrAddress.length() > 0) {
                    strncpy(CUT_WSClient::m_szAddress, bstrAddress, sizeof(CUT_WSClient::m_szAddress)-1);
                    CUT_WSClient::m_szAddress[sizeof(CUT_WSClient::m_szAddress)-1] = NULL;
                    }

                SafeArrayGetUBound(psa, 1, &lUBound);
                SafeArrayGetLBound(psa, 1, &lLBound);
                lpszBuffer = new char [lUBound - lLBound + 2];

				long l; 
                for(l=lLBound; l<=lUBound; l++)
                    SafeArrayGetElement(psa, &l, (unsigned char *)&lpszBuffer[l-lLBound]);
                lpszBuffer[l-lLBound] = NULL;

                nBytesSend = lUBound - lLBound + 1;
                lRetCode = CUT_WSClient::SendTo(lpszBuffer, nBytesSend);
                if(lRetCode != UTE_SUCCESS)
                    nBytesSend = 0;
                delete [] lpszBuffer;
                }

			if(!m_bGoingToClose) {
				m_bUseMarshaling =
					(bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnSendTo(nBytesSend);
				}
			break;
			}
		case(METHOD_WAIT_FOR_SEND):
			lRetCode = CUT_WSClient::WaitForSend((long)ptrVarParams[0], (long)ptrVarParams[1]);
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnWaitForSend(lRetCode);
				}
			break;
		case(METHOD_RECEIVE):
			{
			char	*buffer  = new char[(long)ptrVarParams[0] + 1];

  			lRetCode = CUT_WSClient::Receive(buffer, (long)ptrVarParams[0], m_nReceiveTimeout);
			if(!m_bGoingToClose) {
                VARIANT var;
                VariantInit(&var);
                var.vt = VT_ARRAY | VT_UI1;

                // Copy data to safearray
                if(lRetCode > 0) 
                    SetSafeArrayData(&m_arrayLastLine, buffer, lRetCode);
                else {
                    SafeArrayDestroy(m_arrayLastLine);
                    m_arrayLastLine = NULL;
                    }
                var.parray = m_arrayLastLine;

				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnReceive(var, lRetCode);
				}
			delete [] buffer;
			break;
			}
		case(METHOD_RECEIVE_FROM):
			{
			char	*buffer  = new char[(long)ptrVarParams[0] + 1];
            char    from[100];
            int     nDataLength = (int)(long)ptrVarParams[0];


  			lRetCode = CUT_WSClient::ReceiveFrom(buffer, nDataLength, m_nReceiveTimeout);

            
            if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
                _snprintf(from,sizeof(from)-1, "%d.%d.%d.%d", m_sockAddr.sin_addr.S_un.S_un_b.s_b1,
                                             m_sockAddr.sin_addr.S_un.S_un_b.s_b2,
                                             m_sockAddr.sin_addr.S_un.S_un_b.s_b3,
                                             m_sockAddr.sin_addr.S_un.S_un_b.s_b4);

                VARIANT var;
                VariantInit(&var);
                var.vt = VT_ARRAY | VT_UI1;

                // Copy data to safearray
                if(lRetCode == UTE_SUCCESS) 
                    SetSafeArrayData(&m_arrayLastLine, buffer, nDataLength);
                else {
                    *from = NULL;
                    SafeArrayDestroy(m_arrayLastLine);
                    m_arrayLastLine = NULL;
                    }
                var.parray = m_arrayLastLine;

                // Fire the event
				Fire_OnReceiveFrom(var, _bstr_t(from), lRetCode);
				}
			delete [] buffer;
			break;
			}
		case(METHOD_RECEIVE_LINE):
			{
			char	*buffer  = new char[1001];

			lRetCode = CUT_WSClient::ReceiveLine(buffer, 1000, m_nReceiveTimeout);
            buffer[lRetCode] = NULL;
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
                m_bstrLastReceived = buffer;
				Fire_OnReceiveLine(m_bstrLastReceived, lRetCode);
				}
			delete [] buffer;
			break;
			}
		case(METHOD_RECEIVE_TO_FILE):
			{
			OpenMsgType	type = (((long)ptrVarParams[1]) == (long)FileTruncate) ? UTM_OM_WRITING : UTM_OM_APPEND;
			lRetCode = CUT_WSClient::ReceiveToFile(_bstr_t(ptrVarParams[0]), type, m_nReceiveTimeout);
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnReceiveToFile(lRetCode);
				}
			break;
			}
		case(METHOD_CLOSE_CONNECTION):
			lRetCode = CUT_WSClient::CloseConnection();
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnCloseConnection(lRetCode);
				}
			break;
		case(METHOD_RESET):
			lRetCode = CUT_WSClient::Reset();
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnReset(lRetCode);
				}
			break;
		case(METHOD_ACCEPT_CONNECTION):
			lRetCode = CUT_WSClient::AcceptConnection();
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnAcceptConnection(lRetCode);
				}
			break;

		// Unknown method error
		default:
			return UTE_ERROR;
		}

	return lRetCode;
}

/***************************************************
SetSafeArrayData
	Sets safe array data from char buffer.
Params
    psa     - safe array pointer
    buffer  - data
    size    - data size
Return
	none
****************************************************/
void CSocket::SetSafeArrayData(SAFEARRAY **ppsa, LPCSTR buffer, int size)
{
    if(ppsa != NULL && *ppsa != NULL) 
        SafeArrayDestroy(*ppsa);

    SAFEARRAYBOUND  bound = {size, 0};
    if((*ppsa = SafeArrayCreate(VT_UI1, 1, &bound)) == NULL)
        return;

    for(long i=0; i<size; i++) {
        SafeArrayPutElement(*ppsa, &i, (unsigned char *)&buffer[i]);
        }

}

#pragma warning (pop)