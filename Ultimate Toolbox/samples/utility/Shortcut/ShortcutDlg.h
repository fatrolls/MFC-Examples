// ShortcutDlg.h : header file
//

#include "resource.h"		// main symbols
#include "OXShortcut.h"

/////////////////////////////////////////////////////////////////////////////
// CShortcutDlg dialog

class CShortcutDlg : public CDialog
{
// Construction
public:
	CShortcutDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShortcutDlg)
	enum { IDD = IDD_SHORTCUT_DIALOG };
	CButton	m_ctlBool;
	CSpinButtonCtrl	m_ctlSpin;
	CHotKeyCtrl	m_ctlHotkey;
	CComboBox	m_ctlFn;
	BOOL	m_bThrowException;
	CString	m_sPathCreate;
	CString	m_sPathOpen;
	CString	m_sFN;
	BOOL	m_bParam;
	int		m_nParam;
	CString	m_sParam;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShortcutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateControls();
	void DemoOutput(LPCTSTR sFN);

	HICON		m_hIcon;
	COXShortcut m_scDemo;
	BOOL		m_bCreate;
	CString		m_sOutput;
	CString		m_sCurDir;

	// Generated message map functions
	//{{AFX_MSG(CShortcutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCreate();
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonFileOk();
	afx_msg void OnButtonFnOk();
	afx_msg void OnRadioCreate();
	afx_msg void OnRadioOpen();
	afx_msg void OnSelchangeComboFn();
	afx_msg void OnParamBool();
	afx_msg void OnSave();
	afx_msg void OnButtonParamString();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
