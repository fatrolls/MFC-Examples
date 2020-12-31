//=================================================================
//  class: CDNSPropPage
//  File:  DNSPropPage.cpp
//
//  DNS ActiveX control property page
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
#include "UTDns.h"
#include "DNSPropPage.h"

/////////////////////////////////////////////////////////////////////////////
// CDNSPropPage
/////////////////////////////////////////////////////////////////////////////

	
/***************************************************
InitializeControlsFromObject
	Initialize property page controls from object data
Params
    none
Return
	none
****************************************************/
void CDNSPropPage::InitializeControlsFromObject()
{
	LONG			nTimeOut		= 0;
	VARIANT_BOOL	bVariantBoool	= FALSE;

	// Get IDNS interface of the object
	IDNS	*pDNS;
	m_ppUnk[0]->QueryInterface(IID_IDNS, (void**)&pDNS);

	// Set connection time-out
	ShowError(pDNS->get_LookupTimeOut(&nTimeOut));
	SetDlgItemInt(IDC_EDIT_LOOKUP_TO, (int)nTimeOut);

	// Set blocking mode
	ShowError(pDNS->get_IncludeDefaultMX(&bVariantBoool));
	SendDlgItemMessage(IDC_INCL_DEF_MX, CB_SETCURSEL, (WPARAM)(bVariantBoool) ? 1 : 0);

	// Set blocking mode
	ShowError(pDNS->get_BlockingMode(&bVariantBoool));
	SendDlgItemMessage(IDC_BLOCKING_MODE, CB_SETCURSEL, (WPARAM)(bVariantBoool) ? 1 : 0);

	// Set protocol type
	ProtocolTypes	type;
	ShowError(pDNS->get_Protocol(&type));
	SendDlgItemMessage(IDC_PROTOCOL_TYPE, CB_SETCURSEL, (WPARAM)(type == ptUDP) ? 1 : 0);

	// Release IDNS interface
	pDNS->Release();

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
STDMETHODIMP CDNSPropPage::Apply(void)
{
	HRESULT	hr = S_OK;

	ATLTRACE(_T("CDNSProp::Apply\n"));

	// Cycle throuh all objects
	for (UINT i = 0; i < m_nObjects; i++) {

		// Get IDNS interface of the object
		IDNS	*pDNS;
		m_ppUnk[i]->QueryInterface(IID_IDNS, (void**)&pDNS);

		// If the value of property was changed - apply it from
		// the property page to the object

		// Connection time-out
		if(m_nDirtyFlags | LOOKUP_TIME_OUT) {
			int nTimeOut = GetDlgItemInt(IDC_EDIT_LOOKUP_TO);
			if(ShowError(pDNS->put_LookupTimeOut(nTimeOut)))
				hr = E_FAIL;
			}

		// Include default MX
		if(hr == S_OK && m_nDirtyFlags | INCLUDE_DEF_MX) {
			BOOL bIncludeDefMx = (BOOL)SendDlgItemMessage(IDC_INCL_DEF_MX, CB_GETCURSEL);
 			if(ShowError(pDNS->put_IncludeDefaultMX(bIncludeDefMx)))
				hr = E_FAIL;
			}

		// Blocking mode
		if(hr == S_OK && m_nDirtyFlags | BLOCKING_MODE) {
			BOOL bBlockingMode = (BOOL)SendDlgItemMessage(IDC_BLOCKING_MODE, CB_GETCURSEL);
 			if(ShowError(pDNS->put_BlockingMode(bBlockingMode)))
				hr = E_FAIL;
			}

		// Protocol type
		if(hr == S_OK && m_nDirtyFlags | PROTOCOL_TYPE) {
			int nProtocol = SendDlgItemMessage(IDC_PROTOCOL_TYPE, CB_GETCURSEL);
			if(ShowError(pDNS->put_Protocol((nProtocol == 0) ? ptTCP : ptUDP)))
				hr = E_FAIL;
			}

		// Release IDNS interface
		pDNS->Release();

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
BOOL CDNSPropPage::ShowError(HRESULT hResult) 
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