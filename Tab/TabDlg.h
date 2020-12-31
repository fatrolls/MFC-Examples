// TabDlg.h : header file
//

#pragma once

#include "VSTab.h"
#include "BCMenu.h"
#include "tdlg.h"

#define VSTAB_ID	3001

// CTabDlg dialog
class CTabDlg : public CDialog
{
// Construction
public:
	CTabDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TAB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	BCMenu m_menu;
	CToolTipCtrl m_ToolTip;

	CVSTab m_vsTab;
	CImageList m_ImageList;

	BOOL bShowTips;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	afx_msg void OnVSTabLButtonDown(NMHDR* pNMHDR, LRESULT*);
	afx_msg void OnVSTabRButtonDown(NMHDR* pNMHDR, LRESULT*);
	afx_msg void OnVSTabMouseMove(NMHDR* pNMHDR, LRESULT*);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedDeleteItem();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
