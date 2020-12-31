
// ReadWriteExcelDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

class CReadWriteExcelDlgAutoProxy;


// CReadWriteExcelDlg 对话框
class CReadWriteExcelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReadWriteExcelDlg);
	friend class CReadWriteExcelDlgAutoProxy;

// 构造
public:
	CReadWriteExcelDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CReadWriteExcelDlg();

// 对话框数据
	enum { IDD = IDD_READWRITEEXCEL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CReadWriteExcelDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
};
