
// DHtmlEditDemoDlg.h : Header

#if !defined(AFX_DHTMLEDITDEMODLG_H__AF3E29B6_2B28_46D0_9D37_74D6C9E41B4A__INCLUDED_)
#define AFX_DHTMLEDITDEMODLG_H__AF3E29B6_2B28_46D0_9D37_74D6C9E41B4A__INCLUDED_

#pragma once

#include "afxhtml.h"
#include "cHtmlEditor.h"
#include "afxwin.h"

// CDHtmlEditDemoDlg Dialogfeld
class CDHtmlEditDemoDlg : public CDialog
{
public:
	CDHtmlEditDemoDlg(CWnd* pParent = NULL);	// Standardkonstruktor

	//{{AFX_DATA(CDHtmlEditDemoDlg)
	enum { IDD = IDD_MAIN_DIALOG };
	CButton	mCtrl_Html5;
	CStatic	mCtrl_StaticUrl;
	CButton	mCtrl_GoForward;
	CButton	mCtrl_GoBack;
	CButton	mCtrl_Load;
	CEdit	mCtrl_EditUrl;
	CButton	mCtrl_Save;
	CButton	mCtrl_Help;
	CButton	mCtrl_BgText;
	CButton	mCtrl_BgBody;
	CButton	mCtrl_BgCell;
	CButton	mCtrl_Clear;
	CButton	mCtrl_ColLeft;
	CButton	mCtrl_ColRight;
	CButton	mCtrl_Combine;
	CButton	mCtrl_DeleteCol;
	CButton	mCtrl_DeleteRow;
	CButton	mCtrl_ForeColor;
	CButton	mCtrl_Hr;
	CButton	mCtrl_HrProp;
	CButton	mCtrl_Image;
	CButton	mCtrl_Link;
	CButton	mCtrl_NoBr;
	CButton	mCtrl_RemoveFormat;
	CButton	mCtrl_RowAbove;
	CButton	mCtrl_RowBelow;
	CButton	mCtrl_Split;
	CButton	mCtrl_Table;
	CButton	mCtrl_TableProp;
	CStatic	mCtrl_StaticEditor;
	CButton	mCtrl_CheckSource;
	CButton mCtrl_CheckDesign;
	CButton mCtrl_CheckBold;
	CButton mCtrl_CheckItalic;
	CButton mCtrl_CheckUnderline;
	CButton mCtrl_CheckLeftAlign;
	CButton mCtrl_CheckCenterAlign;
	CButton mCtrl_CheckRightAlign;
	CButton mCtrl_CheckOrderList;
	CButton mCtrl_CheckUnOrderList;
	CComboBox mCtrl_ComboFontName;
	CComboBox mCtrl_ComboFontSize;
	//}}AFX_DATA

protected:
	//{{AFX_VIRTUAL(CDHtmlEditDemoDlg)
	public:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	CHtmlEditor *pi_Editor;
	HICON m_hIcon;

	//{{AFX_MSG(CDHtmlEditDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnComboSelchangeComboFontname();
	afx_msg void OnSelchangeComboFontsize();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEditchangeComboFontsize();
	afx_msg void OnCloseupComboFontsize();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg LRESULT OnExitSizeMove(WPARAM wParam, LPARAM lParam);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnUserChangedFontsize();
	void SetHRproperties();
	void SetTableProperties();
	void OnWmCommand(WPARAM wParam);
	void OnUpdateUI(WPARAM wParam);

	// Do not declare these variables as static in CDHtmlEditDemoDlg::OnMsgUpdateUI()
	// Otherwise you get problems if you open this dialog twice !!
	#define _CheckBoxCount 10
	BOOL    mb_CheckStatus[_CheckBoxCount];

	#define _ComboBoxCount 2
	CString ms_ComboStatus[_ComboBoxCount];

	CRect   mk_OrgMsie;
	CRect   mk_OrgMain;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_DHTMLEDITDEMODLG_H__AF3E29B6_2B28_46D0_9D37_74D6C9E41B4A__INCLUDED_)
