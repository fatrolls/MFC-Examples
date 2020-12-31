// TaskBarNotifierDemoDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "TaskbarNotifier.h"


// CTaskBarNotifierDemoDlg dialog
class CTaskBarNotifierDemoDlg : public CDialog
{
// Construction
public:
	CTaskBarNotifierDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TASKBARNOTIFIERDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CEdit m_wndEdit;
	CTaskbarNotifier m_wndTaskbarNotifier1;
	CTaskbarNotifier m_wndTaskbarNotifier2;
	CTaskbarNotifier m_wndTaskbarNotifier3;
	CTaskbarNotifier m_wndTaskbarNotifier4;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg LRESULT OnTaskbarNotifierClicked(WPARAM wParam,LPARAM lParam);
};
