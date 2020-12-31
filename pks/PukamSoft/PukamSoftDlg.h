// PukamSoftDlg.h : header file
//

#if !defined(AFX_PUKAMSOFTDLG_H__8004AE55_8C2B_4AFD_879C_6B6698543C0D__INCLUDED_)
#define AFX_PUKAMSOFTDLG_H__8004AE55_8C2B_4AFD_879C_6B6698543C0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MainMenuDlg.h"
#include "CustomerInfoDlg.h"
#include "InwardTransactionsDlg.h"
#include "OutwardTransactionsDlg.h"
#include "BillingInfoDlg.h"
#include "ReportsDlg.h"
#include "TopBandDlg.h"
#include "LeftNavDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CPukamSoftDlg dialog

class CPukamSoftDlg : public CDialog
{
// Construction
public:
	void DestroyCurrentlyVisibleDialog();
	BOOL ShowReportsDlg();
	BOOL ShowBillingInfoDlg();
	BOOL ShowOutwardTransactionsDlg();
	BOOL ShowInwardTransactionsDlg();
	BOOL ShowCustomerInfoDlg();
	BOOL ShowMainMenuDlg();
	CPukamSoftDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPukamSoftDlg)
	enum { IDD = IDD_PUKAMSOFT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPukamSoftDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CLeftNavDlg* m_pLeftNavDlg;
	CTopBandDlg* m_pTopBandDlg;
	CReportsDlg* m_pReportsDlg;
	CBillingInfoDlg* m_pBillingInfoDlg;
	COutwardTransactionsDlg* m_pOutwardTransactionsDlg;
	CInwardTransactionsDlg* m_pInwardTransactionsDlg;
	CCustomerInfoDlg* m_pCustomerInfoDlg;
	CMainMenuDlg* m_pMainMenuDlg;
	CDialog** m_pCurrentlyVisibleDialog;
	HICON m_hIcon;
	BOOL m_bAnimating;
	BOOL m_bExitStatus;

	// Generated message map functions
	//{{AFX_MSG(CPukamSoftDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnActivateApp( BOOL bActive, HTASK hTask );
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetLeftNavState(UINT nID);
	void DestroyLeftNav();
	BOOL ShowLeftNav();
	UINT GetSubTitleID();
	void DestroyTopBand();
	BOOL ShowTopBand();
	void HideLeftNav();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUKAMSOFTDLG_H__8004AE55_8C2B_4AFD_879C_6B6698543C0D__INCLUDED_)
