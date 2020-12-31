// RegistryDemoDlg.h : header file
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

/////////////////////////////////////////////////////////////////////////////
// CRegistryDemoDlg dialog
#include "OXRegistryItem.h"

class CRegistryDemoDlg : public CDialog
{
// Construction
public:
	CRegistryDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRegistryDemoDlg)
	enum { IDD = IDD_REGISTRYDEMO_DIALOG };
	CStatic	m_wndNewValueStatic;
	CEdit	m_wndNewValue;
	CStatic	m_wndText1Static;
	CEdit	m_wndText1;
	CButton	m_wndBool1;
	CEdit	m_wndResult;
	CStatic	m_wndFullRegistryItemStatic;
	CEdit	m_wndFullRegistryItem;
	CComboBox	m_wndActions;
	CComboBox	m_wndRegistryName;
	CString	m_sFullRegistryItem;
	CString	m_sKeyNames;
	CString	m_sMachineName;
	CString	m_sRegistryName;
	CString	m_sValueName;
	BOOL	m_bBool1;
	CString	m_sText1;
	CString	m_sNewValue;
	BOOL	m_bDepthFirst;
	BOOL	m_bIncludeSubkeys;
	BOOL	m_bIncludeValues;
	BOOL	m_bRecursive;
	BOOL	m_bReversedOrder;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegistryDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	COXRegistryItem m_registryItem;
	CString m_sCallResult;

	struct COXAction
		{
		BOOL m_bEnableFullRegistryItem;
		BOOL m_bEnableBool1;
		BOOL m_bEnableText1;
		BOOL m_bEnableNewValue;
		LPCTSTR m_pszText;
		};
	static COXAction m_actions[];



	// Generated message map functions
	//{{AFX_MSG(CRegistryDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCombine();
	afx_msg void OnSplit();
	afx_msg void OnDo();
	afx_msg void OnSelchangeActions();
	afx_msg void OnDefault();
	afx_msg void OnList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
