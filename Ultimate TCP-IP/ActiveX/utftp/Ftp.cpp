// =================================================================
// Ultimate TCP-IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// =================================================================

// Ftp.cpp : Implementation of CFtp

#include "stdafx.h"
#include "UTFtp.h"
#include "Ftp.h"

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
// CFtp
/////////////////////////////////////////////////////////////////////////////

/***************************************************
CFtp
	Standart constructor. 
Params
    none
Return
	none
****************************************************/
CFtp::CFtp() : CUT_MethodQueue<CFtp, MethodTypeTag>(this),
		m_nCurDirEntryIndex(0),			// Initialize current directory entry
		m_bBlockingMode(FALSE),			// Set non blocking mode as default
		m_lnConnectTimeOut(5),			// Set default connection time-out to 5 secs
		m_bGoingToClose(FALSE),			// Initialize closing flag with FALSE
		m_bAbortFlag(FALSE),			// Clear abort flag
        m_bstrServerCurDir(L""),        // Initialize server current directory
		m_bstrHostName(L""),			// Initialize host name property variable
		m_bstrUserName(L"anonymous"),	// Initialize user name property variable
		m_bstrUserPassword(L"anonymous@anonymous.com"),	// Initialize user password property variable
		m_bstrAccount(L"")				// Initialize account property variable

{
	// Load Ftp Icon
	m_hFtpIcon = LoadIcon(_Module.m_hInst, MAKEINTRESOURCE(IDI_ICON_FTP));	

	// Initiate default control size 32 x 32 pixels
    SIZE	sz = { 32, 32 };
    AtlPixelToHiMetric (&sz, &m_sizeExtent);		// convert pixels to himetric
    m_sizeNatural	= m_sizeExtent;					// store natural extent

	// Disable resizing of the control
	m_bAutoSize		= TRUE;				
  
}

/***************************************************
~CFtp
	Destructor.
Params
    none
Return
	none
****************************************************/
CFtp::~CFtp()
{
	// Set flags to terminate all running threads
	m_bGoingToClose	= TRUE;
	m_bAbortFlag	= TRUE;

	// If thread is running - will wait till it exits
	// or will time-out. 
	if(m_hMethodThread != NULL) {
		// Resume working thread
		ResumeThread(m_hMethodThread);

		WaitWithMsgLoop(m_hMethodThread, max(m_lnConnectTimeOut * 2000, 120000));
		}

	// Destroy Ftp icon handle
	if(m_hFtpIcon) {
		DestroyIcon( m_hFtpIcon );							
		m_hFtpIcon = NULL;
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
STDMETHODIMP CFtp::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = {	&IID_IFtp,};
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
HRESULT CFtp::OnDraw(ATL_DRAWINFO& di)
{
	// Fill background & draw a boreder
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	// Draw Ftp Icon
	if(m_hFtpIcon)
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hFtpIcon);	
 		
	return S_OK;
}


////////////////////////////////////////////////////
//	IFtp interface properties Set/Get functions
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
STDMETHODIMP CFtp::get_ConnectTimeOut(long *pVal)
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
STDMETHODIMP CFtp::put_ConnectTimeOut(long newVal)
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
		return AtlReportError(CLSID_Ftp,"Invalid Connect Time Out value", IID_IFtp, E_FAIL);


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
STDMETHODIMP CFtp::get_BlockingMode(VARIANT_BOOL *pVal)
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
STDMETHODIMP CFtp::put_BlockingMode(VARIANT_BOOL newVal)
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
get_FireWallMode
	Gets fire wall mode value
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CFtp::get_FireWallMode(VARIANT_BOOL *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (VARIANT_BOOL)CUT_FTPClient::GetFireWallMode();
	return S_OK;
}

/***************************************************
put_FireWallMode
	Set fire wall mode value
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
****************************************************/
STDMETHODIMP CFtp::put_FireWallMode(VARIANT_BOOL newVal)
{
	if(newVal == (VARIANT_BOOL)CUT_FTPClient::GetFireWallMode())	return S_OK;

	if(FireOnRequestEdit(DISPID_FIREWALL_MODE) == S_FALSE)
		return S_FALSE;

	SetFireWallMode(newVal);

	m_bRequiresSave = TRUE;

	FireOnChanged(DISPID_FIREWALL_MODE);

	SendOnDataChange(NULL);

	return S_OK;
}

/***************************************************
get_TransferMode
	Gets transfer mode value
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CFtp::get_TransferMode(FtpTransferMode *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (FtpTransferMode)CUT_FTPClient::GetTransferMode();
	return S_OK;
}

/***************************************************
get_TransferStructure
	Gets transfer structure value
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CFtp::get_TransferStructure(FtpTransferStructure *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (FtpTransferStructure)CUT_FTPClient::GetTransferStructure();
	return S_OK;
}

/***************************************************
get_TransferType
	Gets transfer type value
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CFtp::get_TransferType(FtpTransferType *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (FtpTransferType)CUT_FTPClient::GetTransferType();
	return S_OK;
}

/***************************************************
get_MultilineResponseLineCount
	Gets multiline response lines count
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK		- success
	E_POINTER	- wrong pointer
****************************************************/
STDMETHODIMP CFtp::get_MultilineResponseLineCount(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = CUT_FTPClient::GetMultiLineResponseLineCount();
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
STDMETHODIMP CFtp::get_HostName(BSTR *pVal)
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
STDMETHODIMP CFtp::put_HostName(BSTR newVal)
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
STDMETHODIMP CFtp::get_UserName(BSTR *pVal)
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
STDMETHODIMP CFtp::put_UserName(BSTR newVal)
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
STDMETHODIMP CFtp::get_UserPassword(BSTR *pVal)
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
STDMETHODIMP CFtp::put_UserPassword(BSTR newVal)
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
get_Account
	Returns account
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CFtp::get_Account(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, m_bstrAccount))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
put_Account
	Set user account
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
****************************************************/
STDMETHODIMP CFtp::put_Account(BSTR newVal)
{
	if(_bstr_t(newVal) == m_bstrAccount)	return S_OK;

	if(FireOnRequestEdit(DISPID_ACCOUNT) == S_FALSE)
		return S_FALSE;

	m_bstrAccount = newVal;

	m_bRequiresSave = TRUE;

	FireOnChanged(DISPID_ACCOUNT);

	SendOnDataChange(NULL);

	return S_OK;
}

/***************************************************
get_DirEntryName
	Returns current directory entry name
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CFtp::get_DirEntryName(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, _bstr_t(m_CurDirEntry.fileName)))
		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
get_DirEntrySize
	Returns current directory entry size
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CFtp::get_DirEntrySize(long *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_CurDirEntry.fileSize;
	return S_OK;
}

/***************************************************
get_DirEntryDay
	Returns current directory entry day
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CFtp::get_DirEntryDay(int *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_CurDirEntry.day;
	return S_OK;
}

/***************************************************
get_DirEntryMonth
	Returns current directory entry month
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CFtp::get_DirEntryMonth(int *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_CurDirEntry.month;
	return S_OK;
}


/***************************************************
get_DirEntryYear
	Returns current directory entry year
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CFtp::get_DirEntryYear(int *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_CurDirEntry.year;
	return S_OK;
}

/***************************************************
get_DirEntryHour
	Returns current directory entry hour
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CFtp::get_DirEntryHour(int *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_CurDirEntry.hour;
	return S_OK;
}


/***************************************************
get_DirEntryMinute
	Returns current directory entry minute
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CFtp::get_DirEntryMinute(int *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = m_CurDirEntry.minute;
	return S_OK;
}

/***************************************************
get_DirEntryIsDir
	Returns current directory entry directory flag
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CFtp::get_DirEntryIsDir(VARIANT_BOOL *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	*pVal = (VARIANT_BOOL)m_CurDirEntry.isDir;
	return S_OK;
}

/***************************************************
get_CurrentDir
	Gets current server directory. You can get this property
    after calling GetCurDir method
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
****************************************************/
STDMETHODIMP CFtp::get_CurrentDir(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;

	if(!SysReAllocString(pVal, m_bstrServerCurDir))
		return E_OUTOFMEMORY;

	return S_OK;
}

////////////////////////////////////////////////////
//	IFtp interface methods
////////////////////////////////////////////////////

/***************************************************
CancelFtp
	Cancel current Ftp operation
Params
    none
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CFtp::CancelFtp()
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
STDMETHODIMP CFtp::AboutBox()
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
STDMETHODIMP CFtp::GetErrorText(long ErrorCode, BSTR *ErrorText)
{
 	HRESULT		hResult			= S_OK;
 	CComBSTR	bstrErrorMsg	= CUT_ERR::GetErrorString(ErrorCode);
 
 	if(!SysReAllocString(ErrorText, bstrErrorMsg))
 		hResult = E_OUTOFMEMORY;
 
 	return hResult;
}


/***************************************************
CdUp
	Moves up one directory level on the 
    currently connected FTP server
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::CdUp(long *Result)
{
	AddMethod(METHOD_CDUP, Result, NULL);
	return S_OK;
}

/***************************************************
ChDir
	Changes the current directory of the 
    currently connected FTP server
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::ChDir(BSTR DirName, long *Result)
{
	AddMethod(METHOD_CHDIR, Result, _VP(DirName), NULL);
	return S_OK;
}

/***************************************************
Close
	Closes an open connection
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::Close(long *Result)
{
	AddMethod(METHOD_CLOSE, Result, NULL);
	return S_OK;
}

/***************************************************
Connect
	Connect to the given FTP site
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::Connect(long *Result)
{
	AddMethod(METHOD_CONNECT, Result, _VP(m_bstrHostName), _VP(m_bstrUserName), _VP(m_bstrUserPassword), _VP(m_bstrAccount), NULL);
	return S_OK;
}

/***************************************************
DeleteFile
	Deletes  the specified file off of the
    currently connect FTP server.
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::DeleteFile(BSTR FileName, long *Result)
{
	AddMethod(METHOD_DELETE_FILE, Result, _VP(FileName), NULL);
	return S_OK;
}

/***************************************************
GetDirInfo
	Retrieves the current directory infomation
    on the currently connected FTP server.
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::GetDirInfo(long *Result)
{
	AddMethod(METHOD_GET_DIR_INFO, Result, NULL);
	return S_OK;
}

/***************************************************
GetHelp
	Returns help information from the 
    currently connected server. Once this 
    command completes successfully then
    the information can be retrieved using 
    the GetMultiLineResponse function.
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::GetHelp(BSTR Param, long *Result)
{
	AddMethod(METHOD_GET_HELP, Result, _VP(Param), NULL);
	return S_OK;
}

/***************************************************
MkDir
	Creates a new directory on the 
    currently connected FTP server
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::MkDir(BSTR Directory, long *Result)
{
	AddMethod(METHOD_MKDIR, Result, _VP(Directory), NULL);
	return S_OK;
}

/***************************************************
NoOp
	Performs a No-op operation. This is 
    usually used to check and see if the
    connection is still up.
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::NoOp(long *Result)
{
	AddMethod(METHOD_NOOP, Result, NULL);
	return S_OK;
}

/***************************************************
ReceiveFile
	Retrieves the specified file from the
    currently connected FTP site. The file
    is then saved to the specified destination
    file.
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::ReceiveFile(BSTR SourceFileName, BSTR DestFileName, long *Result)
{
	AddMethod(METHOD_RECEIVE_FILE, Result, _VP(SourceFileName), _VP(DestFileName), NULL);
	return S_OK;
}

/***************************************************
RenameFile
	Renames the given file on the currently
    connected FTP site.
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::RenameFile(BSTR SourceFileName, BSTR DestFileName, long *Result)
{
	AddMethod(METHOD_RENAME_FILE, Result, _VP(SourceFileName), _VP(DestFileName), NULL);
	return S_OK;
}

/***************************************************
RemoveDir
	Removes a directory on the 
    currently connected FTP server
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::RemoveDir(BSTR Directory, long *Result)
{
	AddMethod(METHOD_REMOVE_DIR, Result, _VP(Directory), NULL);
	return S_OK;
}

/***************************************************
SendFile
	Sends the specified local file to
    the given destination on the currently
    connected FTP site.
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::SendFile(BSTR SourceFileName, BSTR DestFileName, long *Result)
{
	AddMethod(METHOD_SEND_FILE, Result, _VP(SourceFileName), _VP(DestFileName), NULL);
	return S_OK;
}

/***************************************************
Quote
	Sends a custom command to the server
	custom command can be any valid FTP command or 
	any server specific command.
Params
	Command	- custom command
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::Quote(BSTR Command, long *Result)
{
	AddMethod(METHOD_QUOTE, Result, _VP(Command), NULL);
	return S_OK;
}

/***************************************************
ResumeFile
	Resumes retrieving the specified file from the
    currently connected FTP site.
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::ResumeFile(BSTR SourceFileName, BSTR DestFileName, long *Result)
{
	AddMethod(METHOD_RESUME_FILE, Result, _VP(SourceFileName), _VP(DestFileName), NULL);
	return S_OK;
}

/***************************************************
GetCurDir
	Gets the name of the current
    directory on the currently connected
    FTP server.
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::GetCurDir(long *Result)
{
    m_bstrServerCurDir = "";
	AddMethod(METHOD_GET_CUR_DIR, Result, NULL);
	return S_OK;
}

/***************************************************
SetTransferMode
	Sets the data transfer mode.
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::SetTransferMode(FtpTransferMode TransferMode, long *Result)
{
	AddMethod(METHOD_SET_TRANSFER_MODE, Result, _VP((long)TransferMode), NULL);
	return S_OK;
}

/***************************************************
SetTransferStructure
	Sets the data transfer structure
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::SetTransferStructure(FtpTransferStructure TransferStructure, long *Result)
{
	AddMethod(METHOD_SET_TRANSFER_STRUCTURE, Result, _VP((long)TransferStructure), NULL);
	return S_OK;
}

/***************************************************
SetTransferType
	Sets the data transfer type.
Params
	Result	- pointer to result variable
Return
	S_OK	- success
****************************************************/
STDMETHODIMP CFtp::SetTransferType(FtpTransferType TransferType, long *Result)
{
	AddMethod(METHOD_SET_TRANSFER_TYPE, Result, _VP((long)TransferType), NULL);
	return S_OK;
}

/***************************************************
ResetDirEntryEnum
	Resets directory entries enumeration
Params
	none
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CFtp::ResetDirEntryEnum()
{
	m_nCurDirEntryIndex = 0;
	return S_OK;
}

/***************************************************
ResetDirEntryEnum
	Enumeratedirectory entries
Params
	none
Return
	S_OK			- success
****************************************************/
STDMETHODIMP CFtp::EnumDirEntry(long *Result)
{
	if(m_nCurDirEntryIndex >= GetDirInfoCount())
		*Result = UTE_INDEX_OUTOFRANGE;
	
	else if(GetDirEntry(m_nCurDirEntryIndex, &m_CurDirEntry) != UTE_SUCCESS)
		*Result = UTE_INDEX_OUTOFRANGE;

	else {
		++m_nCurDirEntryIndex;
		*Result = UTE_SUCCESS;
		}

	return S_OK;
}

/***************************************************
GetMultilineResponse
	Returns one line from the response string list.
Params
	Index		- index of the line
	Result		- pointer to the result varaible
Return
	S_OK			- success
	E_OUTOFMEMORY	- out of memory
	E_FAIL			- line index is out of range
****************************************************/
STDMETHODIMP CFtp::GetMultilineResponse(long Index, BSTR *Result)
{
	_bstr_t	bstrLine = CUT_FTPClient::GetMultiLineResponse(Index);

	if(!SysReAllocString(Result, bstrLine))
		return E_OUTOFMEMORY;

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
STDMETHODIMP CFtp::GetInterfaceSafetyOptions(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
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
STDMETHODIMP CFtp::SetInterfaceSafetyOptions(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
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
BOOL CFtp::IsAborted() {
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
BOOL CFtp::ReceiveFileStatus(long bytesReceived){
	Fire_OnReceiveStatus(bytesReceived);
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
BOOL CFtp::SendFileStatus(long bytesSent){
	Fire_OnSendStatus(bytesSent);
    return !IsAborted();
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
BOOL CFtp::WaitWithMsgLoop(HANDLE hEvent, long lTimeout)
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
long CFtp::ExecuteMethod(MethodTypeTag MethodID, _variant_t *ptrVarParams, BOOL bForceNonBlocking)
{
	LONG	lRetCode;

    // If we are not going to destroy the object - clear the abort flag
	if(!m_bGoingToClose)
	    m_bAbortFlag	= FALSE;

	switch(MethodID) {
		case(METHOD_CDUP):
			lRetCode = CUT_FTPClient::CdUp();
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnCdUp(lRetCode);
				}
			break;
		case(METHOD_CHDIR):
			lRetCode = CUT_FTPClient::ChDir(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnChDir(lRetCode);
				}
			break;
		case(METHOD_CONNECT):
			lRetCode = CUT_FTPClient::FTPConnect(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]), _bstr_t(ptrVarParams[2]), _bstr_t(ptrVarParams[3]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnConnect(lRetCode);
				}
			break;
		case(METHOD_CLOSE):
			lRetCode = CUT_FTPClient::Close();
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnClose(lRetCode);
				}
			break;
		case(METHOD_DELETE_FILE):
			lRetCode = CUT_FTPClient::DeleteFile(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnDeleteFile(lRetCode);
				}
			break;
		case(METHOD_GET_DIR_INFO):
			lRetCode = CUT_FTPClient::GetDirInfo();
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnGetDirInfo(lRetCode);
				}
			break;
		case(METHOD_GET_HELP):
			lRetCode = CUT_FTPClient::GetHelp(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnGetHelp(lRetCode);
				}
			break;
		case(METHOD_MKDIR):
			lRetCode = CUT_FTPClient::MkDir(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnMkDir(lRetCode);
				}
			break;
		case(METHOD_NOOP):
			lRetCode = CUT_FTPClient::NoOp();
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnNOOP(lRetCode);
				}
			break;
		case(METHOD_RECEIVE_FILE):
			lRetCode = CUT_FTPClient::ReceiveFile(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnReceiveFile(lRetCode);
				}
			break;
		case(METHOD_RENAME_FILE):
			lRetCode = CUT_FTPClient::RenameFile(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnRenameFile(lRetCode);
				}	
			break;
		case(METHOD_REMOVE_DIR):
			lRetCode = CUT_FTPClient::RmDir(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnRemDir(lRetCode);
				}
			break;
		case(METHOD_SEND_FILE):
			lRetCode = CUT_FTPClient::SendFile(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnSendFile(lRetCode);
				}
			break;
		case(METHOD_GET_CUR_DIR):
			char	buffer[_MAX_PATH+1];
			lRetCode = CUT_FTPClient::GetCurDir(buffer, _MAX_PATH);
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
                m_bstrServerCurDir = buffer;
				Fire_OnGetCurDir(lRetCode, m_bstrServerCurDir);
				}
			break;
		case(METHOD_SET_TRANSFER_MODE):
			lRetCode = CUT_FTPClient::SetTransferMode((long)ptrVarParams[0]);
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnSetTransferMode(lRetCode);
				}
			break;
		case(METHOD_SET_TRANSFER_STRUCTURE):
			lRetCode = CUT_FTPClient::SetTransferStructure((long)ptrVarParams[0]);
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnSetTransferStructure(lRetCode);
				}
			break;
		case(METHOD_SET_TRANSFER_TYPE):
			lRetCode = CUT_FTPClient::SetTransferType((long)ptrVarParams[0]);
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnSetTransferType(lRetCode);
				}
			break;
		case(METHOD_QUOTE):
			lRetCode = CUT_FTPClient::Quote(_bstr_t(ptrVarParams[0]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnQuote(lRetCode);
				}
			break;
		case(METHOD_RESUME_FILE):
			lRetCode = CUT_FTPClient::ResumeReceiveFile(_bstr_t(ptrVarParams[0]), _bstr_t(ptrVarParams[1]));
			if(!m_bGoingToClose) {
				m_bUseMarshaling = (bForceNonBlocking) ? TRUE : !m_bBlockingMode; 
				Fire_OnResumeFile(lRetCode);
				}
			break;

		// Unknown method error
		default:
			return UTE_ERROR;
		}


	return lRetCode;
}


#pragma warning (pop)