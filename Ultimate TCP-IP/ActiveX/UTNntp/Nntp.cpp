//=================================================================
//  class: CNntp
//  File:  Nntp.cpp
//
//  Implementation of CNntp class
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
#include "UTNntp.h"
#include "Nntp.h"

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
// CNntp
/////////////////////////////////////////////////////////////////////////////
/***************************************************
CNntp
	Standart constructor. 
Params
    none
Return
	none
****************************************************/
CNntp::CNntp() : CUT_MethodQueue<CNntp, MethodTypeTag>(this),
		m_bBlockingMode(FALSE),			// Set non blocking mode as default
		m_lnConnectTimeOut(5),			// Set default connection time-out to 5 secs
		m_lnReceiveTimeOut(5),			// Set default receive time-out to 5 secs
		m_bGoingToClose(FALSE),			// Initialize closing flag with FALSE
		m_bAbortFlag(FALSE),			// Clear abort flag
		m_lnCurArticleInfoIndex(0),		// Initialize current article info index
		m_bstrHostName(L""),			// Initialize Host name property variable
		m_bstrUserName(L""),			// Initialize User name property variable
		m_bstrUserPassword(L""),		// Initialize Password name property variable
        m_bstrServerDate(L"")           // Initialize Server Date property variable
{
	// Load Nntp Icon
	m_hNntpIcon = LoadIcon(_Module.m_hInst, MAKEINTRESOURCE(IDI_ICON_NNTP));	

	// Initiate default control size 32 x 32 pixels
    SIZE	sz = { 32, 32 };
    AtlPixelToHiMetric (&sz, &m_sizeExtent);		// convert pixels to himetric
    m_sizeNatural	= m_sizeExtent;					// store natural extent

	// Disable resizing of the control
	m_bAutoSize		= TRUE;				
  
}

/***************************************************
~CNntp
	Destructor.
Params
    none
Return
	none
****************************************************/
CNntp::~CNntp()
{
	// Set flags to terminate all running threads
	m_bGoingToClose	= TRUE;
	m_bAbortFlag	= TRUE;

	// If thread is running - will wait till it exits
	// or will time-out. 
	if(m_hMethodThread != NULL) {
		// Resume working thread
		ResumeThread(m_hMethodThread);

		WaitWithMsgLoop(m_hMethodThread, max((m_lnConnectTimeOut + m_lnReceiveTimeOut) * 1000, 120000));
		}

	// Destroy Nntp icon handle
	if(m_hNntpIcon) {
		DestroyIcon( m_hNntpIcon );							
		m_hNntpIcon = NULL;
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
STDMETHODIMP CNntp::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = {	&IID_INntp,	};
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
HRESULT CNntp::OnDraw(ATL_DRAWINFO& di)
{
	// Fill background & draw a boreder
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	// Draw Nntp Icon
	if(m_hNntpIcon)
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hNntpIcon);	
 		
	return S_OK;
}


////////////////////////////////////////////////////
//	INntp interface properties Set/Get functions
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
STDMETHODIMP CNntp::get_ConnectTimeOut(long *pVal)
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
STDMETHODIMP CNntp::put_ConnectTimeOut(long newVal)
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
		return AtlReportError(CLSID_Nntp,"Invalid Connect Time Out value", IID_INntp, E_FAIL);


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
STDMETHODIMP CNntp::get_ReceiveTimeOut(long *pVal)
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
STDMETHODIMP CNntp::put_ReceiveTimeOut(long newVal)
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
		return AtlReportError(CLSID_Nntp,"Invalid Receive Time Out value", IID_INntp,E_FAIL);

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
STDMETHODIMP CNntp::get_BlockingMode(VARIANT_BOOL *pVal)
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
STDMETHODIMP CNntp::put_BlockingMode(VARIANT_BOOL newVal)
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
get_HostName
	Returns host name
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CNntp::get_HostName(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, m_bstrHostName))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
put_HostName
	Set host name
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
****************************************************/
STDMETHODIMP CNntp::put_HostName(BSTR newVal)
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
STDMETHODIMP CNntp::get_UserName(BSTR *pVal)
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
STDMETHODIMP CNntp::put_UserName(BSTR newVal)
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
STDMETHODIMP CNntp::get_UserPassword(BSTR *pVal)
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
STDMETHODIMP CNntp::put_UserPassword(BSTR newVal)
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
get_NewsGroupCount
	Gets news groups count
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CNntp::get_NewsGroupCount(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = CUT_NNTPClient::NGetNewsGroupCount();
	return S_OK;
}

/***************************************************
get_NewArticleCount
	Gets new article headers count
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CNntp::get_NewArticleCount(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = CUT_NNTPClient::NGetNewArticlesCount();
	return S_OK;
}

/***************************************************
get_ArticleHeaderCount
	Gets article headers count
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CNntp::get_ArticleHeaderCount(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = CUT_NNTPClient::NGetArticleHeaderCount();
	return S_OK;
}

/***************************************************
get_ServerDate
	Returns server date. Call GetServerDate method prior
    to this call
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CNntp::get_ServerDate(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, m_bstrServerDate))
		return E_OUTOFMEMORY;

	return S_OK;
}


////////////////////////////////////////////////////
//	Current Article information get methods
////////////////////////////////////////////////////

/***************************************************
get_ArticleInfo_ID
	Gets current article ID
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CNntp::get_ArticleInfo_ID(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_CurArticleInfo.nArticleId;
	return S_OK;
}

/***************************************************
get_ArticleInfo_Subject
	Gets current article subject
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CNntp::get_ArticleInfo_Subject(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, _bstr_t(m_CurArticleInfo.lpszSubject)))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_ArticleInfo_Author
	Gets current article author
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CNntp::get_ArticleInfo_Author(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, _bstr_t(m_CurArticleInfo.lpszAuthor)))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_ArticleInfo_Date
	Gets current article date
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CNntp::get_ArticleInfo_Date(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, _bstr_t(m_CurArticleInfo.lpszDate)))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_ArticleInfo_MsgID
	Gets current article message ID
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CNntp::get_ArticleInfo_MsgID(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, _bstr_t(m_CurArticleInfo.lpszMessageId)))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_ArticleInfo_Refer
	Gets current article reference
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CNntp::get_ArticleInfo_Refer(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, _bstr_t(m_CurArticleInfo.lpszReferences)))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_ArticleInfo_ByteCount
	Gets current article bytes count
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CNntp::get_ArticleInfo_ByteCount(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_CurArticleInfo.nByteCount;
	return S_OK;
}

/***************************************************
get_ArticleInfo_LineCount
	Gets current article line count
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CNntp::get_ArticleInfo_LineCount(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_CurArticleInfo.nLineCount;
	return S_OK;
}

/***************************************************
get_ArticleInfo_Status
	Gets current article status
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CNntp::get_ArticleInfo_Status(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_CurArticleInfo.nStatus;
	return S_OK;
}

////////////////////////////////////////////////////
//	INntp interface methods
////////////////////////////////////////////////////

/***************************************************
CancelNntp
	Cancel current Nntp operation
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CNntp::CancelNntp()
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
STDMETHODIMP CNntp::AboutBox()
{
	CAboutDlg	dlg;

	dlg.DoModal();
	return S_OK;
}

/***************************************************
ResetArticleInfoEnum
	Resets article information enumeration
Params
	none
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CNntp::ResetArticleInfoEnum()
{
	m_lnCurArticleInfoIndex = 0;
	return S_OK;
}

/***************************************************
EnumArticleInfo
	Enumerate article information
Params
	Result	- pointer to the result varaible
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CNntp::EnumArticleInfo(long *Result)
{
	if(Result == NULL)	return E_POINTER;
	*Result = ecError;

	if(m_lnCurArticleInfoIndex < CUT_NNTPClient::NGetArticleHeaderCount()) {
		UT_ARTICLEINFO		*ptrInfo;
		
		if((ptrInfo=NGetArticleInfo(m_lnCurArticleInfoIndex)) != NULL) {
			m_CurArticleInfo = *ptrInfo;
			++m_lnCurArticleInfoIndex;
			*Result = ecSuccess;
			}
		}

	return S_OK;
}

/***************************************************
SaveNewsGroupList
	Saves news group list from the file
Params
	FileName	- file name to save to
	Result		- pointer to the result varaible
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CNntp::SaveNewsGroupList(BSTR FileName, long *Result)
{
	if(Result == NULL)	return E_POINTER;
	*Result = CUT_NNTPClient::NSaveNewsGroupList(_bstr_t(FileName));
	return S_OK;
}

/***************************************************
LoadNewsGroupList
	Loads news group list from the file
Params
	FileName	- file name to load from
	Result		- pointer to the result varaible
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CNntp::LoadNewsGroupList(BSTR FileName, long *Result)
{
	if(Result == NULL)	return E_POINTER;
	*Result = CUT_NNTPClient::NLoadNewsGroupList(_bstr_t(FileName));
	return S_OK;
}

/***************************************************
SaveArticleHeaderList
	Saves article headers list from the file
Params
	FileName	- file name to save to
	Result		- pointer to the result varaible
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CNntp::SaveArticleHeaderList(BSTR FileName, long *Result)
{
	if(Result == NULL)	return E_POINTER;
	*Result = CUT_NNTPClient::NSaveArticleHeaderList(_bstr_t(FileName));
	return S_OK;
}

/***************************************************
LoadArticleHeaderList
	Loads article headers list from the file
Params
	FileName	- file name to load from
	Result		- pointer to the result varaible
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CNntp::LoadArticleHeaderList(BSTR FileName, long *Result)
{
	if(Result == NULL)	return E_POINTER;
	*Result = CUT_NNTPClient::NLoadArticleHeaderList(_bstr_t(FileName));
	return S_OK;
}

/***************************************************
GetNewsGroupTitle
	Gets news group title
Params
	Index	- index of the news group
	Result	- pointer to the result varaible
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CNntp::GetNewsGroupTitle(long Index, BSTR *Result)
{
	if(Result == NULL)	return E_POINTER;

	_bstr_t	bstrTitle = CUT_NNTPClient::NGetNewsGroupTitle(Index);
	
	if(!SysReAllocString(Result, bstrTitle))
		return E_OUTOFMEMORY;

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
STDMETHODIMP CNntp::GetErrorText(long ErrorCode, BSTR *ErrorText)
{
 	HRESULT		hResult			= S_OK;
 	CComBSTR	bstrErrorMsg	= CUT_ERR::GetErrorString(ErrorCode);
 
 	if(!SysReAllocString(ErrorText, bstrErrorMsg))
 		hResult = E_OUTOFMEMORY;
 
 	return hResult;
}

/***************************************************
Connect
	Connect to an NNTP server with a user name and passord
Params
	Result	- pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CNntp::Connect(long *Result)
{
	AddMethod(METHOD_CONNECT, Result, _VP(m_bstrHostName), _VP(m_bstrUserName), _VP(m_bstrUserPassword), NULL);
	return S_OK;
}

/***************************************************
Close
	close the connection to an NNTP server
Params
	Result	- pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CNntp::Close(long *Result)
{
	AddMethod(METHOD_CLOSE, Result, NULL);
	return S_OK;
}

/***************************************************
CheckCanPost
	Check to see if posting is allowed on the 
    selected server. 
Params
	Result	- pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CNntp::CheckCanPost(long *Result)
{
	AddMethod(METHOD_CHECK_CAN_POST, Result, NULL);
	return S_OK;
}

/***************************************************
GetServerDate
	Gets the NNTP server's date
Params
	Result	- pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CNntp::GetServerDate(long *Result)
{
    m_bstrServerDate = L"";
	AddMethod(METHOD_GET_SERVER_DATE, Result, NULL);
	return S_OK;
}

/***************************************************
SelectNewsGroup
	Select a news group from the available Groups on 
	the Server by sending a GROUP command.
Params
	Result	- pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CNntp::SelectNewsGroup(BSTR NewsGroup, long *Result)
{
	AddMethod(METHOD_SELECT_NEWS_GROUP, Result, _VP(NewsGroup), NULL);
	return S_OK;
}

/***************************************************
GetArticle
	Prompt the server to send the article Identified 
	by the message ID
Params
	Result	- pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CNntp::GetArticle(BSTR ArticleID, BSTR FileName, long *Result)
{
	AddMethod(METHOD_GET_ARTICLE, Result, _VP(ArticleID), _VP(FileName), NULL);
	return S_OK;
}

/***************************************************
PostArticle
	Post a message as an article to an NNTP News Group
Params
	Result	- pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CNntp::PostArticle(BSTR NewsGroup, BSTR From, BSTR Subject, BSTR Article, long *Result)
{
	AddMethod(METHOD_POST_ARTICLE, Result, _VP(NewsGroup), _VP(From), _VP(Subject), _VP(Article), NULL);
	return S_OK;
}

/***************************************************
PostArticleFromFile
	Post a message as an article to an NNTP News Group
    from the file
Params
    FileName    - file name with RFC822 message
	Result	    - pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CNntp::PostArticleFromFile(BSTR FileName, long *Result)
{
	AddMethod(METHOD_POST_ARTICLE_FROM_FILE, Result, _VP(FileName), NULL);
	return S_OK;
}


/***************************************************
GetArticleList
	Attempt to get a list of the articles avilable on 
	the selected news group.
Params
	Type	itRequestAll	- will load all the newsgroups and clear our existing memory list
			itRequestNew	- will load only the newsgroups loaded since our last download
	Result	- pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CNntp::GetArticleList(RequestInfoType Type, long *Result)
{
	AddMethod(METHOD_GET_ARTICLE_LIST, Result, _VP((Type == itRequestAll) ? 0L : 1L), NULL);
	return S_OK;
}

/***************************************************
GetNewsGroupList
	Retrives the list of available News Groups on the connected server
    issue a LIST command wich returns a list of valid newsgroups.
Params
	Type	itRequestAll	- will load all the newsgroups and clear our existing memory list
			itRequestNew	- will load only the newsgroups loaded since our last download
	Result	- pointer to the result varaible
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CNntp::GetNewsGroupList(RequestInfoType Type, long *Result)
{
	AddMethod(METHOD_GET_NEWS_GROUP_LIST, Result, _VP((Type == itRequestAll) ? 0L : 1L), NULL);
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
STDMETHODIMP CNntp::GetInterfaceSafetyOptions(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
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
STDMETHODIMP CNntp::SetInterfaceSafetyOptions(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
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
BOOL CNntp::IsAborted() {
	return m_bAbortFlag;
}

/********************************
OnSendArticleProgress
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
BOOL CNntp::OnSendArticleProgress(long bytesSent,long totalBytes) {
	Fire_OnSendArticleProgress(bytesSent, totalBytes);
    return !m_bAbortFlag;
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
BOOL CNntp::WaitWithMsgLoop(HANDLE hEvent, long lTimeout)
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
long CNntp::ExecuteMethod(MethodTypeTag MethodID, _variant_t *ptrVarParams, BOOL bForceNonBlocking)
{
	LONG	lRetCode;

    // If we are not going to destroy the object - clear the abort flag
	if(!m_bGoingToClose)
	    m_bAbortFlag	= FALSE;

    switch(MethodID) {
		case(METHOD_CONNECT):
			lRetCode = CUT_NNTPClient::NConnect((LPCTSTR)_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]), _bstr_t(ptrVarParams[2]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnConnect(lRetCode);
				}
			break;
		case(METHOD_CLOSE):
			lRetCode = CUT_NNTPClient::NClose();
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnClose(lRetCode);
				}
			break;
		case(METHOD_CHECK_CAN_POST):
			lRetCode = CUT_NNTPClient::NCanPost();
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnCheckCanPost(lRetCode);
				}
			break;
		case(METHOD_GET_SERVER_DATE):
			char	buffer[LINE_BUFFER_SIZE+1];
			lRetCode = CUT_NNTPClient::NGetServerDate(buffer, LINE_BUFFER_SIZE);
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
                m_bstrServerDate = buffer;
				Fire_OnGetServerDate(m_bstrServerDate, lRetCode);
				}
			break;
		case(METHOD_SELECT_NEWS_GROUP):
			lRetCode = CUT_NNTPClient::NSelectNewsGroup((LPCTSTR)_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnSelectNewsGroup(lRetCode);
				}
			break;
		case(METHOD_GET_ARTICLE):
			lRetCode = CUT_NNTPClient::NGetArticle((LPCTSTR)_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnGetArticle(lRetCode);
				}
			break;
		case(METHOD_POST_ARTICLE):
			lRetCode = CUT_NNTPClient::NPostArticle((LPCTSTR)_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]), _bstr_t(ptrVarParams[2]), _bstr_t(ptrVarParams[3]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnPostArticle(lRetCode);
				}
			break;
		case(METHOD_POST_ARTICLE_FROM_FILE):
            {
            // Load the file in the temp Message class
            CUT_Msg msg;
            lRetCode = msg.LoadMessage(_bstr_t(ptrVarParams[0]));

            // If successful post NNTP article
            if(lRetCode == UTE_SUCCESS)
                lRetCode = CUT_NNTPClient::NPostArticle(msg);

			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnPostArticle(lRetCode);
				}
			break;
            }
        case(METHOD_GET_ARTICLE_LIST):
			lRetCode = CUT_NNTPClient::NGetArticleList((long)ptrVarParams[0]);
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnGetArticleList(lRetCode);
				}
			break;
		case(METHOD_GET_NEWS_GROUP_LIST):
			lRetCode = CUT_NNTPClient::NGetNewsGroupList((long)ptrVarParams[0]);
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnGetNewsGroupList(lRetCode);
				}
			break;

		// Unknown method error
		default:
			return UTE_ERROR;
		}

	return lRetCode;
}



#pragma warning (pop)