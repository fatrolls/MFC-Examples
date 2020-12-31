
// TestDlg.h : 头文件
//

#pragma once


// CTestDlg 对话框
class CTestDlg : public CSkinDialog
{
// 构造
public:
	CTestDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CTestDlg();

// 对话框数据
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	CSkinButton m_btnOK;
	CSkinButton m_btnCancel;
	CSkinCheckBox m_check;
	CSkinRadioBox m_radio1;
	CSkinRadioBox m_radio2;
	CSkinRadioButton m_tab1;
	CSkinRadioButton m_tab2;
	CSkinCheckButton m_checkbtn;
	CSkinComboBox m_combo;
	CSkinStatic m_staClick;
	CSkinStatic m_staSep;
	CSkinHyperLink m_link;
	CSkinEdit m_edit;
	CSkinTabCtrl m_tabctrl;
	CSkinSliderCtrl m_slider;
	CSkinProgressCtrl m_progress;
	CGifAnimation m_GifAnimation;

	CSkinToolTipHelper m_SkinToolTipHelper; // 提示

	CDUIManager* m_pDuiManager;
	bool m_bMouseHover;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnStnClickedStaClick();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	LRESULT OnDuiMessage(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};
