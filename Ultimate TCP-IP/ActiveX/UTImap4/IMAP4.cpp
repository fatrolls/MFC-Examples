//=================================================================
//  class: CIMAP4
//  File:  IMAP4.cpp
//
//  Implementation of CIMAP4 class
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
#include "UTImap4.h"
#include "IMAP4.h"

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
// CIMAP4
/////////////////////////////////////////////////////////////////////////////

/***************************************************
CIMAP4
	Standart constructor. 
Params
    none
Return
	none
****************************************************/
CIMAP4::CIMAP4() : CUT_MethodQueue<CIMAP4, MethodTypeTag> (this),
        m_CurStatusData(NULL),			// Initialize last status data
        m_CurMessageData(NULL),			// Initialize current message data
		m_CurMessage(NULL),				// Initialize current decoding message
		m_bBlockingMode(FALSE),			// Set non blocking mode as default
		m_bGoingToClose(FALSE),			// Initialize closing flag with FALSE
		m_bAbortFlag(FALSE)				// Clear abort flag
		
{
	// Load IMAP4 Icon
	m_hIMAP4Icon = LoadIcon(_Module.m_hInst, MAKEINTRESOURCE(IDI_ICON_IMAP4));	

	// Initiate default control size 32 x 32 pixels
    SIZE	sz = { 32, 32 };
    AtlPixelToHiMetric (&sz, &m_sizeExtent);		// convert pixels to himetric
    m_sizeNatural	= m_sizeExtent;					// store natural extent

	// Disable resizing of the control
	m_bAutoSize		= TRUE;				
}

/***************************************************
~CIMAP4
	Destructor.
Params
    none
Return
	none
****************************************************/
CIMAP4::~CIMAP4()
{
	// Set flags to terminate all running threads
	m_bGoingToClose	= TRUE;
	m_bAbortFlag	= TRUE;

    // Set IMAP4 class destroy flag
    CUT_IMAP4Client::m_bGoingToDestroy = TRUE;

	// Destroy message class
	if(m_CurMessage != NULL)
		delete m_CurMessage;

    // Destroy status data class
    if(m_CurStatusData != NULL)
        delete m_CurStatusData;

	// If thread is running - will wait till it exits
	// or will time-out. 
	if(m_hMethodThread != NULL) {
		// Resume working thread
		ResumeThread(m_hMethodThread);

		WaitWithMsgLoop(m_hMethodThread, 120000);
		}

	// Destroy IMAP4 icon handle
	if(m_hIMAP4Icon) {
		DestroyIcon( m_hIMAP4Icon );							
		m_hIMAP4Icon = NULL;
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
STDMETHODIMP CIMAP4::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IIMAP4,
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
HRESULT CIMAP4::OnDraw(ATL_DRAWINFO& di)
{
	// Fill background & draw a boreder
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	// Draw IMAP4 Icon
	if(m_hIMAP4Icon)
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hIMAP4Icon);	
 		
	return S_OK;
}


////////////////////////////////////////////////////
//	IIMAP4 interface properties Set/Get functions
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
STDMETHODIMP CIMAP4::get_ConnectTimeOut(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = CUT_IMAP4Client::GetConnectTimeout();
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
STDMETHODIMP CIMAP4::put_ConnectTimeOut(long newVal)
{
	if(newVal == CUT_IMAP4Client::GetConnectTimeout())	return S_OK;

	if(FireOnRequestEdit(DISPID_CONNECT_TIME_OUT) == S_FALSE)
		return S_FALSE;

	if(CUT_IMAP4Client::SetConnectTimeout(newVal) == CUT_SUCCESS) {
		m_bRequiresSave = TRUE;

		FireOnChanged(DISPID_CONNECT_TIME_OUT);

		SendOnDataChange(NULL);
		}
	else 
		return AtlReportError(CLSID_IMAP4,"Invalid Connect Time Out value", IID_IIMAP4, E_FAIL);


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
STDMETHODIMP CIMAP4::get_ReceiveTimeOut(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = CUT_IMAP4Client::GetIMAP4TimeOut();
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
STDMETHODIMP CIMAP4::put_ReceiveTimeOut(long newVal)
{
	if(newVal == CUT_IMAP4Client::GetIMAP4TimeOut())	return S_OK;

	if(FireOnRequestEdit(DISPID_RECEIVE_TIME_OUT) == S_FALSE)
		return S_FALSE;

	if(CUT_IMAP4Client::SetIMAP4TimeOut(newVal) == CUT_SUCCESS) {
		
		m_bRequiresSave = TRUE;

		FireOnChanged(DISPID_RECEIVE_TIME_OUT);

		SendOnDataChange(NULL);
		}
	else 
		return AtlReportError(CLSID_IMAP4,"Invalid Receive Time Out value", IID_IIMAP4,E_FAIL);

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
STDMETHODIMP CIMAP4::get_BlockingMode(VARIANT_BOOL *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = m_bBlockingMode;
	return S_OK;
}

/***************************************************
get_NewMailCheckInterval
	Gets new mail check interval
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CIMAP4::get_NewMailCheckInterval(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	*pVal = CUT_IMAP4Client::GetNewMailCheckInterval();
	return S_OK;

}

/***************************************************
put_NewMailCheckInterval
	Sets new mail check interval
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
	E_FAIL		- invalid connect time-out value
****************************************************/
STDMETHODIMP CIMAP4::put_NewMailCheckInterval(long newVal)
{
	if(newVal == CUT_IMAP4Client::GetNewMailCheckInterval())	return S_OK;

	if(FireOnRequestEdit(DISPID_NEW_MAIL_CHECK_INER) == S_FALSE)
		return S_FALSE;

	if(CUT_IMAP4Client::SetNewMailCheckInterval(newVal) == CUT_SUCCESS) {
		
		m_bRequiresSave = TRUE;

		FireOnChanged(DISPID_NEW_MAIL_CHECK_INER);

		SendOnDataChange(NULL);
		}
	else 
		return AtlReportError(CLSID_IMAP4,"Invalid interval value", IID_IIMAP4,E_FAIL);

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
STDMETHODIMP CIMAP4::put_BlockingMode(VARIANT_BOOL newVal)
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
get_IMAP4HostName
	Returns IMAP4 host name
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::get_HostName(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, m_bstrHostName))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
put_IMAP4HostName
	Set IMAP4 host name
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
****************************************************/
STDMETHODIMP CIMAP4::put_HostName(BSTR newVal)
{
	if(_bstr_t(newVal) == m_bstrHostName)	return S_OK;

	if(FireOnRequestEdit(DISPID_HOST_NAME) == S_FALSE)
		return S_FALSE;

	m_bstrHostName = newVal;

	m_bRequiresSave = TRUE;

	FireOnChanged(DISPID_HOST_NAME);

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
STDMETHODIMP CIMAP4::get_UserName(BSTR *pVal)
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
STDMETHODIMP CIMAP4::put_UserName(BSTR newVal)
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
STDMETHODIMP CIMAP4::get_UserPassword(BSTR *pVal)
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
STDMETHODIMP CIMAP4::put_UserPassword(BSTR newVal)
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
get_MailBoxWriteAccess
	Gets mail box write access permition
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::get_MailBoxWriteAccess(VARIANT_BOOL *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (VARIANT_BOOL) m_bMailBoxWriteAccess;
	return S_OK;
}

/***************************************************
get_MailBoxMsgNumber
	Gets number of messages in the mail box 
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::get_MailBoxMsgNumber(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_lMailBoxMsgNumber;
	return S_OK;
}

/***************************************************
get_MailBoxMsgRecent
	Gets number of recent messages in the mail box 
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::get_MailBoxMsgRecent(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_lMailBoxMsgRecent;
	return S_OK;
}

/***************************************************
get_MailBoxSystemFlags
	Gets mail box system flags
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::get_MailBoxSystemFlags(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_lMailBoxFlags;
	return S_OK;
}

/***************************************************
get_MailBoxFlags
	Gets mail box flags
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::get_MailBoxFlags(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, _bstr_t(m_szMailBoxUnknownFlags)))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_MailBoxPermSystemFlags
	Gets mail box permanent system flags
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::get_MailBoxPermSystemFlags(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_lMailBoxPermanentFlags;
	return S_OK;
}

/***************************************************
get_MailBoxPermFlags
	Gets mail box permanent flags
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::get_MailBoxPermFlags(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, _bstr_t(m_szMailBoxPermanentUnknownFlags)))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_MailBoxUID
	Gets mail box unique identifier validity value
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::get_MailBoxUID(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_lMailBoxUIVV;
	return S_OK;
}

/***************************************************
get_MailBoxMsgUnseen
	Gets number of unseen messages in the mail box 
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::get_MailBoxMsgUnseen(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_lMailBoxMsgUnSeen;
	return S_OK;
}

/***************************************************
get_Capability
	Gets IMAP4 server capability string
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::get_Capability(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, _bstr_t(GetCapability())))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_ClientState
	Gets client state
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::get_ClientState(IMAP4ClientState *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (IMAP4ClientState)GetClientState();
	return S_OK;
}

////////////////////////////////////////////////////
//	IIMAP4 interface methods
////////////////////////////////////////////////////

/***************************************************
Cancel
	Cancel current IMAP4 operation
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CIMAP4::Cancel()
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
STDMETHODIMP CIMAP4::AboutBox()
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
STDMETHODIMP CIMAP4::GetErrorText(long ErrorCode, BSTR *ErrorText)
{
 	HRESULT		hResult			= S_OK;
 
 	if(!SysReAllocString(ErrorText, _bstr_t(CUT_ERR::GetErrorString(ErrorCode))))
 		hResult = E_OUTOFMEMORY;
 
 	return hResult;
}

/***************************************************
GetLastCommandResponseText
	Returns a text send by the server with the last
    command response
Params
    none
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetLastCommandResponseText(BSTR *Text)
{
    HRESULT		hResult			= S_OK;

    if(!SysReAllocString(Text, _bstr_t(CUT_IMAP4Client::GetLastCommandResponseText())))
 		hResult = E_OUTOFMEMORY;

    return hResult;
}

/***************************************************
GetAttachNumber
	Gets current decoding message attachments number
Params
	AttachNumber- pointer to the result varaible
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CIMAP4::GetAttachNumber(long *AttachNumber)
{
	if(AttachNumber == NULL)	return E_POINTER;

	*AttachNumber = 0;
	if(m_CurMessage != NULL)
		*AttachNumber = m_CurMessage->GetAttachmentNumber();

	return S_OK;
}

/***************************************************
GetDecodedMsgBody
	Gets current decoding message decoded message body
Params
	MsgBody		- pointer to the result varaible
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetDecodedMsgBody(BSTR *MsgBody)
{
	if(MsgBody == NULL)	return E_POINTER;

	_bstr_t		bstrMsgBody = "";

	if(m_CurMessage != NULL)
		bstrMsgBody = m_CurMessage->GetMessageBody();

 	if(!SysReAllocString(MsgBody, bstrMsgBody))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
GetAttachName
	Gets current decoding message attachment name
Params
	AttachIndex	- attachment index
	Name		- pointer to the name result varaible
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetAttachName(long AttachIndex, BSTR *Name)
{
	if(Name == NULL )	return E_POINTER;

	char	szName[_MAX_PATH + 1] = "", szType[_MAX_PATH + 1] = "";

	if(m_CurMessage != NULL) 
		m_CurMessage->GetAttachmentInfo(	AttachIndex, 
											szName, _MAX_PATH,
											szType, _MAX_PATH,
											NULL);

	if(!SysReAllocString(Name, _bstr_t(szName)))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
GetAttachType
	Gets current decoding message attachment type
Params
	AttachIndex	- attachment index
	Type		- pointer to the type result varaible
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetAttachType(long AttachIndex, BSTR *Type)
{
	if(Type == NULL)	return E_POINTER;

	char	szName[_MAX_PATH + 1] = "", szType[_MAX_PATH + 1] = "";

	if(m_CurMessage != NULL) 
		m_CurMessage->GetAttachmentInfo(	AttachIndex, 
											szName, _MAX_PATH,
											szType, _MAX_PATH,
											NULL);

	if(!SysReAllocString(Type, _bstr_t(szType)))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
GetMsgHeader
	Gets current message header
Params
	Type	- type of the header
	Header	- pointer to result variable
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetMsgHeader(MsgHeaderFields Type, BSTR *Header)
{
	HRESULT		hr = S_OK;
    _bstr_t     bstrHeader = "";
	
	if(Header == NULL)	return E_POINTER;

    if(m_CurMessage != NULL) {
	    int		index, nHeaderCount = m_CurMessage->GetHeaderCount((HeaderFieldID)Type);
	    LPCSTR	ptrData;
	    for(index = 0; index < nHeaderCount; index ++) {
		    if((ptrData = m_CurMessage->GetHeaderByType((HeaderFieldID)Type, index)) != NULL) {
                bstrHeader += ptrData;
                if(Type == UTM_CUSTOM_FIELD) {
                    bstrHeader += "\r\n";
                    }
			    }
		    }
        }


 	if(!SysReAllocString(Header, bstrHeader))
 		hr = E_OUTOFMEMORY;

	return hr;
}

/***************************************************
GetMsgHeaderFieldName
	Gets message header field name
Params
	Type	- type of the header
	Name	- pointer to result variable
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetMsgHeaderFieldName(MsgHeaderFields Type, BSTR *Name)
{
	if(Name == NULL)	return E_POINTER;

	_bstr_t	bstrName = "";

    if(m_CurMessage != NULL) {
        if(Type == UTM_CUSTOM_FIELD) {
            LPCSTR  lpszHeaderName;
            int     i = 0;
            while( (lpszHeaderName = m_CurMessage->GetCustomFieldName(i++)) != NULL) {
                bstrName += lpszHeaderName;
                bstrName += "\r\n";
                }
            }
        else {
		    bstrName = m_CurMessage->GetFieldName((HeaderFieldID)Type);
            }
        }

 	if(!SysReAllocString(Name, bstrName))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
DecodeMsgAttach
	Decodes message attachment into the file
Params
	AttachIndex	- attachment index
	DestFileName- destination file name	to save to
	Result		- pointer to the result code varaible
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::DecodeMsgAttach(long AttachIndex, BSTR DestFileName, long *Result)
{
	if(Result == NULL)	return E_POINTER;

	*Result = UTE_NO_CURRENT_MSG_SET;
	if(m_CurMessage != NULL) 
		*Result = (long)m_CurMessage->Decode(AttachIndex, _bstr_t(DestFileName));

	return S_OK;
}

/***************************************************
GetMsgSequenceNumber
	Gets current message sequence number
Params
    Result	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetMsgSequenceNumber(long *Result)
{
	if(Result == NULL)	return E_POINTER;
    if(m_CurMessageData != NULL)
	    *Result = m_CurMessageData->m_lMsgNumber;
    else
        *Result = -1;
	return S_OK;
}

/***************************************************
GetMsgSize
	Gets current message size
Params
    Result	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetMsgSize(long *Result)
{
	if(Result == NULL)	return E_POINTER;
    if(m_CurMessageData != NULL)
	    *Result = m_CurMessageData->m_lSize;
    else
        *Result = -1;
	return S_OK;
}

/***************************************************
GetMsgFlags
	Gets current message flags
Params
    Result	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetMsgFlags(BSTR *Result)
{
	if(Result == NULL)	return E_POINTER;

    _bstr_t bstrFlags;

    if(m_CurMessageData != NULL)
	    bstrFlags = m_CurMessageData->m_szUnknownFlags;

   	if(!SysReAllocString(Result, bstrFlags))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
GetMsgSystemFlags
	Gets current message system flags
Params
    Result	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetMsgSystemFlags(long *Result)
{
	if(Result == NULL)	return E_POINTER;
    if(m_CurMessageData != NULL)
	    *Result = m_CurMessageData->m_lFlags;
    else
        *Result = -1;
	return S_OK;
}

/***************************************************
GetMsgDate
	Gets current message date and time string
Params
    Result	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetMsgDate(BSTR *Result)
{
	if(Result == NULL)	return E_POINTER;

    _bstr_t bstrFlags;

    if(m_CurMessageData != NULL)
	    bstrFlags = m_CurMessageData->m_szDateTime;

   	if(!SysReAllocString(Result, bstrFlags))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
GetMsgUID
	Gets current message UID
Params
    Result	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetMsgUID(long *Result)
{
	if(Result == NULL)	return E_POINTER;
    if(m_CurMessageData != NULL)
	    *Result = m_CurMessageData->m_lUID;
    else
        *Result = -1;
	return S_OK;
}

/***************************************************
SMTPConnect
	Connects to the IMAP4 server
Params
	LocalName	- local host name or IP address
	Result		- pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CIMAP4::Connect(long *Result)
{
	AddMethod(METHOD_CONNECT, Result, _VP(m_bstrHostName), _VP(m_bstrUserName), _VP(m_bstrUserPassword), NULL);
	return S_OK;
}

/***************************************************
SMTPClose
	Close connection to the IMAP4 server
Params
	Result		- pointer to the result varaible
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CIMAP4::Close(long *Result)
{
	AddMethod(METHOD_CLOSE, Result, NULL);
	return S_OK;
}

/***************************************************
Noop
	Execute NOOP commnad.
Params
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::Noop(long *Result)
{
    AddMethod(METHOD_NOOP, Result, NULL);
	return S_OK;
}

/***************************************************
MailBoxSelect
	Selects the mail box.
Params
    MailBoxName - mail box to select
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MailBoxSelect(BSTR MailBoxName, long *Result)
{
    AddMethod(METHOD_MAIL_BOX_SELECT, Result, _VP(MailBoxName), NULL);
	return S_OK;
}

/***************************************************
MailBoxExamine
	Examines the mail box.
Params
    MailBoxName - mail box to examine
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MailBoxExamine(BSTR MailBoxName, long *Result)
{
    AddMethod(METHOD_MAIL_BOX_EXAMINE, Result, _VP(MailBoxName), NULL);
	return S_OK;
}

/***************************************************
MailBoxCreate
	Creates the mail box.
Params
    MailBoxName - mail box to create
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MailBoxCreate(BSTR MailBoxName, long *Result)
{
    AddMethod(METHOD_MAIL_BOX_CREATE, Result, _VP(MailBoxName), NULL);
	return S_OK;
}

/***************************************************
MailBoxDelete
	Deletes the mail box.
Params
    MailBoxName - mail box to delete
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MailBoxDelete(BSTR MailBoxName, long *Result)
{
    AddMethod(METHOD_MAIL_BOX_DELETE, Result, _VP(MailBoxName), NULL);
	return S_OK;
}

/***************************************************
MailBoxSubscribe
	Subscribe the mail box.
Params
    MailBoxName - mail box to subscribe
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MailBoxSubscribe(BSTR MailBoxName, long *Result)
{
    AddMethod(METHOD_MAIL_BOX_SUBSCRIBE, Result, _VP(MailBoxName), NULL);
	return S_OK;
}

/***************************************************
MailBoxUnSubscribe
	UnSubscribe the mail box.
Params
    MailBoxName - mail box to unsubscribe
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MailBoxUnSubscribe(BSTR MailBoxName, long *Result)
{
    AddMethod(METHOD_MAIL_BOX_UNSUBSCRIBE, Result, _VP(MailBoxName), NULL);
	return S_OK;
}

/***************************************************
MailBoxRename
	Renames the mail box.
Params
    MailBoxName     - mail box to rename
    MailBoxNewName  - new mail box name
    Result		    - pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MailBoxRename(BSTR MailBoxName, BSTR MailBoxNewName, long *Result)
{
    AddMethod(METHOD_MAIL_BOX_RENAME, Result, _VP(MailBoxName), _VP(MailBoxNewName), NULL);
	return S_OK;
}

/***************************************************
MailBoxList
	List the mail box items.
Params
    Reference   - reference name
    MailBoxName - mail box name
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MailBoxList(BSTR Reference, BSTR MailBoxName, long *Result)
{
	AddMethod(METHOD_MAIL_BOX_LIST, Result, _VP(Reference), _VP(MailBoxName), NULL);
	return S_OK;
}

/***************************************************
MailBoxLSub
	List the mail box subscribed items.
Params
    Reference   - reference name
    MailBoxName - mail box name
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MailBoxLSub(BSTR Reference, BSTR MailBoxName, long *Result)
{
	AddMethod(METHOD_MAIL_BOX_LSUB, Result, _VP(Reference), _VP(MailBoxName), NULL);
	return S_OK;
}

/***************************************************
GetMailBoxListSize
	Gets size of the result mail box list
Params
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::GetMailBoxListSize(long *Result)
{
    *Result = CUT_IMAP4Client::GetMailBoxListSize();
	return S_OK;
}

/***************************************************
GetMailBoxListName
	Gets the mail box list item name
Params
    Index       - item index
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::GetMailBoxListName(long Index, BSTR *Name)
{
    _bstr_t     bstrStr;
    LPCSTR      ptrName, ptrDelimiter;
    int         nAttrib;

    if(CUT_IMAP4Client::GetMailBoxListItem(Index, ptrName, ptrDelimiter, nAttrib) == CUT_SUCCESS)
        bstrStr = ptrName;

    if(!SysReAllocString(Name, bstrStr))
		return E_OUTOFMEMORY;

    return S_OK;
}

/***************************************************
GetMailBoxListDelimiter
	Gets the mail box list item delimiter
Params
    Index       - item index
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::GetMailBoxListDelimiter(long Index, BSTR *Delimiter)
{
    _bstr_t     bstrStr;
    LPCSTR      ptrName, ptrDelimiter;
    int         nAttrib;

    if(CUT_IMAP4Client::GetMailBoxListItem(Index, ptrName, ptrDelimiter, nAttrib) == CUT_SUCCESS)
        bstrStr = ptrDelimiter;

    if(!SysReAllocString(Delimiter, bstrStr))
		return E_OUTOFMEMORY;

    return S_OK;
}

/***************************************************
GetMailBoxListAttrib
	Gets the mail box list item attribute
Params
    Index       - item index
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::GetMailBoxListAttrib(long Index, long *Attrib)
{
    *Attrib     = 0;

    LPCSTR      ptrName, ptrDelimiter;
    int         nAttrib;

    if(CUT_IMAP4Client::GetMailBoxListItem(Index, ptrName, ptrDelimiter, nAttrib) == CUT_SUCCESS)
        *Attrib = (long) nAttrib;

    return S_OK;
}

/***************************************************
MailBoxAppend
	Append to the mail box.
Params
    MailBoxName - mail box to append to
    FileName    - message file name
    Flags       - flags sting
    DateTime    - message date and time string
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MailBoxAppend(BSTR MailBoxName, BSTR FileName, BSTR Flags, BSTR DateTime, long *Result)
{
    AddMethod(METHOD_MAIL_BOX_APPEND, Result, _VP(MailBoxName), _VP(FileName), _VP(Flags), _VP(DateTime), NULL);
	return S_OK;
}

/***************************************************
MailBoxCheck
	Checks the mail box.
Params
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MailBoxCheck(long *Result)
{
	AddMethod(METHOD_MAIL_BOX_CHECK, Result, NULL);
	return S_OK;
}

/***************************************************
MailBoxClose
	Closes the mail box.
Params
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MailBoxClose(long *Result)
{
	AddMethod(METHOD_MAIL_BOX_CLOSE, Result, NULL);
	return S_OK;
}

/***************************************************
MessageExpunge
	Expunge the message with \Deleted flag
Params
    Result		- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MessageExpunge(long *Result)
{
    AddMethod(METHOD_MESSAGE_EXPUNGE, Result, NULL);
	return S_OK;
}

/***************************************************
MessageSearch
	Search for messages
Params
    SearchString    - search string
    UseUID          - use UID except of sequence numbers
    Result	    	- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MessageSearch(BSTR SearchString, VARIANT_BOOL UseUID, long *Result)
{
    AddMethod(METHOD_MESSAGE_SEARCH, Result, _VP(SearchString), _VP(UseUID), NULL);
	return S_OK;
}

/***************************************************
GetSearchResultSize
	Returns Search result size
Params
    Result  - pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::GetSearchResultSize(long *Result)
{
    *Result = CUT_IMAP4Client::GetSearchResultSize();
	return S_OK;
}

/***************************************************
GetSearchResultItem
	Returns Search result item
Params
    Index   - item index 
    Result  - pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::GetSearchResultItem(long Index, long *MessageID)
{
    CUT_IMAP4Client::GetSearchResultItem(Index, *MessageID);
	return S_OK;
}

/***************************************************
MessageCopy
	Copy the messages
Params
    MessageSet      - messages set to copy
    DestMailBoxName - destination mail box
    UseUID          - use UID except of sequence numbers
    Result	    	- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MessageCopy(BSTR MessageSet, BSTR DestMailBoxName, VARIANT_BOOL UseUID, long *Result)
{
    AddMethod(METHOD_MESSAGE_COPY, Result, _VP(MessageSet), _VP(DestMailBoxName), _VP(UseUID), NULL);
	return S_OK;
}

/***************************************************
MessageFetch
	Fetch then messages
Params
    MessageSet      - messages set to copy
    Item            - item to fetch
    SetSeenFlag     - TRUE if the server should set \Seen flag after fetch
    UseUID          - use UID except of sequence numbers
    Result	    	- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MessageFetch(BSTR MessageSet, IMAP4FetchItem Item, VARIANT_BOOL SetSeenFlag, VARIANT_BOOL UseUID, long *Result)
{
    AddMethod(METHOD_MESSAGE_FETCH, Result, _VP(MessageSet), _VP((long)Item), _VP(SetSeenFlag), _VP(UseUID), NULL);
	return S_OK;
}

/***************************************************
GetMessageListSize
	Gets message result list size
Params
    Size    - pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::GetMessageListSize(long *Size)
{
    *Size = CUT_IMAP4Client::GetMsgDataListSize();
	return S_OK;
}

/***************************************************
SetCurrentMessage
	Selects current message from the result list
Params
    Index   - index of the message
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::SetCurrentMessage(long Index, long *Result)
{
	*Result = CUT_IMAP4Client::GetMsgDataListItem(Index, m_CurMessageData);

    if(m_CurMessage != NULL)
        delete m_CurMessage; 

    if(m_CurMessageData != NULL && m_CurMessageData->m_ptrData != NULL) {
        m_CurMessage = new CUT_Msg();
        m_CurMessage->LoadMessage(*m_CurMessageData->m_ptrData);
        }

	return S_OK;
}

/***************************************************
MessageStore
	Stores messages flags
Params
    MessageSet      - messages set to copy
    Type            - method of storing
    Flags           - flags to store
    UseUID          - use UID except of sequence numbers
    Result	    	- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MessageStore(BSTR MessageSet, IMAP4StoreType Type, BSTR Flags, VARIANT_BOOL UseUID, long *Result)
{
	AddMethod(METHOD_MESSAGE_STORE, Result, _VP(MessageSet), _VP((long)Type), _VP(Flags), _VP(UseUID), NULL);
	return S_OK;
}

/***************************************************
FlagsToString
	Converts flags to string format
Params
    Flags           - flags to convert
    Result	    	- pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::FlagsToString(long Flags, BSTR *Result)
{
    char        buffer[MAX_LINE_BUFFER+1];

    CUT_IMAP4Client::FlagsToString((int)Flags, buffer, MAX_LINE_BUFFER);

    if(!SysReAllocString(Result, _bstr_t(buffer)))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
MailBoxStatus
	Gets mail box status IMAP4ver1 only
Params
    MailBoxName - mail box name
    StatusName  - status name to get
    Result	    - pointer to the result varaible
Return
	S_OK
****************************************************/
STDMETHODIMP CIMAP4::MailBoxStatus(BSTR MailBoxName, BSTR StatusName, long *Result)
{
	AddMethod(METHOD_MAIL_BOX_STATUS, Result, _VP(MailBoxName), _VP(StatusName), NULL);
	return S_OK;
}

/***************************************************
GetStatusResultName
	Gets name from the last status result 
Params
    Name    - pointer to the result varaible
Return
	S_OK            - success
    E_OUTOFMEMORY   - out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetStatusResultName(BSTR *Name)
{
    _bstr_t     bstrName;

    if(m_CurStatusData != NULL)
        bstrName = m_CurStatusData->m_strName.c_str();

    if(!SysReAllocString(Name, bstrName))
	    return E_OUTOFMEMORY;
	    
	return S_OK;
}

/***************************************************
GetStatusResultMsgNumber
	Gets number of messages from the last status result 
Params
    Number    - pointer to the result varaible
Return
	S_OK            - success
    E_OUTOFMEMORY   - out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetStatusResultMsgNumber(long *Number)
{
    *Number = 0;
    if(m_CurStatusData != NULL)
        *Number = m_CurStatusData->m_lMsgNumber;
	return S_OK;
}

/***************************************************
GetStatusResultMsgRecent
	Gets number of recent messages from the last status result 
Params
    RecentNumber    - pointer to the result varaible
Return
	S_OK            - success
    E_OUTOFMEMORY   - out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetStatusResultMsgRecent(long *RecentNumber)
{
    *RecentNumber = 0;
    if(m_CurStatusData != NULL)
        *RecentNumber = m_CurStatusData->m_lMsgRecent;
	return S_OK;
}

/***************************************************
GetStatusResultMsgUnseen
	Gets number of unseen messages from the last status result 
Params
    UnseenNumber    - pointer to the result varaible
Return
	S_OK            - success
    E_OUTOFMEMORY   - out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetStatusResultMsgUnseen(long *UnseenNumber)
{
    *UnseenNumber = 0;
    if(m_CurStatusData != NULL)
        *UnseenNumber = m_CurStatusData->m_lMsgUnseen;
	return S_OK;
}

/***************************************************
GetStatusResultNextUID
	Gets Next UID from the last status result 
Params
    UID    - pointer to the result varaible
Return
	S_OK            - success
    E_OUTOFMEMORY   - out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetStatusResultNextUID(long *UID)
{
    *UID = 0;
    if(m_CurStatusData != NULL)
        *UID = m_CurStatusData->m_lNextUID;
	return S_OK;
}

/***************************************************
GetStatusResultUIVV
	Gets UIVV from the last status result 
Params
    UIVV    - pointer to the result varaible
Return
	S_OK            - success
    E_OUTOFMEMORY   - out of memory
****************************************************/
STDMETHODIMP CIMAP4::GetStatusResultUIVV(long *UIVV)
{
    *UIVV = 0;
    if(m_CurStatusData != NULL)
        *UIVV = m_CurStatusData->m_lUIVV;
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
STDMETHODIMP CIMAP4::GetInterfaceSafetyOptions(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
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
STDMETHODIMP CIMAP4::SetInterfaceSafetyOptions(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
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
BOOL CIMAP4::WaitWithMsgLoop(HANDLE hEvent, long lTimeout)
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

/********************************
OnAlertMessage
	This virtual function called each time we 
	receive an alert message.

PARAM:
	lpszAlertMsg	- alert message
RETURN:
	none
*********************************/
void CIMAP4::OnAlertMessage(LPCSTR lpszAlertMsg) 
{
    if(!m_bGoingToClose)
        Fire_OnAlert(_bstr_t(lpszAlertMsg));
}

/********************************
OnExpunge
	Virtual function OnExpunge will be called with deleted message 
	number as a parameter for each EXPUNGE response.

	The EXPUNGE response reports that the specified message sequence
	number has been permanently removed from the mailbox.  The message
	sequence number for each successive message in the mailbox is
	immediately decremented by 1, and this decrement is reflected in
	message sequence numbers in subsequent responses (including other
	untagged EXPUNGE responses).

	As a result of the immediate decrement rule, message sequence
	numbers that appear in a set of successive EXPUNGE responses
	depend upon whether the messages are removed starting from lower
	numbers to higher numbers, or from higher numbers to lower
	numbers.  For example, if the last 5 messages in a 9-message
	mailbox are expunged; a "lower to higher" server will send five
	untagged EXPUNGE responses for message sequence number 5, whereas
	a "higher to lower server" will send successive untagged EXPUNGE
	responses for message sequence numbers 9, 8, 7, 6, and 5.
PARAM:
	nMsgNumber	- message number
RETURN:
	none
*********************************/
void CIMAP4::OnExpunge(long nMsgNumber) 
{
    if(!m_bGoingToClose)
        Fire_OnExpunge(nMsgNumber);
}

/********************************
OnFetch
	Virtual function OnFetch() called each time 
	we receive a FETCH response from the server.
PARAM:
	data	- message data
RETURN:
	TRUE	- if there is no further processing required
*********************************/
void CIMAP4::OnFetch()
{
    if(!m_bGoingToClose) 
        Fire_OnFetch();
}

/********************************
OnExists
	Virtual function called each time we receive 
	an EXISTS response
PARAM:
	nMsgNumber	- number of messages in the mail box
RETURN:
	none
*********************************/
void CIMAP4::OnExists(long nMsgNumber) 
{
    if(!m_bGoingToClose)
        Fire_OnExists(nMsgNumber);
}

/********************************
OnRecent
	Virtual function called each time we receive 
	an RECENT response
PARAM:
	nMsgNumber	- number of messages in the mail box with \Recent flag
RETURN:
	none
*********************************/
void CIMAP4::OnRecent(long nMsgNumber) 
{
    if(!m_bGoingToClose)
        Fire_OnRecent(nMsgNumber);
}

/********************************
NewMailThreadStarted
	Virtual function called when the new mail
    thread is started
PARAM:
	none
RETURN:
	FALSE   - if the thread should terminate
*********************************/
BOOL CIMAP4::NewMailThreadStarted() {
    // We need to call CoInitialize on the new mail checking thread 
    // so we can later fire events from that thread
    CoInitialize(NULL);
    return TRUE;
}

/********************************
NewMailThreadTerminated
	Virtual function called when the new mail
    thread is terminated
PARAM:
	none
RETURN:
	none
*********************************/
void CIMAP4::NewMailThreadTerminated() {
    CoUninitialize();
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
long CIMAP4::ExecuteMethod(MethodTypeTag MethodID, _variant_t *ptrVarParams, BOOL bForceNonBlocking)
{
	LONG	lRetCode;

    // If we are not going to destroy the object - clear the abort flag
	if(!m_bGoingToClose)
	    m_bAbortFlag	= FALSE;

    switch(MethodID) {
		case(METHOD_CONNECT):
            lRetCode = CUT_IMAP4Client::IMAP4Connect(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]), _bstr_t(ptrVarParams[2]));
			if(!m_bGoingToClose) {
				Fire_OnConnect(lRetCode);
				}
			break;
		case(METHOD_CLOSE):
            lRetCode = CUT_IMAP4Client::IMAP4Close();
			if(!m_bGoingToClose) {
				Fire_OnClose(lRetCode);
				}
			break;
		case(METHOD_NOOP):
            lRetCode = CUT_IMAP4Client::Noop();
			if(!m_bGoingToClose) {
				Fire_OnNoop(lRetCode);
				}
			break;
		case(METHOD_MAIL_BOX_SELECT):
            lRetCode = CUT_IMAP4Client::MailBoxSelect(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				Fire_OnMailBoxSelect(lRetCode);
				}
			break;
		case(METHOD_MAIL_BOX_EXAMINE):
            lRetCode = CUT_IMAP4Client::MailBoxExamine(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				Fire_OnMailBoxExamine(lRetCode);
				}
			break;
		case(METHOD_MAIL_BOX_CREATE):
            lRetCode = CUT_IMAP4Client::MailBoxCreate(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				Fire_OnMailBoxCreate(lRetCode);
				}
			break;
		case(METHOD_MAIL_BOX_DELETE):
            lRetCode = CUT_IMAP4Client::MailBoxDelete(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				Fire_OnMailBoxDelete(lRetCode);
				}
			break;
		case(METHOD_MAIL_BOX_SUBSCRIBE):
            lRetCode = CUT_IMAP4Client::MailBoxSubscribe(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				Fire_OnMailBoxSubscribe(lRetCode);
				}
			break;
		case(METHOD_MAIL_BOX_UNSUBSCRIBE):
            lRetCode = CUT_IMAP4Client::MailBoxUnSubscribe(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				Fire_OnMailBoxUnsubscribe(lRetCode);
				}
			break;
		case(METHOD_MAIL_BOX_RENAME):
            lRetCode = CUT_IMAP4Client::MailBoxRename(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]));
			if(!m_bGoingToClose) {
				Fire_OnMailBoxRename(lRetCode);
				}
			break;
		case(METHOD_MAIL_BOX_LIST):
            lRetCode = CUT_IMAP4Client::MailBoxList(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]));
			if(!m_bGoingToClose) {
				Fire_OnMailBoxList(lRetCode);
				}
			break;
		case(METHOD_MAIL_BOX_LSUB):
            lRetCode = CUT_IMAP4Client::MailBoxLSub(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]));
			if(!m_bGoingToClose) {
				Fire_OnMailBoxLSub(lRetCode);
				}
			break;
		case(METHOD_MAIL_BOX_APPEND):
            lRetCode = CUT_IMAP4Client::MailBoxAppend(_bstr_t(ptrVarParams[0]), CUT_FileDataSource(_bstr_t(ptrVarParams[1])), _bstr_t(ptrVarParams[2]), _bstr_t(ptrVarParams[3]));
			if(!m_bGoingToClose) {
				Fire_OnMailBoxAppend(lRetCode);
				}
			break;
		case(METHOD_MAIL_BOX_CHECK):
            lRetCode = CUT_IMAP4Client::MailBoxCheck();
			if(!m_bGoingToClose) {
				Fire_OnMailBoxCheck(lRetCode);
				}
			break;
		case(METHOD_MAIL_BOX_CLOSE):
            lRetCode = CUT_IMAP4Client::MailBoxClose();
			if(!m_bGoingToClose) {
				Fire_OnMailBoxClose(lRetCode);
				}
			break;
		case(METHOD_MAIL_BOX_STATUS):
            if(m_CurStatusData == NULL)
                m_CurStatusData = new UT_StatusData();

            lRetCode = CUT_IMAP4Client::MailBoxStatus(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]), *m_CurStatusData);
			if(!m_bGoingToClose) {
				Fire_OnMailBoxStatus(lRetCode);
				}
			break;
		case(METHOD_MESSAGE_EXPUNGE):
            lRetCode = CUT_IMAP4Client::MessageExpunge();
			if(!m_bGoingToClose) {
				Fire_OnMessageExpunge(lRetCode);
				}
			break;
		case(METHOD_MESSAGE_SEARCH):
            lRetCode = CUT_IMAP4Client::MessageSearch(_bstr_t(ptrVarParams[0]), NULL, (VARIANT_BOOL)ptrVarParams[1]);
			if(!m_bGoingToClose) {
				Fire_OnMessageSearch(lRetCode);
				}
			break;
		case(METHOD_MESSAGE_COPY):
            lRetCode = CUT_IMAP4Client::MessageCopy(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]), (VARIANT_BOOL)ptrVarParams[2]);
			if(!m_bGoingToClose) {
				Fire_OnMessageCopy(lRetCode);
				}
			break;
		case(METHOD_MESSAGE_FETCH):
            lRetCode = CUT_IMAP4Client::MessageFetch(_bstr_t(ptrVarParams[0]), (FetchItem)(long)ptrVarParams[1], (VARIANT_BOOL)ptrVarParams[2], (VARIANT_BOOL)ptrVarParams[3]);
			if(!m_bGoingToClose) {
				Fire_OnMessageFetch(lRetCode);
				}
			break;
        case(METHOD_MESSAGE_STORE): 
            {
            char    *szStoreType[] = {  "FLAGS",
                                "FLAGS.SILENT",
                                "+FLAGS",
                                "+FLAGS.SILENT",
                                "-FLAGS",
                                "-FLAGS.SILENT"};

            lRetCode = CUT_IMAP4Client::MessageStore(_bstr_t(ptrVarParams[0]), szStoreType[(long)ptrVarParams[1]], _bstr_t(ptrVarParams[2]), (VARIANT_BOOL)ptrVarParams[3]);
			if(!m_bGoingToClose) {
				Fire_OnMessageStore(lRetCode);
				}
			break;
            }
    
		// Unknown method error
		default:
			return UTE_ERROR;
		}

	return lRetCode;
}

#pragma warning (pop)