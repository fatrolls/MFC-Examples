//=================================================================
//  class: CHistoryPropPage
//  File:  HistoryPropPage.h
//
//  History ActiveX control property page
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

#ifndef __HISTORYPROPPAGE_H_
#define __HISTORYPROPPAGE_H_

#include "resource.h"       // main symbols

#define		TMP_BUFFER_SIZE		256

EXTERN_C const CLSID CLSID_HistoryPropPage;

/////////////////////////////////////////////////////////////////////////////
// CHistoryPropPage
class ATL_NO_VTABLE CHistoryPropPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHistoryPropPage, &CLSID_HistoryPropPage>,
	public IPropertyPageImpl<CHistoryPropPage>,
	public CDialogImpl<CHistoryPropPage>
{
private:

	// Enumeration of property dialog controls
	typedef enum {
		LOG_FILE_NAME			= 1,			// Log file name field
		LOG_ENABLED				= 2,			// Log enabled field
		TIME_STAMPED_LOG		= 4,			// Time stamped log field
		ALIGNMENT				= 8,			// Alignment field
		MARGIN					= 16,			// Margin field
		TIME_STAMP_FORMAT		= 32,			// Time stamp format field
		MAX_HISTORY_LENGHT		= 64			// Max history length field
	} DirtyObjects;

	int		m_nDirtyFlags;					// Dirty flag for each control

	void	InitializeControlsFromObject();	// Initialize property page controls from object data
	BOOL	ShowError(HRESULT hResult);		// Helper function for displaying error messages

public:
	CHistoryPropPage() : m_nDirtyFlags(0)
	{
		m_dwTitleID = IDS_TITLEHistoryPropPage;
		m_dwHelpFileID = IDS_HELPFILEHistoryPropPage;
		m_dwDocStringID = IDS_DOCSTRINGHistoryPropPage;
	}

	enum {IDD = IDD_HISTORYPROPPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_HISTORYPROPPAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHistoryPropPage) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CHistoryPropPage)
	CHAIN_MSG_MAP(IPropertyPageImpl<CHistoryPropPage>)

	COMMAND_HANDLER(IDC_MARGIN, EN_CHANGE, OnChangeMargin)
	COMMAND_HANDLER(IDC_HISTORY_LENGTH, EN_CHANGE, OnChangeHistoryLenght)

	COMMAND_HANDLER(IDC_LOG_NAME, EN_CHANGE, OnChangeLogName)
	COMMAND_HANDLER(IDC_TIMESTAMP_FORMAT, EN_CHANGE, OnChangeTimeStampFormat)
	
	COMMAND_HANDLER(IDC_ALIGNMENT, CBN_SELCHANGE, OnChangeAligment)

	COMMAND_HANDLER(IDC_ENABLE_LOG, BN_CLICKED, OnChangeEnableLog)
	COMMAND_HANDLER(IDC_TIME_LOG, BN_CLICKED, OnChangeTimeLog)

	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	STDMETHOD(Apply)(void);

	// Margin have been changed
	LRESULT OnChangeMargin(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= MARGIN;
		SetDirty( TRUE );
		return 0;
		}

	// History length have been changed
	LRESULT OnChangeHistoryLenght(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= MAX_HISTORY_LENGHT;
		SetDirty( TRUE );
		return 0;
		}

	// Log file name have been changed
	LRESULT OnChangeLogName(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= LOG_FILE_NAME;
		SetDirty( TRUE );
		return 0;
		}

	// Time stamp format have been changed
	LRESULT OnChangeTimeStampFormat(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= TIME_STAMP_FORMAT;
		SetDirty( TRUE );
		return 0;
		}
	// Alignment have been changed
	LRESULT OnChangeAligment(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= ALIGNMENT;
		SetDirty( TRUE );
		return 0;
		}

	// Log enabled have been changed
	LRESULT OnChangeEnableLog(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= LOG_ENABLED;
		SetDirty( TRUE );
		return 0;
		}

	// Time stamped flag have been changed
	LRESULT OnChangeTimeLog(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		m_nDirtyFlags |= TIME_STAMPED_LOG;
		SetDirty( TRUE );
		return 0;
		}

	// Property dialog initialization
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		SendDlgItemMessage(IDC_ALIGNMENT, CB_ADDSTRING , 0, (LPARAM)"0 - Left");
		SendDlgItemMessage(IDC_ALIGNMENT, CB_ADDSTRING , 0, (LPARAM)"2 - Right");
		SendDlgItemMessage(IDC_ALIGNMENT, CB_ADDSTRING , 0, (LPARAM)"6 - Center");
		InitializeControlsFromObject();
		return 0;
		}
};

#endif //__HISTORYPROPPAGE_H_
