//=================================================================
//  class: CHttp
//  File:  Http.h
//
//	HTTP ActiveX control
//  Implementation of CHttp class
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
#include "UTHttp.h"
#include "Http.h"

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
// CHttp
/////////////////////////////////////////////////////////////////////////////

/***************************************************
CHttp
	Standart constructor. 
Params
    none
Return
	none
****************************************************/
CHttp::CHttp() : CUT_MethodQueue<CHttp, MethodTypeTag>(this),
		m_bBlockingMode(FALSE),			// Set non blocking mode as default
		m_lnConnectTimeOut(5),			// Set default connection time-out to 5 secs
		m_bGoingToClose(FALSE),			// Initialize closing flag with FALSE
		m_bAbortFlag(FALSE)				// Clear abort flag

{
	// Load Http Icon
	m_hHttpIcon = LoadIcon(_Module.m_hInst, MAKEINTRESOURCE(IDI_ICON_HTTP));	

	// Initiate default control size 32 x 32 pixels
    SIZE	sz = { 32, 32 };
    AtlPixelToHiMetric (&sz, &m_sizeExtent);		// convert pixels to himetric
    m_sizeNatural	= m_sizeExtent;					// store natural extent

	// Disable resizing of the control
	m_bAutoSize		= TRUE;				
  
}

/***************************************************
~CHttp
	Destructor.
Params
    none
Return
	none
****************************************************/
CHttp::~CHttp()
{
	// Set flags to terminate all running threads
	m_bGoingToClose	= TRUE;
	m_bAbortFlag	= TRUE;

	// If thread is running - will wait till it exits
	// or will time-out. 
	if(m_hMethodThread != NULL) {
		// Resume working thread
		ResumeThread(m_hMethodThread);

		WaitWithMsgLoop(m_hMethodThread, max(m_lnConnectTimeOut * 5000, 180000));
		}

	// Destroy Http icon handle
	if(m_hHttpIcon) {
		DestroyIcon( m_hHttpIcon );							
		m_hHttpIcon = NULL;
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
STDMETHODIMP CHttp::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IHttp,
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
HRESULT CHttp::OnDraw(ATL_DRAWINFO& di)
{
	// Fill background & draw a boreder
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	// Draw Http Icon
	if(m_hHttpIcon)
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hHttpIcon);	
 		
	return S_OK;
}



////////////////////////////////////////////////////
//	IHttp interface properties Set/Get functions
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
STDMETHODIMP CHttp::get_ConnectTimeOut(long *pVal)
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
STDMETHODIMP CHttp::put_ConnectTimeOut(long newVal)
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
		return AtlReportError(CLSID_Http,"Invalid Connect Time Out value", IID_IHttp, E_FAIL);


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
STDMETHODIMP CHttp::get_BlockingMode(VARIANT_BOOL *pVal)
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
STDMETHODIMP CHttp::put_BlockingMode(VARIANT_BOOL newVal)
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
get_BodyLineCount
	Get number of lines in the body result
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CHttp::get_BodyLineCount(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = CUT_HTTPClient::GetBodyLineCount();
	return S_OK;
}

/***************************************************
get_HeaderLineCount
	Get number of lines in the header
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CHttp::get_HeaderLineCount(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = CUT_HTTPClient::GetHeaderLineCount();
	return S_OK;
}

/***************************************************
get_LinkTagCount
	Get number of link tags lines 
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CHttp::get_LinkTagCount(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = CUT_HTTPClient::GetLinkTagCount();
	return S_OK;
}

/***************************************************
get_ModifiedDate
	Get modified date from the header
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHttp::get_ModifiedDate(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

 	_bstr_t	bstrLine = CUT_HTTPClient::GetModifiedDateFromHeader();
 
 	if(!SysReAllocString(pVal, bstrLine))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_ContentType
	Get content type from the header
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHttp::get_ContentType(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

 	_bstr_t	bstrLine = CUT_HTTPClient::GetContentType();
 
 	if(!SysReAllocString(pVal, bstrLine))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_MaxLinesToStore
	Get maximum number of lines to store
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CHttp::get_MaxLinesToStore(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = GetMaxLinesToStore();
	return S_OK;
}

/***************************************************
put_MaxLinesToStore
	Set maximum number of lines to store
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CHttp::put_MaxLinesToStore(long newVal)
{
	if(newVal == CUT_HTTPClient::GetMaxLinesToStore())	return S_OK;

	if(FireOnRequestEdit(DISPID_MAX_LINES_TO_STORE) == S_FALSE)
		return S_FALSE;

	if(CUT_HTTPClient::MaxLinesToStore(newVal) == CUT_SUCCESS) {
		m_bRequiresSave = TRUE;

		FireOnChanged(DISPID_MAX_LINES_TO_STORE);

		SendOnDataChange(NULL);
		}
	else 
		return AtlReportError(CLSID_Http,"Invalid Maximum Lines To Store value", IID_IHttp, E_FAIL);

	return S_OK;
}

/***************************************************
get_ProxyServer
	Gets proxy server name
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHttp::get_ProxyServer(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

 	_bstr_t	bstrProxy = CUT_HTTPClient::GetProxy();
 
 	if(!SysReAllocString(pVal, bstrProxy))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
put_ProxyServer
	Puts proxy server name
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CHttp::put_ProxyServer(BSTR newVal)
{
	_bstr_t	bstrProxy = newVal;

	if(bstrProxy == _bstr_t(CUT_HTTPClient::GetProxy()))	return S_OK;

	if(FireOnRequestEdit(DISPID_PROXY_SERVER) == S_FALSE)
		return S_FALSE;

	CUT_HTTPClient::SetProxy(bstrProxy);
	if(bstrProxy.length() == 0)
		UseProxyServer(FALSE);
	else
		UseProxyServer(TRUE);

	m_bRequiresSave = TRUE;

	FireOnChanged(DISPID_PROXY_SERVER);

	SendOnDataChange(NULL);

	return S_OK;
}

////////////////////////////////////////////////////
//	IHttp interface methods
////////////////////////////////////////////////////

/***************************************************
GET
	Sends a GET statement to the currently 
    connected server or proxy then retrieves the 
	results into the list or file.
Params
    URL			- URL to be Requested
	[FileName]	- file name to save the data in
	Result		- pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CHttp::GET(BSTR URL, BSTR FileName, long *Result)
{
	AddMethod(METHOD_GET, Result, _VP(URL), _VP(FileName), NULL);
	return S_OK;
}

/***************************************************
HEAD
	Sends a HEAD statement to the currently 
    connected server or to the proxy then 
	retrieves the results
Params
    URL			- URL to be Requested
	Result		- pointer to the result varaible
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHttp::HEAD(BSTR URL, long *Result)
{
	AddMethod(METHOD_HEAD, Result, _VP(URL), NULL);
	return S_OK;
}

/***************************************************
CommandLine
	Issues a custom command 
Params
	Command		- command to issue
    URL			- URL to be Requested
	Data		- additional data to send
	Result		- pointer to the result varaible
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHttp::CommandLine(BSTR Command, BSTR URL, BSTR Data, long *Result)
{
	AddMethod(METHOD_OTHER, Result, _VP(Command), _VP(URL), _VP(Data), NULL);
	return S_OK;
}

/***************************************************
PUT
	Create a resource at the target URL
Params
    URL			- URL to put on
	FileName	- file name to put
	Result		- pointer to the result varaible
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHttp::PUT(BSTR URL, BSTR FileName, long *Result)
{
	AddMethod(METHOD_PUT, Result, _VP(URL), _VP(FileName), NULL);
	return S_OK;
}

/***************************************************
DeleteFile
	The DELETE method requests that the origin server 
	delete the resource identified by the Request-URI.
Params
    URL			- URL to be deleted
	Result		- pointer to the result varaible
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHttp::DeleteFile(BSTR URL, long *Result)
{
	AddMethod(METHOD_DEL_FILE, Result, _VP(URL), NULL);
	return S_OK;
}

/***************************************************
CancelHttp
	Cancel current Http operation
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CHttp::CancelHttp()
{
	m_bAbortFlag = TRUE;
	return S_OK;
}

/***************************************************
AddSendHeaderTag
    Adds a tag to the list of MIME tags to send
    as part of any command sent
Params
    tag - tag string to add to the list
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CHttp::AddSendHeaderTag(BSTR Tag, long *Result)
{
	*Result = CUT_HTTPClient::AddSendHeaderTag(_bstr_t(Tag));
	return S_OK;
}

/***************************************************
ClearSendHeaderTags
	Clears all header tags from the tag list
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CHttp::ClearSendHeaderTags()
{
	CUT_HTTPClient::ClearSendHeaderTags();
	return S_OK;
}

/***************************************************
ClearReceivedData
	Clears all received data
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CHttp::ClearReceivedData()
{
	CUT_HTTPClient::ClearReceivedData();
	return S_OK;
}

/***************************************************
GetBodyLine
	Returns a body line from memory storage
Params
    Index	- 0 based index of line to get
	Result	- pointer to the result varaible
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHttp::GetBodyLine(long Index, BSTR *Result)
{
 	_bstr_t	bstrLine	= CUT_HTTPClient::GetBodyLine(Index);
 
 	if(!SysReAllocString(Result, bstrLine))
 		return E_OUTOFMEMORY;
	
	return S_OK;
}

/***************************************************
GetHeaderLine
	Returns a header line from memory storage
Params
    Index	- 0 based index of line to get
	Result	- pointer to the result varaible
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CHttp::GetHeaderLine(long Index, BSTR *Result)
{
 	_bstr_t	bstrLine	= CUT_HTTPClient::GetHeaderLine(Index);
 
 	if(!SysReAllocString(Result, bstrLine))
 		return E_OUTOFMEMORY;
	
	return S_OK;
}

/*********************************************
GetLinkTag
    returns a link tag from memory storage
Params
    Index	- 0 based index of the tag
	Result	- pointer to the result varaible
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
**********************************************/
STDMETHODIMP CHttp::GetLinkTag(long Index, BSTR *Result)
{
	char	buffer[1000];
 	_bstr_t	bstrLine	= L"";
	
	if(CUT_HTTPClient::GetLinkTag(Index, buffer, sizeof(buffer)-1) == UTE_SUCCESS)
		bstrLine = buffer;
 
 	if(!SysReAllocString(Result, bstrLine))
 		return E_OUTOFMEMORY;
	
	return S_OK;
}

/*********************************************
SaveToFile
    Saves memory storage to a file
Params
    FileName	- name of the file to create
	Result		- pointer to the result varaible
Return
	S_OK			- success
**********************************************/
STDMETHODIMP CHttp::SaveToFile(BSTR FileName, long *Result)
{
	*Result = CUT_HTTPClient::SaveToFile(_bstr_t(FileName));
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
STDMETHODIMP CHttp::AboutBox()
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
STDMETHODIMP CHttp::GetErrorText(long ErrorCode, BSTR *ErrorText)
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
STDMETHODIMP CHttp::GetInterfaceSafetyOptions(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
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
STDMETHODIMP CHttp::SetInterfaceSafetyOptions(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
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
BOOL CHttp::IsAborted() {
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
BOOL CHttp::WaitWithMsgLoop(HANDLE hEvent, long lTimeout)
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
ExecuteMethod
	Executes method of specified type and then fire
	event if nesessary.
Params
    type	- type of method
Return
	UTE_SUCCESS	- success
	UTE_ERROR	- error
****************************************************/
long CHttp::ExecuteMethod(MethodTypeTag MethodID, _variant_t *ptrVarParams, BOOL bForceNonBlocking)
{
	LONG	lRetCode;

    // If we are not going to destroy the object - clear the abort flag
	if(!m_bGoingToClose)
	    m_bAbortFlag	= FALSE;

	switch(MethodID) {
		case(METHOD_GET):
			lRetCode = CUT_HTTPClient::GET(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnGET(lRetCode);
				}
			break;
		case(METHOD_HEAD):
			lRetCode = CUT_HTTPClient::HEAD(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnHEAD(lRetCode);
				}
			break;
		case(METHOD_PUT):
			lRetCode = CUT_HTTPClient::PUT(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnPUT(lRetCode);
				}
			break;
		case(METHOD_DEL_FILE):
			lRetCode = CUT_HTTPClient::DeleteFile(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnDeleteFile(lRetCode);
				}
			break;
		case(METHOD_OTHER):
			lRetCode = CUT_HTTPClient::CommandLine(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]), _bstr_t(ptrVarParams[2]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnCommandLine(lRetCode);
				}
			break;

		// Unknown method error
		default:
			return UTE_ERROR;
		}

	return lRetCode;
}

#pragma warning (pop)