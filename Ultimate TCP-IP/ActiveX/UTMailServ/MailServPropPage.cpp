//=================================================================
//  class: CMailServPropPage
//  File:  MailServPropPage.cpp
//
//  Mail Server ActiveX control property page
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
#include "MailServPropPage.h"

/////////////////////////////////////////////////////////////////////////////
// CMailServPropPage
/////////////////////////////////////////////////////////////////////////////

/***************************************************
InitializeControlsFromObject
	Initialize property page controls from object data
Params
    none
Return
	none
****************************************************/
void CMailServPropPage::InitializeControlsFromObject()
{
	BSTR	bstrString	= SysAllocStringLen(NULL, _MAX_PATH + 1);

	// Get IMailServ interface of the object
	IMailServ	*pFinger;
	m_ppUnk[0]->QueryInterface(IID_IMailServ, (void**)&pFinger);

	// Set root key
	ShowError(pFinger->get_RegistryRootKey(&bstrString));
	SetDlgItemText(IDC_ROOT_KEY, _bstr_t(bstrString));

	// Release IMailServ interface
	pFinger->Release();

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
STDMETHODIMP CMailServPropPage::Apply(void)
{
	HRESULT	hr = S_OK;
	_TCHAR	buffer[_MAX_PATH*2 + 1];

	ATLTRACE(_T("CMailServPropPage::Apply\n"));

	// Cycle throuh all objects
	for (UINT i = 0; i < m_nObjects; i++) {

		// Get IMailServ interface of the object
		IMailServ	*pFinger;
		m_ppUnk[i]->QueryInterface(IID_IMailServ, (void**)&pFinger);

		// If the value of property was changed - apply it from
		// the property page to the object

		// Root key
		if(hr == S_OK && m_nDirtyFlags | ROOT_KEY) {
			GetDlgItemText(IDC_ROOT_KEY, buffer, _MAX_PATH*2);
 			if(ShowError(pFinger->put_RegistryRootKey(_bstr_t(buffer))))
				hr = E_FAIL;
			}

		// Release IMailServ interface
		pFinger->Release();

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
BOOL CMailServPropPage::ShowError(HRESULT hResult) 
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

