//=================================================================
//  class: CIMAP4PropPage
//  File:  IMAP4PropPage.h
//
//  IMAP4 ActiveX control property page
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


#ifndef __IMAP4PROPPAGE_H_
#define __IMAP4PROPPAGE_H_

#include "resource.h"       // main symbols

EXTERN_C const CLSID CLSID_IMAP4PropPage;

#define		TMP_BUFFER_SIZE		256

/////////////////////////////////////////////////////////////////////////////
// CIMAP4PropPage
class ATL_NO_VTABLE CIMAP4PropPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIMAP4PropPage, &CLSID_IMAP4PropPage>,
	public IPropertyPageImpl<CIMAP4PropPage>,
	public CDialogImpl<CIMAP4PropPage>
{
private:

	// Enumeration of property dialog controls
	typedef enum {
		CONNECT_TIME_OUT	    = 1,			// Connection time-out field
		BLOCKING_MODE		    = 2,			// Blocking mode field
		RECEIVE_TIME_OUT	    = 4,			// Receive time-out field
		HOST_NAME		        = 8,			// IMAP4 Host Name mode field
		NEW_MAIL_CHECK_INTERVAL	= 16,			// New mail check interval
		USER_NAME			    = 32,			// User name field
		PASSWORD			    = 64			// Password field
	} DirtyObjects;

	int		m_nDirtyFlags;					// Dirty flag for each control

	void	InitializeControlsFromObject();	// Initialize property page controls from object data
	BOOL	ShowError(HRESULT hResult);		// Helper function for displaying error messages

public:
	CIMAP4PropPage() : m_nDirtyFlags(0)
	{
		m_dwTitleID = IDS_TITLEIMAP4PropPage;
		m_dwHelpFileID = IDS_HELPFILEIMAP4PropPage;
		m_dwDocStringID = IDS_DOCSTRINGIMAP4PropPage;
	}

	enum {IDD = IDD_IMAP4PROPPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_IMAP4PROPPAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CIMAP4PropPage) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CIMAP4PropPage)
	CHAIN_MSG_MAP(IPropertyPageImpl<CIMAP4PropPage>)
	COMMAND_HANDLER(IDC_EDITCONNECT_TO, EN_CHANGE, OnChangeEditconnect_to)
	COMMAND_HANDLER(IDC_BLOCKING_MODE, CBN_SELCHANGE, OnChangeBlockingMode)
	COMMAND_HANDLER(IDC_RECEIVE_TIME_OUT, EN_CHANGE, OnChangeReceiveTimeOut)
	COMMAND_HANDLER(IDC_HOST_NAME, EN_CHANGE, OnChangeIMAP4HostName)
	COMMAND_HANDLER(IDC_NEW_MAIL_INTERVAL, EN_CHANGE, OnChangeNewMailInterval)
	COMMAND_HANDLER(IDC_USER_NAME, EN_CHANGE, OnChangeUserName)
	COMMAND_HANDLER(IDC_PASSWORD, EN_CHANGE, OnChangePassword)
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

	// Blocking mode have been changed
	LRESULT OnChangeBlockingMode(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= BLOCKING_MODE;
		SetDirty( TRUE );
		return 0;
		}

	// Receive time-out have been changed
	LRESULT OnChangeReceiveTimeOut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= RECEIVE_TIME_OUT;
		SetDirty( TRUE );
		return 0;
		}

	// Host name have been changed
	LRESULT OnChangeIMAP4HostName(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= HOST_NAME;
		SetDirty( TRUE );
		return 0;
		}

	// New IMAP4 check interval have been changed
	LRESULT OnChangeNewMailInterval(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= NEW_MAIL_CHECK_INTERVAL;
		SetDirty( TRUE );
		return 0;
		}

	// User name have been changed
	LRESULT OnChangeUserName(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= USER_NAME;
		SetDirty( TRUE );
		return 0;
		}

	// Password have been changed
	LRESULT OnChangePassword(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= PASSWORD;
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

#endif //__IMAP4PROPPAGE_H_
