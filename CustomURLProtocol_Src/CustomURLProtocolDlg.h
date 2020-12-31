// CustomURLProtocolDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "CustomURLProtocolApp.h"


// CCustomURLProtocolDlg dialog
class CCustomURLProtocolDlg : public CDialog
{
// Construction
public:
	CCustomURLProtocolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CUSTOMURLPROTOCOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ProtocolName;
	CEdit m_CompanyName;
	CEdit m_AppPath;
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedCancel();

	CustomURLProtocol m_CustomURLProtocol;
	CString CCustomURLProtocolDlg::CreateHtmlFile();
	void initializeParameter();
	afx_msg void OnBnClickedBtnDelete();
};
