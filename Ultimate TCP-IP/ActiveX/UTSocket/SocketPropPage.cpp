//=================================================================
//  class: CSocketPropPage
//  File:  SocketPropPage.cpp
//
//  Socket ActiveX control property page
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
#include "UTSocket.h"
#include "SocketPropPage.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

/////////////////////////////////////////////////////////////////////////////
// CSocketPropPage
/////////////////////////////////////////////////////////////////////////////

/***************************************************
InitializeControlsFromObject
	Initialize property page controls from object data
Params
    none
Return
	none
****************************************************/
void CSocketPropPage::InitializeControlsFromObject()
{
	LONG			lValue		= 0;
	VARIANT_BOOL	bBOOL		= FALSE;
	int				nItem		= 0;
	char			buffer[100] = "";

	// Get ISocket interface of the object
	ISocket	*pSocket;
	m_ppUnk[0]->QueryInterface(IID_ISocket, (void**)&pSocket);

	// Set connection time-out
	ShowError(pSocket->get_ConnectTimeOut(&lValue));
	SetDlgItemInt(IDC_CONNECT_TIME_OUT, lValue);

	// Set blocking mode
	ShowError(pSocket->get_BlockingMode(&bBOOL));
	SendDlgItemMessage(IDC_BLOCKING_MODE, CB_SETCURSEL, (WPARAM)(bBOOL) ? 1 : 0);

	// Set receive time out
	ShowError(pSocket->get_ReceiveTimeOut(&lValue));
	SetDlgItemInt(IDC_RECEIVE_TIME_OUT, lValue);

	// Set send time out
	ShowError(pSocket->get_SendTimeOut(&lValue));
	SetDlgItemInt(IDC_SEND_TIME_OUT, lValue);

	// Set Protocol
	SocketProtocol Protocol;
	ShowError(pSocket->get_Protocol(&Protocol));
	_ltoa((long)Protocol, buffer, 10);
	nItem = SendDlgItemMessage(IDC_PROTOCOL, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCSTR)buffer);
	SendDlgItemMessage(IDC_PROTOCOL, CB_SETCURSEL, (WPARAM)nItem);

	// Set Type
	SocketType Type;
	ShowError(pSocket->get_Type(&Type));
	_ltoa((long)Type, buffer, 10);
	nItem = SendDlgItemMessage(IDC_TYPE, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCSTR)buffer);
	SendDlgItemMessage(IDC_TYPE, CB_SETCURSEL, (WPARAM)nItem);

	// Set Family
	SocketFamily Family;
	ShowError(pSocket->get_Family(&Family));
	_ltoa(Family, buffer, 10);
	nItem = SendDlgItemMessage(IDC_FAMILY, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCSTR)buffer);
	SendDlgItemMessage(IDC_FAMILY, CB_SETCURSEL, (WPARAM)nItem);

	// Release ISocket interface
	pSocket->Release();

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
STDMETHODIMP CSocketPropPage::Apply(void)
{
	HRESULT	hr			= S_OK;
	int		nItem		= 0;
	char	buffer[100] = "";

	ATLTRACE(_T("CSocketPropPage::Apply\n"));

	// Cycle throuh all objects
	for (UINT i = 0; i < m_nObjects; i++) {

		// Get ISocket interface of the object
		ISocket	*pSocket;
		m_ppUnk[i]->QueryInterface(IID_ISocket, (void**)&pSocket);

		// If the value of property was changed - apply it from
		// the property page to the object

		// Connection time-out
		if(m_nDirtyFlags | CONNECT_TIME_OUT) {
			int nTimeOut = GetDlgItemInt(IDC_CONNECT_TIME_OUT);
			if(ShowError(pSocket->put_ConnectTimeOut(nTimeOut)))
				hr = E_FAIL;
			}

		// Blocking mode
		if(hr == S_OK && m_nDirtyFlags | BLOCKING_MODE) {
			BOOL bBlockingMode = (BOOL)SendDlgItemMessage(IDC_BLOCKING_MODE, CB_GETCURSEL);
 			if(ShowError(pSocket->put_BlockingMode(bBlockingMode)))
				hr = E_FAIL;
			}

		// Receive time out
		if(hr == S_OK && m_nDirtyFlags | RECEIVE_TIME_OUT) {
			int nTimeOut = GetDlgItemInt(IDC_RECEIVE_TIME_OUT);
			if(ShowError(pSocket->put_ReceiveTimeOut(nTimeOut)))
				hr = E_FAIL;
			}

		// Send time out
		if(hr == S_OK && m_nDirtyFlags | SEND_TIME_OUT) {
			int nTimeOut = GetDlgItemInt(IDC_SEND_TIME_OUT);
			if(ShowError(pSocket->put_SendTimeOut(nTimeOut)))
				hr = E_FAIL;
			}

		// Socket type
		if(hr == S_OK && m_nDirtyFlags | SOCKET_TYPE) {
			nItem = SendDlgItemMessage(IDC_TYPE, CB_GETCURSEL);
			SendDlgItemMessage(IDC_TYPE, CB_GETLBTEXT, (WPARAM)nItem, (LPARAM)(LPCSTR)buffer);
 			if(ShowError(pSocket->put_Type((SocketType)atol(buffer))))
				hr = E_FAIL;
			}

		// Socket protocol
		if(hr == S_OK && m_nDirtyFlags | SOCKET_PROTOCOL) {
			nItem = SendDlgItemMessage(IDC_PROTOCOL, CB_GETCURSEL);
			SendDlgItemMessage(IDC_PROTOCOL, CB_GETLBTEXT, (WPARAM)nItem, (LPARAM)(LPCSTR)buffer);
 			if(ShowError(pSocket->put_Protocol((SocketProtocol)atol(buffer))))
				hr = E_FAIL;
			}

		// Socket family
		if(hr == S_OK && m_nDirtyFlags | SOCKET_FAMILY) {
			nItem = SendDlgItemMessage(IDC_FAMILY, CB_GETCURSEL);
			SendDlgItemMessage(IDC_FAMILY, CB_GETLBTEXT, (WPARAM)nItem, (LPARAM)(LPCSTR)buffer);
 			if(ShowError(pSocket->put_Family((SocketFamily)atol(buffer))))
				hr = E_FAIL;
			}

		// Release ISocket interface
		pSocket->Release();

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
BOOL CSocketPropPage::ShowError(HRESULT hResult) 
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
