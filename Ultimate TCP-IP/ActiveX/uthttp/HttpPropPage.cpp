//=================================================================
//  class: CHttpPropPagePage
//  File:  HttpPropPage.cpp
//
//  Http ActiveX control property page
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
#include "HttpPropPage.h"

/////////////////////////////////////////////////////////////////////////////
// CHttpPropPagePage
/////////////////////////////////////////////////////////////////////////////

/***************************************************
InitializeControlsFromObject
	Initialize property page controls from object data
Params
    none
Return
	none
****************************************************/
void CHttpPropPage::InitializeControlsFromObject()
{
	LONG			nLong			= 0;
	VARIANT_BOOL	bBlockingMode	= FALSE;

	// Get IHttp interface of the object
	IHttp	*pHttp;
	m_ppUnk[0]->QueryInterface(IID_IHttp, (void**)&pHttp);

	// Set connection time-out
	ShowError(pHttp->get_ConnectTimeOut(&nLong));
	SetDlgItemInt(IDC_EDITCONNECT_TO, (int)nLong);

	// Set max. lines to store
	ShowError(pHttp->get_MaxLinesToStore(&nLong));
	SetDlgItemInt(IDC_MAX_LINES_TO_STORE, (int)nLong);

	// Set blocking mode
	ShowError(pHttp->get_BlockingMode(&bBlockingMode));
	SendDlgItemMessage(IDC_BLOCKING_MODE, CB_SETCURSEL, (WPARAM)(bBlockingMode) ? 1 : 0);

	// Set Proxy server name
	BSTR	bstrProxyName = SysAllocStringLen(NULL, 100);
	ShowError(pHttp->get_ProxyServer(&bstrProxyName));
	SetDlgItemText(IDC_PROXY_NAME, _bstr_t(bstrProxyName));

	// Release IHttp interface
	pHttp->Release();

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
STDMETHODIMP CHttpPropPage::Apply(void)
{
	HRESULT	hr = S_OK;

	ATLTRACE(_T("CHttpPropPage::Apply\n"));

	// Cycle throuh all objects
	for (UINT i = 0; i < m_nObjects; i++) {

		// Get IHttp interface of the object
		IHttp	*pHttp;
		m_ppUnk[i]->QueryInterface(IID_IHttp, (void**)&pHttp);

		// If the value of property was changed - apply it from
		// the property page to the object

		// Connection time-out
		if(m_nDirtyFlags | CONNECT_TIME_OUT) {
			int nTimeOut = GetDlgItemInt(IDC_EDITCONNECT_TO);
			if(ShowError(pHttp->put_ConnectTimeOut(nTimeOut)))
				hr = E_FAIL;
			}

		// Max Lines to receive
		if(hr == S_OK && m_nDirtyFlags | MAX_LINES_TO_RECEIVE) {
			int nMaxLines = GetDlgItemInt(IDC_MAX_LINES_TO_STORE);
			if(ShowError(pHttp->put_MaxLinesToStore(nMaxLines)))
				hr = E_FAIL;
			}

		// Blocking mode
		if(hr == S_OK && m_nDirtyFlags | BLOCKING_MODE) {
			BOOL bBlockingMode = (BOOL)SendDlgItemMessage(IDC_BLOCKING_MODE, CB_GETCURSEL);
 			if(ShowError(pHttp->put_BlockingMode(bBlockingMode)))
				hr = E_FAIL;
			}

		// Proxy server name
		if(hr == S_OK && m_nDirtyFlags | PROXY_SERVER) {
			char	buffer[100];
			GetDlgItemText(IDC_PROXY_NAME, buffer, sizeof(buffer)-1);
			_bstr_t	bstrProxyName = buffer;
 			if(ShowError(pHttp->put_ProxyServer(bstrProxyName)))
				hr = E_FAIL;
			}

		// Release IHttp interface
		pHttp->Release();

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
BOOL CHttpPropPage::ShowError(HRESULT hResult) 
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
