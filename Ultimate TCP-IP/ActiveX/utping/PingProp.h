//=================================================================
//  class: CPingProp
//  File:  PingProp.h
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

#ifndef __PINGPROP_H_
#define __PINGPROP_H_

#include "resource.h"       // main symbols

EXTERN_C const CLSID CLSID_PingProp;

/////////////////////////////////////////////////////////////////////////////
// CPingProp
class ATL_NO_VTABLE CPingProp :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPingProp, &CLSID_PingProp>,
	public IPropertyPageImpl<CPingProp>,
	public CDialogImpl<CPingProp>
{
private:

	// Enumeration of property dialog controls
	typedef enum {
		BLOCKING_MODE		= 1,			// Blocking mode field
        DO_LOOKUP   		= 2,			// Do lookup field
        MAX_TIME_OUTS		= 4				// Max Time outs field
	} DirtyObjects;

	int		m_nDirtyFlags;					// Dirty flag for each control

	void	InitializeControlsFromObject();	// Initialize property page controls from object data
	BOOL	ShowError(HRESULT hResult);		// Helper function for displaying error messages

public:
	CPingProp()  : m_nDirtyFlags(0)
	{
		m_dwTitleID = IDS_TITLEPingProp;
		m_dwHelpFileID = IDS_HELPFILEPingProp;
		m_dwDocStringID = IDS_DOCSTRINGPingProp;
	}

	enum {IDD = IDD_PINGPROP};

DECLARE_REGISTRY_RESOURCEID(IDR_PINGPROP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPingProp) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CPingProp)
	CHAIN_MSG_MAP(IPropertyPageImpl<CPingProp>)
	COMMAND_HANDLER(IDC_BLOCKING_MODE, CBN_SELCHANGE, OnChangeBlockingMode)
    COMMAND_HANDLER(IDC_DO_LOOKUP, CBN_SELCHANGE, OnChangeDoLookup)
    COMMAND_HANDLER(IDC_EDIT_MAX_TIME_OUTS, EN_CHANGE, OnChangeMaxTimeOuts)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	STDMETHOD(Apply)(void);

	// Blocking mode have been changed
	LRESULT OnChangeBlockingMode(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= BLOCKING_MODE;
		SetDirty( TRUE );
		return 0;
		}

    // Do lookup have been changed
	LRESULT OnChangeDoLookup(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= DO_LOOKUP;
		SetDirty( TRUE );
		return 0;
		}
    
    // Max time outs have been changed
	LRESULT OnChangeMaxTimeOuts(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= MAX_TIME_OUTS;
		SetDirty( TRUE );
		return 0;
		}

	// Property dialog initialization
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		SendDlgItemMessage(IDC_BLOCKING_MODE, CB_ADDSTRING , 0, (LPARAM)"FALSE");
		SendDlgItemMessage(IDC_BLOCKING_MODE, CB_ADDSTRING , 0, (LPARAM)"TRUE");
		SendDlgItemMessage(IDC_DO_LOOKUP, CB_ADDSTRING , 0, (LPARAM)"FALSE");
		SendDlgItemMessage(IDC_DO_LOOKUP, CB_ADDSTRING , 0, (LPARAM)"TRUE");
		InitializeControlsFromObject();
		return 0;
		}

};

#endif //__PINGPROP_H_
