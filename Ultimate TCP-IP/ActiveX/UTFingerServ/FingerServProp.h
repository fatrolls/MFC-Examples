//=================================================================
//  class: CFingerServProp
//  File:  FingerServProp.h
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

#ifndef __FINGERSERVPROP_H_
#define __FINGERSERVPROP_H_

#include "resource.h"       // main symbols

EXTERN_C const CLSID CLSID_FingerServProp;

/////////////////////////////////////////////////////////////////////////////
// CFingerServProp
class ATL_NO_VTABLE CFingerServProp :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFingerServProp, &CLSID_FingerServProp>,
	public IPropertyPageImpl<CFingerServProp>,
	public CDialogImpl<CFingerServProp>
{
private:

	// Enumeration of property dialog controls
	typedef enum {
		PATH				= 1,			// Root path
		MAX_CONNECTIONS		= 2,			// Maximum connections number
		PORT				= 4				// Listening port number
	} DirtyObjects;

	int		m_nDirtyFlags;					// Dirty flag for each control

	void	InitializeControlsFromObject();	// Initialize property page controls from object data
	BOOL	ShowError(HRESULT hResult);		// Helper function for displaying error messages

public:
	CFingerServProp() : m_nDirtyFlags(0)
	{
		m_dwTitleID = IDS_TITLEFingerServProp;
		m_dwHelpFileID = IDS_HELPFILEFingerServProp;
		m_dwDocStringID = IDS_DOCSTRINGFingerServProp;
	}

	enum {IDD = IDD_FINGERSERVPROP};

DECLARE_REGISTRY_RESOURCEID(IDR_FINGERSERVPROP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFingerServProp) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CFingerServProp)
	CHAIN_MSG_MAP(IPropertyPageImpl<CFingerServProp>)
	COMMAND_HANDLER(IDC_PORT, EN_CHANGE, OnChangePort)
	COMMAND_HANDLER(IDC_PATH, EN_CHANGE, OnChangePath)
	COMMAND_HANDLER(IDC_MAX_CONNECTIONS, EN_CHANGE, OnChangeMaxConn)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	STDMETHOD(Apply)(void);

	// Connection time-out have been changed
	LRESULT OnChangePort(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= PORT;
		SetDirty( TRUE );
		return 0;
		}

	// Receive time-out have been changed
	LRESULT OnChangePath(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= PATH;
		SetDirty( TRUE );
		return 0;
		}

	// Blocking mode have been changed
	LRESULT OnChangeMaxConn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= MAX_CONNECTIONS;
		SetDirty( TRUE );
		return 0;
		}

	// Property dialog initialization
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		InitializeControlsFromObject();
		return 0;
		}

};

#endif //__FINGERSERVPROP_H_
