
// MainDlg.h : 头文件
//

#pragma once

#include "ImgWnd.h"



// CMainDlg 对话框
class CMainDlg : public CImgWnd
{
// 构造
public:
	CMainDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DLG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog();

// 实现
protected:
	// 生成的消息映射函数
	DECLARE_MESSAGE_MAP()
};
