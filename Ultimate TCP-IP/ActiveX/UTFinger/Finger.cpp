//=================================================================
//  class: CFinger
//  File:  Finger.cpp
//
//  Implementation of CFinger class
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
#include "UTFinger.h"
#include "Finger.h"

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
// CFinger

/***************************************************
CFinger
	Standart constructor. 
Params
    none
Return
	none
****************************************************/
CFinger::CFinger() :
		m_bBlockingMode(FALSE),			// Set non blocking mode as default
		m_lnConnectTimeOut(5),			// Set default connection time-out to 5 secs
		m_lnReceiveTimeOut(5),			// Set default receive time-out to 5 secs
		m_lnNumberOfLines(0),			// Initialize number of received lines to 0
		m_bFingerThreadRunning(FALSE),	// Clear finger thread flag
		m_bstrAddress(L""),				// Clear address to finger
		m_bstrFileName(L""),			// Clear file name to store the data
		m_bGoingToClose(FALSE),			// Initialize closing flag with FALSE
		m_hFingerThread(NULL),			// Initialize finger thread with NULL
		m_bAbortFlag(FALSE)				// Clear abort flag

{
	// Load Finger Icon
	m_hFingerIcon = LoadIcon(_Module.m_hInst, MAKEINTRESOURCE(IDI_ICON_FINGER));	

	// Initiate default control size 32 x 32 pixels
    SIZE	sz = { 32, 32 };
    AtlPixelToHiMetric (&sz, &m_sizeExtent);		// convert pixels to himetric
    m_sizeNatural	= m_sizeExtent;					// store natural extent

	// Disable resizing of the control
	m_bAutoSize		= TRUE;				
  
}

/***************************************************
~CFinger
	Destructor.
Params
    none
Return
	none
****************************************************/
CFinger::~CFinger()
{
	// Set flags to terminate all running threads
	m_bGoingToClose	= TRUE;
	m_bAbortFlag	= TRUE;

	// If finger thread is running - will wait till it exits
	// or will time-out. Time-out value is based upon m_lnConnectTimeOut
	// and m_lnReceiveTimeOut but it can't be less than 2 minutes
	if(m_bFingerThreadRunning) 
		WaitWithMsgLoop(m_hFingerThread, max((m_lnConnectTimeOut + m_lnReceiveTimeOut) * 1000, 120000));

	// Destroy Finger icon handle
	if(m_hFingerIcon) {
		DestroyIcon( m_hFingerIcon );							
		m_hFingerIcon = NULL;
		}
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
STDMETHODIMP CFinger::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFinger,
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
HRESULT CFinger::OnDraw(ATL_DRAWINFO& di)
{
	// Fill background & draw a boreder
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	// Draw Finger Icon
	if(m_hFingerIcon)
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hFingerIcon);	
 		
	return S_OK;
}


////////////////////////////////////////////////////
//	IFinger interface properties Set/Get functions
////////////////////////////////////////////////////

/***************************************************
get_ConnectTimeOut
	Get connect time-out value
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
7	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CFinger::get_ConnectTimeOut(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = m_lnConnectTimeOut;
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
STDMETHODIMP CFinger::put_ConnectTimeOut(long newVal)
{
	if(newVal == m_lnConnectTimeOut)	return S_OK;

	if(FireOnRequestEdit(DISPID_CONNECT_TIME_OUT) == S_FALSE)
		return S_FALSE;

	if(SetConnectTimeout(newVal) == CUT_SUCCESS) {
		m_lnConnectTimeOut = newVal;
		m_bRequiresSave = TRUE;

		FireOnChanged(DISPID_CONNECT_TIME_OUT);

		SendOnDataChange(NULL);
		}
	else 
		return AtlReportError(CLSID_Finger,"Invalid Connect Time Out value", IID_IFinger, E_FAIL);


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
STDMETHODIMP CFinger::get_ReceiveTimeOut(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = m_lnReceiveTimeOut;
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
STDMETHODIMP CFinger::put_ReceiveTimeOut(long newVal)
{
	if(newVal == m_lnReceiveTimeOut)	return S_OK;

	if(FireOnRequestEdit(DISPID_RECEIVE_TIME_OUT) == S_FALSE)
		return S_FALSE;

	if(SetReceiveTimeout(newVal) == CUT_SUCCESS) {
		m_lnReceiveTimeOut = newVal;
		m_bRequiresSave = TRUE;

		FireOnChanged(DISPID_RECEIVE_TIME_OUT);

		SendOnDataChange(NULL);
		}
	else 
		return AtlReportError(CLSID_Finger,"Invalid Receive Time Out value", IID_IFinger,E_FAIL);

	return S_OK;
}

/***************************************************
get_NumberReturnLines
	Get number of result lines
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CFinger::get_NumberReturnLines(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_lnNumberOfLines;
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
STDMETHODIMP CFinger::get_BlockingMode(VARIANT_BOOL *pVal)
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
STDMETHODIMP CFinger::put_BlockingMode(VARIANT_BOOL newVal)
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

////////////////////////////////////////////////////
//	IFinger interface methods
////////////////////////////////////////////////////

/***************************************************
CancelFinger
	Cancel current finger operation
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CFinger::CancelFinger()
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
STDMETHODIMP CFinger::AboutBox()
{
	CAboutDlg	dlg;

	dlg.DoModal();
	return S_OK;
}

/***************************************************
Finger
	Finger the specified address. If file name size
	is not 0 it save data in the file, otherwise in
	the string list.
Params
    Address		- address to finger
	[FileName]	- file name to save the data in
	Result		- pointer to the result varaible
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CFinger::Finger(BSTR Address, BSTR FileName, long *Result)
{
	HRESULT		hResult		= S_OK;

	// If thread is already running return ecInUse
	if( ! m_bFingerThreadRunning ) {

		// Check address string length
		if(SysStringLen(Address) > 0) {

			m_lnNumberOfLines	= 0;			// Clear number of received lines
			m_bAbortFlag		= FALSE;		// Clear abort flag
			m_bstrAddress		= Address;		// Save address
			m_bstrFileName		= FileName;		// Save file name (optional) to store data 

			// If we use blocking mode
			if(m_bBlockingMode) {
				LONG	lRetCode;

				// Finger address to string list or file
				if(m_bstrFileName.length() == 0)
					lRetCode = CUT_FingerClient::Finger(m_bstrAddress);
				else
					lRetCode = CUT_FingerClient::Finger(m_bstrAddress, m_bstrFileName);

				// Get number of result lines
				m_lnNumberOfLines = GetNumberReturnLines();
	
				// Fire FingerResult event
				Fire_OnFinger(lRetCode);

				*Result = lRetCode;
				}

			// If we use non blocking mode - create separate thread
			else {
				// Marshal all event sinks intefaces into streams
				MarshalInterfacesToStream(this);

				// Begin finger thread
				m_hFingerThread = (HANDLE)_beginthread(( void (__cdecl *)(void *)) FingerThread,NULL, (void *) this);
				if(m_hFingerThread == (HANDLE) -1) {
					*Result = ecInternalError;
					hResult = E_OUTOFMEMORY;
					}
				else  {
					m_bFingerThreadRunning = TRUE;
					*Result = ecSuccess;
					}
				}
			}
		else
			*Result = ecInvalidAddress;
		}
	else 
		*Result = ecInUse;

	return hResult;
}

/***************************************************
GetReturnLine
	Returns one line from the result string list.
	The string list will be empty if you specify
	the file name in Finger() function.
Params
	Index		- index of the line
	Line		- pointer to the result varaible
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
	E_FAIL			- line index is out of range
****************************************************/
STDMETHODIMP CFinger::GetReturnLine(long Index, BSTR *Line)
{
	HRESULT		hResult		= S_OK;
	CComBSTR	bstrLine	= L"";

    if(Index >= 0 && Index < m_lnNumberOfLines) {
		bstrLine = CUT_FingerClient::GetReturnLine(Index);
        }
	else
		return AtlReportError(CLSID_Finger,"Line index is out of range", IID_IFinger, E_FAIL);
	
	if(!SysReAllocString(Line, bstrLine))
		hResult = E_OUTOFMEMORY;

	return hResult;
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
STDMETHODIMP CFinger::GetErrorText(long ErrorCode, BSTR *ErrorText)
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
STDMETHODIMP CFinger::GetInterfaceSafetyOptions(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
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
STDMETHODIMP CFinger::SetInterfaceSafetyOptions(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
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
IsAborted
    This virtual function is called during time consuming
	operations to check if we want to abort operatin
Params
    none
Return
    TRUE	- abort operation
	FALSE	- continue
****************************************************/
BOOL CFinger::IsAborted() {
	return m_bAbortFlag;
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
BOOL CFinger::WaitWithMsgLoop(HANDLE hEvent, long lTimeout)
{
	struct _timeb	tstruct;
	DWORD			dwStartTime, dwCurTime;
	DWORD			dwRet;
	MSG				msg;
    

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
			break;          // Something else happened (timeout)

		// There is one or more window message available. Dispatch them
		while(PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE))
		{
			// Each time subtract from timeout value
			_ftime( &tstruct );
			dwCurTime  =	tstruct.millitm + (DWORD)(tstruct.time * 1000);
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
FingerThread
    Finger thread function.
Params
    pThis	- pointer to the CFinger class
Return
	none
****************************************************/
void __stdcall CFinger::FingerThread( LPVOID pThis )
{

	CFinger		*ptrFinger	= (CFinger*)  pThis;
	HRESULT		hr = CoInitialize(NULL);
	LONG		lRetCode;

	if( hr == S_OK ) {
		if(ptrFinger != NULL) {

			if(ptrFinger->m_bstrFileName.length() == 0)
				lRetCode = ptrFinger->CUT_FingerClient::Finger(ptrFinger->m_bstrAddress);
			else
				lRetCode = ptrFinger->CUT_FingerClient::Finger(ptrFinger->m_bstrAddress, ptrFinger->m_bstrFileName);

			ptrFinger->m_lnNumberOfLines = ptrFinger->GetNumberReturnLines();

			if(!ptrFinger->m_bGoingToClose)
				ptrFinger->Fire_OnFinger(lRetCode);
			}

		CoUninitialize();

		ptrFinger->m_bFingerThreadRunning = FALSE;
		}

	_endthread();
	return;
}


#pragma warning (pop)