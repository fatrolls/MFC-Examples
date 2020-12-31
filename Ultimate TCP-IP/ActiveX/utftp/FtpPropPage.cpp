//=================================================================
//  class: CFtpPropPagePage
//  File:  FtpPropPage.cpp
//
//  Ftp ActiveX control property page
//
// =================================================================
// Ultimate TCP-IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// =================================================================

#include "stdafx.h"
#include "UTFtp.h"
#include "FtpPropPage.h"

/////////////////////////////////////////////////////////////////////////////
// CFtpPropPagePage
/////////////////////////////////////////////////////////////////////////////
/***************************************************
InitializeControlsFromObject
	Initialize property page controls from object data
Params
    none
Return
	none
****************************************************/
void CFtpPropPage::InitializeControlsFromObject()
{
	LONG			nTimeOut	= 0;
	VARIANT_BOOL	bBOOL		= FALSE;
	BSTR			bstrString	= SysAllocStringLen(NULL, TMP_BUFFER_SIZE);

	// Get IFtp interface of the object
	IFtp	*pFtp;
	m_ppUnk[0]->QueryInterface(IID_IFtp, (void**)&pFtp);

	// Set connection time-out
	ShowError(pFtp->get_ConnectTimeOut(&nTimeOut));
	SetDlgItemInt(IDC_EDITCONNECT_TO, (int)nTimeOut);

	// Set blocking mode
	ShowError(pFtp->get_BlockingMode(&bBOOL));
	SendDlgItemMessage(IDC_BLOCKING_MODE, CB_SETCURSEL, (WPARAM)(bBOOL) ? 1 : 0);

	// Set fire wall mode
	ShowError(pFtp->get_FireWallMode(&bBOOL));
	SendDlgItemMessage(IDC_FIRE_WALL_MODE, CB_SETCURSEL, (WPARAM)(bBOOL) ? 1 : 0);

	// Set host name
	ShowError(pFtp->get_HostName(&bstrString));
	SetDlgItemText(IDC_HOST_NAME, _bstr_t(bstrString));

	// Set account
	ShowError(pFtp->get_Account(&bstrString));
	SetDlgItemText(IDC_ACCOUNT, _bstr_t(bstrString));

	// Set user name
	ShowError(pFtp->get_UserName(&bstrString));
	SetDlgItemText(IDC_USER_NAME, _bstr_t(bstrString));

	// Set password
	ShowError(pFtp->get_UserPassword(&bstrString));
	SetDlgItemText(IDC_PASSWORD, _bstr_t(bstrString));

	// Release IFtp interface
	pFtp->Release();

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
STDMETHODIMP CFtpPropPage::Apply(void)
{
	HRESULT	hr = S_OK;
	char	buffer[TMP_BUFFER_SIZE + 1];

	ATLTRACE(_T("CFtpPropPage::Apply\n"));

	// Cycle throuh all objects
	for (UINT i = 0; i < m_nObjects; i++) {

		// Get IFtp interface of the object
		IFtp	*pFtp;
		m_ppUnk[i]->QueryInterface(IID_IFtp, (void**)&pFtp);

		// If the value of property was changed - apply it from
		// the property page to the object

		// Connection time-out
		if(m_nDirtyFlags | CONNECT_TIME_OUT) {
			int nTimeOut = GetDlgItemInt(IDC_EDITCONNECT_TO);
			if(ShowError(pFtp->put_ConnectTimeOut(nTimeOut)))
				hr = E_FAIL;
			}

		// Blocking mode
		if(hr == S_OK && m_nDirtyFlags | BLOCKING_MODE) {
			BOOL bBlockingMode = (BOOL)SendDlgItemMessage(IDC_BLOCKING_MODE, CB_GETCURSEL);
 			if(ShowError(pFtp->put_BlockingMode(bBlockingMode)))
				hr = E_FAIL;
			}

		// Fire wall mode
		if(hr == S_OK && m_nDirtyFlags | FIRE_WALL_MODE) {
			BOOL bFireWallMode = (BOOL)SendDlgItemMessage(IDC_FIRE_WALL_MODE, CB_GETCURSEL);
 			if(ShowError(pFtp->put_FireWallMode(bFireWallMode)))
				hr = E_FAIL;
			}

		// Host name
		if(m_nDirtyFlags | HOST_NAME) {
			GetDlgItemText(IDC_HOST_NAME, buffer, TMP_BUFFER_SIZE);
			if(ShowError(pFtp->put_HostName(_bstr_t(buffer))))
				hr = E_FAIL;
			}

		// Account
		if(m_nDirtyFlags | ACCOUNT) {
			GetDlgItemText(IDC_ACCOUNT, buffer, TMP_BUFFER_SIZE);
			if(ShowError(pFtp->put_Account(_bstr_t(buffer))))
				hr = E_FAIL;
			}

		// User name
		if(m_nDirtyFlags | USER_NAME) {
			GetDlgItemText(IDC_USER_NAME, buffer, TMP_BUFFER_SIZE);
			if(ShowError(pFtp->put_UserName(_bstr_t(buffer))))
				hr = E_FAIL;
			}

		// Password
		if(m_nDirtyFlags | PASSWORD) {
			GetDlgItemText(IDC_PASSWORD, buffer, TMP_BUFFER_SIZE);
			if(ShowError(pFtp->put_UserPassword(_bstr_t(buffer))))
				hr = E_FAIL;
			}


		// Release IFtp interface
		pFtp->Release();

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
BOOL CFtpPropPage::ShowError(HRESULT hResult) 
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
