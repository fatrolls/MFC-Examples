//=================================================================
//  class: CFingerProp
//  File:  FingerProp.h
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

#ifndef __FINGERPROP_H_
#define __FINGERPROP_H_

#include "resource.h"       // main symbols

EXTERN_C const CLSID CLSID_FingerProp;

/////////////////////////////////////////////////////////////////////////////
// CFingerProp
class ATL_NO_VTABLE CFingerProp :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFingerProp, &CLSID_FingerProp>,
	public IPropertyPageImpl<CFingerProp>,
	public CDialogImpl<CFingerProp>
{
private:

	// Enumeration of property dialog controls
	typedef enum {
		CONNECT_TIME_OUT	= 1,			// Connection time-out field
		RECEIVE_TIME_OUT	= 2,			// Receive time-out field
		BLOCKING_MODE		= 4				// Blocking mode field
	} DirtyObjects;

	int		m_nDirtyFlags;					// Dirty flag for each control

	void	InitializeControlsFromObject();	// Initialize property page controls from object data
	BOOL	ShowError(HRESULT hResult);		// Helper function for displaying error messages

public:
	CFingerProp() : m_nDirtyFlags(0)
	{
		m_dwTitleID		= IDS_TITLEFingerProp;
		m_dwHelpFileID	= IDS_HELPFILEFingerProp;
		m_dwDocStringID = IDS_DOCSTRINGFingerProp;
	}

	enum {IDD = IDD_FINGERPROP};

DECLARE_REGISTRY_RESOURCEID(IDR_FINGERPROP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFingerProp) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CFingerProp)
	CHAIN_MSG_MAP(IPropertyPageImpl<CFingerProp>)
	COMMAND_HANDLER(IDC_EDITCONNECT_TO, EN_CHANGE, OnChangeEditconnect_to)
	COMMAND_HANDLER(IDC_RECEIVE_TO, EN_CHANGE, OnChangeReceive_to)
	COMMAND_HANDLER(IDC_BLOCKING_MODE, CBN_SELCHANGE, OnChangeBlockingMode)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	STDMETHOD(Apply)(void);

	// Connection time-out have been changed
	LRESULT OnChangeEditconnect_to(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= CONNECT_TIME_OUT;
		SetDirty( TRUE );
		return 0;
		}

	// Receive time-out have been changed
	LRESULT OnChangeReceive_to(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= RECEIVE_TIME_OUT;
		SetDirty( TRUE );
		return 0;
		}

	// Blocking mode have been changed
	LRESULT OnChangeBlockingMode(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= BLOCKING_MODE;
		SetDirty( TRUE );
		return 0;
		}

	// Property dialog initialization
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		SendDlgItemMessage(IDC_BLOCKING_MODE, CB_ADDSTRING , 0, (LPARAM)"FALSE");
		SendDlgItemMessage(IDC_BLOCKING_MODE, CB_ADDSTRING , 0, (LPARAM)"TRUE");
		InitializeControlsFromObject();
		return 0;
		}
};

#endif //__FINGERPROP_H_
