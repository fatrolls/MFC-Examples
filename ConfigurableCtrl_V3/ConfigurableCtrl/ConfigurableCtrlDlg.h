
// ConfigurableCtrlDlg.h : header file
//

#pragma once
#include "ConfigListCtrl.h"

// CConfigurableCtrlDlg dialog
class CConfigurableCtrlDlg : public CDialogEx
{
// Construction
public:
	CConfigurableCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CONFIGURABLECTRL_DIALOG };

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
	CConfigListCtrl m_ListCtrl;
	afx_msg void OnMove(int x, int y);
private:
	void SetItemValue();
	BOOL	m_bKeyUp;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton m_EnDisAll;
	afx_msg void OnBnClickedButEndisall();
	CEdit m_EnDisCol;
	CEdit m_EnDisRow;
	afx_msg void OnBnClickedButEndiscell();
	CTabCtrl m_PropsTab;
	afx_msg void OnSelchangeTabprops(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_EnDisCell;
	CStatic m_EnDisRowStat;
	CStatic m_EnDisColStat;
private:
	void ViewEnDisTabItems(BOOL bVisible);
	void ViewRowColTabItems(BOOL bVisible);
	void ViewCtrlTabItems(BOOL bVisible);
	void ViewComboTabItems(BOOL bVisible);
	void ViewAlignmentTabItems(BOOL bVisible);
public:
	CButton m_EnDisGrp;
	CButton m_RC_AddColumn;
	CButton m_RC_AddRow;
	CEdit m_RC_HeaderName;
	CEdit m_RC_RowName;
	CEdit m_RC_HeaderPos;
	CEdit m_RC_HeaderWidth;
	CStatic m_RC_Sta_Head;
	CStatic m_RC_Sta_RowName;
	CStatic m_RC_Sta_HeadPos;
	CStatic m_RC_Sta_HeadWidth;
	afx_msg void OnBnClickedRowcolAddcol();
	CButton m_RC_RemoveColumn;
	CButton m_RC_RemoveRow;
	CEdit m_RC_Row;
	CStatic m_RC_Sta_Row;
	afx_msg void OnBnClickedRowcolRemcol();
	afx_msg void OnBnClickedRowcolAddrow();
	afx_msg void OnBnClickedRowcolRemrow();
	CEdit m_Ctrl_Column;
	CButton m_Ctrl_Add;
	CButton m_Ctrl_Remove;
	CEdit m_Ctrl_Row;
	CComboBox m_Ctrl_Type;
	CStatic m_Ctrl_Sta_Col;
	CStatic m_Ctrl_Sta_Row;
	CStatic m_Ctrl_Sta_Type;
	CEdit m_Ctrl_Default;
	CStatic m_Ctrl_Sta_Default;
	afx_msg void OnBnClickedCtrlAdd();
	afx_msg void OnBnClickedCtrlRem();
	afx_msg void OnBnClickedCbAdd();
	afx_msg void OnBnClickedCbSel();
	afx_msg void OnBnClickedCbRemove();
	CButton m_CB_Add;
	CEdit m_CB_Column;
	CEdit m_CB_Index;
	CButton m_CB_Remove;
	CEdit m_CB_Row;
	CButton m_CB_Select;
	CEdit m_CB_TextValue;
	CStatic m_CB_Sta_Index;
	CStatic m_CB_Sta_Row;
	CStatic m_CB_Sta_TextValue;
	CStatic m_CB_Sta_Column;
	afx_msg void OnBnClickedEvaEvaluate();
	CEdit m_Eval_Column;
	CEdit m_Eval_Row;
	CStatic m_Eval_Value;
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	CComboBox m_Align_Align;
	CButton m_Align_Button;
	CEdit m_Align_Column;
	CEdit m_Align_Row;
	CStatic m_Align_Sta_Align;
	CStatic m_Align_Sta_Row;
	CStatic m_Align_Sta_Column;
	afx_msg void OnBnClickedAlignBut();
};
