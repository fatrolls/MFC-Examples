#pragma once
#include "afxwin.h"


// CDlgSpatilQuery 对话框
#include "mxobject1.h"
class CDlgSpatilQuery : public CDialog
{
	DECLARE_DYNAMIC(CDlgSpatilQuery)

public:
	CDlgSpatilQuery(IMXObjectPtr& pMap, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSpatilQuery();

// 对话框数据
	enum { IDD = IDD_DIALOG_SPATIALQUERY };
    IMXObjectPtr m_pMap;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmbSrcSet;//查询数据集
	CComboBox m_cmbOpSet;//操作数据集
	CComboBox m_cmbOpType;//查询方式
	double m_dis;//距离
	CComboBox m_cmbUnit;//单位
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboOpset();
	afx_msg void OnCbnSelchangeComboOptype();
};
