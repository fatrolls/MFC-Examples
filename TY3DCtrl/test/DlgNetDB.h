#pragma once
#include "afxwin.h"


// CDlgNetDB 对话框

class CDlgNetDB : public CDialog
{
	DECLARE_DYNAMIC(CDlgNetDB)

public:
	CDlgNetDB(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgNetDB();

// 对话框数据
	enum { IDD = IDD_DIALOG_NETDATA };
    CString m_strServer;
    CString m_strDB;
    CString m_strUser;
    CString m_strPwd;
    CString m_strPort;
    CString m_strTable;
    CString m_strServType;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
 
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CComboBox m_cmbType;

	afx_msg void OnBnClickedTest();
	afx_msg void OnCbnSelchangeCmbType();
};
