//=================================================================
//  class: CPingProp
//  File:  PingProp.cpp
//
//  Finger ActiveX control property page
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
#include "UTPing.h"
#include "PingProp.h"

/////////////////////////////////////////////////////////////////////////////
// CPingProp
/////////////////////////////////////////////////////////////////////////////
/***************************************************
InitializeControlsFromObject
	Initialize property page controls from object data
Params
    none
Return
	none
****************************************************/
void CPingProp::InitializeControlsFromObject()
{
	LONG			nTimeOut	= 0;
	VARIANT_BOOL	bBool       = FALSE;
    long            nLong;

	// Get IPing interface of the object
	IPing	*pPing;
	m_ppUnk[0]->QueryInterface(IID_IPing, (void**)&pPing);

	// Set blocking mode
	ShowError(pPing->get_BlockingMode(&bBool));
	SendDlgItemMessage(IDC_BLOCKING_MODE, CB_SETCURSEL, (WPARAM)(bBool) ? 1 : 0);

	// Set do lookup
	ShowError(pPing->get_DoLookup(&bBool));
	SendDlgItemMessage(IDC_DO_LOOKUP, CB_SETCURSEL, (WPARAM)(bBool) ? 1 : 0);

	ShowError(pPing->get_MaxTimeOuts(&nLong));
	SetDlgItemInt(IDC_EDIT_MAX_TIME_OUTS, (int)nLong);

    // Release IPing interface
	pPing->Release();

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
STDMETHODIMP CPingProp::Apply(void)
{
	HRESULT	hr = S_OK;

	ATLTRACE(_T("CPingProp::Apply\n"));

	// Cycle throuh all objects
	for (UINT i = 0; i < m_nObjects; i++) {

		// Get IPing interface of the object
		IPing	*pPing;
		m_ppUnk[i]->QueryInterface(IID_IPing, (void**)&pPing);

		// If the value of property was changed - apply it from
		// the property page to the object

		// Blocking mode
		if(hr == S_OK && m_nDirtyFlags | BLOCKING_MODE) {
			BOOL bBlockingMode = (BOOL)SendDlgItemMessage(IDC_BLOCKING_MODE, CB_GETCURSEL);
 			if(ShowError(pPing->put_BlockingMode(bBlockingMode)))
				hr = E_FAIL;
			}

		// Do lookup
		if(hr == S_OK && m_nDirtyFlags | DO_LOOKUP) {
			BOOL bDoLookup = (BOOL)SendDlgItemMessage(IDC_DO_LOOKUP, CB_GETCURSEL);
 			if(ShowError(pPing->put_DoLookup(bDoLookup)))
				hr = E_FAIL;
			}

        // Max Time outs
		if(hr == S_OK && m_nDirtyFlags | MAX_TIME_OUTS) {
			int nMaxTimeOuts = GetDlgItemInt(IDC_EDIT_MAX_TIME_OUTS);
			if(ShowError(pPing->put_MaxTimeOuts(nMaxTimeOuts)))
				hr = E_FAIL;
			}


		// Release IPing interface
		pPing->Release();

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
BOOL CPingProp::ShowError(HRESULT hResult) 
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
