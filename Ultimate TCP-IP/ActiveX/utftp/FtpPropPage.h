//=================================================================
//  class: CFtpPropPage
//  File:  FtpPropPage.h
//
//  Ftp ActiveX control property page
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

#ifndef __FTPPROPPAGE_H_
#define __FTPPROPPAGE_H_

#include "resource.h"       // main symbols

#define		TMP_BUFFER_SIZE		256

EXTERN_C const CLSID CLSID_FtpPropPage;

/////////////////////////////////////////////////////////////////////////////
// CFtpPropPage
class ATL_NO_VTABLE CFtpPropPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFtpPropPage, &CLSID_FtpPropPage>,
	public IPropertyPageImpl<CFtpPropPage>,
	public CDialogImpl<CFtpPropPage>
{
private:

	// Enumeration of property dialog controls
	typedef enum {
		CONNECT_TIME_OUT	= 1,			// Connection time-out field
		BLOCKING_MODE		= 2,			// Blocking mode field
		FIRE_WALL_MODE		= 4,			// Fire Wall mode field
		HOST_NAME			= 8,			// Host Name mode field
		ACCOUNT				= 16,			// Account field
		USER_NAME			= 32,			// User name field
		PASSWORD			= 64			// Password field
	} DirtyObjects;

	int		m_nDirtyFlags;					// Dirty flag for each control

	void	InitializeControlsFromObject();	// Initialize property page controls from object data
	BOOL	ShowError(HRESULT hResult);		// Helper function for displaying error messages

public:
	CFtpPropPage() : m_nDirtyFlags(0)
	{
		m_dwTitleID = IDS_TITLEFtpPropPage;
		m_dwHelpFileID = IDS_HELPFILEFtpPropPage;
		m_dwDocStringID = IDS_DOCSTRINGFtpPropPage;
	}

	enum {IDD = IDD_FTPPROPPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_FTPPROPPAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFtpPropPage) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CFtpPropPage)
	CHAIN_MSG_MAP(IPropertyPageImpl<CFtpPropPage>)
	COMMAND_HANDLER(IDC_EDITCONNECT_TO, EN_CHANGE, OnChangeEditconnect_to)
	COMMAND_HANDLER(IDC_BLOCKING_MODE, CBN_SELCHANGE, OnChangeBlockingMode)
	COMMAND_HANDLER(IDC_FIRE_WALL_MODE, CBN_SELCHANGE, OnChangeFireWallMode)
	COMMAND_HANDLER(IDC_HOST_NAME, EN_CHANGE, OnChangeHostName)
	COMMAND_HANDLER(IDC_ACCOUNT, EN_CHANGE, OnChangeAccount)
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

	// Fire wall mode have been changed
	LRESULT OnChangeFireWallMode(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= FIRE_WALL_MODE;
		SetDirty( TRUE );
		return 0;
		}

	// Host name have been changed
	LRESULT OnChangeHostName(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= HOST_NAME;
		SetDirty( TRUE );
		return 0;
		}

	// Account have been changed
	LRESULT OnChangeAccount(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= ACCOUNT;
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
		SendDlgItemMessage(IDC_FIRE_WALL_MODE, CB_ADDSTRING , 0, (LPARAM)"FALSE");
		SendDlgItemMessage(IDC_FIRE_WALL_MODE, CB_ADDSTRING , 0, (LPARAM)"TRUE");
		InitializeControlsFromObject();
		return 0;
		}

};

#endif //__FTPPROPPAGE_H_
