// HistoryComboDemoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHistoryComboDemoDlg dialog

#include "OXHistoryCombo.h"

class CHistoryComboDemoDlg : public CDialog
{
// Construction
public:
	CHistoryComboDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHistoryComboDemoDlg)
	enum { IDD = IDD_HISTORYCOMBODEMO_DIALOG };
	CSpinButtonCtrl	m_wndMaxCountSpin;
	COXHistoryCombo	m_wndHistoryCombo;
	int		m_nType;
	BOOL	m_bSmallGap;
	BOOL	m_bButton1;
	BOOL	m_bButton2;
	BOOL	m_bButton3;
	BOOL	m_bButton4;
	BOOL	m_bButton5;
	BOOL	m_bButton6;
	int		m_nMaxCount;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistoryComboDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHistoryComboDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMoveToolbar();
	afx_msg void OnStyleChange();
	afx_msg void OnSave();
	afx_msg void OnShow();
	afx_msg void OnRestore();
	afx_msg void OnChangeMaxCount();
	afx_msg void OnExtra();
	afx_msg void OnUpdateExtra(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
