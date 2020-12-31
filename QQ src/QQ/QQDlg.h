
// QQDlg.h : 头文件
//

#pragma once
#include ".\UI\Dialog\DlgBase.h"

// CQQDlg 对话框
class CQQDlg : public CDlgBase
{
// 构造
public:
	CQQDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QQ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

	virtual void InitUI(CRect rcClient);
	virtual void OnSize(CRect rcClient);

	afx_msg LRESULT OnMessageLoginList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageLoginMenu(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageButtomAccount(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageButtomStatus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageCheckPassWord(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageCheckAutoLogin(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageEditAccount(WPARAM wParam, LPARAM lParam);
};
