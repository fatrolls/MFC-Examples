// ChartATL_DemoApplicationDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "chartctrl1.h"


// CChartATL_DemoApplicationDlg dialog
class CChartATL_DemoApplicationDlg : public CDialog
{
// Construction
public:
	CChartATL_DemoApplicationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CHARTATL_DEMOAPPLICATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnEnChangeEdit1();

	int m_DispVal1;
	int m_DispVal2;
	int m_TargetVal1;
	int m_TargetVal2;
	int m_RBack;
	int m_GBack;
	int m_BBack;
	int m_RHori;
	int m_GHori;
	int m_BHori;
	int m_RVer;
	int m_GVer;
	int m_BVer;
	int m_RChart1;
	int m_GChart1;
	int m_BChart1;
	int m_RChart2;
	int m_GChart2;
	int m_BChart2;

public:
	CComboBox m_HoriStyle;
	CComboBox m_VerStyle;
	CComboBox m_Chart1Style;
	CComboBox m_Chart2Style;
	CChartctrl1 m_ChartCtrl;

	void SetBackColor();
	void SetHoriColor();
	void SetVerColor();
	void SetChart1Color();
	void SetChart2Color();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnEnKillfocusEdit5();
	afx_msg void OnEnKillfocusEdit6();
	afx_msg void OnEnKillfocusEdit7();
	afx_msg void OnEnKillfocusEdit8();
	afx_msg void OnEnKillfocusEdit9();
	afx_msg void OnEnKillfocusEdit10();
	afx_msg void OnEnKillfocusEdit11();
	afx_msg void OnEnKillfocusEdit12();
	afx_msg void OnEnKillfocusEdit13();
	afx_msg void OnEnKillfocusEdit14();
	afx_msg void OnEnKillfocusEdit15();
	afx_msg void OnEnKillfocusEdit16();
	afx_msg void OnEnKillfocusEdit17();
	afx_msg void OnEnKillfocusEdit18();
	afx_msg void OnEnKillfocusEdit19();
public:
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnCbnSelchangeCombo5();
public:
	afx_msg void OnEnChangeEdit11();
public:
	int m_RefreshSpeed;
public:
	afx_msg void OnEnKillfocusEdit20();
public:
	afx_msg void OnEnChangeEdit13();
};
