//=================================================================
//  class: CFingerProp
//  File:  FingerProp.cpp
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
#include "UTFinger.h"
#include "FingerProp.h"

/////////////////////////////////////////////////////////////////////////////
// CFingerProp class
/////////////////////////////////////////////////////////////////////////////

/***************************************************
InitializeControlsFromObject
	Initialize property page controls from object data
Params
    none
Return
	none
****************************************************/
void CFingerProp::InitializeControlsFromObject()
{
	LONG			nTimeOut		= 0;
	VARIANT_BOOL	bBlockingMode	= FALSE;

	// Get IFinger interface of the object
	IFinger	*pFinger;
	m_ppUnk[0]->QueryInterface(IID_IFinger, (void**)&pFinger);

	// Set connection time-out
	ShowError(pFinger->get_ConnectTimeOut(&nTimeOut));
	SetDlgItemInt(IDC_EDITCONNECT_TO, (int)nTimeOut);

	// Set receive time-out
	ShowError(pFinger->get_ReceiveTimeOut(&nTimeOut));
	SetDlgItemInt(IDC_RECEIVE_TO, (int)nTimeOut);

	// Set blocking mode
	ShowError(pFinger->get_BlockingMode(&bBlockingMode));
	SendDlgItemMessage(IDC_BLOCKING_MODE, CB_SETCURSEL, (WPARAM)(bBlockingMode) ? 1 : 0);

	// Release IFinger interface
	pFinger->Release();

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
STDMETHODIMP CFingerProp::Apply(void)
{
	HRESULT	hr = S_OK;

	ATLTRACE(_T("CFingerProp::Apply\n"));

	// Cycle throuh all objects
	for (UINT i = 0; i < m_nObjects; i++) {

		// Get IFinger interface of the object
		IFinger	*pFinger;
		m_ppUnk[i]->QueryInterface(IID_IFinger, (void**)&pFinger);

		// If the value of property was changed - apply it from
		// the property page to the object

		// Connection time-out
		if(m_nDirtyFlags | CONNECT_TIME_OUT) {
			int nTimeOut = GetDlgItemInt(IDC_EDITCONNECT_TO);
			if(ShowError(pFinger->put_ConnectTimeOut(nTimeOut)))
				hr = E_FAIL;
			}

		// Receive time-out
		if(hr == S_OK && m_nDirtyFlags | RECEIVE_TIME_OUT) {
			int nTimeOut = GetDlgItemInt(IDC_RECEIVE_TO);
			if(ShowError(pFinger->put_ReceiveTimeOut(nTimeOut)))
				hr = E_FAIL;
			}

		// Blocking mode
		if(hr == S_OK && m_nDirtyFlags | BLOCKING_MODE) {
			BOOL bBlockingMode = (BOOL)SendDlgItemMessage(IDC_BLOCKING_MODE, CB_GETCURSEL);
 			if(ShowError(pFinger->put_BlockingMode(bBlockingMode)))
				hr = E_FAIL;
			}

		// Release IFinger interface
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
BOOL CFingerProp::ShowError(HRESULT hResult) 
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