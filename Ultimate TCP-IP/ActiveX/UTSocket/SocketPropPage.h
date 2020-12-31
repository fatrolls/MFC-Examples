//=================================================================
//  class: CSocketPropPage
//  File:  SocketPropPage.h
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

#ifndef __SOCKETPROPPAGE_H_
#define __SOCKETPROPPAGE_H_

#include "resource.h"       // main symbols

#define		TMP_BUFFER_SIZE		256

EXTERN_C const CLSID CLSID_SocketPropPage;

/////////////////////////////////////////////////////////////////////////////
// CSocketPropPage
class ATL_NO_VTABLE CSocketPropPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSocketPropPage, &CLSID_SocketPropPage>,
	public IPropertyPageImpl<CSocketPropPage>,
	public CDialogImpl<CSocketPropPage>
{
private:

	// Enumeration of property dialog controls
	typedef enum {
		CONNECT_TIME_OUT	= 1,			// Connection time-out field
		BLOCKING_MODE		= 2,			// Blocking mode field
		RECEIVE_TIME_OUT	= 4,			// Receive time-out field
		SEND_TIME_OUT		= 8,			// Send time-out field
		SOCKET_TYPE			= 16,			// Socket type
		SOCKET_FAMILY		= 32,			// Socket family
		SOCKET_PROTOCOL		= 64			// Socket protocol
	} DirtyObjects;

	int		m_nDirtyFlags;					// Dirty flag for each control

	void	InitializeControlsFromObject();	// Initialize property page controls from object data
	BOOL	ShowError(HRESULT hResult);		// Helper function for displaying error messages

public:
	CSocketPropPage()  : m_nDirtyFlags(0)
	{
		m_dwTitleID = IDS_TITLESocketPropPage;
		m_dwHelpFileID = IDS_HELPFILESocketPropPage;
		m_dwDocStringID = IDS_DOCSTRINGSocketPropPage;
	}

	enum {IDD = IDD_SOCKETPROPPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_SOCKETPROPPAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSocketPropPage) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CSocketPropPage)
	CHAIN_MSG_MAP(IPropertyPageImpl<CSocketPropPage>)
	COMMAND_HANDLER(IDC_CONNECT_TIME_OUT, EN_CHANGE, OnChangeConnectTimeOut)
	COMMAND_HANDLER(IDC_BLOCKING_MODE, CBN_SELCHANGE, OnChangeBlockingMode)
	COMMAND_HANDLER(IDC_RECEIVE_TIME_OUT, EN_CHANGE, OnChangeReceiveTimeOut)
	COMMAND_HANDLER(IDC_SEND_TIME_OUT, EN_CHANGE, OnChangeSendTimeOut)
	COMMAND_HANDLER(IDC_TYPE, CBN_SELCHANGE, OnChangeType)
	COMMAND_HANDLER(IDC_FAMILY, CBN_SELCHANGE, OnChangeFamily)
	COMMAND_HANDLER(IDC_PROTOCOL, CBN_SELCHANGE, OnChangeProtocol)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	STDMETHOD(Apply)(void);

	// Connection time-out have been changed
	LRESULT OnChangeConnectTimeOut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
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

	// Send time-out have been changed
	LRESULT OnChangeSendTimeOut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= SEND_TIME_OUT;
		SetDirty( TRUE );
		return 0;
		}

	// Socket type have been changed
	LRESULT OnChangeType(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= SOCKET_TYPE;
		SetDirty( TRUE );
		return 0;
		}

	// Socket family have been changed
	LRESULT OnChangeFamily(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= SOCKET_FAMILY;
		SetDirty( TRUE );
		return 0;
		}

	// Socket protocol have been changed
	LRESULT OnChangeProtocol(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= SOCKET_PROTOCOL;
		SetDirty( TRUE );
		return 0;
		}


	// Property dialog initialization
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		SendDlgItemMessage(IDC_BLOCKING_MODE, CB_ADDSTRING , 0, (LPARAM)"FALSE");
		SendDlgItemMessage(IDC_BLOCKING_MODE, CB_ADDSTRING , 0, (LPARAM)"TRUE");

		SendDlgItemMessage(IDC_TYPE, CB_ADDSTRING , 0, (LPARAM)"1 - TCP");
		SendDlgItemMessage(IDC_TYPE, CB_ADDSTRING , 0, (LPARAM)"2 - UDP");

		SendDlgItemMessage(IDC_PROTOCOL, CB_ADDSTRING , 0, (LPARAM)"0  - IP");
		SendDlgItemMessage(IDC_PROTOCOL, CB_ADDSTRING , 0, (LPARAM)"1  - ICMP");
		SendDlgItemMessage(IDC_PROTOCOL, CB_ADDSTRING , 0, (LPARAM)"2  - IGMP");
		SendDlgItemMessage(IDC_PROTOCOL, CB_ADDSTRING , 0, (LPARAM)"3  - IGGP");
		SendDlgItemMessage(IDC_PROTOCOL, CB_ADDSTRING , 0, (LPARAM)"6  - TCP");
		SendDlgItemMessage(IDC_PROTOCOL, CB_ADDSTRING , 0, (LPARAM)"12 - PUP");
		SendDlgItemMessage(IDC_PROTOCOL, CB_ADDSTRING , 0, (LPARAM)"17 - UDP");
		SendDlgItemMessage(IDC_PROTOCOL, CB_ADDSTRING , 0, (LPARAM)"22 - IDP");
		SendDlgItemMessage(IDC_PROTOCOL, CB_ADDSTRING , 0, (LPARAM)"77 - ND");

		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"1  - UNIX");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"2  - INET");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"3  - IMPLINK");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"4  - PUP");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"5  - CHAOS");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"6  - NS");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"6  - IPX");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"7  - ISO");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"7  - OSI");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"8  - ECMA");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"9  - DATAKIT");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"10 - CCITT");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"11 - SNA");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"12 - DECNET");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"13 - DLI");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"14 - LAT");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"15 - HYLINK");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"16 - APPLETALK");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"17 - NETBIOS");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"18 - VOICEVIEW");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"19 - FIREFOX");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"20 - UNKNOWN1");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"21 - BAN");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"22 - ATM");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"23 - INET6");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"24 - CLUSTER");
		SendDlgItemMessage(IDC_FAMILY, CB_ADDSTRING , 0, (LPARAM)"25 - IEEE 12844");

		InitializeControlsFromObject();
		return 0;
		}
};

#endif //__SOCKETPROPPAGE_H_
