//=================================================================
//  class: CDNSPropPage
//  File:  DNSPropPage.h
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

#ifndef __DNSPROPPAGE_H_
#define __DNSPROPPAGE_H_

#include "resource.h"       // main symbols

EXTERN_C const CLSID CLSID_DNSPropPage;

/////////////////////////////////////////////////////////////////////////////
// CDNSPropPage
class ATL_NO_VTABLE CDNSPropPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDNSPropPage, &CLSID_DNSPropPage>,
	public IPropertyPageImpl<CDNSPropPage>,
	public CDialogImpl<CDNSPropPage>
{
private:

	// Enumeration of property dialog controls
	typedef enum {
		LOOKUP_TIME_OUT		= 1,			// Lookup time-out field
		INCLUDE_DEF_MX		= 2,			// If true, adds the entered domain as an MX record
		BLOCKING_MODE		= 4,			// Blocking mode field
		PROTOCOL_TYPE		= 8				// Protocol type field
	} DirtyObjects;

	int		m_nDirtyFlags;					// Dirty flag for each control

	void	InitializeControlsFromObject();	// Initialize property page controls from object data
	BOOL	ShowError(HRESULT hResult);		// Helper function for displaying error messages

public:
	CDNSPropPage()  : m_nDirtyFlags(0)
	{
		m_dwTitleID = IDS_TITLEDNSPropPage;
		m_dwHelpFileID = IDS_HELPFILEDNSPropPage;
		m_dwDocStringID = IDS_DOCSTRINGDNSPropPage;
	}

	enum {IDD = IDD_DNSPROPPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_DNSPROPPAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDNSPropPage) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CDNSPropPage)
	CHAIN_MSG_MAP(IPropertyPageImpl<CDNSPropPage>)
	COMMAND_HANDLER(IDC_EDIT_LOOKUP_TO, EN_CHANGE, OnChangeEditLookup_TO)
	COMMAND_HANDLER(IDC_INCL_DEF_MX, CBN_SELCHANGE, OnChangeIncludeDefMX)
	COMMAND_HANDLER(IDC_BLOCKING_MODE, CBN_SELCHANGE, OnChangeBlockingMode)
	COMMAND_HANDLER(IDC_PROTOCOL_TYPE, CBN_SELCHANGE, OnChangePtotocol)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	STDMETHOD(Apply)(void);

	// Lookup time-out have been changed
	LRESULT OnChangeEditLookup_TO(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= LOOKUP_TIME_OUT;
		SetDirty( TRUE );
		return 0;
		}

	// Include default MX have been changed
	LRESULT OnChangeIncludeDefMX(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= INCLUDE_DEF_MX;
		SetDirty( TRUE );
		return 0;
		}

	// Blocking mode have been changed
	LRESULT OnChangeBlockingMode(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= BLOCKING_MODE;
		SetDirty( TRUE );
		return 0;
		}

	// Protocol type have been changed
	LRESULT OnChangePtotocol(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= PROTOCOL_TYPE;
		SetDirty( TRUE );
		return 0;
		}

	// Property dialog initialization
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		SendDlgItemMessage(IDC_BLOCKING_MODE, CB_ADDSTRING , 0, (LPARAM)"FALSE");
		SendDlgItemMessage(IDC_BLOCKING_MODE, CB_ADDSTRING , 0, (LPARAM)"TRUE");

		SendDlgItemMessage(IDC_INCL_DEF_MX, CB_ADDSTRING , 0, (LPARAM)"FALSE");
		SendDlgItemMessage(IDC_INCL_DEF_MX, CB_ADDSTRING , 0, (LPARAM)"TRUE");

		SendDlgItemMessage(IDC_PROTOCOL_TYPE, CB_ADDSTRING , 0, (LPARAM)"TCP");
		SendDlgItemMessage(IDC_PROTOCOL_TYPE, CB_ADDSTRING , 0, (LPARAM)"UDP");
		
		InitializeControlsFromObject();
		return 0;
		}

};

#endif //__DNSPROPPAGE_H_
