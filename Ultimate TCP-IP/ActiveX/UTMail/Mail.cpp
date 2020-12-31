//=================================================================
//  class: CMail
//  File:  Mail.cpp
//
//  Implementation of CMail class
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
#include "UTMail.h"
#include "Mail.h"

#include <process.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include "ut_clnt.h"
#include "AboutDlg.h"
#include "UTMessage.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

/////////////////////////////////////////////////////////////////////////////
// CMail
/////////////////////////////////////////////////////////////////////////////

/***************************************************
CMail
	Standart constructor. 
Params
    none
Return
	none
****************************************************/
CMail::CMail() : CUT_MethodQueue<CMail, MethodTypeTag>(this),

		m_bBlockingMode(FALSE),			// Set non blocking mode as default
		m_bGoingToClose(FALSE),			// Initialize closing flag with FALSE
		m_bAbortFlag(FALSE),			// Clear abort flag
        m_nMsgNumber(0),                // Initialize number of messages
        m_lMsgSize(0),                  // Initialize message size
        m_bstrLineRead(L"")             // Initialize last line read
		
{
	// Load Mail Icon
	m_hMailIcon = LoadIcon(_Module.m_hInst, MAKEINTRESOURCE(IDI_ICON_MAIL));	

	// Initiate default control size 32 x 32 pixels
    SIZE	sz = { 32, 32 };
    AtlPixelToHiMetric (&sz, &m_sizeExtent);		// convert pixels to himetric
    m_sizeNatural	= m_sizeExtent;					// store natural extent

	// Disable resizing of the control
	m_bAutoSize		= TRUE;				

    // Initialize local host name
    m_bstrLocalHostName = "localhost";

#ifdef _BLOCKING_MODE_ONLY

    // Set blocking mode 
    m_bBlockingMode = TRUE;

#endif // _BLOCKING_MODE_ONLY

}

/***************************************************
~CMail
	Destructor.
Params
    none
Return
	none
****************************************************/
CMail::~CMail()
{
	// Set flags to terminate all running threads
	m_bGoingToClose	= TRUE;
	m_bAbortFlag	= TRUE;

	// If thread is running - will wait till it exits
	// or will time-out. 
	if(m_hMethodThread != NULL) {
		// Resume working thread
		ResumeThread(m_hMethodThread);

		WaitWithMsgLoop(m_hMethodThread, 120000);
		}

	// Destroy Mail icon handle
	if(m_hMailIcon) {
		DestroyIcon( m_hMailIcon );							
		m_hMailIcon = NULL;
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
STDMETHODIMP CMail::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMail,
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
HRESULT CMail::OnDraw(ATL_DRAWINFO& di)
{
	// Fill background & draw a boreder
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	// Draw Mail Icon
	if(m_hMailIcon)
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hMailIcon);	
 		
	return S_OK;
}


////////////////////////////////////////////////////
//	IMail interface properties Set/Get functions
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
STDMETHODIMP CMail::get_ConnectTimeOut(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = CUT_SMTPMailClient::GetConnectTimeout();
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
STDMETHODIMP CMail::put_ConnectTimeOut(long newVal)
{
	if(newVal == CUT_SMTPMailClient::GetConnectTimeout())	return S_OK;

	if(FireOnRequestEdit(DISPID_CONNECT_TIME_OUT) == S_FALSE)
		return S_FALSE;

	if(CUT_SMTPMailClient::SetConnectTimeout(newVal) == CUT_SUCCESS) {
		CUT_POP3MailClient::SetConnectTimeout(newVal);
		m_bRequiresSave = TRUE;

		FireOnChanged(DISPID_CONNECT_TIME_OUT);

		SendOnDataChange(NULL);
		}
	else 
		return AtlReportError(CLSID_Mail,"Invalid Connect Time Out value", IID_IMail, E_FAIL);


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
STDMETHODIMP CMail::get_ReceiveTimeOut(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = CUT_SMTPMailClient::GetSMTPTimeOut();
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
STDMETHODIMP CMail::put_ReceiveTimeOut(long newVal)
{
	if(newVal == CUT_SMTPMailClient::GetSMTPTimeOut())	return S_OK;

	if(FireOnRequestEdit(DISPID_RECEIVE_TIME_OUT) == S_FALSE)
		return S_FALSE;

	if(CUT_SMTPMailClient::SetSMTPTimeOut(newVal) == CUT_SUCCESS) {
		CUT_POP3MailClient::SetPOP3TimeOut(newVal);
		
		m_bRequiresSave = TRUE;

		FireOnChanged(DISPID_RECEIVE_TIME_OUT);

		SendOnDataChange(NULL);
		}
	else 
		return AtlReportError(CLSID_Mail,"Invalid Receive Time Out value", IID_IMail,E_FAIL);

	return S_OK;
}

#ifndef _BLOCKING_MODE_ONLY

/***************************************************
get_BlockingMode
	Get blocking mode value
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CMail::get_BlockingMode(VARIANT_BOOL *pVal)
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
STDMETHODIMP CMail::put_BlockingMode(VARIANT_BOOL newVal)
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

#endif // _BLOCKING_MODE_ONLY

/***************************************************
get_LocalHostName
	Returns Local host name
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMail::get_LocalHostName(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, m_bstrLocalHostName))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
put_LocalHostName
	Set Local host name
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
****************************************************/
STDMETHODIMP CMail::put_LocalHostName(BSTR newVal)
{
	if(_bstr_t(newVal) == m_bstrLocalHostName)	return S_OK;

	if(FireOnRequestEdit(DISPID_LOCAL_HOST_NAME) == S_FALSE)
		return S_FALSE;

	m_bstrLocalHostName = newVal;

	m_bRequiresSave = TRUE;

	FireOnChanged(DISPID_LOCAL_HOST_NAME);

	SendOnDataChange(NULL);

	return S_OK;
}
/***************************************************
get_MailHostName
	Returns Mail host name
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMail::get_MailHostName(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, m_bstrMailHostName))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
put_MailHostName
	Set Mail host name
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
****************************************************/
STDMETHODIMP CMail::put_MailHostName(BSTR newVal)
{
	if(_bstr_t(newVal) == m_bstrMailHostName)	return S_OK;

	if(FireOnRequestEdit(DISPID_MAIL_HOST_NAME) == S_FALSE)
		return S_FALSE;

	m_bstrMailHostName = newVal;

	m_bRequiresSave = TRUE;

	FireOnChanged(DISPID_MAIL_HOST_NAME);

	SendOnDataChange(NULL);

	return S_OK;
}

/***************************************************
get_POP3HostName
	Returns POP3 host name
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMail::get_POP3HostName(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, m_bstrPOP3HostName))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
put_POP3HostName
	Set POP3 host name
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
****************************************************/
STDMETHODIMP CMail::put_POP3HostName(BSTR newVal)
{
	if(_bstr_t(newVal) == m_bstrPOP3HostName)	return S_OK;

	if(FireOnRequestEdit(DISPID_POP3_HOST_NAME) == S_FALSE)
		return S_FALSE;

	m_bstrPOP3HostName = newVal;

	m_bRequiresSave = TRUE;

	FireOnChanged(DISPID_POP3_HOST_NAME);

	SendOnDataChange(NULL);

	return S_OK;
}

/***************************************************
get_UserName
	Returns user name
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMail::get_UserName(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, m_bstrUserName))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
put_UserName
	Set user name
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
****************************************************/
STDMETHODIMP CMail::put_UserName(BSTR newVal)
{
	if(_bstr_t(newVal) == m_bstrUserName)	return S_OK;

	if(FireOnRequestEdit(DISPID_USER_NAME) == S_FALSE)
		return S_FALSE;

	m_bstrUserName = newVal;

	m_bRequiresSave = TRUE;

	FireOnChanged(DISPID_USER_NAME);

	SendOnDataChange(NULL);

	return S_OK;
}

/***************************************************
get_UserPassword
	Returns user password
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMail::get_UserPassword(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, m_bstrUserPassword))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
put_UserPassword
	Set user password
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
****************************************************/
STDMETHODIMP CMail::put_UserPassword(BSTR newVal)
{
	if(_bstr_t(newVal) == m_bstrUserPassword)	return S_OK;

	if(FireOnRequestEdit(DISPID_USER_PASSWORD) == S_FALSE)
		return S_FALSE;

	m_bstrUserPassword = newVal;

	m_bRequiresSave = TRUE;

	FireOnChanged(DISPID_USER_PASSWORD);

	SendOnDataChange(NULL);

	return S_OK;
}

/***************************************************
get_MsgNumber
	Gets number of messages. Use this property after 
    calling GetMsgNumber method.
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMail::get_MsgNumber(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = m_nMsgNumber;
	return S_OK;
}

/***************************************************
get_MsgSize
	Gets message size. Use this property after calling
    GetMsgSize method.
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMail::get_MsgSize(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = m_lMsgSize;
	return S_OK;
}

/***************************************************
get_LineRead
	Returns last linr read by ReatTopLine or ReadMsgLine 
    methods
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMail::get_LineRead(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, m_bstrLineRead))
		return E_OUTOFMEMORY;

	return S_OK;
}

////////////////////////////////////////////////////
//	IMail interface methods
////////////////////////////////////////////////////

#ifndef _BLOCKING_MODE_ONLY
/***************************************************
CancelMail
	Cancel current Mail operation
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::CancelMail()
{
	m_bAbortFlag = TRUE;
	return S_OK;
}
#endif // _BLOCKING_MODE_ONLY

/***************************************************
AboutBox
	Display about box
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::AboutBox()
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
STDMETHODIMP CMail::GetErrorText(long ErrorCode, BSTR *ErrorText)
{
 	HRESULT		hResult			= S_OK;
 	CComBSTR	bstrErrorMsg	= CUT_ERR::GetErrorString(ErrorCode);
 
 	if(!SysReAllocString(ErrorText, bstrErrorMsg))
 		hResult = E_OUTOFMEMORY;
 
 	return hResult;
}

/***************************************************
SMTPConnect
	Connects to the mail server
Params
	Result		- pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CMail::SMTPConnect(long *Result)
{
	AddMethod(METHOD_SMTP_CONNECT, Result, _VP(m_bstrMailHostName), _VP(m_bstrLocalHostName), NULL);
	return S_OK;
}

/***************************************************
SMTPClose
	Close connection to the mail server
Params
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::SMTPClose(long *Result)
{
	AddMethod(METHOD_SMTP_CLOSE, Result, NULL);
	return S_OK;
}

/***************************************************
SendMail
	Sends mail
Params
	To		- To field
	From	- From field
	Subject	- Subject field
	Message	- Message body 
	Cc		- CC field
	Bcc		- BCC field
	Attach	- Names of attachments separated by ','
	Result	- pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CMail::SendMail(BSTR To, BSTR From, BSTR Subject, BSTR Message, BSTR Cc, BSTR Bcc, BSTR Attach, long *Result)
{
	AddMethod(METHOD_SEND_MAIL, Result,		_VP(To), 
											_VP(From), 
											_VP(Subject), 
											_VP(Message), 
											_VP(Cc), 
											_VP(Bcc), 
											_VP(Attach), 
											NULL);
	return S_OK;
}

/***************************************************
SendMailFromFile
	Sends mail from the file
Params
	FileName    - file name which stores message in RFC822 format
	Result	    - pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CMail::SendMailFromFile(BSTR FileName, long *Result)
{
	
    AddMethod(METHOD_SEND_MAIL_FROM_FILE, Result, _VP(FileName), NULL);
	return S_OK;
}


/***************************************************
POP3Connect
	Connects to the POP3 server
Params
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::POP3Connect(long *Result)
{
	AddMethod(METHOD_POP3_CONNECT, Result, _VP(m_bstrPOP3HostName), _VP(m_bstrUserName), _VP(m_bstrUserPassword), NULL);
	return S_OK;
}

/***************************************************
POP3Close
	Close connection to the POP3 server
Params
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::POP3Close(long *Result)
{
	AddMethod(METHOD_POP3_CLOSE, Result, NULL);
	return S_OK;
}

/***************************************************
GetMsgNumber
	Get number of messages
Params
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::GetMsgNumber(long *Result)
{
    m_nMsgNumber = 0;
	AddMethod(METHOD_GET_MSG_NUMBER, Result, NULL);
	return S_OK;
}

/***************************************************
GetMsgSize
	Gets message size
Params
	MsgIndex	- message index
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::GetMsgSize(long MsgIndex, long *Result)
{
    m_lMsgSize = 0;
	AddMethod(METHOD_GET_MSG_SIZE, Result, _VP(MsgIndex), NULL);
	return S_OK;
}

/***************************************************
SaveMsg
	Gets message and saves it to the file
Params
	MsgIndex	- message index
	FileName	- file name to save message into
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::SaveMsg(long MsgIndex, BSTR FileName, long *Result)
{
	AddMethod(METHOD_SAVE_MSG, Result, _VP(MsgIndex), _VP(FileName), NULL);
	return S_OK;
}

/***************************************************
DeleteMsg
	Mark a message for deletion.
Params
	MsgIndex	- message index
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::DeleteMsg(long MsgIndex, long *Result)
{
	AddMethod(METHOD_DELETE_MSG, Result, _VP(MsgIndex), NULL);
	return S_OK;
}

/***************************************************
DeleteMsg
	If any messages have been marked as deleted 
    by the pop3 server they are unmarked.
Params
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::ResetDelete(long *Result)
{
	AddMethod(METHOD_RESET_DELETE, Result, NULL);
	return S_OK;
}

/***************************************************
OpenMsg
    To allow us read part of the message without having to download it all
    we will issue a RETR command and receive only the response from the server
    If the server response is positive then we will flag the MessageOpen.
    By doing so the message will be available to us on the receive buffer where we can 
    either read the whole message or receive it by line by line
Params
	MsgIndex	- message index
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::OpenMsg(long MsgIndex, long *Result)
{
	AddMethod(METHOD_OPEN_MSG, Result, _VP(MsgIndex), NULL);
	return S_OK;
}

/***************************************************
CloseMsg
    Close the currently open message by reading all
    availabe lines of the messages if any.
Params
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::CloseMsg(long *Result)
{
	AddMethod(METHOD_CLOSE_MSG, Result, NULL);
	return S_OK;
}

/***************************************************
ReadMsgLine
    Read a single line of the Already open message
    A call to OpenMsg() should be made prior to calling this function
Params
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::ReadMsgLine(long *Result)
{
    m_bstrLineRead = L"";
	AddMethod(METHOD_READ_MSG_LINE, Result, NULL);
	return S_OK;
}

/***************************************************
OpenTop
    To allow us to read the top part of the message without having to download it all.
    We will issue a TOP command and receive only the response from the server
    If the server response is positive then we will flag the TopOpen.
    By doing so the message will be available to us on the receive buffer where we can 
    either read the whole message Top or receive it by line by line.
Params
	MsgIndex	- message index
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::OpenTop(long MsgIndex, long MsgLines, long *Result)
{
	AddMethod(METHOD_OPEN_TOP, Result, _VP(MsgIndex), _VP(MsgLines), NULL);
	return S_OK;
}

/***************************************************
CloseTop
    Close the currently open message by reading all
    availabe lines of the Top response if any.
Params
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::CloseTop(long *Result)
{
	AddMethod(METHOD_CLOSE_TOP, Result, NULL);
	return S_OK;
}

/***************************************************
ReadTopLine
    Read a single line of the already open message Top.
    A call to OpenTop() should be made prior to calling this function
Params
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMail::ReadTopLine(long *Result)
{
    m_bstrLineRead = L"";
	AddMethod(METHOD_READ_TOP_LINE, Result, NULL);
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
STDMETHODIMP CMail::GetInterfaceSafetyOptions(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
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
STDMETHODIMP CMail::SetInterfaceSafetyOptions(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
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
OnSaveMsg
    Virtual function designed to be overridden to  
    receive report of progress of save message process.
PARAM
    bytesRetrieved - Number of bytes received so far
RETURN
    TRUE	- to continue
    FALSE	- to cancel
****************************************************/
BOOL CMail::OnSaveMsg(long bytesRetrieved) {

#ifndef _BLOCKING_MODE_ONLY
	if(!m_bGoingToClose) {
		m_bUseMarshaling = !m_bBlockingMode; 
		Fire_OnSaveMsgProgress(bytesRetrieved);
		}
#endif // _BLOCKING_MODE_ONLY

    return !CUT_POP3MailClient::m_bAbortFlag;
}

/********************************
OnSendMailProgress
	Virtual function to be overridden to inform the user
	of the send mail progress and to check if the user wants
	to cancel the process.
PARAM:
    long bytesSent  - number of bytes sent 
    long totalBytes - Total number of bytes for the message being processed
RETURN
    FALSE - cancel the send process
    TRUE  - Continue
*********************************/
BOOL CMail::OnSendMailProgress(long bytesSent,long totalBytes){

#ifndef _BLOCKING_MODE_ONLY
	if(!m_bGoingToClose)
		Fire_OnSendMailProgress(bytesSent, totalBytes);
#endif // _BLOCKING_MODE_ONLY
    return !(m_bAbortFlag); // GW (Oct 11th 2000, called the class memeber not the CUT_SMTPClient memeber)
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
BOOL CMail::WaitWithMsgLoop(HANDLE hEvent, long lTimeout)
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
long CMail::ExecuteMethod(MethodTypeTag MethodID, _variant_t *ptrVarParams, BOOL bForceNonBlocking)
{
	LONG	lRetCode;
	char	buffer[MAX_LINE_LENGTH + 1];

    // If we are not going to destroy the object - clear the abort flag
	if(!m_bGoingToClose)
	    m_bAbortFlag	= FALSE;

    switch(MethodID) {
		case(METHOD_SMTP_CONNECT):
			lRetCode = CUT_SMTPClient::SMTPConnect(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]));

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnSMTPConnect(lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;
		case(METHOD_SMTP_CLOSE):
			lRetCode = CUT_SMTPClient::SMTPClose();

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnSMTPClose(lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;
		case(METHOD_SEND_MAIL_FROM_FILE):
            {
            CUT_Msg     msg;
        
            // Load file in the message class
            if((lRetCode = msg.LoadMessage(_bstr_t(ptrVarParams[0]))) == UTE_SUCCESS) {
    			lRetCode = CUT_SMTPClient::SendMail(msg);
                }

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnSendMail(lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;
            }
		case(METHOD_SEND_MAIL):
			{
			_bstr_t m_bstrAttachments	= ptrVarParams[6];
			int		i, nAttachNumber	= CUT_StrMethods::GetParseStringPieces(m_bstrAttachments, ",");
			LPSTR	*lpszAttach			= NULL;

			// Create attachments list
			if(nAttachNumber > 0) {
				lpszAttach = new LPSTR[nAttachNumber];
				for(i = 0; i < nAttachNumber; i++) {
					lpszAttach[i] = new char[_MAX_PATH + 1];
					CUT_StrMethods::ParseString(m_bstrAttachments, ",", i, lpszAttach[i], _MAX_PATH);
					}
				}

			lRetCode = CUT_SMTPClient::SendMail(	_bstr_t(ptrVarParams[0]),
													_bstr_t(ptrVarParams[1]),
													_bstr_t(ptrVarParams[2]),
													_bstr_t(ptrVarParams[3]),
													_bstr_t(ptrVarParams[4]),
													_bstr_t(ptrVarParams[5]),
													(LPCSTR *) lpszAttach,
													nAttachNumber);
			
        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnSendMail(lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY

			// Clean attachments buffer
			if(lpszAttach != NULL) {
				for(i = 0; i < nAttachNumber; i++) 
					if(lpszAttach[i] != NULL)
					delete [] lpszAttach[i];
				delete [] lpszAttach;
				}

			break;
			}
		case(METHOD_POP3_CONNECT):
			lRetCode = CUT_POP3Client::POP3Connect(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]), _bstr_t(ptrVarParams[2]));

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnPOP3Connect(lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY

			break;
		case(METHOD_POP3_CLOSE):
			lRetCode = CUT_POP3Client::POP3Close();

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnPOP3Close(lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;
		case(METHOD_GET_MSG_NUMBER):
			lRetCode = CUT_POP3Client::GetNumMsgs(&m_nMsgNumber);

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnGetMsgNumber((long)m_nMsgNumber, lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;
		case(METHOD_GET_MSG_SIZE):
			lRetCode = CUT_POP3Client::GetMsgSize((long)ptrVarParams[0], &m_lMsgSize);

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnGetMsgSize(m_lMsgSize, lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;
		case(METHOD_SAVE_MSG):
			lRetCode = CUT_POP3Client::SaveMsg((long)ptrVarParams[0], _bstr_t(ptrVarParams[1]));

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnSaveMsg(lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;
		case(METHOD_DELETE_MSG):
			lRetCode = CUT_POP3Client::DeleteMsg((long)ptrVarParams[0]);

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnDeleteMsg(lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;
		case(METHOD_RESET_DELETE):
			lRetCode = CUT_POP3Client::ResetDelete();

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnResetDelete(lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;
		case(METHOD_OPEN_MSG):
			lRetCode = CUT_POP3Client::OpenMsg((long)ptrVarParams[0]);

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnOpenMsg(lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;
		case(METHOD_CLOSE_MSG):
			lRetCode = CUT_POP3Client::CloseMsg();

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnCloseMsg(lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;
		case(METHOD_READ_MSG_LINE):
			lRetCode = CUT_POP3Client::ReadMsgLine(buffer, MAX_LINE_LENGTH);

            m_bstrLineRead = buffer;

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnReadMsgLine(m_bstrLineRead, lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;
		case(METHOD_OPEN_TOP):
			lRetCode = CUT_POP3Client::OpenTop((long)ptrVarParams[0], (long)ptrVarParams[1]);

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnOpenTop(lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;
		case(METHOD_CLOSE_TOP):
			lRetCode = CUT_POP3Client::CloseTop();

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnCloseTop(lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;
		case(METHOD_READ_TOP_LINE):
			lRetCode = CUT_POP3Client::ReadTopLine(buffer, MAX_LINE_LENGTH);

            m_bstrLineRead = buffer;

        #ifndef _BLOCKING_MODE_ONLY
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnReadTopLine(m_bstrLineRead, lRetCode);
				}
        #endif // _BLOCKING_MODE_ONLY
			break;

		// Unknown method error
		default:
			return UTE_ERROR;
		}

	return lRetCode;
}


#pragma warning (pop)