// CalculatorCtrlDlg.h : header file
//

#pragma once

#include "OXCalculatorCtrl.h"

// CCalculatorCtrlDlg dialog
class CCalculatorCtrlDlg : public CDialog
{
// Construction
public:
	CCalculatorCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CALCULATORCTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	COXCalculatorPopup m_calc;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCalculator();
	double m_fValue;
};
