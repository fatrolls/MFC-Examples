// WavTipSampleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWavTipSampleDlg dialog
#include "WavTipCtrl.h"

class CWavTipSampleDlg : public CDialog
{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CWavTipSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWavTipSampleDlg)
	enum { IDD = IDD_WAVTIPSAMPLE_DIALOG };
	CButton	m_checkTipSound;
	CComboBox	m_comboTipSound;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWavTipSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWavTipCtrl m_tooltip;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWavTipSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckTipsound();
	afx_msg void OnSelchangeComboTipsound();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
