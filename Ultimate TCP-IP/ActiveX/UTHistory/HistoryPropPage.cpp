//=================================================================
//  class: CHistoryPropPagePage
//  File:  HistoryPropPagePage.cpp
//
//  History ActiveX control property page
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
#include "UTHistory.h"
#include "HistoryPropPage.h"

/////////////////////////////////////////////////////////////////////////////
// CHistoryPropPagePage
/////////////////////////////////////////////////////////////////////////////

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

/***************************************************
InitializeControlsFromObject
	Initialize property page controls from object data
Params
    none
Return
	none
****************************************************/
void CHistoryPropPage::InitializeControlsFromObject()
{
	LONG			lValue			= 0;
	BSTR			bstrString		= SysAllocStringLen(NULL, TMP_BUFFER_SIZE);
	char			buffer[TMP_BUFFER_SIZE + 1]		= "";
	int				nItem			= 0;
	VARIANT_BOOL	bBOOL			= FALSE;

	// Get IHistory interface of the object
	IHistory	*pHistory;
	m_ppUnk[0]->QueryInterface(IID_IHistory, (void**)&pHistory);

	// Set margin
	ShowError(pHistory->get_Margin(&lValue));
	SetDlgItemInt(IDC_MARGIN, lValue);

	// Set max history length
	ShowError(pHistory->get_MaxHistoryLength(&lValue));
	SetDlgItemInt(IDC_HISTORY_LENGTH, lValue);

	// Set log file name
	ShowError(pHistory->get_LogName(&bstrString));
	SetDlgItemText(IDC_LOG_NAME, _bstr_t(bstrString));

	// Set time stamp format
	ShowError(pHistory->get_TimeStampFormat(&bstrString));
	SetDlgItemText(IDC_TIMESTAMP_FORMAT, _bstr_t(bstrString));

	// Set alignment
	AlignmentType Alignment;
	ShowError(pHistory->get_Alignment(&Alignment));
	_ltoa((long)Alignment, buffer, 10);
	nItem = SendDlgItemMessage(IDC_ALIGNMENT, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCSTR)buffer);
	SendDlgItemMessage(IDC_ALIGNMENT, CB_SETCURSEL, (WPARAM)nItem);

	// Set enable log flag
	ShowError(pHistory->get_EnableLog(&bBOOL));
	SendDlgItemMessage(IDC_ENABLE_LOG, BM_SETCHECK, (WPARAM)bBOOL);

	// Set time stamped log flag
	ShowError(pHistory->get_TimeStampedLog(&bBOOL));
	SendDlgItemMessage(IDC_TIME_LOG, BM_SETCHECK, (WPARAM)bBOOL);
	
	// Release IHistory interface
	pHistory->Release();

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
STDMETHODIMP CHistoryPropPage::Apply(void)
{
	HRESULT	hr = S_OK;

	ATLTRACE(_T("CHistoryPropPage::Apply\n"));

	// Cycle throuh all objects
	for (UINT i = 0; i < m_nObjects; i++) {
		char			buffer[TMP_BUFFER_SIZE + 1]		= "";
		VARIANT_BOOL	bBOOL							= FALSE;
		int				nItem							= 0;
		long			lValue							= 0;


		// Get IHistory interface of the object
		IHistory	*pHistory;
		m_ppUnk[i]->QueryInterface(IID_IHistory, (void**)&pHistory);

		// If the value of property was changed - apply it from
		// the property page to the object

		// Get margin
		if(m_nDirtyFlags | MARGIN) {
			lValue = (long)GetDlgItemInt(IDC_MARGIN);
			if(ShowError(pHistory->put_Margin(lValue)))
				hr = E_FAIL;
			}

		// Get max history length
		if(hr == S_OK && m_nDirtyFlags | MAX_HISTORY_LENGHT) {
			lValue = (long)GetDlgItemInt(IDC_HISTORY_LENGTH);
			if(ShowError(pHistory->put_MaxHistoryLength(lValue)))
				hr = E_FAIL;
			}

		// Get log file name
		if(hr == S_OK && m_nDirtyFlags | LOG_FILE_NAME) {
			GetDlgItemText(IDC_LOG_NAME, buffer, TMP_BUFFER_SIZE);
			if(ShowError(pHistory->put_LogName(_bstr_t(buffer))))
				hr = E_FAIL;
			}

		// Get time stamp format
		if(hr == S_OK && m_nDirtyFlags | TIME_STAMP_FORMAT) {
			GetDlgItemText(IDC_TIMESTAMP_FORMAT, buffer, TMP_BUFFER_SIZE);
			if(ShowError(pHistory->put_TimeStampFormat(_bstr_t(buffer))))
				hr = E_FAIL;
			}

		// Get alignment
		if(hr == S_OK && m_nDirtyFlags | ALIGNMENT) {
			nItem = SendDlgItemMessage(IDC_ALIGNMENT, CB_GETCURSEL);
			SendDlgItemMessage(IDC_ALIGNMENT, CB_GETLBTEXT, (WPARAM)nItem, (LPARAM)(LPCSTR)buffer);
 			if(ShowError(pHistory->put_Alignment((AlignmentType)atol(buffer))))
				hr = E_FAIL;
			}

		// Get enable log flag
		if(hr == S_OK && m_nDirtyFlags | LOG_ENABLED) {
			bBOOL = (SendDlgItemMessage(IDC_ENABLE_LOG, BM_GETCHECK, (WPARAM)0, (LPARAM)0) == BST_CHECKED) ? TRUE : FALSE;
			if(ShowError(pHistory->put_EnableLog(bBOOL)))
				hr = E_FAIL;
			}

		// Get time stamped log flag
		if(hr == S_OK && m_nDirtyFlags | TIME_STAMPED_LOG) {
			bBOOL = (SendDlgItemMessage(IDC_TIME_LOG, BM_GETCHECK, (WPARAM)0, (LPARAM)0) == BST_CHECKED) ? TRUE : FALSE;
			if(ShowError(pHistory->put_TimeStampedLog(bBOOL)))
				hr = E_FAIL;
			}


		// Release IHistory interface
		pHistory->Release();

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
BOOL CHistoryPropPage::ShowError(HRESULT hResult) 
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

#pragma warning (pop)