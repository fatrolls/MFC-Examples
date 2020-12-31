//=================================================================
//  class: CMailPropPage
//  File:  MailPropPage.cpp
//
//  Mail ActiveX control property page
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
#include "MailPropPage.h"

/////////////////////////////////////////////////////////////////////////////
// CMailPropPage
/////////////////////////////////////////////////////////////////////////////

/***************************************************
InitializeControlsFromObject
	Initialize property page controls from object data
Params
    none
Return
	none
****************************************************/
void CMailPropPage::InitializeControlsFromObject()
{
	LONG			nTimeOut	= 0;
	VARIANT_BOOL	bBOOL		= FALSE;
	BSTR			bstrString	= SysAllocStringLen(NULL, TMP_BUFFER_SIZE);

	// Get IMail interface of the object
	IMail	*pMail;
	m_ppUnk[0]->QueryInterface(IID_IMail, (void**)&pMail);

	// Set connection time-out
	ShowError(pMail->get_ConnectTimeOut(&nTimeOut));
	SetDlgItemInt(IDC_EDITCONNECT_TO, (int)nTimeOut);

	// Set blocking mode
#ifndef _BLOCKING_MODE_ONLY
	ShowError(pMail->get_BlockingMode(&bBOOL));
	SendDlgItemMessage(IDC_BLOCKING_MODE, CB_SETCURSEL, (WPARAM)(bBOOL) ? 1 : 0);
#else 
    SendDlgItemMessage(IDC_BLOCKING_MODE, CB_SETCURSEL, 1);
    ::EnableWindow(GetDlgItem(IDC_BLOCKING_MODE), FALSE);
#endif // _BLOCKING_MODE_ONLY

	// Set receive time out
	ShowError(pMail->get_ReceiveTimeOut(&nTimeOut));
	SetDlgItemInt(IDC_RECEIVE_TIME_OUT, (int)nTimeOut);

	// Mail Set host name
	ShowError(pMail->get_MailHostName(&bstrString));
	SetDlgItemText(IDC_MAIL_HOST_NAME, _bstr_t(bstrString));

	// Local Set host name
	ShowError(pMail->get_LocalHostName(&bstrString));
	SetDlgItemText(IDC_LOCAL_HOST_NAME, _bstr_t(bstrString));

    // Set host name
	ShowError(pMail->get_POP3HostName(&bstrString));
	SetDlgItemText(IDC_POP3_HOST_NAME, _bstr_t(bstrString));

	// Set user name
	ShowError(pMail->get_UserName(&bstrString));
	SetDlgItemText(IDC_USER_NAME, _bstr_t(bstrString));

	// Set password
	ShowError(pMail->get_UserPassword(&bstrString));
	SetDlgItemText(IDC_PASSWORD, _bstr_t(bstrString));

	// Release IMail interface
	pMail->Release();

}

/***************************************************
Apply
	Apply current values from the property page to
	the objects.
Params
    none
Return
	S_OK	- success
	E_FAIL	- wrong data
****************************************************/
STDMETHODIMP CMailPropPage::Apply(void)
{
	HRESULT	hr = S_OK;
	char	buffer[TMP_BUFFER_SIZE + 1];

	ATLTRACE(_T("CMailPropPage::Apply\n"));

	// Cycle throuh all objects
	for (UINT i = 0; i < m_nObjects; i++) {

		// Get IMail interface of the object
		IMail	*pMail;
		m_ppUnk[i]->QueryInterface(IID_IMail, (void**)&pMail);

		// If the value of property was changed - apply it from
		// the property page to the object

		// Connection time-out
		if(m_nDirtyFlags | CONNECT_TIME_OUT) {
			int nTimeOut = GetDlgItemInt(IDC_EDITCONNECT_TO);
			if(ShowError(pMail->put_ConnectTimeOut(nTimeOut)))
				hr = E_FAIL;
			}

    #ifndef _BLOCKING_MODE_ONLY
		// Blocking mode
		if(hr == S_OK && m_nDirtyFlags | BLOCKING_MODE) {
			BOOL bBlockingMode = (BOOL)SendDlgItemMessage(IDC_BLOCKING_MODE, CB_GETCURSEL);
 			if(ShowError(pMail->put_BlockingMode(bBlockingMode)))
				hr = E_FAIL;
			}
    #endif // _BLOCKING_MODE_ONLY

		// Receive time out
		if(hr == S_OK && m_nDirtyFlags | RECEIVE_TIME_OUT) {
			int nTimeOut = GetDlgItemInt(IDC_RECEIVE_TIME_OUT);
			if(ShowError(pMail->put_ReceiveTimeOut(nTimeOut)))
				hr = E_FAIL;
			}

		// Mail Host name
		if(m_nDirtyFlags | MAIL_HOST_NAME) {
			GetDlgItemText(IDC_MAIL_HOST_NAME, buffer, TMP_BUFFER_SIZE);
			if(ShowError(pMail->put_MailHostName(_bstr_t(buffer))))
				hr = E_FAIL;
			}

		// Local Host name
		if(m_nDirtyFlags | LOCAL_HOST_NAME) {
			GetDlgItemText(IDC_LOCAL_HOST_NAME, buffer, TMP_BUFFER_SIZE);
			if(ShowError(pMail->put_LocalHostName(_bstr_t(buffer))))
				hr = E_FAIL;
			}

        // POP3 Host name
		if(m_nDirtyFlags | POP3_HOST_NAME) {
			GetDlgItemText(IDC_POP3_HOST_NAME, buffer, TMP_BUFFER_SIZE);
			if(ShowError(pMail->put_POP3HostName(_bstr_t(buffer))))
				hr = E_FAIL;
			}

		// User name
		if(m_nDirtyFlags | USER_NAME) {
			GetDlgItemText(IDC_USER_NAME, buffer, TMP_BUFFER_SIZE);
			if(ShowError(pMail->put_UserName(_bstr_t(buffer))))
				hr = E_FAIL;
			}

		// Password
		if(m_nDirtyFlags | PASSWORD) {
			GetDlgItemText(IDC_PASSWORD, buffer, TMP_BUFFER_SIZE);
			if(ShowError(pMail->put_UserPassword(_bstr_t(buffer))))
				hr = E_FAIL;
			}


		// Release IMail interface
		pMail->Release();

		// If there was an error - return
		if(hr != S_OK) {
			InitializeControlsFromObject();
			return hr;
			}
		}

	// Clear dirty flags
	m_bDirty		= FALSE;
	m_nDirtyFlags	= 0;

	return S_OK;
}

/***************************************************
ShowError
	Helper function for displaying error message in
	case if hResult is an error
Params
    hResult	- error code
Return
	TRUE	- if there was an error 
	FALSE	- if not
****************************************************/
BOOL CMailPropPage::ShowError(HRESULT hResult) 
{
	// Check if error code failed
	if FAILED(hResult) {

		USES_CONVERSION;

		CComPtr<IErrorInfo>		pError;
		CComBSTR				strError;

		// Get description of the error 
		GetErrorInfo(0, &pError);
		pError->GetDescription(&strError);

		// Display error message box
		MessageBox(OLE2T(strError), _T("Error"), MB_ICONEXCLAMATION);

		return TRUE;
		}

	return FALSE;
}



