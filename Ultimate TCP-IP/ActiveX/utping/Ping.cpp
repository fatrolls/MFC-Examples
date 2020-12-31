//=================================================================
//  class: CPing
//  File:  Ping.cpp 
//
//  Implementation of CPing class
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
#include "UTPing.h"
#include "Ping.h"

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
// CPing
/////////////////////////////////////////////////////////////////////////////

/***************************************************
CPing
	Standart constructor. 
Params
    none
Return
	none
****************************************************/
CPing::CPing() :
        m_bBlockingMode(FALSE),			// Set non blocking mode as default
		m_lnTimeOut(2000),				// Set default time-out 
		m_lnInterval(500),				// Set default interval
		m_nDataSize(32),				// Set default size of data to send
		m_nPingCount(5),				// Number of packets to send
		m_nMaxHops(30),					// Max hops number
		m_bTraceRoute(FALSE),				// Clear trace out flag
		m_bPingThreadRunning(FALSE),	// Clear Ping thread flag
		m_bstrAddress(L""),				// Clear address to Ping
		m_bGoingToClose(FALSE),			// Initialize closing flag with FALSE
		m_hPingThread(NULL),			// Initialize Ping thread with NULL
		m_bAbortFlag(FALSE)				// Clear abort flag

{
	// Load Ping Icon
	m_hPingIcon = LoadIcon(_Module.m_hInst, MAKEINTRESOURCE(IDI_ICON_PING));	

	// Initiate default control size 32 x 32 pixels
    SIZE	sz = { 32, 32 };
    AtlPixelToHiMetric (&sz, &m_sizeExtent);		// convert pixels to himetric
    m_sizeNatural	= m_sizeExtent;					// store natural extent

	// Disable resizing of the control
	m_bAutoSize		= TRUE;				
  
}

/***************************************************
~CPing
	Destructor.
Params
    none
Return
	none
****************************************************/
CPing::~CPing()
{
	// Set flags to terminate all running threads
	m_bGoingToClose	= TRUE;
	m_bAbortFlag	= TRUE;

	// If Ping thread is running - will wait till it exits
	// or will time-out. Time-out value is based upon m_lnConnectTimeOut
	// and m_lnReceiveTimeOut but it can't be less than 2 minutes
	if(m_bPingThreadRunning) 
		WaitWithMsgLoop(m_hPingThread, max(m_lnTimeOut * 1000, 120000));
		
	// Destroy Ping icon handle
	if(m_hPingIcon) {
		DestroyIcon( m_hPingIcon );							
		m_hPingIcon = NULL;
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
STDMETHODIMP CPing::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPing,
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
HRESULT CPing::OnDraw(ATL_DRAWINFO& di)
{
	// Fill background & draw a boreder
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	// Draw Ping Icon
	if(m_hPingIcon)
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hPingIcon);	
 		
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
STDMETHODIMP CPing::get_BlockingMode(VARIANT_BOOL *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = (VARIANT_BOOL)m_bBlockingMode;
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
STDMETHODIMP CPing::put_BlockingMode(VARIANT_BOOL newVal)
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
get_DoLookup
	Gets DoLookup flag. If this flag is set then we
    are performing lookups on IP addresses.
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CPing::get_DoLookup(VARIANT_BOOL *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = GetDoLookup();
	return S_OK;
}

/***************************************************
put_DoLookup
	Sets DoLookup flag. 
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CPing::put_DoLookup(VARIANT_BOOL newVal)
{
	if(newVal == (VARIANT_BOOL)GetDoLookup())	return S_OK;

	if(FireOnRequestEdit(DISPID_DO_LOOKUP) == S_FALSE)
		return S_FALSE;

    SetDoLookup(newVal!=0);

	m_bRequiresSave = TRUE;
	FireOnChanged(DISPID_DO_LOOKUP);
	SendOnDataChange(NULL);

	return S_OK;
}

/***************************************************
get_MaxTimeOuts
	Gets maximum timeouts number
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CPing::get_MaxTimeOuts(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = GetMaxTimeOuts();
	return S_OK;
}

/***************************************************
put_MaxTimeOuts
	Sets maximum timeouts number
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CPing::put_MaxTimeOuts(long newVal)
{
	if(newVal == GetMaxTimeOuts())	return S_OK;

	if(FireOnRequestEdit(DISPID_MAX_TIME_OUTS) == S_FALSE)
		return S_FALSE;

    SetMaxTimeOuts(newVal);

	m_bRequiresSave = TRUE;
	FireOnChanged(DISPID_MAX_TIME_OUTS);
	SendOnDataChange(NULL);

	return S_OK;
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
STDMETHODIMP CPing::GetInterfaceSafetyOptions(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
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
STDMETHODIMP CPing::SetInterfaceSafetyOptions(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
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
Ping
	Pings the address or domain name 
Params
    Address		- address or domain name to be pinged
	Count		- number of packets to send
	TimeOut		- max time waiting for reply (milisec.)
	DataSize	- size of data to send
	Interaval	- interval between packets in milisec.
	Result		- pointer to result variable
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CPing::Ping(BSTR Address, int Count, int TimeOut, int Interval, int DataSize, int *Result)
{
	HRESULT		hResult		= S_OK;

	m_bstrAddress	= Address;
	m_nPingCount	= Count;
	m_lnTimeOut		= TimeOut;
	m_lnInterval	= Interval;
	m_nDataSize		= DataSize;

    // Clear the results vector
    m_DataVector.clear();

	// If thread is already running return ecInUse
	if( ! m_bPingThreadRunning ) {

		// Check address string length
		if(SysStringLen(Address) > 0) {

			m_bAbortFlag		= FALSE;		// Clear abort flag
			m_bTraceRoute			= FALSE;

			// If we use blocking mode
			if(m_bBlockingMode) {
				long lRetCode = CUT_ICMP::Ping(m_bstrAddress,
														m_lnTimeOut,
														m_nDataSize,
														m_lnInterval,
														m_nPingCount);
    			if(!m_bGoingToClose)
	    			Fire_OnPing(lRetCode);

                *Result = lRetCode;
            }
            else {

			    // Marshal all event sinks intefaces into streams
			    MarshalInterfacesToStream(this);

                // Begin Ping thread
			    m_hPingThread = (HANDLE)_beginthread(( void (__cdecl *)(void *)) PingThread,NULL, (void *) this);
			    if(m_hPingThread == (HANDLE) -1) {
				    *Result = ecInternalError;
				    hResult = E_OUTOFMEMORY;
				    }
			    else  {
				    m_bPingThreadRunning = TRUE;
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
TraceRoute
	Trace out the address or domain name 
Params
    Address		- address or domain name to be pinged
	TimeOut		- max time waiting for reply (milisec.)
	DataSize	- size of data to send
	MaxHops		- maximum hops number
	Result		- pointer to result variable
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CPing::TraceRoute(BSTR Address, int TimeOut, int MaxHops, int DataSize, int *Result)
{
	HRESULT		hResult		= S_OK;

	m_bstrAddress	= Address;
	m_lnTimeOut		= TimeOut;
	m_nDataSize		= DataSize;
	m_nMaxHops		= MaxHops;

    // Clear the results vector
    m_DataVector.clear();

    // If thread is already running return ecInUse
	if( ! m_bPingThreadRunning ) {

		// Check address string length
		if(SysStringLen(Address) > 0) {

			m_bAbortFlag		= FALSE;		// Clear abort flag
			m_bTraceRoute			= TRUE;

			// If we use blocking mode
			if(m_bBlockingMode) {
				long lRetCode = CUT_ICMP::TraceRoute(m_bstrAddress,
														    m_lnTimeOut,
														    m_nDataSize,
														    m_nMaxHops);
    			if(!m_bGoingToClose)
	    			Fire_OnTraceRoute(lRetCode);

                *Result = lRetCode;
            }
            else {
			    // Marshal all event sinks intefaces into streams
			    MarshalInterfacesToStream(this);

			    // Begin Ping thread
			    m_hPingThread = (HANDLE)_beginthread(( void (__cdecl *)(void *)) PingThread,NULL, (void *) this);
			    if(m_hPingThread == (HANDLE) -1) {
				    *Result = ecInternalError;
				    hResult = E_OUTOFMEMORY;
				    }
			    else  {
				    m_bPingThreadRunning = TRUE;
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
CancelPing
	Cancel current Ping operation
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CPing::CancelPing()
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
STDMETHODIMP CPing::AboutBox()
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
STDMETHODIMP CPing::GetErrorText(long ErrorCode, BSTR *ErrorText)
{
 	HRESULT		hResult			= S_OK;
 	CComBSTR	bstrErrorMsg	= CUT_ERR::GetErrorString(ErrorCode);
 
 	if(!SysReAllocString(ErrorText, bstrErrorMsg))
 		hResult = E_OUTOFMEMORY;
 
 	return hResult;
}

/***************************************************
OnReceiveICMP
	Virtual function is called each time we receive ICMP
Params
    none
Return
    none
****************************************************/
void CPing::OnReceiveICMP() {
    CICMP_Data  data(   CUT_ICMP::GetResponseMessage(),
                        CUT_ICMP::GetResponseAddress(),
                        CUT_ICMP::GetResponseName(),
                        CUT_ICMP::GetResponseDuration(),
                        CUT_ICMP::GetResponseType(),
                        CUT_ICMP::GetResponseCode(),
                        CUT_ICMP::GetResponseSequence());

    m_DataVector.push_back(data);
    Fire_OnReceiveICMP();
	return;
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
BOOL CPing::IsAborted() {
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
BOOL CPing::WaitWithMsgLoop(HANDLE hEvent, long lTimeout)
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
PingThread
    Ping thread function.
Params
    pThis	- pointer to the CPing class
Return
	none
****************************************************/
void __stdcall CPing::PingThread( LPVOID pThis )
{

	CPing		*ptrPing	= (CPing*)  pThis;
	HRESULT		hr = CoInitialize(NULL);
	LONG		lRetCode;

	if( hr == S_OK ) {
		if(ptrPing != NULL) {

			if(ptrPing->m_bTraceRoute)
				lRetCode = ptrPing->CUT_ICMP::TraceRoute(	ptrPing->m_bstrAddress,
														ptrPing->m_lnTimeOut,
														ptrPing->m_nDataSize,
														ptrPing->m_nMaxHops);
			else
				lRetCode = ptrPing->CUT_ICMP::Ping(		ptrPing->m_bstrAddress,
														ptrPing->m_lnTimeOut,
														ptrPing->m_nDataSize,
														ptrPing->m_lnInterval,
														ptrPing->m_nPingCount);
			if(!ptrPing->m_bGoingToClose)
                if(ptrPing->m_bTraceRoute)
                    ptrPing->Fire_OnTraceRoute(lRetCode);
                else
				    ptrPing->Fire_OnPing(lRetCode);
			}

		CoUninitialize();

		ptrPing->m_bPingThreadRunning = FALSE;
		}

	_endthread();
	return;
}

//////////////////////////////////////////////
//	Current data Get functions
//////////////////////////////////////////////


/***************************************************
GetResponseSize
    Gets the size of the ICMP data vector
Params
	Size	- data vector size
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CPing::GetResponseSize(long *Size)
{
	*Size = (long)m_DataVector.size();
	return S_OK;
}

/***************************************************
GetResponseMessage
    Gets response message
Params
	Message - message
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CPing::GetResponseMessage(long Index, BSTR *Message)
{
    _bstr_t bstr;

    if(Index >= 0 && Index < (long)m_DataVector.size())
        bstr = m_DataVector[Index].m_strMessage.c_str();
    else if(Index == -1 && m_DataVector.size() > 0)
        bstr = m_DataVector[m_DataVector.size() - 1].m_strMessage.c_str();

	if(!SysReAllocString(Message, bstr))
		return E_OUTOFMEMORY;
	
	return S_OK;
}

/***************************************************
GetResponseAddress
    Gets response address
Params
	Address - address
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CPing::GetResponseAddress(long Index, BSTR *Address)
{
    _bstr_t bstr;

    if(Index >= 0 && Index < (long)m_DataVector.size())
        bstr = m_DataVector[Index].m_strAddress.c_str();
    else if(Index == -1 && m_DataVector.size() > 0)
        bstr = m_DataVector[m_DataVector.size() - 1].m_strAddress.c_str();

	if(!SysReAllocString(Address, bstr))
		return E_OUTOFMEMORY;
	
	return S_OK;
}

/***************************************************
GetResponseName
    Gets response name
Params
	Name    - name
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CPing::GetResponseName(long Index, BSTR *Name)
{
    _bstr_t bstr;

    if(Index >= 0 && Index < (long)m_DataVector.size())
        bstr = m_DataVector[Index].m_strName.c_str();
    else if(Index == -1 && m_DataVector.size() > 0)
        bstr = m_DataVector[m_DataVector.size() - 1].m_strName.c_str();

	if(!SysReAllocString(Name, bstr))
		return E_OUTOFMEMORY;
	
	return S_OK;
}

/***************************************************
GetResponseDuration
    Gets response duration
Params
	Duration    - duration
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CPing::GetResponseDuration(long Index, long *Duration)
{
    *Duration = 0;
    if(Index >= 0 && Index < (long)m_DataVector.size())
        *Duration = m_DataVector[Index].m_lDuration;
    else if(Index == -1 && m_DataVector.size() > 0)
        *Duration = m_DataVector[m_DataVector.size()-1].m_lDuration;

	return S_OK;
}

/***************************************************
GetResponseType
    Gets response type
Params
	Type    - type
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CPing::GetResponseType(long Index, long *Type)
{
    *Type = 0;
    if(Index >= 0 && Index < (long)m_DataVector.size())
        *Type = m_DataVector[Index].m_lType;
    else if(Index == -1 && m_DataVector.size() > 0)
        *Type = m_DataVector[m_DataVector.size()-1].m_lType;

	return S_OK;
}

/***************************************************
GetResponseCode
    Gets response code
Params
	Code    - code
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CPing::GetResponseCode(long Index, long *Code)
{
    *Code = 0;
    if(Index >= 0 && Index < (long)m_DataVector.size())
        *Code = m_DataVector[Index].m_lCode;
    else if(Index == -1 && m_DataVector.size() > 0)
        *Code = m_DataVector[m_DataVector.size()-1].m_lCode;

	return S_OK;
}

/***************************************************
GetResponseSequence
    Gets response sequence
Params
	Sequence    - sequence
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CPing::GetResponseSequence(long Index, long *Sequence)
{
    *Sequence = 0;
    if(Index >= 0 && Index < (long)m_DataVector.size())
        *Sequence = m_DataVector[Index].m_lSequence;
    else if(Index == -1 && m_DataVector.size() > 0)
        *Sequence = m_DataVector[m_DataVector.size()-1].m_lSequence;

	return S_OK;
}

#pragma warning (pop)