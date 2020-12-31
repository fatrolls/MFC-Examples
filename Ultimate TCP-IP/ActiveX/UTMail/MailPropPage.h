//=================================================================
//  class: CMailPropPage
//  File:  MailPropPage.h
//
//  Mail ActiveX control property page
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


#ifndef __MAILPROPPAGE_H_
#define __MAILPROPPAGE_H_

#include "resource.h"       // main symbols

EXTERN_C const CLSID CLSID_MailPropPage;

#define		TMP_BUFFER_SIZE		256

/////////////////////////////////////////////////////////////////////////////
// CMailPropPage
/////////////////////////////////////////////////////////////////////////////
class ATL_NO_VTABLE CMailPropPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMailPropPage, &CLSID_MailPropPage>,
	public IPropertyPageImpl<CMailPropPage>,
	public CDialogImpl<CMailPropPage>
{
private:

	// Enumeration of property dialog controls
	typedef enum {
		CONNECT_TIME_OUT	= 1,			// Connection time-out field
		BLOCKING_MODE		= 2,			// Blocking mode field
		RECEIVE_TIME_OUT	= 4,			// Receive time-out field
		MAIL_HOST_NAME		= 8,			// Mail Host Name mode field
		POP3_HOST_NAME		= 16,			// POP3 Host Name mode field
		USER_NAME			= 32,			// User name field
		PASSWORD			= 64,			// Password field
        LOCAL_HOST_NAME		= 128			// Local Host Name mode field
	} DirtyObjects;

	int		m_nDirtyFlags;					// Dirty flag for each control

	void	InitializeControlsFromObject();	// Initialize property page controls from object data
	BOOL	ShowError(HRESULT hResult);		// Helper function for displaying error messages

public:
	CMailPropPage()  : m_nDirtyFlags(0)
	{
		m_dwTitleID = IDS_TITLEMailPropPage;
		m_dwHelpFileID = IDS_HELPFILEMailPropPage;
		m_dwDocStringID = IDS_DOCSTRINGMailPropPage;
	}

	enum {IDD = IDD_MAILPROPPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_MAILPROPPAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMailPropPage) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CMailPropPage)
	CHAIN_MSG_MAP(IPropertyPageImpl<CMailPropPage>)
	COMMAND_HANDLER(IDC_EDITCONNECT_TO, EN_CHANGE, OnChangeEditconnect_to)
	COMMAND_HANDLER(IDC_BLOCKING_MODE, CBN_SELCHANGE, OnChangeBlockingMode)
	COMMAND_HANDLER(IDC_RECEIVE_TIME_OUT, EN_CHANGE, OnChangeReceiveTimeOut)
	COMMAND_HANDLER(IDC_MAIL_HOST_NAME, EN_CHANGE, OnChangeMailHostName)
    COMMAND_HANDLER(IDC_LOCAL_HOST_NAME, EN_CHANGE, OnChangeLocalHostName)
    COMMAND_HANDLER(IDC_POP3_HOST_NAME, EN_CHANGE, OnChangePOP3HostName)
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

	// Mail Host name have been changed
	LRESULT OnChangeMailHostName(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= MAIL_HOST_NAME;
		SetDirty( TRUE );
		return 0;
		}

	// Local Host name have been changed
	LRESULT OnChangeLocalHostName(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= LOCAL_HOST_NAME;
		SetDirty( TRUE );
		return 0;
		}

    // POP3 Host name have been changed
	LRESULT OnChangePOP3HostName(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= POP3_HOST_NAME;
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

#endif //__MAILPROPPAGE_H_
