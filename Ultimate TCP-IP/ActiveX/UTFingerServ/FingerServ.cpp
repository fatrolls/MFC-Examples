//=================================================================
//  class: CFingerServ
//  File:  FingerServ.h
//
//  Implementation of CFingerServServ class
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
#include "UTFingerServ.h"
#include "FingerServ.h"
#include "AboutDlg.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

/////////////////////////////////////////////////////////////////////////////
// CFingerServ
/////////////////////////////////////////////////////////////////////////////

/***************************************************
CFingerServ
	Standart constructor. 
Params
    none
Return
	none
****************************************************/
CFingerServ::CFingerServ() :
		m_lFingerServerPort(79),
		m_bGoingToClose(FALSE)

{
	// Load Finger Icon
	m_hFingerServIcon = LoadIcon(_Module.m_hInst, MAKEINTRESOURCE(IDI_ICON_FINGERSERV));	

	// Initiate default control size 32 x 32 pixels
    SIZE	sz = { 32, 32 };
    AtlPixelToHiMetric (&sz, &m_sizeExtent);		// convert pixels to himetric
    m_sizeNatural	= m_sizeExtent;					// store natural extent

	// Disable resizing of the control
	m_bAutoSize		= TRUE;				

	// Initialize lock
	m_EventLock.Init();
}

/***************************************************
~CFingerServ
	Destructor.
Params
    none
Return
	none
****************************************************/
CFingerServ::~CFingerServ()
{
	m_bGoingToClose = TRUE;

	// Stop accept connections
	StopAccept();

	// Destroy Finger icon handle
	if(m_hFingerServIcon) {
		DestroyIcon( m_hFingerServIcon );							
		m_hFingerServIcon = NULL;
		}

	// Terminate lock
	m_EventLock.Term();

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
STDMETHODIMP CFingerServ::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFingerServ,
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
HRESULT CFingerServ::OnDraw(ATL_DRAWINFO& di)
{
	// Fill background & draw a boreder
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	// Draw Finger Icon
	if(m_hFingerServIcon)
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hFingerServIcon);	
 		
	return S_OK;
}

////////////////////////////////////////////////////
//	IFingerServ interface properties Set/Get functions
////////////////////////////////////////////////////

/***************************************************
get_Path
	Gets current server root path
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CFingerServ::get_Path(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	
	_bstr_t	bstrPath = GetPath();

 	if(!SysReAllocString(pVal, bstrPath))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
put_Path
	Set current server root path
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
****************************************************/
STDMETHODIMP CFingerServ::put_Path(BSTR newVal)
{
	_bstr_t	bstrPath = newVal;

	if(stricmp(bstrPath, GetPath()) == NULL)	return S_OK;

	if(FireOnRequestEdit(DISPID_PATH) == S_FALSE)
		return S_FALSE;

	SetPath(bstrPath);
	
	m_bRequiresSave = TRUE;
	FireOnChanged(DISPID_PATH);
	SendOnDataChange(NULL);

	return S_OK;
}

/***************************************************
get_Connections
	Get number of connections
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CFingerServ::get_Connections(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (long)GetNumConnections();	
	return S_OK;
}

/***************************************************
get_MaxConnections
	Get maximum number of connections
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CFingerServ::get_MaxConnections(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (long)GetMaxConnections();	
	return S_OK;
}

/***************************************************
put_MaxConnections
	Set maximum number of connections
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
****************************************************/
STDMETHODIMP CFingerServ::put_MaxConnections(long newVal)
{
	if(newVal == GetMaxConnections())	return S_OK;

	if(FireOnRequestEdit(DISPID_MAX_CONNECTIONS) == S_FALSE)
		return S_FALSE;

	SetMaxConnections((int)newVal);
	
	m_bRequiresSave = TRUE;
	FireOnChanged(DISPID_MAX_CONNECTIONS);
	SendOnDataChange(NULL);

	return S_OK;
}

/***************************************************
get_Port
	Get listening port number
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CFingerServ::get_Port(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_lFingerServerPort;	
	return S_OK;
}

/***************************************************
put_Port
	Set listening port number
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
****************************************************/
STDMETHODIMP CFingerServ::put_Port(long newVal)
{
	if(newVal == m_lFingerServerPort)	return S_OK;

	if(FireOnRequestEdit(DISPID_PORT) == S_FALSE)
		return S_FALSE;

	m_lFingerServerPort = newVal;
	
	m_bRequiresSave = TRUE;
	FireOnChanged(DISPID_PORT);
	SendOnDataChange(NULL);

	return S_OK;
}

////////////////////////////////////////////////////
//	IFingerServ interface methods
////////////////////////////////////////////////////

/***************************************************
Start
	Starts finger server
Params
    Result		- pointer to the result variable
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CFingerServ::Start(long *Result)
{
	if(m_serverSocket != INVALID_SOCKET) {
		*Result = UTE_ALREADY_IN_USE;
		OnStatus("Finger Server already running");
		return S_OK;
		}

	// Marshal event interfaces
	MarshalInterfacesToStream(this);

	// Start listening
	if((*Result = (long)ConnectToPort((unsigned short)m_lFingerServerPort)) == UTE_SUCCESS) 
		// Start accept connections
		if((*Result = (long)StartAccept()) == UTE_SUCCESS) 
			OnStatus("Finger Server started");

	return S_OK;
}

/***************************************************
Stop
	Stops finger server
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CFingerServ::Stop()
{
    // Shut down the accept thread
    StopAccept();

	OnStatus("Server stopped");

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
STDMETHODIMP CFingerServ::AboutBox()
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
STDMETHODIMP CFingerServ::GetErrorText(long ErrorCode, BSTR *ErrorText)
{
 	HRESULT		hResult			= S_OK;
 	CComBSTR	bstrErrorMsg	= CUT_ERR::GetErrorString(ErrorCode);
 
 	if(!SysReAllocString(ErrorText, bstrErrorMsg))
 		hResult = E_OUTOFMEMORY;
 
 	return hResult;
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
STDMETHODIMP CFingerServ::GetInterfaceSafetyOptions(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
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
STDMETHODIMP CFingerServ::SetInterfaceSafetyOptions(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
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

/********************************
CreateInstance
    Returns a pointer to an instance
    of a class derived from CUT_WSThread
PARAM
    NONE
RETURN
    CUT_WSThread *  - the new created instance 
        of the thread class
*********************************/
CUT_WSThread * CFingerServ::CreateInstance(){
    return new CUT_FingerThreadEx;
}

/***************************************************
OnStatus
    This virtual function is called each time we have any
	status information to display.
Params
	StatusText	- status text
Return
	UTE_SUCCESS - success   
****************************************************/
int CFingerServ::OnStatus(LPCSTR StatusText)
{
	if(!m_bGoingToClose) {
		m_EventLock.Lock();
		Fire_OnStatus(_bstr_t(StatusText));
		m_EventLock.Unlock();
		}
	return UTE_SUCCESS;
}

/***************************************************
OnCanAccept
    This virtual function is called each time the server 
    accepting new connection.
Params
	LPCSTR	    - IP address of connecting user
Return
	TRUE        - accept 
    FALSE       - cancel
****************************************************/
long CFingerServ::OnCanAccept(LPCSTR address){
    VARIANT_BOOL	result	= TRUE;
	if(!m_bGoingToClose) {
    	HRESULT	hr = CoInitialize(NULL);

		m_EventLock.Lock();
		Fire_OnCanAccept(_bstr_t(address), &result);
		m_EventLock.Unlock();

    	if(hr == S_OK)
	    		CoUninitialize();					
		}
    return (long)result;
}


//=================================================================
//  class: CUT_FingerThreadEx
//=================================================================

/***************************************************
OnMaxConnect
    This member is called when the maximum number of
    connections allowed has already been reached
PARAM
    NONE
RETURN
    VOID    
****************************************************/
void CUT_FingerThreadEx::OnMaxConnect(){
	HRESULT	hr = CoInitialize(NULL);

	if(!((CFingerServ *)m_winsockclass_this)->m_bGoingToClose) {
		((CFingerServ *)m_winsockclass_this)->m_EventLock.Lock();
		((CFingerServ *)m_winsockclass_this)->Fire_OnMaxConnect();
		((CFingerServ *)m_winsockclass_this)->m_EventLock.Unlock();
		}
	CUT_FingerThread::OnMaxConnect();

	if(hr == S_OK)
			CoUninitialize();					
    return;
}
/***************************************************
OnConnect
    This member is called when a connection is made and
    accepted. Do all processing here, since the connection
    is automatically terminated when this funtion returns.
    Plus the thread that this function runs in is terminated
    as well.
PARAM
    NONE
RETURN
    VOID
****************************************************/
void CUT_FingerThreadEx::OnConnect(){
	HRESULT	hr = CoInitialize(NULL);

	if(!((CFingerServ *)m_winsockclass_this)->m_bGoingToClose) {
		((CFingerServ *)m_winsockclass_this)->m_EventLock.Lock();
		((CFingerServ *)m_winsockclass_this)->Fire_OnConnect();
		((CFingerServ *)m_winsockclass_this)->m_EventLock.Unlock();
		}

	CUT_FingerThread::OnConnect();

	if(hr == S_OK)
			CoUninitialize();					
	return;
}


#pragma warning (pop)