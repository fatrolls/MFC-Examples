//=================================================================
//  class: CMailServPropPage
//  File:  MailServPropPage.h
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

#ifndef __MAILSERVPROPPAGE_H_
#define __MAILSERVPROPPAGE_H_

#include "resource.h"       // main symbols

EXTERN_C const CLSID CLSID_MailServPropPage;

/////////////////////////////////////////////////////////////////////////////
// CMailServPropPage
class ATL_NO_VTABLE CMailServPropPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMailServPropPage, &CLSID_MailServPropPage>,
	public IPropertyPageImpl<CMailServPropPage>,
	public CDialogImpl<CMailServPropPage>
{
private:

	// Enumeration of property dialog controls
	typedef enum {
		ROOT_KEY				= 1			// Root registry key
	} DirtyObjects;

	int		m_nDirtyFlags;					// Dirty flag for each control

	void	InitializeControlsFromObject();	// Initialize property page controls from object data
	BOOL	ShowError(HRESULT hResult);		// Helper function for displaying error messages

public:
	CMailServPropPage() : m_nDirtyFlags(0)
	{
		m_dwTitleID = IDS_TITLEMailServPropPage;
		m_dwHelpFileID = IDS_HELPFILEMailServPropPage;
		m_dwDocStringID = IDS_DOCSTRINGMailServPropPage;
	}

	enum {IDD = IDD_MAILSERVPROPPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_MAILSERVPROPPAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMailServPropPage) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CMailServPropPage)
	CHAIN_MSG_MAP(IPropertyPageImpl<CMailServPropPage>)
	COMMAND_HANDLER(IDC_ROOT_KEY, EN_CHANGE, OnChangeRootKey)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	STDMETHOD(Apply)(void);

	// Receive time-out have been changed
	LRESULT OnChangeRootKey(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= ROOT_KEY;
		SetDirty( TRUE );
		return 0;
		}

	// Property dialog initialization
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		InitializeControlsFromObject();
		return 0;
		}
};

#endif //__MAILSERVPROPPAGE_H_
