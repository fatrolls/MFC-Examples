//=================================================================
//  class: CMailServ
//  File:  MailServ.cpp
//
//  Implementation of CMailServ class
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
#include "UTMailServ.h"
#include "MailServ.h"
#include "AboutDlg.h"


// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

/////////////////////////////////////////////////////////////////////////////
// CMailServ
/////////////////////////////////////////////////////////////////////////////

/***************************************************
CMailServ
	Standart constructor. 
Params
    none
Return
	none
****************************************************/
CMailServ::CMailServ() :
		m_bGoingToClose(FALSE)
{
	// Initialize server classes
	m_ptrPOP3Server = new POP3ServerEx(*this);
	m_ptrSMTPServer = new SMTPServerEx(*this);
	m_ptrSMTPOut	= new SMTPOutEx(*this);
	SetServerClasses(m_ptrPOP3Server, m_ptrSMTPServer, m_ptrSMTPOut);
	
	// Load Mail Icon
	m_hMailServIcon = LoadIcon(_Module.m_hInst, MAKEINTRESOURCE(IDI_ICON_MAILSERV));	

	// Initiate default control size 32 x 32 pixels
    SIZE	sz = { 32, 32 };
    AtlPixelToHiMetric (&sz, &m_sizeExtent);		// convert pixels to himetric
    m_sizeNatural	= m_sizeExtent;					// store natural extent

	// Disable resizing of the control
	m_bAutoSize		= TRUE;				

	// Initialize lock
	m_EventLock.Init();

	// Initialize registry root key
	_tcscpy(m_szRootKey, _T("SOFTWARE\\EMAIL_S"));
}

/***************************************************
~CMailServ
	Destructor.
Params
    none
Return
	none
****************************************************/
CMailServ::~CMailServ()
{
	m_bGoingToClose = TRUE;

	// Destroy Mail icon handle
	if(m_hMailServIcon) {
		DestroyIcon( m_hMailServIcon );							
		m_hMailServIcon = NULL;
		}

	// Terminate lock
	m_EventLock.Term();

	// Destroy server classes
	if(m_ptrPOP3Server != NULL)
		delete m_ptrPOP3Server;
	if(m_ptrSMTPServer != NULL)
		delete m_ptrSMTPServer;
	if(m_ptrSMTPOut != NULL)
		delete m_ptrSMTPOut;

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
STDMETHODIMP CMailServ::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMailServ,
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
HRESULT CMailServ::OnDraw(ATL_DRAWINFO& di)
{
	// Fill background & draw a boreder
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	// Draw Mail Icon
	if(m_hMailServIcon)
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hMailServIcon);	
 		
	return S_OK;
}

////////////////////////////////////////////////////
//	IMailServ interface properties Set/Get functions
////////////////////////////////////////////////////

/***************************************************
get_RegistryRootKey
	Gets registry root key
Params
    pVal	- pointer to the variable receiving the value
Return
	S_OK			- success
	E_POINTER		- wrong pointer
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMailServ::get_RegistryRootKey(BSTR *pVal)
{
	if(pVal == NULL)	return E_POINTER;
	
 	if(!SysReAllocString(pVal, _bstr_t(Sys_GetRootKey())))
 		return E_OUTOFMEMORY;

	return S_OK;
}

/***************************************************
put_RegistryRootKey
	Set registry root key
Params
    newVal	- new value of the property
Return
	S_OK		- success
	S_FALSE		- can't change property now
****************************************************/
STDMETHODIMP CMailServ::put_RegistryRootKey(BSTR newVal)
{
	_bstr_t	bstrRoot = newVal;

	if(_tcsicmp(bstrRoot, Sys_GetRootKey()) == NULL)	return S_OK;

	if(FireOnRequestEdit(DISPID_REGISTRY_ROOT_KEY) == S_FALSE)
		return S_FALSE;

	Sys_SetRootKey(bstrRoot);
	
	m_bRequiresSave = TRUE;
	FireOnChanged(DISPID_REGISTRY_ROOT_KEY);
	SendOnDataChange(NULL);

	return S_OK;
}


////////////////////////////////////////////////////
//	IMailServ interface methods
////////////////////////////////////////////////////

/***************************************************
Start
	Starts finger server
Params
    Result		- pointer to the result variable
Return
	S_OK		- success
****************************************************/
STDMETHODIMP CMailServ::Start(long *Result)
{
	MarshalInterfacesToStream(this);
	*Result = CUT_MailServer::Start();
	return S_OK;
}


/***************************************************
User_Add
    Adds a new user to the user list
Params
	Name			- user name 
	Password		- user password
	MailAddresses	- email addresses separated by ','
	Result			- pointer to the result variable
Return
	S_OK			- success   
****************************************************/
STDMETHODIMP CMailServ::User_Add(BSTR Name, BSTR Password, BSTR MailAddresses, long *Result)
{
	*Result = UTE_ERROR;

	// Get pointer to the user manager class
	CUT_UserManager	*ptrUserManager = GetUserManager();

	if(ptrUserManager != NULL) {
		CUT_TStringList	listMailAddresses;
		int				index = 0;
		_TCHAR			buffer[_MAX_PATH + 1];

		while(CUT_StrMethods::ParseString(_bstr_t(MailAddresses), _T(" ,"), index++, buffer, _MAX_PATH) == UTE_SUCCESS)
			listMailAddresses.AddString(buffer);

		*Result = ptrUserManager->User_Add(_bstr_t(Name), _bstr_t(Password), listMailAddresses);
		}

	return S_OK;
}

/***************************************************
User_Modify
    Modify user in the user list
Params
	Name			    - user name to modify
    NewName			    - new user name
	NewPassword		    - new user password
	NewMailAddresses	- new email addresses separated by ','
	Result			    - pointer to the result variable
Return
	S_OK			- success   
****************************************************/
STDMETHODIMP CMailServ::User_Modify(BSTR Name, BSTR NewName, BSTR NewPassword, BSTR NewAddresses, long *Result)
{
	*Result = UTE_ERROR;

	// Get pointer to the user manager class
	CUT_UserManager	*ptrUserManager = GetUserManager();

	if(ptrUserManager != NULL) {
		CUT_TStringList	listMailAddresses;
		int				index = 0;
		_TCHAR			buffer[_MAX_PATH + 1];

		while(CUT_StrMethods::ParseString(_bstr_t(NewAddresses), _T(" ,"), index++, buffer, _MAX_PATH) == UTE_SUCCESS)
			listMailAddresses.AddString(buffer);

		*Result = ptrUserManager->User_Modify(_bstr_t(Name), _bstr_t(NewName), _bstr_t(NewPassword), &listMailAddresses);
		}

	return S_OK;
}

/***************************************************
User_Delete
    Deletes a user from the user list
Params
	Name			- user name 
	Result			- pointer to the result variable
Return
	S_OK			- success   
****************************************************/
STDMETHODIMP CMailServ::User_Delete(BSTR Name, long *Result)
{
	*Result = UTE_ERROR;

	// Get pointer to the user manager class
	CUT_UserManager	*ptrUserManager = GetUserManager();

	if(ptrUserManager != NULL) 
		*Result = ptrUserManager->User_Delete(_bstr_t(Name));

	return S_OK;
}

/***************************************************
User_GetCount
    Gets number of users in the user list
Params
	Result			- pointer to the result variable
Return
	S_OK			- success   
****************************************************/
STDMETHODIMP CMailServ::User_GetCount(long *UserCount)
{
	*UserCount = 0;

	// Get pointer to the user manager class
	CUT_UserManager	*ptrUserManager = GetUserManager();

	if(ptrUserManager != NULL) 
		*UserCount = ptrUserManager->User_GetCount();

	return S_OK;
}

/***************************************************
User_GetName
    Gets user name from the user list
Params
	Index			- index of the user
	Name			- pointer to the user name variable
Return
	S_OK			- success   
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMailServ::User_GetName(long Index, BSTR *Name)
{
	// Get pointer to the user manager class
	CUT_UserManager	*ptrUserManager = GetUserManager();

	if(ptrUserManager != NULL) {
		CUT_UserInfo *ptrUserInfo = ptrUserManager->User_GetUser(Index);
		if(ptrUserInfo != NULL) {

	 		if(!SysReAllocString(Name, _bstr_t(ptrUserInfo->szUserName)))
 				return E_OUTOFMEMORY;
			}
		}

	return S_OK;
}

/***************************************************
User_GetPassword
    Gets user password from the user list
Params
	Index			- index of the user
	Password		- pointer to the user password variable
Return
	S_OK			- success   
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMailServ::User_GetPassword(long Index, BSTR *Password)
{
	// Get pointer to the user manager class
	CUT_UserManager	*ptrUserManager = GetUserManager();

	if(ptrUserManager != NULL) {
		CUT_UserInfo *ptrUserInfo = ptrUserManager->User_GetUser(Index);
		if(ptrUserInfo != NULL) {

	 		if(!SysReAllocString(Password, _bstr_t(ptrUserInfo->szPassword)))
 				return E_OUTOFMEMORY;
			}
		}

	return S_OK;
}
/***************************************************
User_GetAddress
    Gets user address from the user list
Params
	Index			- index of the user
	MailAddresses	- pointer to the email addresses separated by ',' variable
Return
	S_OK			- success   
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMailServ::User_GetAddress(long Index, BSTR *MailAddresses)
{
	// Get pointer to the user manager class
	CUT_UserManager	*ptrUserManager = GetUserManager();

	if(ptrUserManager != NULL) {
		CUT_UserInfo *ptrUserInfo = ptrUserManager->User_GetUser(Index);
		if(ptrUserInfo != NULL) {

			// Convert list of email addresses to one string separated with ','
			_bstr_t	bstrMailAddresses = "";
			for(int i=0; i<ptrUserInfo->listEmailAddresses.GetCount(); i++){
				if(i != 0)
					bstrMailAddresses += ",";
				bstrMailAddresses += ptrUserInfo->listEmailAddresses.GetString(i);
				}

	 		if(!SysReAllocString(MailAddresses, bstrMailAddresses))
 				return E_OUTOFMEMORY;
			}
		}

	return S_OK;
}

/***************************************************
DNS_GetCount
    Gets number of DNS names 
Params
	DNSCount	- pointer to the result variable
Return
	S_OK		- success   
****************************************************/
STDMETHODIMP CMailServ::DNS_GetCount(long *DNSCount)
{
	*DNSCount = Sys_GetDNSNamesCount();
	return S_OK;
}

/***************************************************
DNS_Get
    Gets DNS name by index
Params
	Index	- index of DNS name to get	
	DNSName	- pointer to the result variable
Return
	S_OK			- success   
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMailServ::DNS_Get(long Index, BSTR *DNSName)
{
	if(!SysReAllocString(DNSName, _bstr_t(Sys_GetDNSName(Index))))
		return E_OUTOFMEMORY;
	return S_OK;
}

/***************************************************
DNS_Add
    Adds new DNS name to the list
Params
	DNSName	- DNS name to add
	Result	- pointer to the result variable
Return
	S_OK	- success   
****************************************************/
STDMETHODIMP CMailServ::DNS_Add(BSTR DNSName, long *Result)
{
	*Result = UTE_ERROR;
	if(Sys_AddDNSName(_bstr_t(DNSName)))
		*Result = UTE_SUCCESS;	
	return S_OK;
}

/***************************************************
DNS_Delete
    Deletes a DNS name from the list
Params
	Index	- index of DNS name to delete
	Result	- pointer to the result variable
Return
	S_OK	- success   
****************************************************/
STDMETHODIMP CMailServ::DNS_Delete(long Index, long *Result)
{
	*Result = UTE_ERROR;
	if(Sys_DeleteDNSName(Index))
		*Result = UTE_SUCCESS;	
	return S_OK;
}

/***************************************************
LocalName_GetCount
    Gets number of Local Names names 
Params
	LocalNamesCount	- pointer to the result variable
Return
	S_OK			- success   
****************************************************/
STDMETHODIMP CMailServ::LocalName_GetCount(long *LocalNamesCount)
{
	*LocalNamesCount = Sys_GetLocalNamesCount();
	return S_OK;
}

/***************************************************
LocalName_Get
    Gets Local Name by index
Params
	Index		- index of DNS name to get	
	LocalName	- pointer to the result variable
Return
	S_OK			- success   
	E_OUTOFMEMORY	- out of memory
****************************************************/
STDMETHODIMP CMailServ::LocalName_Get(long Index, BSTR *LocalName)
{
	if(!SysReAllocString(LocalName, _bstr_t(Sys_GetLocalName(Index))))
		return E_OUTOFMEMORY;
	return S_OK;
}

/***************************************************
LocalName_Add
    Adds new Local Name to the list
Params
	LocalName	- Local Name to add
	Result		- pointer to the result variable
Return
	S_OK	- success   
****************************************************/
STDMETHODIMP CMailServ::LocalName_Add(BSTR LocalName, long *Result)
{
	*Result = UTE_ERROR;
	if(Sys_AddLocalName(_bstr_t(LocalName)))
		*Result = UTE_SUCCESS;	

	return S_OK;
}

/***************************************************
LocalName_Delete
    Deletes a Local Name from the list
Params
	Index	- index of DNS name to delete
	Result	- pointer to the result variable
Return
	S_OK	- success   
****************************************************/
STDMETHODIMP CMailServ::LocalName_Delete(long Index, long *Result)
{
	*Result = UTE_ERROR;
	if(Sys_DeleteLocalName(Index))
		*Result = UTE_SUCCESS;	

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
STDMETHODIMP CMailServ::AboutBox()
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
STDMETHODIMP CMailServ::GetErrorText(long ErrorCode, BSTR *ErrorText)
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
STDMETHODIMP CMailServ::GetInterfaceSafetyOptions(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
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
STDMETHODIMP CMailServ::SetInterfaceSafetyOptions(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
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
OnStatus
    This virtual function is called each time we have any
	status information to display.
Params
	StatusText	- status text
Return
	UTE_SUCCESS - success   
****************************************************/
int CMailServ::OnStatus(LPCSTR StatusText)
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
long CMailServ::OnCanAccept(LPCSTR address){
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

/////////////////////////////////////////////////////////////////////////////
// POP3ServerEx
/////////////////////////////////////////////////////////////////////////////

/********************************
CreateInstance
    Creates an Instance of a
    CUT_POP3Thread class and return
    a pointer to it
Params
    none
Return
    pointer to an instance of a 
    CUT_POP3Thread
*********************************/
CUT_WSThread * POP3ServerEx::CreateInstance(){
   return new POP3ThreadEx;
}


/////////////////////////////////////////////////////////////////////////////
// POP3ThreadEx
/////////////////////////////////////////////////////////////////////////////

/********************************
OnMaxConnect
    This function is called when a
    new connection is made and the
    system has already reached its
    max. number of allowed connections
Params
    none
Return 
    none
*********************************/
void POP3ThreadEx::OnMaxConnect(){
	HRESULT	hr = CoInitialize(NULL);

	CUT_POP3Thread::OnMaxConnect();

	if(hr == S_OK)
			CoUninitialize();					
}

/********************************
OnConnect
    This function is called when a new 
    connection is made. This function
    receives all of the POP3 commands
    and processes them
Params
    none
Return
    none
*********************************/
void POP3ThreadEx::OnConnect(){
	HRESULT	hr = CoInitialize(NULL);

	CUT_POP3Thread::OnConnect();

	if(hr == S_OK)
			CoUninitialize();					
}

/////////////////////////////////////////////////////////////////////////////
// SMTPServerEx
/////////////////////////////////////////////////////////////////////////////

/********************************
CreateInstance
    Creates an Instance of a
    CUT_POP3Thread class and return
    a pointer to it
Params
    none
Return
    pointer to an instance of a 
    CUT_POP3Thread
*********************************/
CUT_WSThread * SMTPServerEx::CreateInstance(){
   return new SMTPThreadEx;
}

/////////////////////////////////////////////////////////////////////////////
// SMTPThreadEx
/////////////////////////////////////////////////////////////////////////////

/********************************
OnMaxConnect
    This function is called when a
    new connection is made and the
    system has already reached its
    max. number of allowed connections
Params
    none
Return 
    none
*********************************/
void SMTPThreadEx::OnMaxConnect(){
	HRESULT	hr = CoInitialize(NULL);

	CUT_SMTPThread::OnMaxConnect();

	if(hr == S_OK)
			CoUninitialize();					
}

/********************************
OnConnect
    This function is called when a new 
    connection is made. This function
    receives all of the POP3 commands
    and processes them
Params
    none
Return
    none
*********************************/
void SMTPThreadEx::OnConnect(){
	HRESULT	hr = CoInitialize(NULL);

	CUT_SMTPThread::OnConnect();

	if(hr == S_OK)
			CoUninitialize();					
}

/////////////////////////////////////////////////////////////////////////////
// SMTPOutEx
/////////////////////////////////////////////////////////////////////////////
/***************************************
SendMail
    Sends mail
Params
    info - pointer to the calling CUT_SMTPOut class        
Return
    none
****************************************/
void SMTPOutEx::SendMail(CUT_SMTPOutInfo	*info)
{
	HRESULT	hr = CoInitialize(NULL);

	CUT_SMTPOut::SendMail(info);

	if(hr == S_OK)
			CoUninitialize();					
}


#pragma warning (pop)