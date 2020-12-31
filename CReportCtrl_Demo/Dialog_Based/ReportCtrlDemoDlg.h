// ReportCtrlDemoDlg.h : header file
//

#if !defined(AFX_REPORTCTRLDEMODLG_H__5A1856CE_2D95_4CEB_9299_88DFFC7493A6__INCLUDED_)
#define AFX_REPORTCTRLDEMODLG_H__5A1856CE_2D95_4CEB_9299_88DFFC7493A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CReportCtrlDemoDlg dialog

#include "reportctrl.h"
class CReportCtrlDemoDlg : public CDialog
{
// Construction
public:
	CReportCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CReportCtrlDemoDlg)
	enum { IDD = IDD_REPORTCTRLDEMO_DIALOG };
	CReportCtrl	m_wndList;
	BOOL	m_bGridLines;
	BOOL	m_bEditable;
	BOOL	m_bSortable;
	int		m_nChkStyle;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportCtrlDemoDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	DWORD GetStatesInput();
	static COleDateTime GenRandDate();
	static CString GenRandStr();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CReportCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAllowedit();
	afx_msg void OnSelectionAll();
	afx_msg void OnSelectionInvert();
	afx_msg void OnSelectionUnall();
	afx_msg void OnCheckboxAll();
	afx_msg void OnCheckboxInvert();
	afx_msg void OnCheckboxUnall();
	afx_msg void OnUpdateCheckboxAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCheckboxInvert(CCmdUI* pCmdUI);
	afx_msg void OnPositionUp();
	afx_msg void OnUpdatePositionUp(CCmdUI* pCmdUI);
	afx_msg void OnPositionDown();
	afx_msg void OnUpdatePositionDown(CCmdUI* pCmdUI);
	afx_msg void OnPositionTop();
	afx_msg void OnUpdatePositionTop(CCmdUI* pCmdUI);
	afx_msg void OnPositionBottom();
	afx_msg void OnUpdatePositionBottom(CCmdUI* pCmdUI);
	afx_msg void OnPositionSwap();
	afx_msg void OnUpdatePositionSwap(CCmdUI* pCmdUI);
	afx_msg void OnGridlines();
	afx_msg void OnAllowsort();
	afx_msg void OnSelect();
	afx_msg void OnCheck();
	afx_msg void OnDelete();
	afx_msg void OnPosition();
	afx_msg void OnChkStyle();
	//}}AFX_MSG
	afx_msg LRESULT OnCheckBox(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnItemSorted(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTCTRLDEMODLG_H__5A1856CE_2D95_4CEB_9299_88DFFC7493A6__INCLUDED_)
