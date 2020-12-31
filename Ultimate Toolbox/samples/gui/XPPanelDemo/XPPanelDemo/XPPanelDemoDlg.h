// XPPanelDemoDlg.h : header file
//

#pragma once

#include "OXTaskPanel.h"

// CXPPanelDemoDlg dialog
class CXPPanelDemoDlg : public CDialog
{
// Construction
public:
	CXPPanelDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_XPPanelDemo_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	COXTaskPanel m_TaskPanel;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
