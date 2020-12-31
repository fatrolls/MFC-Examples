
// DlgTestDlg.h : 头文件
//
#include "CDrawDlg.h"

#pragma once


// CDlgTestDlg 对话框
class CDlgTestDlg : public CDrawDlg
{
// 构造
public:
	CDlgTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DLGTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
