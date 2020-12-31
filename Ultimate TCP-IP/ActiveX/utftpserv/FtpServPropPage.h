//=================================================================
//  class: CFtpServPropPage
//  File:  FtpServProp.h
//
//  HTTP Server ActiveX control property page
//
// =================================================================
// Ultimate TCP-IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// =================================================================

#ifndef __FtpServPROP_H_
#define __FtpServPROP_H_

#include "resource.h"       // main symbols

EXTERN_C const CLSID CLSID_FtpServProp;

/////////////////////////////////////////////////////////////////////////////
// CFtpServPropPage
class ATL_NO_VTABLE CFtpServPropPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFtpServPropPage, &CLSID_FtpServProp>,
	public IPropertyPageImpl<CFtpServPropPage>,
	public CDialogImpl<CFtpServPropPage>
{
private:

	// Enumeration of property dialog controls
	typedef enum {
		PATH				= 1,			// Root path
		MAX_CONNECTIONS		= 2,			// Maximum connections number
		PORT				= 4,			// Listening port number
		WELCOME_MSG			= 8,			// Server welcome message
        MAX_TIME_OUT		= 16			// Server maximum timeout
	} DirtyObjects;

	int		m_nDirtyFlags;					// Dirty flag for each control

	void	InitializeControlsFromObject();	// Initialize property page controls from object data
	BOOL	ShowError(HRESULT hResult);		// Helper function for displaying error messages

public:
	CFtpServPropPage() : m_nDirtyFlags(0)
	{
		m_dwTitleID = IDS_TITLEFtpServPropPage;
		m_dwHelpFileID = IDS_HELPFILEFtpServPropPage;
		m_dwDocStringID = IDS_DOCSTRINGFtpServPropPage;
	}

	enum {IDD = IDD_FTPSERVPROPPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_FTPSERVPROPPAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFtpServPropPage) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CFtpServPropPage)
	CHAIN_MSG_MAP(IPropertyPageImpl<CFtpServPropPage>)
	COMMAND_HANDLER(IDC_PORT, EN_CHANGE, OnChangePort)
	COMMAND_HANDLER(IDC_PATH, EN_CHANGE, OnChangePath)
	COMMAND_HANDLER(IDC_MAX_CONNECTIONS, EN_CHANGE, OnChangeMaxConn)
	COMMAND_HANDLER(IDC_WELCOME, EN_CHANGE, OnChangeWelcome)
    COMMAND_HANDLER(IDC_EDIT_MAX_TIME_OUT, EN_CHANGE, OnChangeMaxTimeOut)
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

	// Welcome message have been changed
	LRESULT OnChangeWelcome(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= WELCOME_MSG;
		SetDirty( TRUE );
		return 0;
		}

	// Max TimeOut have been changed
	LRESULT OnChangeMaxTimeOut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= MAX_TIME_OUT;
		SetDirty( TRUE );
		return 0;
		}

    // Property dialog initialization
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		InitializeControlsFromObject();
		return 0;
		}

};

#endif //__FtpServPROP_H_
