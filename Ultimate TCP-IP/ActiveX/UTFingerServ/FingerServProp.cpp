//=================================================================
//  class: CFingerServProp
//  File:  FingerServProp.cpp
//
//  Finger Server ActiveX control property page
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
#include "UTFingerServ.h"
#include "FingerServProp.h"

/////////////////////////////////////////////////////////////////////////////
// CFingerServProp
/////////////////////////////////////////////////////////////////////////////


/***************************************************
InitializeControlsFromObject
	Initialize property page controls from object data
Params
    none
Return
	none
****************************************************/
void CFingerServProp::InitializeControlsFromObject()
{
	LONG	lLong		= 0;
	BSTR	bstrString	= SysAllocStringLen(NULL, _MAX_PATH + 1);

	// Get IFingerServ interface of the object
	IFingerServ	*pFinger;
	m_ppUnk[0]->QueryInterface(IID_IFingerServ, (void**)&pFinger);

	// Set port number
	ShowError(pFinger->get_Port(&lLong));
	SetDlgItemInt(IDC_PORT, (int)lLong);

	// Set path
	ShowError(pFinger->get_Path(&bstrString));
	SetDlgItemText(IDC_PATH, _bstr_t(bstrString));

	// Set max. connections number
	ShowError(pFinger->get_MaxConnections(&lLong));
	SetDlgItemInt(IDC_MAX_CONNECTIONS, (int)lLong);

	// Release IFingerServ interface
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
STDMETHODIMP CFingerServProp::Apply(void)
{
	HRESULT	hr = S_OK;
	char	buffer[_MAX_PATH + 1];

	ATLTRACE(_T("CFingerServProp::Apply\n"));

	// Cycle throuh all objects
	for (UINT i = 0; i < m_nObjects; i++) {

		// Get IFingerServ interface of the object
		IFingerServ	*pFinger;
		m_ppUnk[i]->QueryInterface(IID_IFingerServ, (void**)&pFinger);

		// If the value of property was changed - apply it from
		// the property page to the object

		// Port number
		if(m_nDirtyFlags | PORT) {
			long lPort = GetDlgItemInt(IDC_PORT);
			if(ShowError(pFinger->put_Port(lPort)))
				hr = E_FAIL;
			}

		// Max. connections
		if(hr == S_OK && m_nDirtyFlags | MAX_CONNECTIONS) {
			long lMaxConn = GetDlgItemInt(IDC_MAX_CONNECTIONS);
			if(ShowError(pFinger->put_MaxConnections(lMaxConn)))
				hr = E_FAIL;
			}

		// Path
		if(hr == S_OK && m_nDirtyFlags | PATH) {
			GetDlgItemText(IDC_PATH, buffer, _MAX_PATH);
 			if(ShowError(pFinger->put_Path(_bstr_t(buffer))))
				hr = E_FAIL;
			}

		// Release IFingerServ interface
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
BOOL CFingerServProp::ShowError(HRESULT hResult) 
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