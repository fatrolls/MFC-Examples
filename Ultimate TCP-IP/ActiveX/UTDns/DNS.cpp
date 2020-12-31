//=================================================================
//  class: CDNS
//  File:  DNS.cpp
//
//  Implementation of CDNS class
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
#include <process.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include "UTDns.h"
#include "DNS.h"
#include "AboutDlg.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

/////////////////////////////////////////////////////////////////////////////
// CDNS
/////////////////////////////////////////////////////////////////////////////

/***************************************************
CDNS
	Standart constructor. 
Params
    none
Return
	none
****************************************************/
CDNS::CDNS() :
		m_bBlockingMode(FALSE),			// Set non blocking mode as default
		m_lnLookupTimeOut(20),			// Set default lookup time-out 
		m_bDoAuthoritativeLookup(FALSE),// Clear Authoritative Lookup flag
		m_bDNSThreadRunning(FALSE),		// Clear DNS thread flag
		m_bGoingToClose(FALSE),			// Initialize closing flag with FALSE
		m_hDNSThread(NULL),				// Initialize DNS thread with NULL
		m_bDNSEntryValid(FALSE),		// Clear DNS entry valid flag
		m_bAbortFlag(FALSE)				// Clear abort flag
{
	// Load DNS Icon
	m_hDNSIcon = LoadIcon(_Module.m_hInst, MAKEINTRESOURCE(IDI_ICON_DNS));	

	// Initiate default control size 32 x 32 pixels
    SIZE	sz = { 32, 32 };
    AtlPixelToHiMetric (&sz, &m_sizeExtent);		// convert pixels to himetric
    m_sizeNatural	= m_sizeExtent;					// store natural extent

	// Disable resizing of the control
	m_bAutoSize		= TRUE;				
}


/***************************************************
~CDNS
	Destructor.
Params
    none
Return
	none
****************************************************/
CDNS::~CDNS()
{
	// Set flags to terminate all running threads
	m_bGoingToClose	= TRUE;
	m_bAbortFlag	= TRUE;

	// Hmmm  there is  a bug in ATL 3.0
	// lets try to hack it
	HRESULT		hr = CoInitialize(NULL);



	// If DNS thread is running - will wait till it exits
	// or will time-out. Time-out value is based upon m_lnLookupTimeOut
	// but it can't be less than 2 minutes
	if(m_bDNSThreadRunning) 
	{
		ResumeThread(m_hDNSThread);
		WaitForSingleObject(m_hDNSThread, max(m_lnLookupTimeOut+1 * 1000, 60000));
	}

	// Destroy DNS icon handle
	if(m_hDNSIcon) {
		DestroyIcon( m_hDNSIcon );							
		m_hDNSIcon = NULL;
		}

//	CoUninitialize();
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
STDMETHODIMP CDNS::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = {	&IID_IDNS, };

	for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++) {
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
HRESULT CDNS::OnDraw(ATL_DRAWINFO& di)
{
	// Fill background & draw a boreder
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	// Draw DNS Icon
	if(m_hDNSIcon)
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hDNSIcon);	
 		
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
STDMETHODIMP CDNS::GetInterfaceSafetyOptions(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
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
STDMETHODIMP CDNS::SetInterfaceSafetyOptions(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
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


////////////////////////////////////////////////////
//	Current entry Get functions
////////////////////////////////////////////////////

/***************************************************
get_EntryHostName
    Gets current entry host name
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- not enough memory
****************************************************/
STDMETHODIMP CDNS::get_EntryHostName(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	_bstr_t	bstrString = m_CurDNSEntry.szHost;
	if(!SysReAllocString(pVal, bstrString))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_EntryType
    Gets current entry type
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_EntryType(DNSEntryTypes *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (DNSEntryTypes)m_CurDNSEntry.nType;
	return S_OK;
}

/***************************************************
get_EntryTimeToLive
    Gets current entry Time To Live
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_EntryTimeToLive(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (DNSEntryTypes)m_CurDNSEntry.lTTL;
	return S_OK;
}

/***************************************************
get_EntrySOA_Serial
    Gets current entry Start of Authority Zone Saerial
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_EntrySOA_Serial(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (DNSEntryTypes)m_CurDNSEntry.lSOA_Serial;
	return S_OK;
}

/***************************************************
get_EntrySOA_Refresh
    Gets current entry time interval before the zone 
	should be refreshed.
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_EntrySOA_Refresh(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (DNSEntryTypes)m_CurDNSEntry.lSOA_Refresh;
	return S_OK;
}

/***************************************************
get_EntrySOA_Retry
    Gets current entry time interval that should elapse 
	befaore a failed refresh should be tried.
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_EntrySOA_Retry(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (DNSEntryTypes)m_CurDNSEntry.lSOA_Retry;
	return S_OK;
}

/***************************************************
get_EntrySOA_Expire
	Gets current entry upper limit on the time interval 
	that can elapse before the zone is no longer authoritative.
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_EntrySOA_Expire(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (DNSEntryTypes)m_CurDNSEntry.lSOA_Expire;
	return S_OK;
}

/***************************************************
get_EntrySOA_Minimum
	Gets current entry minimum TTL field that should 
	be exported with any entry from this zone.
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_EntrySOA_Minimum(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (DNSEntryTypes)m_CurDNSEntry.lSOA_Minimum;
	return S_OK;
}

/***************************************************
get_EntryData
	Gets current entry data
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_EntryData(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	_bstr_t	bstrString = m_CurDNSEntry.szData;
	if(!SysReAllocString(pVal, bstrString))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_EntryData2
	Gets current entry data2
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_EntryData2(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	_bstr_t	bstrString = m_CurDNSEntry.szData2;
	if(!SysReAllocString(pVal, bstrString))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_EntryMX_Preference
	Gets current entry 16 bit integer which specifies 
	the prefrence givin to this entry among others at 
	the same host. (Mail Exchange Type entries only)
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_EntryMX_Preference(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (DNSEntryTypes)m_CurDNSEntry.nMX_Preference;
	return S_OK;
}

////////////////////////////////////////////////////
//	IFinger interface properties Set/Get functions
////////////////////////////////////////////////////

/***************************************************
get_LookupTimeOut
    Gets lookup time out
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_LookupTimeOut(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_lnLookupTimeOut;
	return S_OK;
}

/***************************************************
put_LookupTimeOut
    Sets lookup time out
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CDNS::put_LookupTimeOut(long newVal)
{
	if(newVal == m_lnLookupTimeOut)	return S_OK;

	if(FireOnRequestEdit(DISPID_LOOKUP_TIME_OUT) == S_FALSE)
		return S_FALSE;

	if(newVal >= 0) {
		m_lnLookupTimeOut = newVal;
		m_bRequiresSave = TRUE;
		SetLookupTimeOut(m_lnLookupTimeOut);

		FireOnChanged(DISPID_LOOKUP_TIME_OUT);

		SendOnDataChange(NULL);
		}
	else 
		return AtlReportError(CLSID_DNS,"Invalid Lookup Time Out value", IID_IDNS, E_FAIL);

	return S_OK;
}

/***************************************************
get_BlockingMode
    Gets blocking mode
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_BlockingMode(VARIANT_BOOL *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_bBlockingMode;
	return S_OK;
}

/***************************************************
put_BlockingMode
    Sets blocking mode
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CDNS::put_BlockingMode(VARIANT_BOOL newVal)
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
get_IncludeDefaultMX
    Gets IncludeDefaultMX flag
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_IncludeDefaultMX(VARIANT_BOOL *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = GetIncludeDefaultMX();
	return S_OK;
}

/***************************************************
put_IncludeDefaultMX
    Sets IncludeDefaultMX flag
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
****************************************************/
STDMETHODIMP CDNS::put_IncludeDefaultMX(VARIANT_BOOL newVal)
{
	if(newVal == (VARIANT_BOOL)GetIncludeDefaultMX())	return S_OK;

	if(FireOnRequestEdit(DISPID_INCLUDE_DEF_MX) == S_FALSE)
		return S_FALSE;

	IncludeDefaultMX(newVal != 0);
	m_bRequiresSave = TRUE;

	FireOnChanged(DISPID_BLOCKING_MODE);

	SendOnDataChange(NULL);
	
	return S_OK;
}

/***************************************************
get_IsAuthoritative
    Returns TRUE if the last lookup was autoritative.
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_IsAuthoritative(VARIANT_BOOL *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = CUT_DNSClient::IsAuthoritative();
	return S_OK;
}

/***************************************************
get_Protocol
    Gets current protocol TCP or UDP
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CDNS::get_Protocol(ProtocolTypes *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (CUT_DNSClient::GetUseUDP()) ? ptUDP : ptTCP;
	return S_OK;
}

/***************************************************
put_Protocol
    Sets current protocol TCP or UDP
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CDNS::put_Protocol(ProtocolTypes newVal)
{
	if(newVal == ((CUT_DNSClient::GetUseUDP()) ? ptUDP : ptTCP))	return S_OK;

	if(FireOnRequestEdit(DISPID_PROTOCOL) == S_FALSE)
		return S_FALSE;

	if(newVal == ptUDP)
		CUT_DNSClient::SetUseUDP(TRUE);
	else
		CUT_DNSClient::SetUseUDP(FALSE);

	m_bRequiresSave = TRUE;

	FireOnChanged(DISPID_PROTOCOL);

	SendOnDataChange(NULL);

	return S_OK;
}

////////////////////////////////////////////////////
//	IFinger interface methods
////////////////////////////////////////////////////

/***************************************************
Lookup
    Performs a basic DNS lookup of the given
    name. The results are held internally and
    can be retrieved with the Enum... functions
Params
    Server	- the name of the server to send the request to
    Domain	- domain name to look up
    Result  - return code
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CDNS::Lookup(BSTR Server, BSTR Domain, DNSRequestTypes Type, int *Result)
{
	HRESULT		hResult		= S_OK;

	// If thread is already running return fecInUse
	if( ! m_bDNSThreadRunning ) {

		m_bAbortFlag		= FALSE;		// Clear abort flag

		m_bstrServer	= Server;	// Save server name to send the request to
		m_bstrDomain	= Domain;	// Save domain name to lookup
		m_nType			= Type;		// Save request type

		// If we use blocking mode
		if(m_bBlockingMode) {
			LONG	lRetCode;

			// Lookup name
			if(m_bDoAuthoritativeLookup)
				lRetCode = CUT_DNSClient::AuthoritativeLookup(m_bstrServer, m_bstrDomain, m_nType);
			else
				lRetCode = CUT_DNSClient::LookupName(m_bstrServer, m_bstrDomain, m_nType);

			// Fire DNS Result event
			Fire_OnLookup(lRetCode);

			*Result = lRetCode;
			}

		// If we use non blocking mode - create separate thread
		else {
			// Marshal all event sinks intefaces into streams
			MarshalInterfacesToStream(this);

			// Begin DNS thread
			m_hDNSThread = (HANDLE)_beginthread(( void (__cdecl *)(void *)) DNSThread,NULL, (void *) this);
			if(m_hDNSThread == (HANDLE) -1) {
				*Result = ecInternalError;
				hResult = E_OUTOFMEMORY;
				}
			else  {
				m_bDNSThreadRunning = TRUE;
				*Result = ecSuccess;
				}
			}

		}
	else 
		*Result = ecInUse;

	if(!m_bDNSThreadRunning)
		m_bDoAuthoritativeLookup = FALSE;

	return hResult;
}

/***************************************************
AuthoritativeLookup
    Performs an authorized DNS lookup of the given
    name. If the given name server is not
    authorized for the given domain, then this 
    routine will try and search for an authorized
    name server. The results are held internally and
    can be retrieved with the Enum... functions
Params
    Server	- the name of the server to send the request to
    Domain	- domain name to look up
    Result  - return code
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CDNS::AuthoritativeLookup(BSTR Server, BSTR Domain, DNSRequestTypes Type, int *Result)
{
	m_bDoAuthoritativeLookup = TRUE;
	
	return Lookup(Server, Domain, Type, Result);
}

/***************************************************
GetEntryShortName
	Gets the name of the entry type in short format
Params
    EntryType	- entry type
    Name		- pointer to the result name
Return
	S_OK			- success
	E_OUTOFMEMORY	- not enough memory
****************************************************/
STDMETHODIMP CDNS::GetEntryShortName(DNSEntryTypes EntryType, BSTR *Name)
{
	_bstr_t	bstrString = CUT_DNSClient::GetShortName(EntryType);

	if(!SysReAllocString(Name, bstrString))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
GetEntryLongName
	Gets the name of the entry type in long format
Params
    EntryType	- entry type
    Name		- pointer to the result name
Return
	S_OK			- success
	E_OUTOFMEMORY	- not enough memory
****************************************************/
STDMETHODIMP CDNS::GetEntryLongName(DNSEntryTypes EntryType, BSTR *Name)
{
	_bstr_t	bstrString = CUT_DNSClient::GetLongName(EntryType);

	if(!SysReAllocString(Name, bstrString))
 		return E_OUTOFMEMORY;

	return S_OK;
}
/***************************************************
GetNameFromAddress
	Returns the name associated with the given address
Params
    Address - address string to lookup
    Name    - pointer to the result name
    Result  - return code
Return
	S_OK			- success
	E_OUTOFMEMORY	- not enough memory
****************************************************/
STDMETHODIMP CDNS::GetNameFromAddress(BSTR Address, BSTR *Name, int *Result)
{
	char	buffer[DNS_BUFFER_SIZE + 1];
	_bstr_t	bstrString = Address;

	if((*Result = CUT_WSClient::GetNameFromAddress(bstrString, buffer, DNS_BUFFER_SIZE)) == UTE_SUCCESS)
		bstrString = buffer;
	else
		bstrString = L"";

 	if(!SysReAllocString(Name, bstrString))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
GetAddressFromName
	Returns the address associated with the given name
Params
    Name	- name to lookup
    Address - pointer to the result address
    Result  - return code
Return
	S_OK			- success
	E_OUTOFMEMORY	- not enough memory
****************************************************/
STDMETHODIMP CDNS::GetAddressFromName(BSTR Name, BSTR *Address, int *Result)
{
	char	buffer[DNS_BUFFER_SIZE + 1];
	_bstr_t	bstrString = Name;

	if((*Result = CUT_WSClient::GetAddressFromName(bstrString, buffer, DNS_BUFFER_SIZE)) == UTE_SUCCESS)
		bstrString = buffer;
	else
		bstrString = L"";

 	if(!SysReAllocString(Address, bstrString))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
EnumDNSServers
    Enumerates the available name servers
    that were returned during the last lookup.
    If an address is available as well as the
    name then it is also returned
Params
    Name	- pointer to the result name
    Address	- pointer to the result address
    Result  - return code
Return
	S_OK			- success
	E_OUTOFMEMORY	- not enough memory
****************************************************/
STDMETHODIMP CDNS::EnumDNSServers(BSTR *Name, BSTR *Address, int *Result)
{
	char	bufName[DNS_BUFFER_SIZE + 1], bufAddress[DNS_BUFFER_SIZE + 1];

	if((*Result = CUT_DNSClient::EnumDNSServers(bufName, DNS_BUFFER_SIZE, bufAddress, DNS_BUFFER_SIZE)) == UTE_SUCCESS) {
		m_bDNSEntryValid = TRUE;
		
		_bstr_t		bstrString = bufName;
		if(!SysReAllocString(Name, bstrString))
 			return E_OUTOFMEMORY;
		
		bstrString = bufAddress;
		if(!SysReAllocString(Address, bstrString))
 			return E_OUTOFMEMORY;
		}
	else
		m_bDNSEntryValid = FALSE;

	return S_OK;
}

/***************************************************
EnumMXRecords
    Enumerates the available mail servers
    that were returned during the last lookup.
    If an address is available as well as the
    name then it is also returned
Params
    Name	- pointer to the result name
    Address	- pointer to the result address
    Result  - return code
Return
	S_OK			- success
	E_OUTOFMEMORY	- not enough memory
****************************************************/
STDMETHODIMP CDNS::EnumMXRecords(BSTR *Name, BSTR *Address, int *Result)
{
	char	bufName[DNS_BUFFER_SIZE + 1], bufAddress[DNS_BUFFER_SIZE + 1];

	if((*Result = CUT_DNSClient::EnumMXRecords(bufName, DNS_BUFFER_SIZE, bufAddress, DNS_BUFFER_SIZE)) == UTE_SUCCESS) {
		m_bDNSEntryValid = TRUE;
		
		_bstr_t		bstrString = bufName;
		if(!SysReAllocString(Name, bstrString))
 			return E_OUTOFMEMORY;
		
		bstrString = bufAddress;
		if(!SysReAllocString(Address, bstrString))
 			return E_OUTOFMEMORY;
		}
	else
		m_bDNSEntryValid = FALSE;

	return S_OK;
}

/***************************************************
EnumDNSEntry
    Enumerates the available DNS entries
    that were returned during the last lookup.
Params
    Result  - return code
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CDNS::EnumDNSEntry(int *Result)
{
	if((*Result = CUT_DNSClient::EnumDNSEntry(&m_CurDNSEntry)) == UTE_SUCCESS)
		m_bDNSEntryValid = TRUE;
	else
		m_bDNSEntryValid = FALSE;
	return S_OK;
}

/***************************************************
ResetEnumeration
	Resets the enumeration routines so that
    the next time one is called it will start
    from the beginning.
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CDNS::ResetEnumeration()
{
	ResetEnumerations();
	return S_OK;
}

/***************************************************
CancelLookup
	Cancel current name lookup operation
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CDNS::CancelLookup()
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
STDMETHODIMP CDNS::AboutBox()
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
STDMETHODIMP CDNS::GetErrorText(long ErrorCode, BSTR *ErrorText)
{
 	HRESULT		hResult			= S_OK;
 	CComBSTR	bstrErrorMsg	= CUT_ERR::GetErrorString(ErrorCode);
 
 	if(!SysReAllocString(ErrorText, bstrErrorMsg))
 		hResult = E_OUTOFMEMORY;
 
 	return hResult;
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
BOOL CDNS::IsAborted() {
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
BOOL CDNS::WaitWithMsgLoop(HANDLE hEvent, long lTimeout)
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
DNSThread
    DNS thread function.
Params
    pThis	- pointer to the CDNS class
Return
	none
****************************************************/
void __stdcall CDNS::DNSThread( LPVOID pThis )
{

	CDNS		*ptrDNS	= (CDNS*)  pThis;
	HRESULT		hr = CoInitialize(NULL);
	LONG		lRetCode;

	if( hr == S_OK ) {
		if(ptrDNS != NULL) {
			if (ptrDNS->m_bGoingToClose )
			{
				// well the program is exiting so lets abort evrything
				ptrDNS->Fire_OnLookup(UTE_ABORTED);
				CoUninitialize();
				ptrDNS->m_bDoAuthoritativeLookup = FALSE;
				ptrDNS->m_bDNSThreadRunning = FALSE;
				_endthread();
				return ;

			}
			// Lookup name
			if(ptrDNS->m_bDoAuthoritativeLookup)
				lRetCode = ptrDNS->CUT_DNSClient::AuthoritativeLookup(ptrDNS->m_bstrServer, ptrDNS->m_bstrDomain, ptrDNS->m_nType);
			else
				lRetCode = ptrDNS->CUT_DNSClient::LookupName(ptrDNS->m_bstrServer, ptrDNS->m_bstrDomain, ptrDNS->m_nType);

			// Fire FingerResult event
			ptrDNS->Fire_OnLookup(lRetCode);
			}

		CoUninitialize();

		ptrDNS->m_bDoAuthoritativeLookup = FALSE;
		ptrDNS->m_bDNSThreadRunning = FALSE;
		}

	_endthread();
	return;
	}

#pragma warning (pop)