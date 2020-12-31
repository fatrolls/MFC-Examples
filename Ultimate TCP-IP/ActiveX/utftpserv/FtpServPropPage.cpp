//=================================================================
//  class: CFtpServPropPage
//  File:  FtpServProp.cpp
//
//  HTTP Server ActiveX control property page
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
#include "UTFtpServ.h"
#include "FtpServPropPage.h"

/////////////////////////////////////////////////////////////////////////////
// CFtpServPropPage
/////////////////////////////////////////////////////////////////////////////


/***************************************************
InitializeControlsFromObject
	Initialize property page controls from object data
Params
    none
Return
	none
****************************************************/
void CFtpServPropPage::InitializeControlsFromObject()
{
	LONG	lLong		= 0;
	BSTR	bstrString	= SysAllocStringLen(NULL, _MAX_PATH + 1);

	// Get IFtpServ interface of the object
	IFtpServ	*pFtp;
	m_ppUnk[0]->QueryInterface(IID_IFtpServ, (void**)&pFtp);

	// Set port number
	ShowError(pFtp->get_Port(&lLong));
	SetDlgItemInt(IDC_PORT, (int)lLong);

	// Set path
	ShowError(pFtp->get_Path(&bstrString));
	SetDlgItemText(IDC_PATH, _bstr_t(bstrString));

	// Set welcome message
	ShowError(pFtp->get_WelcomeMsg(&bstrString));
	SetDlgItemText(IDC_WELCOME, _bstr_t(bstrString));

	// Set max. connections number
	ShowError(pFtp->get_MaxConnections(&lLong));
	SetDlgItemInt(IDC_MAX_CONNECTIONS, (int)lLong);

	// Set max. time out
	ShowError(pFtp->get_MaxTimeOut(&lLong));
	SetDlgItemInt(IDC_EDIT_MAX_TIME_OUT, (int)lLong);

    // Release IFtpServ interface
	pFtp->Release();

	SysFreeString(bstrString);

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
STDMETHODIMP CFtpServPropPage::Apply(void)
{
	HRESULT	hr = S_OK;
	char	buffer[_MAX_PATH + 1];

	ATLTRACE(_T("CFtpServPropPage::Apply\n"));

	// Cycle throuh all objects
	for (UINT i = 0; i < m_nObjects; i++) {

		// Get IFtpServ interface of the object
		IFtpServ	*pFtp;
		m_ppUnk[i]->QueryInterface(IID_IFtpServ, (void**)&pFtp);

		// If the value of property was changed - apply it from
		// the property page to the object

		// Port number
		if(m_nDirtyFlags | PORT) {
			long lPort = GetDlgItemInt(IDC_PORT);
			if(ShowError(pFtp->put_Port(lPort)))
				hr = E_FAIL;
			}

		// Max. connections
		if(hr == S_OK && m_nDirtyFlags | MAX_CONNECTIONS) {
			long lMaxConn = GetDlgItemInt(IDC_MAX_CONNECTIONS);
			if(ShowError(pFtp->put_MaxConnections(lMaxConn)))
				hr = E_FAIL;
			}

        // Max. time outs
		if(hr == S_OK && m_nDirtyFlags | MAX_TIME_OUT) {
			long lMaxTimeOut = GetDlgItemInt(IDC_EDIT_MAX_TIME_OUT);
			if(ShowError(pFtp->put_MaxTimeOut(lMaxTimeOut)))
				hr = E_FAIL;
			}

		// Path
		if(hr == S_OK && m_nDirtyFlags | PATH) {
			GetDlgItemText(IDC_PATH, buffer, _MAX_PATH);
 			if(ShowError(pFtp->put_Path(_bstr_t(buffer))))
				hr = E_FAIL;
			}

		// Welcome message
		if(hr == S_OK && m_nDirtyFlags | WELCOME_MSG) {
			int		nSize	= SendDlgItemMessage(IDC_WELCOME, WM_GETTEXTLENGTH, 0, 0L);
			LPSTR	buf		= new char [nSize + 3];

			GetDlgItemText(IDC_WELCOME, buf, nSize + 1);
 			if(ShowError(pFtp->put_WelcomeMsg(_bstr_t(buf))))
				hr = E_FAIL;

			delete [] buf;
			}

		// Release IFtpServ interface
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
BOOL CFtpServPropPage::ShowError(HRESULT hResult) 
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